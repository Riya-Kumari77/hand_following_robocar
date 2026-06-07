# Hand Following Robot using Arduino

## Overview

This project implements a Hand Following Robot using an Arduino, two IR obstacle sensors, an HC-SR04 ultrasonic sensor, and an L298N motor driver.

The robot can:

* Follow a hand placed in front of it.
* Turn left when the hand moves to one side.
* Turn right when the hand moves to the other side.
* Move forward when the hand is far away.
* Move backward when the hand is too close.
* Stop when no hand is detected.

The system combines direction detection using IR sensors and distance measurement using an ultrasonic sensor.

---

## Hardware Required

| Component                 | Quantity  |
| ------------------------- | --------- |
| Arduino Uno/Nano          | 1         |
| L298N Motor Driver        | 1         |
| DC Gear Motors            | 2         |
| HC-SR04 Ultrasonic Sensor | 1         |
| IR Obstacle Sensors       | 2         |
| Robot Chassis             | 1         |
| Wheels                    | 2         |
| Battery Pack              | 1         |
| Jumper Wires              | As needed |

---

## Pin Connections

### Motor Driver

| Arduino Pin | Connection |
| ----------- | ---------- |
| D11         | ENA        |
| D4          | IN1        |
| D5          | IN2        |
| D10         | ENB        |
| D6          | IN3        |
| D7          | IN4        |

### Ultrasonic Sensor

| Arduino Pin | Connection |
| ----------- | ---------- |
| D2          | TRIG       |
| D3          | ECHO       |

### IR Sensors

| Arduino Pin | Connection      |
| ----------- | --------------- |
| D9          | Left IR Sensor  |
| A0          | Right IR Sensor |

---

## Working Principle

### Direction Detection

Two IR sensors determine the position of the hand:

| Left IR | Right IR | Action        |
| ------- | -------- | ------------- |
| LOW     | HIGH     | Turn Right    |
| HIGH    | LOW      | Turn Left     |
| LOW     | LOW      | Hand Centered |
| HIGH    | HIGH     | Stop          |

### Distance Control

When the hand is centered:

* Distance > 25 cm → Move Forward
* Distance < 15 cm → Move Backward
* Distance between 15–25 cm → Stop

This creates a comfortable tracking zone.

---

## Features

* Real-time hand following
* Stable IR sensor filtering
* Ultrasonic distance averaging
* Smooth directional control
* Adjustable follow distance
* Compatible with Arduino Uno and Nano

---

## Sensor Calibration

### IR Sensors

Each IR module contains a small potentiometer.

Adjust it until:

* The indicator LED turns ON when your hand is within the desired range.
* The indicator LED turns OFF when the hand moves away.

Recommended range:

15–30 cm

### Ultrasonic Sensor

Ensure:

* Sensor faces forward.
* No wires block the transmitter or receiver.
* Sensor is mounted securely.

---

## Adjustable Parameters

```cpp
const int MOTOR_SPEED = 255;

const int FORWARD_DISTANCE = 25;
const int BACKWARD_DISTANCE = 15;
```

### Increase Follow Distance

```cpp
const int FORWARD_DISTANCE = 35;
```

### Decrease Follow Distance

```cpp
const int FORWARD_DISTANCE = 20;
```

### Reduce Robot Speed

```cpp
const int MOTOR_SPEED = 180;
```

---

## Expected Behavior

1. Place your hand in front of the robot.
2. Move your hand left:

   * Robot turns left.
3. Move your hand right:

   * Robot turns right.
4. Move your hand away:

   * Robot moves forward.
5. Move your hand closer:

   * Robot moves backward.
6. Remove your hand:

   * Robot stops.

---

## Troubleshooting

### Robot Does Not Detect Hand

* Check IR sensor wiring.
* Adjust sensor potentiometers.
* Verify power supply voltage.

### Robot Responds Slowly

* Reduce ultrasonic timeout.
* Ensure battery is fully charged.
* Check for loose connections.

### Robot Moves in Wrong Direction

Swap:

```cpp
turnLeft();
```

and

```cpp
turnRight();
```

inside the main loop.

### Ultrasonic Reads Incorrect Distance

* Check TRIG and ECHO wiring.
* Ensure sensor faces forward.
* Avoid nearby obstacles during testing.

---

## Future Improvements

* Servo-based object scanning
* Human following mode
* Obstacle avoidance
* Bluetooth control
* Voice commands
* PID-based smooth tracking

---

## License

This project is open-source and may be modified for educational and personal robotics projects.
