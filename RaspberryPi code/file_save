#This program recieves sensor values from the STM32 nucleo serially and stores the data values in a csv file.
#By Group 2 Capstone Project

#importing libraries
import serial
import csv
from time import time, sleep, strftime

ser = serial.Serial ("/dev/ttyACM0", 115200) #Open port with baud rate
ser.flushInput()                             #clears the queue

#This program reads the sensors values sent through serial connection
#Decodes the string values and saves in into a csv file with the date and time
#This keeps the program running till it encounters an error
while True:
      try:
        ser_msg = ser.readline()
        sensor_values = ser_msg[0:len(ser_msg)-2].decode("utf-8")  #decode the string values 
        print(sensor_values)
        Temperature, Co2, Noise = sensor_values.split( )
        with open("another_test_data.csv","a") as f:
            writer = csv.writer(f,delimiter=",")
            writer.writerow([strftime("%Y-%m-%d"), strftime("%H:%M:%S"),Temperature, Co2, Noise])
      except:      #This prints an error message when the "try" section of the code does not work
         print("Error!")
         break
