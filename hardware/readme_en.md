## Hardware

This project is a standard numeric keypad.

![Switch Layout](assets/numkeyPad.PNG)

The hardware was designed with KiCad 6.0. The repository includes the PCB and plate designs.

### Manufacturing Files

The repository includes the files used for fabrication.

- **PCB and plates**: Gerber files used for ordering.
- **Acrylic supports**: DXF files and PDF drawings (dimensioned) used for acrylic cutting.


### PCB
The PCB uses a **CH552G** microcontroller and a **4×5 switch matrix** supporting **17 MX-compatible switches** with **Kailh hotswap sockets**.

- PCB thickness: 1.6 mm  
- Screw holes: 3 mm (for M2 brass spacers)

### Plates and Supports

- **top_support**  
  3 mm acrylic plate between the PCB and the switch plate.  
  A 1 mm urethane gap tape is added on top to provide clearance for hotswap sockets.

- **top_plate**  
  1.5 mm plate for MX switches.  
  Switch openings are **13.9 mm square** to reduce switch wobble.  
  Supports **Cherry-style plate-mount stabilizers**.

- **bottom_support**  
  5 mm acrylic spacer between the PCB and bottom plate to provide clearance for the USB connector and switch sockets.

- **bottom_plate**  
  1.6 mm PCB used as the bottom plate.

## Assembly

The plates and supports are stacked and fixed with screws and spacers as shown below.

![Assembly](assets/ch552_numkeyPad_rev2.png)

