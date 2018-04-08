#!/usr/bin/pyhton2.7
from __future__ import print_function
import os
def ispcyfile(fr,pattern='.pyc'):
    if fr.endswith(pattern):
        return True
    else:
		return False

def deletefile(currentDir):
    for fr in os.listdir(currentDir):
        path=os.path.join(currentDir,fr)
        if(os.path.isfile(path)):
            if(ispcyfile(fr) or isELFFile(path)):
                os.remove(path)
                print('delete %s'%path)
        elif(not ispcyfile(fr,'.git')):
            deletefile(path)

def isELFFile(fileName):
    with open(fileName,'rb') as fr:
        first_4=bytearray(fr.read(4))
        return tuple(first_4)==(0x7f,0x45,0x4c,0x46) or tuple(first_4)==(0xca,0xfe,0xba,0xbe)

deletefile('./')
