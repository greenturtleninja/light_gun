### Guide

Connect IR sensor to Ardunio
Green - SCL
Yellow - SDA

Red - 5v
Black - Ground

Use the ardino IDE - to open the ir-sensor.ino, connect via usb and make a note of the COM port

Download and install Processing (https://processing.org/)

Open the ir_blob.pde (JAVA ish, not entirely JAVA)

Upload the ir-sensor.ino in Arduino IDE and check the serial monitor for 8 sets of digits comma separated 
(switch to baud rate 19200 if gibberish coming through)

Once happy, close the serial monitor and run the ir_blob.pde in Processing. That should be it