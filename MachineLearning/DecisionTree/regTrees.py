class treeNode():
    def __init__(self,feat,val,right,left):
        featureToSplitOn=feat
        valueOfSplit=val
        rightBranch=right
        leftBranch=left

from numpy import *
def loadDataSet(fileName):
    dataMat=[]
    fr=open(filename)
    for line in fr.readlines():
        curLine=line.strip().split('\t')
        fltLine=map(float,curLine)
        dataMat.append(fltLine)
    return detaMat
