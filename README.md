# Pico-Echo-Test
Test program to pass UART communications through to USB serial and vise-versa

## Instructions:
- Send bytes from esp01 to pico over uart
- Plug cable into pico and computer
- Monitor the serial port (use device manager to see which new port shows up when its plugged in)
  - Feel free to use coolterm or putty to monitor the data
  - Make sure baud rate agrees for both esp01 code and this code, as well as the monitor youre using
  
## Wiring (following the pin labels at the bottom):

***PICO  --> ESP-01s***

 3v3   --> 3v3
 
 GND   --> GND
 
 GP0   --> RX
 
 GP1   --> TX
 

