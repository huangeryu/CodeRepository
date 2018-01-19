import logRegres
dataMat,labelMat=logRegres.loadDataSet()
weights=logRegres.gradAscent(dataMat,labelMat)
print weights
logRegres.plotBestFit(weights.getA())

