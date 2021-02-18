from ftplib import  FTP
import io
import os
from time import sleep

sleep(15)
with FTP('192.168.0.174') as ftp:   #depends on the location of the pi
    ftp.login('ftpi', 'capstone')
    fp = open('another_test_data.csv','rb')
    remotepath = '/home/ftpi/another_test_data.csv'
    bufsize = 1024
    ftp.storbinary('STOR %s' % os.path.basename("another_test_data.csv"), fp, 1024)
    fp.close()
    ftp.quit()
