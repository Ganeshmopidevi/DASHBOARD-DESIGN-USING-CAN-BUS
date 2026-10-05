# DASHBOARD-DESIGN-USING-CAN-BUS

- CAN based multi‑node fuel &amp; indicator system using LPC2129, LCD, ADC, DS18B20 and fuel gauge.
- This project implements a multi-node automotive-style dashboard system using the LPC2129 microcontroller and CAN protocol. The system displays engine temperature and fuel percentage on an LCD, and controls left and right indicator behavior through separate CAN-connected nodes. 
- The project is divided into three functional nodes: a Main Node for display and coordination, a Fuel Node for ADC-based fuel measurement, and an Indicator Node for LED-based indicator control. This architecture demonstrates distributed embedded system design using CAN communication between nodes.
  
## Block Diagram
<p align="center">
  <img src=" " alt="Block Diagram" width="500">
</p>

## Main node:
- The Main Node reads engine temperature from the DS18B20 sensor, receives fuel percentage from the Fuel Node over CAN, and updates the LCD with temperature, fuel level, and indicator status. The code in MainNode.c initializes CAN, LCD, and external interrupts, reads temperature using ReadTemp(), receives CAN frames, and graphically displays fuel level blocks and indicator symbols on the LCD.

## Fuel Node:
- The Fuel Node reads the fuel gauge value using the on-chip ADC and converts the ADC reading into a percentage. In FuelNode.c, the fuel percentage is packed into a CAN frame with message ID 2 and transmitted continuously to the Main Node. 

## Indicator Node:
- The Indicator Node waits for CAN messages from the Main Node and controls LED patterns for left and right indicator operation. In IndicatorNode.c, CAN frames with ID 1 are used to switch between left indicator mode, right indicator mode, and off mode.
