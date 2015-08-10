#!/usr/bin/env python
# coding=utf-8

#print_xattr.py

import xattr
import os
import sys
from struct import *


def make_clean(directory):
    makefile = os.path.join(directory, "Makefile")
    if os.path.exists(makefile):
        os.chdir(directory)
        os.system("make clean")
        os.system("rm -rf core.*")

def make_clean_all(directory):
    if os.path.isdir(directory):
        make_clean(directory)
        file_list = os.listdir(directory)
        file_list.sort()
        for filename in file_list:
            if filename[0] == '.':
                continue
            filename = os.path.join(directory, filename)
            if os.path.isdir(filename):
                make_clean_all(filename)


def main():
    #from dbgp.client import brk
    #brk(host="191.168.45.215", port=50803)
    make_clean_all(os.getcwd())




if __name__ == "__main__":
    sys.exit(main())

