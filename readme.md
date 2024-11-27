# Simple Temperature and Humidity Sensing Project (C Language Version)

This project demonstrates how to use the **DHT22 temperature and humidity sensor** with the **W55RP20 EVB board**, a one-chip solution combining the RP2040 and W5500. The implementation is done entirely in **C language**, providing a lightweight and efficient way to interact with the hardware.

## Features
- Measures temperature and humidity using the DHT22 sensor.
- Outputs data via the serial console.
- Handles errors such as sensor timeouts and checksum mismatches.
- Easy to set up with minimal wiring.

## Pin Mapping
| DHT22 Pin      | W55RP20 EVB Pin |
|----------------|-----------------|
| **Data**       | **GP28**        |
| **VCC (Power)**| **3.3V**        |
| **GND**        | **GND**         |

## Requirements
- W55RP20 EVB Board
- DHT22 Sensor Module
- 3 jumper wires
- USB cable for serial communication

## Usage
1. Connect the DHT22 sensor to the W55RP20 EVB board as per the pin mapping and enter boot mode.
2. Flash the provided `W55RP20_DHT22_Example.uf2` file to the board using your preferred development environment.
3. Open a serial terminal (e.g., PuTTY, Arduino Serial Monitor) at the appropriate baud rate.
4. Observe the temperature and humidity readings output every 2 seconds.

## Code Overview
The project uses a DHT library in C to interface with the sensor. Key functions include:
- `dht_start_measurement()`: Initiates a measurement.
- `dht_finish_measurement_blocking()`: Retrieves the results of the measurement.
- Outputs the results in both Celsius and Fahrenheit with humidity percentage.

### Example Output

25.6 C (78.1 F), 55.2% humidity 26.1 C (79.0 F), 53.7% humidity DHT sensor not responding. Please check your wiring.

## Notes
- Ensure the data pin has a proper pull-up resistor (enabled in the code).
- This example is designed specifically for **C language**, providing an efficient and low-level approach to working with the W55RP20 and DHT22.

## License
This project is open-source and free to use under the MIT License.