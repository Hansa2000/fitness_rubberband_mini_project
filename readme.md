# Fitness Rubber Band Monitoring System

## Overview
The **Fitness Rubber Band Monitoring System** is an innovative wearable device designed to track and analyze resistance band exercises. Using **strain gauge sensors** integrated into the rubber band, the system detects resistance variations during stretching, providing **real-time feedback on workout intensity**. The data is processed using a **Wheatstone bridge circuit and an Arduino-based microcontroller**, ensuring accurate monitoring and performance analysis.

## Features
- **Real-time resistance tracking** using strain gauge sensors.
- **Wheatstone bridge circuit** for precise resistance variation measurement.
- **Differential amplifier** for signal amplification.
- **Automatic calibration system (software)** to correct initial state errors.
- **OLED display output** for live workout data.
- **Battery-powered for portability.**

## Hardware Components
- **Strain Gauge Sensors** (2-wire & 3-wire configurations tested)
- **LMP7702MA Precision Op-Amp** (for signal amplification)
- **2N7000 MOSFET** (for switching operations)
- **Arduino Microcontroller** (to process data and display results)
- **LCD Display** (to visualize resistance levels)
- **Wheatstone Bridge Circuit** (for accurate strain measurement)
- **Power Supply** (5V battery pack or USB power source)

## Circuit Design
The system consists of the following key components:
1. **Wheatstone Bridge Circuit:** Measures the strain-induced resistance variation.
2. **Differential Amplifier:** Amplifies the small resistance changes detected.
3. **Subtractor Circuit:** Compensates for the initial resistance errors.
4. **Integrator Feedback Circuit:** Maintains signal accuracy over time.
5. **Microcontroller (Arduino):** Reads sensor data, applies necessary corrections, and displays results.
6. **LCD Display:** Shows real-time resistance values and alerts users.

## Software Requirements
- **Arduino IDE** (for programming the microcontroller)
- **Open-source libraries** (for LCD interfacing and signal processing)
- **Python (optional)** for post-processing data visualization

## Installation & Setup
1. **Assemble the circuit** following the schematic provided in the report.
2. **Connect the strain gauge to the Wheatstone bridge.**
3. **Ensure the microcontroller is programmed** with the provided Arduino script.
4. **Power the system using a 5V battery pack or USB power.**
5. **Start the system using the activation switch.**


## Results & Performance
- **Successfully detects strain variations** with high accuracy.
- **Comparison of simulation and prototype results** shows consistency in data.
- **Usable for strength training and rehabilitation monitoring.**

## Future Improvements
- **Connectivity** for mobile app integration.
- **Machine learning-based workout recommendations.**
- **Compact PCB version for commercial use.**

## Contributors
- **M.M.H.N.B. Marasinghe** (University of Moratuwa)
- **G.D.K. Dewagiri** (University of Moratuwa)

## License
This project is open-source and can be freely used for research and educational purposes.
