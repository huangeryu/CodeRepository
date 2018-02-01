import xlrd
import re
class Discrible:
    def __init__(self,discStr=''):
        self.DisList=self.parseStr(discStr)
        self.pattern=re.compile(u'^【?(((\d+(～\d+)?)|[ABCDEF])[bh]?)】?:?.*')

    def parseStr(self,discStr):
        ret=[]
        if(discStr==''):return ret
        temp=discStr.strip().split('\n')
        for istr in temp:
            pass
class Body:
    def __init__(self,startPos=0.0,bitLen=0,cmdStr='',disc=None):
        self.startPos=startPos
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
            changed=False;continue
        cmdStr=table.cell(i,11)#获取データ名
        if(cmdStr=='' or cmdStr==u'－' ):continue
        if(changed):
            informaFrame=Unite(index)
            informaFrame.id=table.cell(i,6).value#获取id
            informaFrame.dlc=table.cell(i,7).value#获取DLC
            ret.append(informaFrame)
        else:
            if(not len(ret)):print "code logic error! exit()";exit()
            body=Body(table.cell(i,8).value,table.cell(i,9).value,cmdStr)#获取开始位置，长度，描述
            body.disc.append(Discrible(table.cell(i,25).value))
            len[-1].bodyList.append(body)
    return ret


def generateDate(unites):
    pass