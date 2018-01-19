from numpy import *
def loadDataSet():
    dataMat=[];labelMat=[]
    fr=open('testSet.txt')
    lines=fr.readlines()
    for line in lines:
        lineArr=line.strip().split()
        dataMat.append([1.0,float(lineArr[0]),float(lineArr[1])])
        labelMat.append(float(lineArr[-1]))
    return dataMat,labelMat

def sigmoid(inx):
    return 1.0/(1+exp(-inx))

def gradAscent(dataMat,labelMat):
    dataMat=mat(dataMat)
    labelMat=mat(labelMat).T

