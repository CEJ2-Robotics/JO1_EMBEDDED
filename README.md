# John Deere Tractor Navigation System

Main project in collaboration with *John Deere* for the undergrad course "**Design of Advanced Embedded Systems**", which delves mainly into *Design and Analysis of Algorithms*, *Digital Signal Processing*, *Shared-Memory Architecture*, and *Communication Interfaces*.

<p align="center">
  <img src="https://github.com/user-attachments/assets/b687bccc-9adf-476f-9d3e-f90a392c2321" alt = "NUCLEO-H755ZI-Q" width="100" height="200"/>
</p>

## System Overview

The system implements a dual-mode navigation architecture on a tricycle-style vehicle platform, featuring differential rear-wheel drive and front-wheel steering. The design incorporates the NUCLEO-H755ZI-Q as the main processing unit, implementing two distinct navigation approaches:

### Vehicle Configuration

- **Drive System**: Rear differential drive with a single ESC-controlled motor
- **Steering System**: Front synchronized wheels controlled via servo motor
- **Actuator Control**: PWM-based control for both drive motor and steering servo
- **Sensor Integration**: Integrated encoder for odometry and MPU6050 IMU for orientation

### Implementation

#### Internal Navigation Mode

- **Orientation Tracking**
  
  - MPU6050 IMU with Kalman filter for noise reduction
  - Trapezoidal integration for yaw angle calculation
  
- **Distance Measurement**

  - Encoder-based odometry via CAN communication
  - Real-time distance calculation using wheel circumference and encoder CPR
  - Arduino Nano as secondary MCU for encoder reading

- **Control Strategy**
  
  - MATLAB-generated pure pursuit algorithm
  - Real-time state vector updates (x, y, yaw)
  - PWM-based motor speed and steering angle control

#### External Navigation Mode

- **Position Acquisition**
  
  - Vision-based marker tracking system
  - NRF24 wireless communication for coordinate transmission
  - Time-based proportional control for waypoint navigation
  - Acoustic feedback system for waypoint arrival
