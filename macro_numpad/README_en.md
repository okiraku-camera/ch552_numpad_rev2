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

- Firmware sketch (this directory): `macro_numpad.ino`
- Web UI (repository root `html/`): `../html/macro_numpad.html`, `../html/macro_numpad.js`, `../html/style.css`
- Common CH552 keypad source files are provided by the `ch552_keyPad_Library` Arduino library.

## Usage

### Quick Start

1. Open `../html/macro_numpad.html` in a WebHID-capable browser.
2. Connect the device from "Connect to Keyboard".
3. Edit keymap/macros and write them to device.

### Detailed WebUI Guide

Detailed operation steps are documented here:

- Japanese: `../html/README.md`
- English: `../html/README_en.md`

## Build

This firmware can be built with:

- Visual Studio Code with the vscode-arduino extension
- arduino-cli
- CH55xDuino v0.25.
- ch552_keyPad_Library (arduino user libraries directory). 

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
