# macro_numpad

## Overview

macro_numpad is a programmable numeric keypad / macro keypad based on CH552G.
By default, it works as a standard numeric keypad, and you can customize keymaps and macros using the Web UI.

## Main Features

- Dual mode: numeric keypad or macro pad (controlled by switch 0)
- 2-layer keymap system (Num/Fn behavior)
- Up to 10 macros (m0-m9)
- Modifier combination support (Shift/Ctrl/Alt/Win)
- Persistent storage in NVM (built-in EEPROM, 128 bytes)

## Hardware Summary

- MCU: CH552G (USB 2.0 Full Speed)
- Matrix: 4x5 positions
- Implemented switches: 17
- Switch 0: mode control (Num/Fn)
- Multi-function LED:
  - Numeric mode: NumLock indicator
  - Macro pad mode: layer indicator

## Software Structure

- Firmware core: `macro_numpad/macro_numpad.ino`
- NVM/keymap: `macro_numpad/nvm_keymap.c`, `macro_numpad/nvm_keymap.h`
- USB/HID: `macro_numpad/USB_*.c`, `macro_numpad/USB_*.h`, `macro_numpad/hid_raw_request.c`
- Web UI: `html/macro_numpad.html`, `html/macro_numpad.js`, `html/style.css`

## Usage

### Quick Start

1. Open `html/macro_numpad.html` in a WebHID-capable browser.
2. Connect the device from "Connect to Keyboard".
3. Edit keymap/macros and write them to device.

### Detailed WebUI Guide

Detailed operation steps are documented here:

- Japanese: `html/README.md`
- English: `html/README_en.md`

## Build

This firmware can be built with:

- Arduino IDE 1.8.19
- Visual Studio Code with the vscode-arduino extension

Both environments require CH55xDuino v0.25.

### Board Configuration

In the board configuration menu, select:

- USB Settings: `USER CODE w/ 148B USB ram`

This option allocates the USB RAM required for HID endpoints.

## Technical Notes

- Keymap and macros are saved separately.
- Macro transmission is aborted immediately when any key is pressed during macro playback.
- Starting bootloader may disconnect the device temporarily.

## License

This project is released under the MIT License.
