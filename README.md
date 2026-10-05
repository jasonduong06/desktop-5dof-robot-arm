# Desktop 5-DOF Robotic Arm

A low-cost, five-degree-of-freedom desktop robotic arm that simulates real-world manufacturing tasks such as picking up, moving, and placing small parts. Built as a hands-on, affordable platform for learning mechatronics, robotics, and automation.

![Arm render](docs/arm_render.png)

## Status
Mechanical design complete in SolidWorks. [Prototype build in progress / update this as you go.]

## Features
- 5 degrees of freedom, driven by 5 servo motors (9g class)
- Gripper end effector for picking up small, lightweight items
- Manual mode: potentiometers control each joint directly
- Automatic mode: pre-loaded action sequences for pick-and-place demos
- Target payload of about 20 g (small items such as chips or light foam blocks)

## Repository contents
- `cad/` - SolidWorks and STEP files for the arm and gripper
- `electronics/` - wiring diagram
- `code/` - controller code
- `docs/` - photos and renders
- `BOM.md` (or `BOM.csv`) - bill of materials with costs and links

## Hardware
- Controller: [Arduino Nano / ESP32 / etc.]
- Servos: [model, e.g. SG90 9g] x [number]
- Power: [5V, X A supply]
- Structure: [3D printed in PLA / other]

## How it works
1. In manual mode, each potentiometer sets the angle of one joint.
2. A switch changes to automatic mode, where the arm runs a stored sequence of positions (for example, pick a part from point A and place it at point B).

## Build it yourself
1. Print or fabricate the parts from the `cad/` folder.
2. Wire the electronics following the diagram in `electronics/`.
3. Upload the code from `code/` to the controller.
4. Assemble and calibrate each joint.

## License
- Code: MIT
- Hardware design files: [CERN-OHL-P, or MIT if you only added one license]

## Author
Jason Duong - Mechatronic Systems Engineering, Western University
