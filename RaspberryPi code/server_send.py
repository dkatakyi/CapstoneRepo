
import ftplib
import io
import os
from time import sleep

#The csv file is sent to the FTP account to be displayed on the website.
sleep(60) #initial set-up time
while True:
    sleep(60) #sent to the FTP every 1 min
    session = ftplib.FTP('192.168.1.67', 'ftpi', 'capstone')
    fp = open('/home/pi/Desktop/test/0b1.csv','rb')
    remotepath = '/home/ftpi/0b1.csv'
    bufsize = 1024
    session.storbinary('STOR %s' % os.path.basename("0b1.csv"), fp, 1024)
    fp.close()
    session.quit()

