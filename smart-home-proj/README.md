About

The project is a demo for a smart home system. it has sensors and controllers than can communicate through TCP protocol. 
The program will simulate the control of four different devices: Alarm, Fire, Light, Temperature.
these are derived from a virtual class called "Agent".
Agent can be added dynamically. each device can subscribe to sensor compatible.
the Agents loaded from two files - "sensor_config" , "controller_config".
As the system needs to handle multi tasks at once, it use multi-threded. each event pass to eventRouter that can handle it on time.