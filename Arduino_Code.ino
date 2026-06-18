#include "Arduino.h"
#include <SoftwareSerial.h>

#define reset_pin 9
#define tx_pin 10
#define rx_pin 11

SoftwareSerial espSerial(rx_pin, tx_pin);

String IO_USERNAME = "REDACTED FOR SECURITY"; 
String IO_KEY = "REDACTED FOR SECURITY"; 
String WIFI_SSID = "REDACTED FOR SECURITY"; 
String WIFI_PASS = "REDACTED FOR SECURITY";

String response;
String resp;

const int sensorpin = A0;

String espData(String command, const long timeout, boolean debug);

void setup() {

  Serial.begin(115200);
  espSerial.begin(9600);

  pinMode(sensorpin, INPUT);

  pinMode(reset_pin, OUTPUT);
  digitalWrite(reset_pin, LOW);
  delay(500);
  digitalWrite(reset_pin, HIGH);

  Serial.println("\n\Booting...");
  Serial.println("setting up Adafruit IO");

  response = espData("get_macaddr", 2000, true);
  response = espData("get_version", 2000, true);
  response = espData("wifi_ssid=" + WIFI_SSID, 4000, true);
  response = espData("wifi_pass=" + WIFI_PASS, 4000, false);
  response = espData("io_key=" + IO_KEY, 4000, false);
  response = espData("io_user=" + IO_USERNAME, 4000, true);

  response = espData("setup_io", 30000, true);

  if (response.indexOf("connected") < 0) {
    Serial.println("\nAdafruit IO Connection Failed");
    while (1);
  }

  response = espData("setup_pubfeed=1,CPEG298pub", 8000, true);
  response = espData("setup_subfeed=3,reset_button", 8000, true);
  response = espData("setup_time,-5", 8000, true);

  Serial.println("Setup Complete");

  response = espData("get_name=1", 1000, true);
  response = espData("get_name=3", 1000, true);
  response = espData("get_date", 1000, true);
  response = espData("get_time", 1000, true);

  response = espData("send_data=3,0", 4000, true);
}



void loop() {

  int minValue = 1023;
  int maxValue = 0;

  unsigned long startTime = millis();

  while (millis() - startTime < 100) {
    int reading = analogRead(sensorpin);

    if (reading < minValue) minValue = reading;
    if (reading > maxValue) maxValue = reading;
  }

  int peakToPeak = maxValue - minValue;

  float voltagePP = peakToPeak * (5.0 / 1023.0);
  float voltageRMS = voltagePP / (2.0 * 1.414);

  float dB = ( 20.0 * log10(voltageRMS / 1.0)) * -1;  
  // chatgpt used to generate math 'generate a arduino code to take input AC voltage and convert to dB'

  Serial.print("AC ADC value is: ");
  Serial.println(peakToPeak);

  Serial.print("AC voltage is: ");
  Serial.println(voltagePP, 4);

  Serial.print("dB value is: ");
  Serial.println(dB, 2);

  response = espData("send_data=1," + String(dB, 2), 4000, false);

  delay(5000);
}

String espData(String command, const long timeout, boolean debug) {

  char c = 0;
  response = "";

  espSerial.println(command);

  long int time = millis();

  while ((time + timeout) > millis()) {

    while (espSerial.available()) {
      c = espSerial.read();
      response += c;
    }

    if ((c == '\n') && (command != "setup_io")) break;
  }

  response.trim();

  if (debug) {
    Serial.println("Resp: " + response);
  }

  return response;
}