#!/usr/bin/env python
# coding=utf-8

#encrypt.py

import os
import sys
import time
import subprocess



def make():
    file_list = os.listdir("./")
    for filename in file_list:
        if ".c" in filename:
            target = filename[0:filename.index(".")]
            cmd = "gcc -g -O0 -lcstl %s -o %s" %(filename, target)
            #os.system(cmd)
            p = subprocess.Popen(cmd, shell=True,
                stdout=subprocess.PIPE, close_fds=True)
def clean():
    os.system("rm -rf *.o")
    file_delete = ""
    file_list = os.listdir("./")
    for filename in file_list:
        if ".c" not in filename and ".py" not in filename:
            file_delete = file_delete + " " + filename
    cmd = "rm -rf %s" % file_delete
    p = subprocess.Popen(cmd, shell=True,
                stdout=subprocess.PIPE, close_fds=True)

def main():
    #from dbgp.client import brk
    #brk(host="191.168.45.215", port=50803)
    now = time.time()
    if len(sys.argv) == 2 and sys.argv[1] == "clean":
        clean()
    else:
        make()
    print "the time is %f" % (time.time() - now)




if __name__ == "__main__":
    sys.exit(main())

