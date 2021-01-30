import serial
from time import sleep

ser = serial.Serial ("/dev/ttyS0", 9600)    #Open port with baud rate

ser.write("Hello!!! Welcome to Chia's Command Line")
ser.write("\n\r")
ser.write("COM>")

while True:
    if ser.read() == chr(127):
        ser.write("\b")
        ser.write(" ")
        ser.write("\b")
    if ser.read() == "\n":
        ser.write("\n\r")
        ser.write("COM>")
        
    else:  
        received_data = ser.read()              #read serial port
        sleep(0.03)
        data_left = ser.inWaiting()             #check for remaining byte
        received_data += ser.read(data_left)
        print (received_data)                   #print received data
        ser.write(received_data)                #transmit data serially 
