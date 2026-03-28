# CH552 Numeric Keypad revision 2

This repository contains hardware design information for building a simple USB numeric keypad using the CH552G microcontroller, along with software information for keyboard firmware that runs on this hardware.

![ch5552_numpad_rev2](hardware/assets/chh552_numpad_rev2.jpg)

## Hardware
The hardware directory includes a complete set of files for **KiCad 6.0**, Gerber files used for manufacturing, and DXF/PDF files for acrylic cutting.

## Software
This section contains software written for the hardware above, including a simple USB HID keypad and macro keypad firmware. It is provided as Arduino sketches using **ch55xDuino** (v0.25) as the core package.

### Simple Numeric Keypad
Stored in the **simple_numPad** directory. The sketch is largely the same as the previously published [ch552_numkeyPad](https://github.com/okiraku-camera/ch552_numkeyPad).    

### Macro Keypad Implementation Using WebHID (macro_numpad)
Among the keypad's 17 keys, this allows you to assign any Usage ID via **WebHID** to 16 keys excluding NumLock.

You can also configure special codes such as media controls and mouse operations. In addition, multiple Usage IDs can be registered to a single key, allowing one action to trigger multiple key inputs.

This was written partly as a WebHID sample implementation.


### Web App for Macro Keypad Configuration (HTML and JavaScript)
This web application communicates with the macro keypad over WebHID and reads/writes codes between the device and the virtual keyboard shown in the browser.


## License
This project contains hardware and software components.

Copyright (c) Takeshi Higasa, okiraku-camera.tokyo

See [LICENSE](./LICENSE)



