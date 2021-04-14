# @file           : server_send.py
# @brief          : Main program body
# @author			: ESE Group 2
# @application	: Room Occupancy Management System
# @purpose		: This program sends the csv file to the website via FTP

#!/usr/bin/python3

#importing libaries 
import ftplib
import io
import os
from time import sleep

sleep(60) #initial set-up time
while True:
    sleep(60) #sent to the website every 1 min
    session = ftplib.FTP('192.168.1.67', 'ftpi', 'capstone')
    fp = open('/home/pi/Desktop/test/0b1.csv','rb')
    remotepath = '/home/ftpi/0b1.csv'
    bufsize = 1024
    session.storbinary('STOR %s' % os.path.basename("0b1.csv"), fp, 1024)
    fp.close()
    session.quit()

