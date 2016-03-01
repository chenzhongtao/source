#!/usr/bin/env python
# coding=utf-8

'''
Created on Nov 28, 2010
Adaboost is short for Adaptive Boosting
@author: Peter
'''
from numpy import *

def loadSimpData():
    """
    加载简单测试数据
    """
    datMat = matrix([[ 1. ,  2.1],
        [ 2. ,  1.1],
        [ 1.3,  1. ],
        [ 1. ,  1. ],
        [ 2. ,  1. ]])
    classLabels = [1.0, 1.0, -1.0, -1.0, 1.0]
    return datMat,classLabels

def loadDataSet(fileName):      #general function to parse tab -delimited floats
    """
    加载数据
    """
    numFeat = len(open(fileName).readline().split('\t')) #get number of fields 
    dataMat = []; labelMat = []
    fr = open(fileName)
    for line in fr.readlines():
        lineArr =[]
        curLine = line.strip().split('\t')
        for i in range(numFeat-1):
            lineArr.append(float(curLine[i]))
        dataMat.append(lineArr)
        labelMat.append(float(curLine[-1]))
    return dataMat,labelMat

def stumpClassify(dataMatrix,dimen,threshVal,threshIneq):#just classify the data
    """
    通过阈值比较对数据进行分类
    dataMatrix：数据
    dimen：特征索引
    threshVal：阈值
    threshIneq：不等式类型
    """
    #返回数组的全部元素先设置为1
    retArray = ones((shape(dataMatrix)[0],1))
    #不满足不等式要求的元素设置为-1
    if threshIneq == 'lt':
        retArray[dataMatrix[:,dimen] <= threshVal] = -1.0
    else:
        retArray[dataMatrix[:,dimen] > threshVal] = -1.0
    return retArray
    

def buildStump(dataArr,classLabels,D):
    """
    单层决策树生成函数
    dataArr：数据集
    classLabels：类别标签
    D：数据的权重向量
    输出：
    bestStump；最佳决策树的参数
    minError：错误率
    bestClasEst：预测值
    
    """
    dataMatrix = mat(dataArr);
    labelMat = mat(classLabels).T
    m,n = shape(dataMatrix)
    numSteps = 10.0;
    bestStump = {};
    bestClasEst = mat(zeros((m,1)))
    minError = inf #init error sum, to +infinity 无穷大
    #遍历所有特征
    for i in range(n):#loop over all dimensions
        #某特征值的最小值
        rangeMin = dataMatrix[:,i].min();
        #某特征值的最大值
        rangeMax = dataMatrix[:,i].max();
        #求步长
        stepSize = (rangeMax-rangeMin)/numSteps
        #大小 小于一个步长和大小一个步长（-1:numSteps+1）
        for j in range(-1,int(numSteps)+1):#loop over all range in current dimension
            #在小于和大于切换不等式
            for inequal in ['lt', 'gt']: #go over less than and greater than
                threshVal = (rangeMin + float(j) * stepSize)
                predictedVals = stumpClassify(dataMatrix,i,threshVal,inequal)#call stump classify with i, j, lessThan
                errArr = mat(ones((m,1)))
                errArr[predictedVals == labelMat] = 0
                weightedError = D.T*errArr  #calc total error multiplied by D
                #print "split: dim %d, thresh %.2f, thresh ineqal: %s, the weighted error is %.3f" % (i, threshVal, inequal, weightedError)
                if weightedError < minError:
                    #保存最小误差的 特征，阈值，不等式号
                    minError = weightedError
                    bestClasEst = predictedVals.copy()
                    bestStump['dim'] = i
                    bestStump['thresh'] = threshVal
                    bestStump['ineq'] = inequal
    return bestStump,minError,bestClasEst


def adaBoostTrainDS(dataArr,classLabels,numIt=40):
    """
    adaBoost算法，DS代表单层决策树(decision stump)
    dataArr：数据集
    classLabels：类别标签
    numIt：迭代次数
    """
    weakClassArr = []
    m = shape(dataArr)[0]
    D = mat(ones((m,1))/m)   #init D to all equal
    aggClassEst = mat(zeros((m,1)))
    for i in range(numIt):
        #最佳的单层决策树
        bestStump,error,classEst = buildStump(dataArr,classLabels,D)#build Stump
        #print "D:",D.T
        #通过错误率更新alpha，错误率越小，alpha越多， 错误率等于50%，alpha等于0
        alpha = float(0.5*log((1.0-error)/max(error,1e-16)))#calc alpha, throw in max(error,eps) to account for error=0
        bestStump['alpha'] = alpha
        #新增一个弱分类器
        weakClassArr.append(bestStump)                  #store Stump Params in Array
        #print "classEst: ",classEst.T
        #由于标签只有0和1，这里的意义是 预测对的数据为-alpha，预测错的值为 alpha
        #这样可以增加错分数据的权重和降低正确分类的权重
        expon = multiply(-1*alpha*mat(classLabels).T,classEst) #exponent for D calc, getting messy
        D = multiply(D,exp(expon))                              #Calc New D for next iteration
        #D是一个概率分布向量，所有元素之和为1
        D = D/D.sum()
        #calc training error of all classifiers, if this is 0 quit for loop early (use break)
        # 记录每个数据点的类别估计累计值
        aggClassEst += alpha*classEst
        #print "aggClassEst: ",aggClassEst.T
        
        #错误向量，对为1，错误为0
        aggErrors = multiply(sign(aggClassEst) != mat(classLabels).T,ones((m,1)))
        #计算错误率
        errorRate = aggErrors.sum()/m
        print "total error: ",errorRate
        if errorRate == 0.0: break
    return weakClassArr,aggClassEst

def adaClassify(datToClass,classifierArr):
    """
    AdaBoost分类函数
    datToClass：待分类样例
    classifierArr: adaBoostTrainDS函数返回的weakClassArr，多个弱分类器
    """
    dataMatrix = mat(datToClass)#do stuff similar to last aggClassEst in adaBoostTrainDS
    m = shape(dataMatrix)[0]
    aggClassEst = mat(zeros((m,1)))
    for i in range(len(classifierArr)):
        classEst = stumpClassify(dataMatrix,classifierArr[i]['dim'],\
                                 classifierArr[i]['thresh'],\
                                 classifierArr[i]['ineq'])#call stump classify
        #多个弱分类结果之和
        aggClassEst += classifierArr[i]['alpha']*classEst
        print aggClassEst
    return sign(aggClassEst)

def plotROC(predStrengths, classLabels):
    import matplotlib.pyplot as plt
    cur = (1.0,1.0) #cursor
    ySum = 0.0 #variable to calculate AUC
    numPosClas = sum(array(classLabels)==1.0)
    yStep = 1/float(numPosClas); xStep = 1/float(len(classLabels)-numPosClas)
    sortedIndicies = predStrengths.argsort()#get sorted index, it's reverse
    fig = plt.figure()
    fig.clf()
    ax = plt.subplot(111)
    #loop through all the values, drawing a line segment at each point
    for index in sortedIndicies.tolist()[0]:
        if classLabels[index] == 1.0:
            delX = 0; delY = yStep;
        else:
            delX = xStep; delY = 0;
            ySum += cur[1]
        #draw line from cur to (cur[0]-delX,cur[1]-delY)
        ax.plot([cur[0],cur[0]-delX],[cur[1],cur[1]-delY], c='b')
        cur = (cur[0]-delX,cur[1]-delY)
    ax.plot([0,1],[0,1],'b--')
    plt.xlabel('False positive rate'); plt.ylabel('True positive rate')
    plt.title('ROC curve for AdaBoost horse colic detection system')
    ax.axis([0,1,0,1])
    plt.show()
    print "the Area Under the Curve is: ",ySum*xStep


if __name__ == "__main__":
    datMat,classLabels = loadSimpData()
    D = mat(ones((5,1))/5)
    #buildStump(datMat, classLabels, D)
    adaBoostTrainDS(datMat, classLabels,numIt=40)
