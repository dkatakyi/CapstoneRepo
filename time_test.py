#! /usr/bin/python3
import subprocess
from time import sleep

y=(0.1)
subprocess.Popen(["python3",'/home/pi/Desktop/file_save.py'])
sleep(y)
subprocess.Popen(["python3",'/home/pi/Desktop/server_send.py'])
sleep(y)