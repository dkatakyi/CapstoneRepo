***************************************************************************************************************************************
  * @file           : time_test.py
  * @brief          : Main program body
  * @author			    : ESE Group 2
  * @application	  : Room Occupancy Management System
  * @purpose		    : This program runs the file_save.py and server_send.py respectively as a subprocess 
******************************************************************************************************************************************

#This program runs the file_save.py and server_send.py  respectively as a subprocess 
#By Group 2 Capstone Project

#! /usr/bin/python3

#importing libraries
import subprocess
from time import sleep

y=(0.1)
subprocess.Popen(["python3",'/home/pi/Desktop/file_save.py']) # runs the file_save.py
sleep(y) # wait for 1ms
subprocess.Popen(["python3",'/home/pi/Desktop/server_send.py']) #runs the server_send.py
sleep(y)
