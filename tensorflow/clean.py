#!/usr/bin/python
#encoding:utf-8
from __future__ import print_function
with open('./test','rb') as fr:
    print(tuple(bytearray(fr.read(4)))==(0x7f,0x45,0x4c,0x46))

