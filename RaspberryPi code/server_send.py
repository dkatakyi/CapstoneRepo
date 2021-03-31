
import ftplib
import io
import os
from time import sleep

sleep(60)
while True:
    sleep(25)
    session = ftplib.FTP('192.168.1.67', 'ftpi', 'capstone')
    fp = open('/home/pi/Desktop/test/0b1.csv','rb')
    remotepath = '/home/ftpi/0b1.csv'
    bufsize = 1024
    session.storbinary('STOR %s' % os.path.basename("0b1.csv"), fp, 1024)
    fp.close()
    session.quit()

