#!/usr/bin/env python
# coding=utf-8

'''
Created on Jan 8, 2011

@author: Peter
'''
from numpy import *

def loadDataSet(fileName):      #general function to parse tab -delimited floats
    """
    加载数据集
    """
    #特征数
    numFeat = len(open(fileName).readline().split('\t')) - 1 #get number of fields 
    dataMat = [];
    labelMat = []
    fr = open(fileName)
    for line in fr.readlines():
        lineArr =[]
        curLine = line.strip().split('\t')
        for i in range(numFeat):
            lineArr.append(float(curLine[i]))
        dataMat.append(lineArr)
        labelMat.append(float(curLine[-1]))
    return dataMat,labelMat

def standRegres(xArr,yArr):
    """
    标准线型回归
    xArr：数据集，x0 = 1
    yArr：目标值
    """
    xMat = mat(xArr);
    yMat = mat(yArr).T
    xTx = xMat.T*xMat
    #判断是否可逆
    if linalg.det(xTx) == 0.0:
        print "This matrix is singular, cannot do inverse"
        return
    #计算回归系数
    ws = xTx.I * (xMat.T*yMat)
    return ws

def lwlr(testPoint,xArr,yArr,k=1.0):
    """
    局部加权线性回归
    testPoint：测试点
    xArr：数据集
    yArr：目标值
    k:高斯核系数, k=1时，如同将将所有看成等权重，较小的k得到较低的误差，但可能会过拟合，对预测结果较差
    """
    xMat = mat(xArr);
    yMat = mat(yArr).T
    m = shape(xMat)[0]
    #权重，使用高斯核计算，每个测试点都要计算一次权重，样本点离测试点越近，权重越大
    weights = mat(eye((m)))
    for j in range(m):                      #next 2 lines create weights matrix
        diffMat = testPoint - xMat[j,:]     #
        weights[j,j] = exp(diffMat*diffMat.T/(-2.0*k**2))
    xTx = xMat.T * (weights * xMat)
    if linalg.det(xTx) == 0.0:
        print "This matrix is singular, cannot do inverse"
        return
    ws = xTx.I * (xMat.T * (weights * yMat))
    return testPoint * ws

def lwlrTest(testArr,xArr,yArr,k=1.0):  #loops over all the data points and applies lwlr to each one
    """
    局部加权线性回归测试函数
    testArr：测试数据集
    xArr：数据集
    yArr：目标值
    k:高斯核系数
    """
    m = shape(testArr)[0]
    yHat = zeros(m)
    for i in range(m):
        yHat[i] = lwlr(testArr[i],xArr,yArr,k)
    return yHat

def lwlrTestPlot(xArr,yArr,k=1.0):  #same thing as lwlrTest except it sorts X first
    yHat = zeros(shape(yArr))       #easier for plotting
    xCopy = mat(xArr)
    xCopy.sort(0)
    for i in range(shape(xArr)[0]):
        yHat[i] = lwlr(xCopy[i],xArr,yArr,k)
    return yHat,xCopy

def rssError(yArr,yHatArr): #yArr and yHatArr both need to be arrays
    """
    计算rss
    """
    return ((yArr-yHatArr)**2).sum()

#如何特征比样本还多(n>m),输入数据的矩阵x不是满秩矩阵，(X.T*X)求逆会出现问题
#所以引入了下面的岭回归，lasso法，前向逐步回归
def ridgeRegres(xMat,yMat,lam=0.2):
    """
    岭回归
    """
    xTx = xMat.T*xMat
    # 加入对角阵，使其非奇异，lam也可以看成是惩罚项，能够减少不重要的参数
    denom = xTx + eye(shape(xMat)[1])*lam
    if linalg.det(denom) == 0.0:
        print "This matrix is singular, cannot do inverse"
        return
    ws = denom.I * (xMat.T*yMat)
    return ws
    
def ridgeTest(xArr,yArr):
    """
    岭回归测试函数
    xArr：数据集
    yArr：目标值
    """
    xMat = mat(xArr);
    yMat=mat(yArr).T
    yMean = mean(yMat,0)
    yMat = yMat - yMean     #to eliminate X0 take mean off of Y
    #regularize X's
    #求均值，列方向(对特征 归一化)
    xMeans = mean(xMat,0)   #calc mean then subtract it off
    #求方差
    xVar = var(xMat,0)      #calc variance of Xi then divide by it
    #数据归一化
    xMat = (xMat - xMeans)/xVar
    numTestPts = 30
    wMat = zeros((numTestPts,shape(xMat)[1]))
    #遍历不同的lam
    for i in range(numTestPts):
        ws = ridgeRegres(xMat,yMat,exp(i-10))
        wMat[i,:]=ws.T
    return wMat

def regularize(xMat):#regularize by columns
    """
    对数据归一化 按列
    """
    inMat = xMat.copy()
    inMeans = mean(inMat,0)   #calc mean then subtract it off
    inVar = var(inMat,0)      #calc variance of Xi then divide by it
    inMat = (inMat - inMeans)/inVar
    return inMat

def stageWise(xArr,yArr,eps=0.01,numIt=100):
    """
    向前逐步线性回归，属于贪心算法，(不断修改系数w)
    xArr：数据集
    yArr：目标值
    eps: 每一步大小
    numIt：迭代次数
    """
    xMat = mat(xArr);
    #转成一列
    yMat=mat(yArr).T
    yMean = mean(yMat,0)
    yMat = yMat - yMean     #can also regularize ys but will get smaller coef
    xMat = regularize(xMat)
    m,n=shape(xMat)
    #returnMat = zeros((numIt,n)) #testing code remove
    ws = zeros((n,1));
    wsTest = ws.copy();
    wsMax = ws.copy()
    for i in range(numIt):
        print ws.T
        #设置误差为无穷大
        lowestError = inf;
        #遍历每个特征
        for j in range(n):
            #增大或缩小或不变 
            for sign in [-1,1]:
                wsTest = ws.copy()
                wsTest[j] += eps*sign
                yTest = xMat*wsTest
                rssE = rssError(yMat.A,yTest.A)
                #保存最小的rss
                if rssE < lowestError:
                    lowestError = rssE
                    wsMax = wsTest
        ws = wsMax.copy()
        #returnMat[i,:]=ws.T
    #return returnMat

#def scrapePage(inFile,outFile,yr,numPce,origPrc):
#    from BeautifulSoup import BeautifulSoup
#    fr = open(inFile); fw=open(outFile,'a') #a is append mode writing
#    soup = BeautifulSoup(fr.read())
#    i=1
#    currentRow = soup.findAll('table', r="%d" % i)
#    while(len(currentRow)!=0):
#        title = currentRow[0].findAll('a')[1].text
#        lwrTitle = title.lower()
#        if (lwrTitle.find('new') > -1) or (lwrTitle.find('nisb') > -1):
#            newFlag = 1.0
#        else:
#            newFlag = 0.0
#        soldUnicde = currentRow[0].findAll('td')[3].findAll('span')
#        if len(soldUnicde)==0:
#            print "item #%d did not sell" % i
#        else:
#            soldPrice = currentRow[0].findAll('td')[4]
#            priceStr = soldPrice.text
#            priceStr = priceStr.replace('$','') #strips out $
#            priceStr = priceStr.replace(',','') #strips out ,
#            if len(soldPrice)>1:
#                priceStr = priceStr.replace('Free shipping', '') #strips out Free Shipping
#            print "%s\t%d\t%s" % (priceStr,newFlag,title)
#            fw.write("%d\t%d\t%d\t%f\t%s\n" % (yr,numPce,newFlag,origPrc,priceStr))
#        i += 1
#        currentRow = soup.findAll('table', r="%d" % i)
#    fw.close()
    
from time import sleep
import json
import urllib2
def searchForSet(retX, retY, setNum, yr, numPce, origPrc):
    sleep(10)
    myAPIstr = 'AIzaSyD2cR2KFyx12hXu6PFU-wrWot3NXvko8vY'
    searchURL = 'https://www.googleapis.com/shopping/search/v1/public/products?key=%s&country=US&q=lego+%d&alt=json' % (myAPIstr, setNum)
    pg = urllib2.urlopen(searchURL)
    retDict = json.loads(pg.read())
    for i in range(len(retDict['items'])):
        try:
            currItem = retDict['items'][i]
            if currItem['product']['condition'] == 'new':
                newFlag = 1
            else: newFlag = 0
            listOfInv = currItem['product']['inventories']
            for item in listOfInv:
                sellingPrice = item['price']
                if  sellingPrice > origPrc * 0.5:
                    print "%d\t%d\t%d\t%f\t%f" % (yr,numPce,newFlag,origPrc, sellingPrice)
                    retX.append([yr, numPce, newFlag, origPrc])
                    retY.append(sellingPrice)
        except: print 'problem with item %d' % i
    
def setDataCollect(retX, retY):
    searchForSet(retX, retY, 8288, 2006, 800, 49.99)
    searchForSet(retX, retY, 10030, 2002, 3096, 269.99)
    searchForSet(retX, retY, 10179, 2007, 5195, 499.99)
    searchForSet(retX, retY, 10181, 2007, 3428, 199.99)
    searchForSet(retX, retY, 10189, 2008, 5922, 299.99)
    searchForSet(retX, retY, 10196, 2009, 3263, 249.99)
    
def crossValidation(xArr,yArr,numVal=10):
    m = len(yArr)                           
    indexList = range(m)
    errorMat = zeros((numVal,30))#create error mat 30columns numVal rows
    for i in range(numVal):
        trainX=[]; trainY=[]
        testX = []; testY = []
        random.shuffle(indexList)
        for j in range(m):#create training set based on first 90% of values in indexList
            if j < m*0.9: 
                trainX.append(xArr[indexList[j]])
                trainY.append(yArr[indexList[j]])
            else:
                testX.append(xArr[indexList[j]])
                testY.append(yArr[indexList[j]])
        wMat = ridgeTest(trainX,trainY)    #get 30 weight vectors from ridge
        for k in range(30):#loop over all of the ridge estimates
            matTestX = mat(testX); matTrainX=mat(trainX)
            meanTrain = mean(matTrainX,0)
            varTrain = var(matTrainX,0)
            matTestX = (matTestX-meanTrain)/varTrain #regularize test with training params
            yEst = matTestX * mat(wMat[k,:]).T + mean(trainY)#test ridge results and store
            errorMat[i,k]=rssError(yEst.T.A,array(testY))
            #print errorMat[i,k]
    meanErrors = mean(errorMat,0)#calc avg performance of the different ridge weight vectors
    minMean = float(min(meanErrors))
    bestWeights = wMat[nonzero(meanErrors==minMean)]
    #can unregularize to get model
    #when we regularized we wrote Xreg = (x-meanX)/var(x)
    #we can now write in terms of x not Xreg:  x*w/var(x) - meanX/var(x) +meanY
    xMat = mat(xArr); yMat=mat(yArr).T
    meanX = mean(xMat,0); varX = var(xMat,0)
    unReg = bestWeights/varX
    print "the best model from Ridge Regression is:\n",unReg
    print "with constant term: ",-1*sum(multiply(meanX,unReg)) + mean(yMat)
    
if __name__ == "__main__":
    dataMat,labelMat = loadDataSet("ex0.txt")
    yHat1,xCopy1 = lwlrTestPlot(dataMat,labelMat, k=1)
    yHat2,xCopy2 = lwlrTestPlot(dataMat,labelMat, k=0.01)
    yHat3,xCopy3 = lwlrTestPlot(dataMat,labelMat, k=0.003)
    
    #xMat=mat(xArr)
    #srtInd = xMat[:,1].argsort(0)
    #xSort=xMat[srtInd][:,0,:]
    #Now you can plot this with Matplotlib:
    import matplotlib.pyplot as plt
    fig = plt.figure(figsize=(5,12))
    ax1 = fig.add_subplot(311)
    ax1.plot(xCopy1[:,1],yHat1)
    #[<matplotlib.lines.Line2D object at 0x03639550>]
    #散点图
    #ax.scatter(mat(dataMat)[:,1].flatten().A[0], mat(labelMat).T.flatten().A[0] , s=2,c='red')
    ax1.scatter(array(dataMat)[:,1], labelMat , s=2, color="r")
    #<matplotlib.collections.PathCollection object at 0x03859110>
    
    ax2 = fig.add_subplot(312)
    ax2.plot(xCopy2[:,1],yHat2)
    ax2.scatter(array(dataMat)[:,1], labelMat , s=2, color="r")
    ax3 = fig.add_subplot(313)
    ax3.plot(xCopy3[:,1],yHat3)
    ax3.scatter(array(dataMat)[:,1], labelMat , s=2, color="r")
    plt.show()
    
    