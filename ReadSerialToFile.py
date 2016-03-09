#!/usr/bin/python
import time
import serial

# Open serial connection: check ports! 
# Ports are usually 0 and 1 after reboot
try:
  ser1 = serial.Serial('/dev/ttyUSB0', 115200)
  ser1.timeout = None

  fo = open("tsys01Data.csv", "w")
  # The main serial data reading loop
except Exception as e:
  print(e)
  
  exit();
  


while True:
  
  # Read line from serial
  data_in1 = ser1.readline()
  
  
  string = data_in1.decode("utf-8")
    

  if string == "end":
    break
    
  # Write CSV to file
  fo.write(string)
  print(string)

fo.close();
