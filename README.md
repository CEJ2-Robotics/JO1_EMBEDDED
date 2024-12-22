# John Deere Tractor Navigation System

Main project in collaboration with *John Deere* for the undergrad course "**Design of Advanced Embedded Systems**", which delves mainly into *Design and Analysis of Algorithms*, *Digital Signal Processing*, *Shared-Memory Architecture*, and *Communication Interfaces*.

<p align="center">
  <img src="https://github.com/user-attachments/assets/ba551d48-1bdb-434d-bece-047efd1e78cd" alt = "NUCLEO-H745ZI-Q" width="240" height="240"/>
</p>

## System Architecture

The system employs a *NUCLEO-H745ZI-Q* development board to control a tricycle-style vehicle platform with synchronized front steering and differential rear drive. Motion control is achieved through dual PWM channels: TIM13 handles servo-based steering with angle-to-pulse width mapping, while TIM14 manages ESC motor control with bidirectional speed control through pulse width modulation.

### Internal Navigation Mode

The internal navigation system fuses data from two sensor streams: a wheel-mounted *encoder* for distance measurement and an *MPU6050 IMU* for orientation tracking. The encoder data is preprocessed by an Arduino Nano and transmitted via *FDCAN* to the main MCU, where raw counts are converted to distance using a counts-per-revolution calibration. 

Orientation tracking implements a signal processing pipeline:

1. Raw IMU measurements undergo offset compensation and scaling
2. A Kalman filter processes each axis to reduce sensor noise
3. Gyroscope integration uses trapezoidal approximation for yaw calculation
4. Continuous angle normalization maintains orientation within 0-360 degrees

The system employs a *MATLAB-generated pure pursuit controller* operating at LINEAR_VELOCITY with a LOOKAHEAD_DISTANCE parameter. Real-time state estimation combines encoder distance and IMU yaw to maintain accurate position tracking in Cartesian coordinates, enabling smooth trajectory following in a snake-like pattern.

### External Navigation Mode

Position data comes from the *John Deere Global Positioning System*, which tracks a vehicle-mounted marker. Coordinates are transmitted through an *NRF24* wireless link between a secondary board (*NUCLEO-F103RB*) and the vehicle. To accommodate the relatively slow GPS update rate, the system implements a time-based proportional control strategy:

The vehicle advances at a fixed SPEED while the controller calculates movement durations proportional to the distance from target. Between movements, the system pauses for STOP_TIME milliseconds to ensure stable position readings. Waypoint arrival triggers an audio alert through a PWM-driven buzzer using TIM1.

Both modes utilize UART3 for debugging and system monitoring, providing real-time state information at 115200 baud. The entire system operates under a FreeRTOS task scheduler, ensuring consistent timing for control loop execution.
