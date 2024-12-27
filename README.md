# John Deere Tractor Navigation System

<p align="justify">Main project in collaboration with <b>John Deere</b> for the undergrad course "<b>Design of Advanced Embedded Systems</b>", which delves mainly into <i>Design and Analysis of Algorithms</i>, <i>Digital Signal Processing</i>, <i>Shared-Memory Architecture</i>, and <i>Communication Interfaces</i>.</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/ba551d48-1bdb-434d-bece-047efd1e78cd" alt = "NUCLEO-H745ZI-Q" width="200" height="200"/>
</p>

## Prototype Description

<p align="justify">Farmers face several challenges, including labor shortages, the need for precision in planting and harvesting, and time-consuming manual operations. Traditional tractors require constant monitoring and human input, increasing operational costs and the likelihood of errors in large-scale farming. There is a growing demand for <i>autonomous systems</i> that can handle repetitive tasks with accuracy and reliability.<br>&nbsp;<br>The proposed solution consists of a <i>tractor prototype</i> that features navigation via waypoints powered by technologies such as wireless communication, camera-based positioning and angle detection, inertial measurement generations and encoder distance calculations.</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/1b476210-97d0-48a6-9460-5cdd5ff1afbb" alt = "Prototype"/>
</p>

## System Architecture

<p align="justify">The system employs a <i>NUCLEO-H745ZI-Q</i> development board to control the tricycle-style vehicle platform with synchronized front steering and differential rear drive. Motion control is achieved through dual PWM channels: <i>TIM13</i> handles servo-based steering with angle-to-pulse width mapping, while <i>TIM14</i> manages ESC motor control with bidirectional speed control through pulse width modulation.</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/d0c4bedb-3c1d-49ac-880f-9bfe21f4aac4" alt = "Vehicle"/>
</p>

### Internal Navigation Mode

<p align="justify">The internal navigation system fuses data from two sensor streams: a wheel-mounted <i>encoder</i> for distance measurement and an <i>MPU6050 IMU</i> (via the <i>I2C4</i> peripheral) for orientation tracking. The encoder data is preprocessed by an Arduino Nano and transmitted via <i>CAN</i> to the main MCU (received by means of the <i>FDCAN1</i> peripheral), where raw counts are converted to distance using a counts-per-revolution calibration.</p>

<p align="justify">Orientation tracking implements a signal processing pipeline:</p>

<ol align="justify">
  <li>Raw IMU measurements undergo offset compensation and scaling.</li>
  <li>A <i>Kalman filter</i> processes each axis to reduce sensor noise.</li>
  <li>Gyroscope integration uses trapezoidal approximation for yaw calculation.</li>
  <li>Continuous angle normalization maintains orientation within 0-360 degrees.</li>
</ol>

<p align="justify">The system employs a <i>MATLAB-generated pure pursuit controller</i> operating at <b>LINEAR_VELOCITY</b> with a <b>LOOKAHEAD_DISTANCE</b> parameter. Real-time state estimation combines encoder distance and IMU yaw to maintain accurate position tracking in Cartesian coordinates, enabling smooth trajectory following in a snake-like pattern.</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/6027e72e-6981-4a71-afb9-62f8e4f565f3" alt = "Internal Navigation Mode Test"/>
</p>

### External Navigation Mode

<p align="justify">Position data comes from the <i>John Deere Global Positioning System</i>, which tracks a vehicle-mounted <i>marker</i>. Coordinates are transmitted through an <i>nRF24L01</i> wireless link (using the <i>SPI5</i> peripheral) between a secondary board (<i>NUCLEO-F103RB</i>) and the vehicle. To accommodate the relatively slow GPS update rate, the system implements a time-based proportional control strategy:</p>

<p align="justify">The vehicle advances at a fixed <b>SPEED</b> while the controller calculates movement durations proportional to the distance from target. Between movements, the system pauses for <b>STOP_TIME</b> milliseconds to ensure stable position readings. Waypoint arrival triggers an audio alert through a PWM-driven buzzer using <i>TIM1</i>.</p>

<p align="justify">Both modes utilize <i>USART3</i> for debugging and system monitoring, providing real-time state information at 115200 baud.</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/52570b92-e074-4024-b223-eaa62c346fd2" alt = "External Navigation Mode Test"/>
</p>

## Vehicle Schematic Diagram & Component Overview

<p align="justify">
  For detailed information on the electronics design, including the KiCad PCB layout, please refer to the 
  <a href="https://github.com/CEJ2-Robotics/JO1_Electronics" style="color: #3B8927;">dedicated electronics repository</a>
</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/768281bf-2760-4cc2-8c32-98f283492d16" alt = "Schematic Diagram"/>
</p>

| Item                                         | Quantity      |
| ---------------------------------------------| ------------- |
| Servo Steering Robot Kit                     | 1             |
| NUCLEO-H745ZI-Q                              | 1             |
| Arduino Nano                                 | 1             |
| nRF24L01 2.4GHz Wireless Module              | 1             |
| MPU6050 IMU                                  | 1             |
| GM 25-370 12V DC Motor with Encoder          | 1             |
| MCP2515 CAN Controller with SPI Interface    | 1             |
| CJMCU-1051 TJA1051 CAN Transceiver           | 1             |
| Tower Pro MG996R Servo Motor                 | 1             |
| 30A ESC (Electronic Speed Controller)        | 1             |
| HW-508 Passive Buzzer Module                 | 1             |
| 330 Ohm Resistor                             | 1             |
| Li-Po Battery 3.7V 2000mAh                   | 2             |
| Li-Po 2S Battery 7.4V 1500mAh                | 1             |
| LM2596 Step Down Regulator 25W 3A            | 2             |
