# Venue_Decibel_Meter

## Overview
Designed and fabricated an Arduino Uno IoT shield featuring an analog microphone front end, OPA344 signal conditioning, and ESP8266 wireless connectivity. Developed embedded firmware to acquire ADC data, estimate sound pressure levels, and stream real-time measurements to the Adafruit IO dashboard.

## Specifications
<table>
  <thead>
    <tr>
      <th>Parameter</th>
      <th>Specification</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>Microcontroller</strong></td>
      <td>Arduino Uno</td>
    </tr>
    <tr>
      <td><strong>Wireless Module</strong></td>
      <td>ESP8266-01S Wi-Fi</td>
    </tr>
    <tr>
      <td><strong>Analog Front End</strong></td>
      <td>OPA344 rail-to-rail operational amplifier</td>
    </tr>
    <tr>
      <td><strong>Sensor</strong></td>
      <td>CMA-4544PF-W electret condenser microphone</td>
    </tr>
    <tr>
      <td><strong>PCB</strong></td>
      <td>Custom two-layer KiCad Arduino Uno shield with ground plane</td>
    </tr>
    <tr>
      <td><strong>Signal Processing</strong></td>
      <td>10-bit ADC sampling, peak-to-peak voltage calculation, RMS conversion, and dB estimation</td>
    </tr>
    <tr>
      <td><strong>Cloud Platform</strong></td>
      <td>Adafruit IO for real-time data visualization</td>
    </tr>
    <tr>
      <td><strong>Indicator</strong></td>
      <td>On-board LED for programmable sound threshold warning</td>
    </tr>
  </tbody>
</table>

## Block Diagram
<img width="520" height="450" alt="block diagram" src="Block_Diagram/Block_Diagram1.png" />

## Control Strategy
The microphone captures ambient audio and the OPA344 amplifies the AC signal. The Arduino continuously samples the amplified waveform through its ADC over a fixed time window. Peak-to-peak voltage is converted to RMS voltage and then estimated in decibels using firmware. The calculated dB value is transmitted via the ESP8266 to Adafruit IO for real-time visualization, while a warning LED indicates when the sound level exceeds a preset threshold.

<img width="520" height="450" alt="schematic" src="Schematics/Full_Schematic.png" />

## PCB Design
Integrated the microphone, OPA344 analog front end, ESP8266-01S, status LEDs, and supporting passive components into a compact 2-layer shield form factor.

<img width="520" height="450" alt="PCB" src="Rendering/Overview.png" />

## Measured Results
- Successfully acquired microphone signals and converted them to digital data using the Arduino ADC.
- Estimated sound levels of approximately 45–49 dB during testing.
- Demonstrated reliable wireless transmission of real-time measurements to the Adafruit IO dashboard.
- Verified continuous cloud monitoring with live graphing and remote reset functionality via the ESP8266 Wi-Fi interface.
<img width="500" height="600" alt="Board" src="Reports/Capture.png" />
Capture of sound pulse into microphone

## Version History

### Version 1.0
- Identified an ADC routing error during hardware bring-up and implemented a jumper-wire rework to restore analog signal acquisition.
- Successfully validated full system functionality following hardware modification, including sensor acquisition and IoT communication.
<img width="500" height="600" alt="Board" src="Images/Top_View.png" />
