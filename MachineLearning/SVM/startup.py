loadedlist=dir()
loaded=False
for name in loadedlist:
    if not cmp(name,'svm'):
        loaded=True
        print "svm.py loaded"
if(loaded):
    reload(svm)
    print "reload svm"
else:
    import svm
    print "import svm"
dataMat,labelMat=svm.loadDataSet('testSet.txt')
print "loadDataSet()"
alphas,b=svm.smoSimple(dataMat,labelMat,0.6,0.001,40)
print "calculate alphas ,bias"
print "plot linegrapha"
svm.plotBestFit(dataMat,labelMat,alphas,b)
