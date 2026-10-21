# Humidity Relay Controller

Arduino sketch that reads temperature and humidity from a DHT11 sensor and switches a relay based on the humidity level. It also prints the temperature (°F), humidity, and a raw analog reading from A0 to the Serial Monitor every 2 seconds.

## Wiring

| Part               | Arduino |
|--------------------|---------|
| DHT11 data pin     | D2      |
| Relay input (IN)   | D4      |
| Voltage input      | A0      |

Power the DHT11 and relay module from 5V and GND. Keep the voltage on A0 between 0 and 5V.

## Requirements

- Arduino IDE
- DHT sensor library (install via **Sketch > Include Library > Manage Libraries**, search "DHT sensor library")

## Usage

1. Wire up the parts.
2. Install the DHT library.
3. Upload the sketch.
4. Open the Serial Monitor at 9600 baud.

## How It Works

- Humidity **below 35%**: relay pin goes `LOW`
- Humidity **above 35%**: relay pin goes `HIGH`
- The A0 value is printed as a raw reading (0 to 1023), not converted to volts.
- If the DHT11 can't be read, the sketch prints an error and tries again.

To change the humidity threshold, edit the `35` in the two `if` statements.
