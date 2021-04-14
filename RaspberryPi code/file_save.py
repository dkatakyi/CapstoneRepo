# @file           : file_save.py
# @brief          : Main program body
# @author			      : ESE Group 2
# @application	   : Room Occupancy Management System
# @purpose		      : This program recieves sensor values from the STM32 nucleo serially and stores the data values in a csv file.


#!/usr/bin/python3

#importing libraries
import serial
import csv
from time import time, sleep, strftime
import os

#creates a device number as well as a csv file to pu the sensor values in it and creates the columns in the csv file to store the sensor values in it.
Device = 0b0001 
filename = "/home/pi/Desktop/" + str(bin(Device)) + ".csv"  
ser = serial.Serial ("/dev/ttyACM0", 115200) #Open port with baud rate
ser.reset_input_buffer()
ser.reset_output_buffer()                           
file = open(filename, "a")
file.truncate(0)
file.write("Date,Time,Temperature(Celsius),CO2(ppm),Noise Level(dBa),Room,Device No\n")
file.close()
ser.flush()

#This program reads the sensors values sent through serial connection
#Decodes the string values and saves in into a csv file with the date and time
while True:
    ser_msg = ser.read_until()
    sensor_values = ser_msg[0:len(ser_msg)-2].decode("utf-8")  #decode the string values  
    print(sensor_values)
    Temperature, Co2, Noise, Room = sensor_values.split( )
    with open(filename,"a") as f:
        writer = csv.writer(f,delimiter=",")
        writer.writerow([strftime("%Y-%m-%d"), strftime("%H:%M:%S"), Temperature, Co2, Noise, Room, str(Device)])
        f.close()
    os.system('cp /home/pi/Desktop/0b1.csv /home/pi/Desktop/test/0b1.csv')

