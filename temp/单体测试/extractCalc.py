#!/usr/bin/python
#encoding:utf-8
import xlrd
import re
class Data:
    def __init__(self,idframe):
        self.parent=idframe
        self.data=[0x00,0x00,0x00,0x00,0x00,0x00,0x0,0x00,0x000]
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
        i=body.validDataPos-1
        temp=value<<body.bitPos
        while(temp):
            tmod=temp%256
            if(i<0):print "fate error;exit()"
            bodyData.data[i]=tmod
            i-=1
            temp=temp//256
        bodyData.calculateFcc()
        return bodyData
    def generateDataFrame(self,bodyList):
        ret=[]
        for body in bodyList:
            if(not body.disc):
                bodyData=self.__setDatabit(body,2**body.bitLen-1)
                ret.append(bodyData.data)
            else:
                for m in body.disc.DisList:
                    if(not len(m[0])):
                        bodyData=self.__setDatabit(body,2**body.bitLen-1)
                        ret.append(bodyData.data)
                    else:
                        for num in range(m[0][0],m[0][1]):
                            bodyData=self.__setDatabit(body,num)
                            ret.append(bodyData.data)
        return ret

class Discrible:
    __pattern=re.compile( u'^【?(((\d+)(～\d+)?)|[ABCDEF])([bh])?】?:?(.*)' )
    def __init__(self,discStr=''):
        self.DisList=self.parseStr(discStr)
        
    def parseStr(self,discStr):
        ret=[]
        if(discStr==''):return ret
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
                    g4=int(match.group(4),base)
                    tl=[[g3,g4+1],match.group(6)]
                ret.append(tl)
            elif len(temp)==1:
                tl=[[],istr]
                ret.append(tl)
        return ret
        
class Body:
    def __init__(self,startPos=0.0,bitLen=0,cmdStr='',disc=None):
        self.validDataPos=int(startPos)
        self.bitPos=int((startPos-int(startPos))*10)
        self.bitLen=bitLen
        self.cmdStr=cmdStr
        self.disc=disc
    
class Unite:
    def __init__(self,index=0,id='',dlc=0,bodyList=[]):
        self.index=index
        self.id=id
        self.dlc=dlc
        self.bodyList=bodyList

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
        startPos=table.cell(i,8).value#获取开始位置
        if(not changed and not isinstance(startPos,float) ):continue
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
#            if(not len(ret)):print "code logic error! exit()";exit()
            body=Body(table.cell(i,8).value,table.cell(i,9).value,table.cell(i,11).value)#获取开始位置，长度，描述
            body.disc=Discrible(table.cell(i,25).value)
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
    for data in idFrame.bodyFrame:
        ret.append(temp+data)
    return ret

def startup(fileName):
    dataInformation=getDataInformation(fileName)
    idFrames=generateDate(dataInformation)
    ret=None
    for idFrame in idFrames:
        if(ret):
            ret+=idFrameToMat(idFrame)
        else:
            ret=idFrameToMat(idFrame)
    return ret
