import csv
import ftplib
from io import BytesIO
from gpiozero import CPUTemperature
from time import sleep, strftime, time

flo = BytesIO()
session = ftplib.FTP('192.168.0.46', 'pi', 'capstone')
n = 0
cpu=CPUTemperature()
with open ("/home/pi/Desktop/cpu_data.csv" , "a") as log:
    while n < 20:
        temperature = cpu.temperature
        log.write("{0},{1}\n".format(strftime("%Y-%m-%d %H:%M:%S"),str(temperature)))
        sleep(1)
        n = n + 1
    

session.storbinary('STOR cpu_data.csv', log)
session.quit()