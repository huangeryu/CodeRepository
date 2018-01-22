from numpy import *
def loadDataSet(fileName):
    dataMat=[];labelMat=[]
    fr=open(fileName)
    for line in fr.readlines():
        lineArr=line.strip().split('\t')
        dataMat.append([float(lineArr[0]),float(lineArr[1])])
        labelMat.append(float(lineArr[2]))
    return dataMat,labelMat

def selectJrand(i,m):
    j=i
    while(j==i):
        j=int(random.uniform(0,m))
    return j

def clipAlpha(aj,H,L):
    if aj>H:
        aj=H
    if L>aj:
        aj=L
    return aj

def smoSimple(dataMatIn,classLabels,C,toler,maxIter):
    dataMatrix=mat(dataMatIn);labelMat=mat(classLabels).transpose()
    b=0;m,n=shape(dataMatrix)
    alphas=mat(zeros((m,1)))
    iter=0
    while(iter<maxIter):
        alphaPairsChanged=0
        for i in range(m):
            fxi=float(multiply(alphas,labelMat).T*(dataMatrix*dataMatrix[i,:].T))+b
            Ei=fxi-float(labelMat[i])
            if((labelMat[i]*Ei<-toler)and(alphas[i]<C))or((labelMat[i]*Ei>toler)and (alphas[i]>0)):
                j=selectJrand(i,m)
                fxj=float(multiply(alphas,labelMat).T*(dataMatrix*dataMatrix[j,:].T))+b
                Ej=fxj-float(labelMat[j])
                alphaIold=alphas[i].copy();alphaJold=alphas[j].copy()
                if(labelMat[i]!=labelMat[j]):
                    L=max(0,alphas[j]-alphas[i])
                    H=min(C,C+alphas[j]-alphas[i])
                else:
                    L=max(0,alphas[j]+alphas[i]-C)
                    H=min(C,alphas[j]+alphas[i])
                if L==H:
                    #print "L=H"
                    continue
                eta=2.0*dataMatrix[i,:]*dataMatrix[j,:].T-dataMatrix[i,:]*dataMatrix[i,:].T-dataMatrix[j,:]*dataMatrix[j,:].T
                if eta>=0:
                    #print "eta>=0"
                    continue
                alphas[j]-=labelMat[j]*(Ei-Ej)/eta
                alphas[j]=clipAlpha(alphas[j],H,L)
                if(abs(alphas[j]-alphaJold)<0.00001):
                    #print "j not moving enought"
                    continue
                alphas[i]+=labelMat[j]*labelMat[i]*(alphaJold-alphas[j])
                b1=b-Ei-labelMat[i]*(alphas[i]-alphaIold)*dataMatrix[i,:]*dataMatrix[i,:].T-labelMat[j]*(alphas[j]-alphaJold)*dataMatrix[i,:]*dataMatrix[j,:].T
                b2=b-Ej-labelMat[i]*(alphas[i]-alphaIold)*dataMatrix[i,:]*dataMatrix[j,:].T-labelMat[j]*(alphas[j]-alphaJold)*dataMatrix[j,:]*dataMatrix[j,:].T
                if(0<alphas[i]and C>alphas[i]):b=b1
                elif(0< alphas[j]and C>alphas[j]):b=b2
                else:b=(b1+b2)/2.0
                alphaPairsChanged+=1
                print "iter:%d i:%d,pairs changed %d"%(iter,i,alphaPairsChanged)
        if(alphaPairsChanged==0):iter+=1
        else: iter=0
        print "iteration number:%d"%iter
    return alphas,b

import matplotlib.pyplot as plt
def plotBestFit(dataMat,labelMat,alphas,b):
    dataArr=array(dataMat)
    n=shape(dataArr)[0]
    xcord1=[];ycord1=[]
    xcord2=[];ycord2=[]
    for i in range(n):
        if int(labelMat[i])==1:
            xcord1.append(dataArr[i,0]); ycord1.append(dataArr[i,1])
        else:
            xcord2.append(dataArr[i,0]); ycord2.append(dataArr[i,1])
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.scatter(xcord1, ycord1, s=30, c='red', marker='s')
    ax.scatter(xcord2, ycord2, s=30, c='green')
    weight=mat(dataMat).T*diag(labelMat)*alphas
    print type(weight)
    dataMin=int(dataArr.min(0)[0]-1);dataMax=int(dataArr.max(0)[0]+1)
    x = arange(dataMin, dataMax, 0.5)
    y=-weight[0]/weight[1]*x-b[0]/weight[1]
    ax.plot(x, y.tolist()[0])
    plt.xlabel('X1'); plt.ylabel('X2')
    plt.show()
