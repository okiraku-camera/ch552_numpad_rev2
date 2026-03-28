# Simple Numeric Keypad Firmware for CH552G

This directory provides a **simple numeric keypad firmware** for the **CH552G** microcontroller. The firmware is intended primarily for **hardware bring-up and USB HID verification**. It enumerates as a **standard USB HID keyboard** and sends key events by scanning 4x5 key-switch matrix. This implementation is based on the `USBHIDKeyboard.c` example included in **CH55xDuino**.

---

## Features

- Minimal **USB HID keyboard implementation**
- Designed for **CH552G hardware bring-up**
- Simple **Matrix-based numeric keypad**
- Based on the **CH55xDuino USBHIDKeyboard example**
- Easy to build with **Arduino IDE or VS Code**

---

## Build Environment

The firmware can be built using:

- **Arduino IDE 1.8.19**
- **Visual Studio Code** with the *vscode-arduino* extension

Both require **CH55xDuino v0.25**.

### Board Configuration

In the board configuration menu, select:

- **USB Settings:** `USER CODE w/ 148B USB ram`

This option allocates the USB RAM required for HID endpoints.

---

## Hardware

The circuit designs and various plate files for this numeric keypad are located in the `hardware` directory. All hardware design work was conducted using **KiCad 6.0**.

---

## License

Copyright (c) 2023 Takeshi Higasa, okiraku-camera.tokyo
Released under the **MIT License**.
