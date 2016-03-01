#!/usr/bin/env python
# coding=utf-8



import os
import sys
import time
import subprocess



def test_write(directory, file_num):
    process = []
    filename_all = ""
    for i in range(file_num):
        filename = "%05d " % i
        filename = os.path.join(directory, filename)
        filename_all = filename_all + " " + filename
    if "-p" in sys.argv:
        if "-a" in sys.argv:
            cmd = "/home/code/github/source/c_language_summary/aio/aio_write_test %s " % (filename_all)
        else:
            cmd = "/home/code/github/source/c_language_summary/aio/write_test %s " % (filename_all)
        p1 = subprocess.Popen(cmd, shell=True, stderr=subprocess.STDOUT,
                                  stdout=subprocess.PIPE)
        process.append(p1)
    else:
        if "-a" in sys.argv:
            os.system("/home/code/github/source/c_language_summary/aio/aio_write_test %s " % (filename_all))
        else:
            os.system("/home/code/github/source/c_language_summary/aio/write_test %s " % (filename_all))
    for i in range(len(process)):
        process[i].wait()


def main():
    dir_in = "/mnt/"
    if  "-h" in sys.argv or "--help" in sys.argv:
        print """eg:    ./test_write.py 40  /mnt/test/ -p -a
        40 is file number
        /mnt/test/ is file directory
        -p is Parallel Write
        -a is asyn write
        """
        return 
    file_num = int(sys.argv[1])
    if len(sys.argv) >= 3:
        dir_in = sys.argv[2]
        
    start_time = time.time()
    print time.ctime()
    test_write(dir_in, file_num)
    print "time: ", time.time() - start_time
    print time.ctime()



if __name__ == "__main__":
    sys.exit(main())

