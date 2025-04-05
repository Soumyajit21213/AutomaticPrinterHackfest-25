# AutomaticPrinterHackfest-25

## Overview

**AutomaticPrinterHackfest-25** is a project developed during Hackfest 2025, focusing on automating printing tasks. The project encompasses hardware design, firmware, and a web interface to streamline printing operations.

## Features

- **Automated Printing**: Enables seamless printing with minimal user intervention.
- **Web Interface**: Provides a user-friendly web platform for managing print jobs.
- **Wireless Connectivity**: Supports Wi-Fi connectivity for remote printing.

## Repository Structure

- `src/main/`: Contains the main source code for the project.
- `website/`: Includes the web interface files.
- `AutomaticPrinter.apk`: Android application for managing the printer.
- `Gerber_Hackfest-Printer_PCB_Hackfest-Printer_2_2025-04-05.zip`: PCB design files for the printer hardware.
- `Wifi_Test.ino`: Arduino sketch for testing Wi-Fi connectivity.
- `controlFlow.mat` & `controlFlowFlowchart.slx`: MATLAB files representing the control flow of the system.

## Installation

1. **Hardware Setup**: Assemble the printer hardware as per the provided PCB design files.
2. **Firmware Upload**: Use the `Wifi_Test.ino` sketch to upload the firmware to the printer's microcontroller.
3. **Web Interface Deployment**: Host the contents of the `website/` directory on a local or remote server.
4. **Android App Installation**: Install the `AutomaticPrinter.apk` on your Android device for mobile management.

## Usage

1. **Connect to Printer**: Ensure the printer is powered on and connected to the same Wi-Fi network as your device.
2. **Access Web Interface**: Navigate to the hosted web interface to manage print jobs.
3. **Use Android App**: Open the AutomaticPrinter app to control the printer from your mobile device.

## Contributing

We welcome contributions! Please fork the repository and submit a pull request with your enhancements.

## License

This project is licensed under the Apache-2.0 License. See the `LICENSE` file for more details.

---

*Note: Ensure that all necessary dependencies and libraries are installed before deploying the system.*
