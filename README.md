# Desktop 5-DOF Robotic Arm

A low-cost, five-degree-of-freedom desktop robotic arm that simulates real-world manufacturing tasks such as picking up, moving, and placing small parts. Built as a hands-on, affordable platform for learning mechatronics, robotics, and automation.


## Status
Mechanical design complete in SolidWorks. 

## Features
- 5 degrees of freedom, driven by 5 servo motors
- Gripper end effector for picking up small, lightweight items
- Manual mode: potentiometers control each joint directly
- Automatic mode: pre-loaded action sequences for pick-and-place demos
- Target payload of about 20 g (small items such as chips or light foam blocks)

## Repository contents
- [CAD / STEP file](cad/robot_arm_assembly.step) - SolidWorks and STEP files for the arm and gripper
<!-- - `electronics/` - wiring diagram -->
<!-- - `code/` - controller code -->
- [Arm Render](docs/arm_render.png) - photos and renders
- [BOM](docs/BOM.xlsx) - bill of materials with costs and links
- `LICENSE` - MIT license

## Hardware
- Controller: Arduino Nano
- Servos: SG90 9g x 5
- Power: 5V 
- Structure: 3D printed in PLA

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
- Hardware design files: MIT

## Author
Jason Duong - Mechatronic Systems Engineering, Western University
