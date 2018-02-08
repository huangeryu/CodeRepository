#!/usr/bin/python
#encoding:utf-8
from __future__ import print_function
import xlrd
import re

class annotation:
    def __init__(self,cmdStr,value):
        self.cmdStr=cmdStr
        self.value=value
    def __str__(self):
        return str(self.cmdStr+" "+hex(self.value))
class Data:
    def __init__(self,idframe):
        self.parent=idframe
        self.data=[0x00,0x00,0x00,0x00,0x00,0x00,0x0,0x00,0x000]
        self.body=None
        self.value=0
    def calculateFcc(self):
        self.data[-1]=(sum(self.data)+self.parent.pFcc)%256

class IDFrame:
    def __init__(self,unite):
        self.lec=0x0C
        self.opc=0x10
        self.canid_h=int('0x0'+unite.id[0],16)
        self.canid_l=int('0x'+unite.id[1:],16)
        self.dlc=int(unite.dlc)
        self.pFcc=self.lec+self.opc+self.canid_h+self.canid_l+self.dlc
        self.bodyFrame=self.generateDataFrame(unite.bodyList)

    def __setDatabit(self,body,value):
        bodyData=Data(self)
        bodyData.body=body
        bodyData.value=value
        i=body.validDataPos-1
#        print("i=%d,bitlen=%d"%(i,body.bitPos),end=" ")
        temp=value<<body.bitPos
        while(temp):
            tmod=temp%256
            if(i<0):print("fate error;exit()")
            bodyData.data[i]|=tmod
#            print("0x%02x"%bodyData.data[i])
            i-=1
            temp=temp//256
        bodyData.calculateFcc()
        return bodyData
    def generateDataFrame(self,bodyList):
        ret1=[]
        ret2=[]
        for body in bodyList:
            if(not len(body.disc.DisList)):
                bodyData=self.__setDatabit(body,2**body.bitLen-1)
                ret1.append(bodyData.data)
                ret2.append(annotation(bodyData.body.cmdStr,bodyData.value))
            else:
                for m in body.disc.DisList:
                    if(not len(m[0])):
                        bodyData=self.__setDatabit(body,2**body.bitLen-1)
                        ret1.append(bodyData.data)
                        ret2.append(annotation(bodyData.body.cmdStr,bodyData.value))
                    else:
                        for num in range(m[0][0],m[0][1]):
                            bodyData=self.__setDatabit(body,num)
                            ret1.append(bodyData.data)
                            ret2.append(annotation(bodyData.body.cmdStr,bodyData.value))
        return ret1,ret2

class Discrible:
    __pattern=re.compile( u'^【?(((\d+)(～\d+)?)|[ABCDEF])([bh])?】?:?(.*)' )
    def __init__(self,discStr=''):
        self.DisList=self.parseStr(discStr)
        
    def parseStr(self,discStr):
        ret=[]
        if(discStr==''):
            return ret
        temp=discStr.strip().split('\n')
        for istr in temp:
            match=Discrible.__pattern.match(istr)
            if(match):
                base=match.group(5)
                if(base=='b'):
                    base=2
                elif base=='h':
                    base=16
                elif not base:
                    base=10                    
                if(not match.group(4)):
                    g1=int(match.group(1),base)
                    tl=[[g1,g1+1],match.group(6)]
                else:
                    g3=int(match.group(3),base)
                    g4=int(match.group(4)[1:],base)
                    tl=[[g3,g4+1],match.group(6)]
                ret.append(tl)
            elif len(temp)==1:
                tl=[[],istr]
                ret.append(tl)
        return ret
        
class Body:
    def __init__(self,startPos='0.0',bitLen=0,cmdStr='',disc=None):
        self.validDataPos=int(str(startPos)[0])
        self.bitPos=int(str(startPos)[2])
        self.bitLen=int(bitLen)
        self.cmdStr=cmdStr
        self.disc=disc
    
class Unite:
    def __init__(self,index=0,id='',dlc=0):
        self.index=index
        self.id=id
        self.dlc=dlc
        self.bodyList=[]

def getDataInformation(fileName):
    data=xlrd.open_workbook(fileName)
    table=data.sheets()[0] #获取第一个工作表
    changed=False
    index=0
    ret=[]
    for i in range(table.nrows):
        currentIndex=table.cell(i,2).value
        if(isinstance(currentIndex,(float))):
            index=int(currentIndex)#获取索引
            changed=True
        else:
            changed=False
        bitl=table.cell(i,9).value
        if(not changed and not isinstance(bitl,float) ):continue
        if(changed):
            informaFrame=Unite(index)
            tid=table.cell(i,6).value
            if(isinstance(tid,float)):
                tid=str(int(tid))
            elif(isinstance(tid,str)):
                tid=tid.strip()
            informaFrame.id=tid#获取id
#            if(len(informaFrame.id)!=3):print "id'len not equal 3!";exit()
            informaFrame.dlc=table.cell(i,7).value#获取DLC
            ret.append(informaFrame)
        else:
            if(not len(ret)):print("code logic error! exit()");exit()
            body=Body(table.cell(i,8).value,table.cell(i,9).value,table.cell(i,11).value)#获取开始位置，长度，描述
            body.disc=Discrible(table.cell(i,25).value)
#            print('i=%d,validDataPos=%d,bitPos=%d,bitLen=%d'%(i,body.validDataPos,body.bitPos,body.bitLen))
            ret[-1].bodyList.append(body)
    return ret


def generateDate(unites):
    ret=[]
    for unite in unites:
        ret.append(IDFrame(unite))
    return ret
def idFrameToMat(idFrame):
    ret=[]
    temp=[idFrame.lec,idFrame.opc,idFrame.canid_h,idFrame.canid_l,idFrame.dlc]
    for data in idFrame.bodyFrame[0]:
        ret.append(temp+data)
    return ret

def startup(fileName):
    dataInformation=getDataInformation(fileName)
    idFrames=generateDate(dataInformation)
    ret1=None
    ret2=None
    for idFrame in idFrames:
        if(ret1):
            ret1+=idFrameToMat(idFrame)
            ret2+=idFrame.bodyFrame[1]
        else:
            ret1=idFrameToMat(idFrame)
            ret2=idFrame.bodyFrame[1]
    return ret1,ret2

def printOut(ret):
    fr=open("testdata.txt",'w')
    print('{',file=fr)
    for num in range(len(ret[0])):
        print('    {',end=' ',file=fr)
        for data in ret[0][num]:
            print('0x%02x,'%(data),sep=',',end=' ',file=fr)
        print('},//'+ret[1][num],file=fr)
    print('}',file=fr)
    fr.close()
class ValueAndIndex:
    def __init__(self,value,index):
        self.value=value
        self.list=[index]
#ret=map<istr,map<value,ValueAndIndex>>
def prepare(ilist):
    ret=dict()
    for index in range(len(ilist)):
        key=ilist[index].cmdStr
        value=ilist[index].value
        if ret.has_key(key):
            imap=ret[key]
            if(imap.has_key(value)):
                imap[value].list.append(index)
            else:
                imap[value]=ValueAndIndex(value,index)
        else:
            ret[key]={value:ValueAndIndex(value,index)}
    return ret

def getValue1(istr):
    pattern=re.compile(u'((\d,){0,}(\d))|(=>(\d+).*)')
    match=pattern.match(istr)
    if(match):
        if(match.group(1)):
            substr=match.group(1)
            subl=substr.replace(u',','')
            return int(subl,2)
        elif(match.group(5)):
            return float('inf')
    else:
        print('istr=%s'%istr)
        return None

def getValue2(istr):
    pattern=re.compile(u'((not\s?(\d,)+)?(\d))|(<(\d+).*)')
    match=pattern.match(istr)
    if match:
        if(match.group(2)):
            return 0
        elif match.group(4):
            return int(match.group(4))
        else:
            return 0
    else:
        return float('-inf')

def openAndExtractData(fileName):
    ret=[]
    data=xlrd.open_workbook(fileName)
    table=data.sheets()[1]
    for i in range(22,84):
        istr=table.cell(i,8).value
        if(istr==u''):continue
        vstr1=unicode(table.cell(i,10).value)
        value1=getValue1(vstr1)
        if(value1==None):print('%s line %d has a error!'%(fileName,i));continue
        vstr2=unicode(table.cell(i,13).value)
        value2=getValue2(vstr2)
        ret.append((istr,value1,value2))
    return ret


def extractUIDate(ret,filterList):
    fr=open("filteredData.txt",'w')
    print('{',file=fr)
    rmap=prepare(ret[1])
    for tpl in filterList:
        istr=tpl[0]
        value1=tpl[1]
        value2=tpl[2]
        if(rmap.has_key(istr)):
            imap=rmap[istr]
            if value1==float('inf'):
                value1=max(imap.keys())
            if(imap.has_key(value1)):
                ilist=imap[value1].list
                for index in ilist:
                    print('    {',end=' ',file=fr)
                    for data in ret[0][index]:
                        print('0x%02x,'%(data),sep=',',end=' ',file=fr)
                    print('},//'+str(ret[1][index]),file=fr)
            else:
                print("%s value1=%02x is missing!"%(istr,value1))
            if(value2==float('-inf')):continue
            if(value2==0):
                value2=min(imap.keys())
            if(imap.has_key(value2)):
                ilist=imap[value2].list
                for index in ilist:
                    print('    {',end=' ',file=fr)
                    for data in ret[0][index]:
                        print('0x%02x,'%(data),sep=',',end=' ',file=fr)
                    print('},//'+str(ret[1][index]),file=fr)
            else:
                print("%s value2=%02x is missing!"%(istr,value2))
        else:
            print("fate: %s is missing"%istr)
    print('}',file=fr)
    fr.close()

def generateUIData(ret,fileName):
    filterList=openAndExtractData(fileName)
    extractUIDate(ret,filterList)

def test():
    ret=startup('//home/huangyu/Desktop/Can/CanData描述.xls')
    generateUIData(ret,'/home/huangyu/Desktop/CAN連携注意喚起.xlsx')

#
def getHashValue(ilist):
    ret=[]
    return ret
#使用md5算法产生一个hash值,构成一个map{hashvalue,index}
def getHashMap(ilist):
    ret={}
    for index in range(len(ilist)):
        hashValue=getHashValue(ilist[index])
        ret[hashValue]=index
    return ret


