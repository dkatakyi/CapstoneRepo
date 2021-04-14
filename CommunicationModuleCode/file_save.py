#This program recieves sensor values from the STM32 nucleo serially and stores the data values in a csv file.
#By Group 2 Capstone Project

#!/usr/bin/python3

#importing libraries
import serial
import csv
from time import time, sleep, strftime
import os

Device = 0b0001
filename = str(bin(Device)) + ".csv"

ser = serial.Serial ("/dev/tty.usbmodem14103", 115200) #Open port with baud rate
ser.reset_input_buffer()
ser.reset_output_buffer()
#ser.flushInput()                             #clears the queue
file = open(filename, "a")
file.truncate(0)
file.write("Date,Time,Temperature,CO2,Noise Level,Room,Device No\n")
file.close()
# ser.write('x'.encode('utf-8'))
ser.flush()

#This program reads the sensors values sent through serial connection
#Decodes the string values and saves in into a csv file with the date and time
#This keeps the program running till it encounters an error
while True:
#      try:
    ser_msg = ser.read_until()
    sensor_values = ser_msg[0:len(ser_msg)-2].decode("utf-8")  #decode the string values
        #senso_values = ser_msg[0:len(ser_msg)-2]
        
    print(sensor_values)
    Temperature, Co2, Noise, Room = sensor_values.split( )
    with open(filename,"a") as f:
        writer = csv.writer(f,delimiter=",")
        writer.writerow([strftime("%Y-%m-%d"), strftime("%H:%M:%S"), Temperature, Co2, Noise, Room, str(Device)])
        f.close()
    os.system('cp 0b1.csv test')
#      except:      #This prints an error message when the "try" section of the code does not work
#         print("Error!")
         #break
