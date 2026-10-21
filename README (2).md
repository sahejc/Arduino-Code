# Arduino Projects

A collection of small Arduino sketches.

## Projects

1. [Ultrasonic Distance Sensor](#1-ultrasonic-distance-sensor)
2. [Humidity Relay Controller](#2-humidity-relay-controller)
3. [Pull-Up Counter](#3-pull-up-counter)
4. [Proximity Alarm](#4-proximity-alarm)
5. [Arduino Voltmeter](#5-arduino-voltmeter)

For all projects, upload the sketch with the Arduino IDE and open the Serial Monitor at **9600 baud**.

---

## 1. Ultrasonic Distance Sensor

Reads distance from an HC-SR04 ultrasonic sensor and prints it in cm. It averages 5 readings and prints `Out of range / no echo` if nothing is detected. Works from about 2 cm to 400 cm.

| HC-SR04 | Arduino |
|---------|---------|
| VCC     | 5V      |
| GND     | GND     |
| TRIG    | D5      |
| ECHO    | D6      |

---

## 2. Humidity Relay Controller

Reads temperature and humidity from a DHT11 sensor and switches a relay based on humidity. It prints temperature (°F), humidity, and a raw A0 reading every 2 seconds.

| Part             | Arduino |
|------------------|---------|
| DHT11 data pin   | D2      |
| Relay input (IN) | D4      |
| Voltage input    | A0      |

**Requires:** the DHT sensor library (Sketch > Include Library > Manage Libraries).

- Humidity below 35%: relay pin goes `LOW`
- Humidity above 35%: relay pin goes `HIGH`
- The A0 value is a raw reading (0 to 1023), not volts. Keep it between 0 and 5V.

To change the threshold, edit the `35` in the two `if` statements.

---

## 3. Pull-Up Counter

Counts pull-ups using an HC-SR04 sensor and shows the distance and count on a 16x2 LCD. Two buttons adjust the count manually.

| Part               | Arduino           |
|--------------------|-------------------|
| HC-SR04 TRIG       | D5                |
| HC-SR04 ECHO       | D6                |
| LCD RS             | D7                |
| LCD EN             | D8                |
| LCD D4, D5, D6, D7 | D9, D10, D11, D12 |
| "Up" button        | A0                |
| "Down" button      | A1                |

Wire the buttons so they pull the pin to GND when pressed.

- Distance is measured in inches.
- When the distance drops below **39 inches**, one pull-up is counted. It only counts again after you move back out to 39 inches or more.
- Pressing the up or down button adds or subtracts 5 from the count.

To change the trigger distance, edit the `39` in the `if(distance<39)` line.

---

## 4. Proximity Alarm

Uses an HC-SR04 sensor to detect how close an object is. A green LED means far, and a red LED with a buzzer beep means close.

| Part         | Arduino |
|--------------|---------|
| HC-SR04 TRIG | D6      |
| HC-SR04 ECHO | D5      |
| Green LED    | D8      |
| Red LED      | D7      |
| Buzzer       | D11     |

Use a resistor in series with each LED. The sketch includes the `IRremote` library but doesn't use it, so either install it or delete the `#include <IRremote.h>` line.

| Echo time  | Meaning         | Result                                  |
|------------|-----------------|-----------------------------------------|
| Above 1000 | Object is far   | Green LED on, red LED off               |
| Below 1000 | Object is close | Red LED on, green LED off, buzzer beeps |

1000 microseconds is roughly 17 cm (about 7 inches). To change the trigger distance, edit the `1000` in the `if` statements.

---

## 5. Arduino Voltmeter

Reads a voltage on pin A1 and prints it in volts every half second.

| Source      | Arduino |
|-------------|---------|
| Voltage (+) | A1      |
| Ground (-)  | GND     |

Only measure voltages between **0 and 5V**. Anything higher can damage the board.

```
voltage = reading / 1023 * 5
```
