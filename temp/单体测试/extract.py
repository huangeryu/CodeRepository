#!usr/bin/python



def openFile(filename,isExistAndReplace):
    rfr=open(filename)
    wfr=open(filename+"_extract.txt",'w+')
    lines=rfr.readlines()
    index=1
    for line in lines:
        ret=isExistAndReplace(line,index)
        if(ret):
            wfr.write(ret)
        index+=1
    rfr.close()
    wfr.close()

def isExistAndReplace(line,index):
    import re
    pattern1=re.compile(".*?((\[\d+\]){14})+")
    match1=pattern1.match(line)
    pattern2=re.compile('.*value\sis\s(\d+)\D+')
    match2=pattern2.match(line)
    pattern3=re.compile('.*(NotifyToCallBack\d+,\d+,\d+)')
    match3=pattern3.match(line)
    nline=str(index)+": "
    if match1:
        lists=re.sub('[\[\]]'," ",match1.group(1)).split()
        for num in lists:
            nline+=str(hex(int(num)))+" "
        nline+='\n'
        return nline
    elif match2:
        nline+=str(hex(int(match2.group(1))))+'\n'
        return nline
    elif match3:
        nline+=match3.group(1)+'\n'
        return nline
    return None
        
openFile('20180130.txt',isExistAndReplace)
