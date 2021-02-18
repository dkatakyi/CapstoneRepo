import subprocess
from time import sleep

y=(0.1)
subprocess.Popen(["python",'file_save.py'])
sleep(y)
subprocess.Popen(["python",'ftptest.py'])
