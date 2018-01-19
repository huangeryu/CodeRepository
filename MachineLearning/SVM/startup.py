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
dataMat,labelMat=svm.loadDataSet()
print "loadDataSet()"
weights=svm.gradAscent(dataMat,labelMat)

