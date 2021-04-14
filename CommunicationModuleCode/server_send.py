
import ftplib
import io
import os
from time import sleep

while True:
    sleep(10)
    session = ftplib.FTP('10.0.0.253', 'ftpi', 'capstone')
    fp = open('test/0b1.csv','rb')
    remotepath = '/home/ftpi/0b1.csv'
    bufsize = 1024
    session.storbinary('STOR %s' % os.path.basename("0b1.csv"), fp, 1024)
    fp.close()
    session.quit()

