#!/usr/bin/env python
# coding=utf-8

'''
Created on Feb 4, 2011
Tree-Based Regression Methods
@author: Peter Harrington
'''
from numpy import *

def loadDataSet(fileName):      #general function to parse tab -delimited floats
    """
    加载数据集
    """
    dataMat = []                #assume last column is target value
    fr = open(fileName)
    for line in fr.readlines():
        curLine = line.strip().split('\t')
        #所有元素转为 浮点型
        fltLine = map(float,curLine) #map all elements to float()
        dataMat.append(fltLine)
    return dataMat

def binSplitDataSet(dataSet, feature, value):
    """
    二分法切分,把数据集切分得到两个子集
    dataSet：数据集合   
    feature：待切分的特征
    value：该特征的某个值
    """
    # nonzero 返回元素不为 0 的下标，为什么后面还有 [0] 得到的矩阵是三维的， 1*row*col,所以要加 [0]
    mat0 = dataSet[nonzero(dataSet[:,feature] > value)[0],:][0]
    mat1 = dataSet[nonzero(dataSet[:,feature] <= value)[0],:][0]
    return mat0,mat1

def regLeaf(dataSet):#returns the value used for each leaf
    """
    生成叶节点值 回归树
    就是目标变量的均值
    """
    return mean(dataSet[:,-1])

def regErr(dataSet):
    """
    误差估计函数,总方差
    就是计算目标变量的平方误差(误差小代表数据的混乱度小)
    """
    return var(dataSet[:,-1]) * shape(dataSet)[0]

def linearSolve(dataSet):   #helper function used in two places
    """
    线性回归
    dataSet:数据集
    """
    m,n = shape(dataSet)
    #x0 = 1
    X = mat(ones((m,n))); Y = mat(ones((m,1)))#create a copy of data with 1 in 0th postion
    X[:,1:n] = dataSet[:,0:n-1];
    #数据集的最后一列
    Y = dataSet[:,-1]#and strip out Y
    xTx = X.T*X
    # 如果矩阵的逆不存在，会造成异常
    if linalg.det(xTx) == 0.0:
        raise NameError('This matrix is singular, cannot do inverse,\n\
        try increasing the second value of ops')
    #ws 参数向量
    ws = xTx.I * (X.T * Y)
    return ws,X,Y

def modelLeaf(dataSet):#create linear model and return coeficients
    """
    生成叶节点模型 模型树
    计算数据的线性模型参数
    """
    ws,X,Y = linearSolve(dataSet)
    return ws

def modelErr(dataSet):
    """
    模型误差，yHat和Y的平方误差
    """
    ws,X,Y = linearSolve(dataSet)
    yHat = X * ws
    return sum(power(Y - yHat,2))

def chooseBestSplit(dataSet, leafType=regLeaf, errType=regErr, ops=(1,4)):
    """
    找到数据的最佳二元切分方式
    dataSet：数据集合
    leafType：创建叶节点的函数的引用
    errType： 计算总方差函数的引用
    ops设定了tols和tolN这两个值,其实就是预剪枝，避免过拟合
    tols: 容许的误差下降值
    tolN：切分的最少样本数
    """
    tolS = ops[0]; tolN = ops[1]
    #if all the target variables are the same value: quit and return value
    #所有目标变量都是这样,叶节点返回None
    if len(set(dataSet[:,-1].T.tolist()[0])) == 1: #exit cond 1
        return None, leafType(dataSet)
    m,n = shape(dataSet)
    #the choice of the best feature is driven by Reduction in RSS error from mean
    S = errType(dataSet)
    bestS = inf; bestIndex = 0; bestValue = 0
    #遍历所有特征
    for featIndex in range(n-1):
        #对每个特征值
        for splitVal in set(dataSet[:,featIndex]):
            mat0, mat1 = binSplitDataSet(dataSet, featIndex, splitVal)
            #样本数过少，跳过
            if (shape(mat0)[0] < tolN) or (shape(mat1)[0] < tolN): continue
            #计算切分的误差
            newS = errType(mat0) + errType(mat1)
            if newS < bestS:
                #最佳切分的特征
                bestIndex = featIndex
                #最佳切分的阈值
                bestValue = splitVal
                bestS = newS
    #if the decrease (S-bestS) is less than a threshold don't do the split
    #小于容许的误差下降值，返回叶节点
    if (S - bestS) < tolS: 
        return None, leafType(dataSet) #exit cond 2
    mat0, mat1 = binSplitDataSet(dataSet, bestIndex, bestValue)
    #样本数过少，返回叶节点
    if (shape(mat0)[0] < tolN) or (shape(mat1)[0] < tolN):  #exit cond 3
        return None, leafType(dataSet)
    #返回 最佳切分的特征 ， 最佳切分的阈值
    return bestIndex,bestValue#returns the best feature to split on
                              #and the value used for that split

def createTree(dataSet, leafType=regLeaf, errType=regErr, ops=(1,4)):#assume dataSet is NumPy Mat so we can array filtering
    """
    递归创建树
    """
    #选择最好的特征和阈值把数据分成两半
    feat, val = chooseBestSplit(dataSet, leafType, errType, ops)#choose the best split
    #如何特征为None，即为叶子节点，返回目标变量的均值
    if feat == None: return val #if the splitting hit a stop condition return val
    retTree = {}
    retTree['spInd'] = feat
    retTree['spVal'] = val
    #把数据分成两部分
    lSet, rSet = binSplitDataSet(dataSet, feat, val)
    #左子树
    retTree['left'] = createTree(lSet, leafType, errType, ops)
    #右子树
    retTree['right'] = createTree(rSet, leafType, errType, ops)
    # 最后返回根
    return retTree  

def isTree(obj):
    """
    判断是否为树
    """
    return (type(obj).__name__=='dict')

def getMean(tree):
    """
    递归函数，找到两个叶子节点并计算它们的平均值
    两个叶子节点平均值赋给父节点，递归到最后返回一个值
    """
    if isTree(tree['right']): tree['right'] = getMean(tree['right'])
    if isTree(tree['left']): tree['left'] = getMean(tree['left'])
    return (tree['left']+tree['right'])/2.0
    
def prune(tree, testData):
    """
    后剪枝算法
    tree:待剪枝的树
    testData:剪枝所需的测试数据
    """
    #测试数据为空,剪枝
    if shape(testData)[0] == 0: return getMean(tree) #if we have no test data collapse 倒塌 the tree
    if (isTree(tree['right']) or isTree(tree['left'])):#if the branches are not trees try to prune them
        lSet, rSet = binSplitDataSet(testData, tree['spInd'], tree['spVal'])
    #如何是子树，继续调用 prune
    if isTree(tree['left']): tree['left'] = prune(tree['left'], lSet)
    if isTree(tree['right']): tree['right'] =  prune(tree['right'], rSet)
    #if they are now both leafs, see if we can merge them
    #两个分支已不再是子树
    if not isTree(tree['left']) and not isTree(tree['right']):
        lSet, rSet = binSplitDataSet(testData, tree['spInd'], tree['spVal'])
        #没有合并的误差
        errorNoMerge = sum(power(lSet[:,-1] - tree['left'],2)) +\
            sum(power(rSet[:,-1] - tree['right'],2))
        treeMean = (tree['left']+tree['right'])/2.0
        #合并的误差
        errorMerge = sum(power(testData[:,-1] - treeMean,2))
        #合并后的误差比较小
        if errorMerge < errorNoMerge: 
            print "merging"
            #返回合并后的数
            return treeMean
        else: return tree
    else: return tree
    
def regTreeEval(model, inDat):
    """
    回归数的预测值
    """
    return float(model)

def modelTreeEval(model, inDat):
    """
    模型树的预测值,这里的model为模型参数
    """
    n = shape(inDat)[1]
    X = mat(ones((1,n+1)))
    X[:,1:n+1]=inDat
    return float(X*model)

def treeForeCast(tree, inData, modelEval=regTreeEval):
    """
    对测试样本进行预测
    """
    if not isTree(tree): return modelEval(tree, inData)
    if inData[tree['spInd']] > tree['spVal']:
        if isTree(tree['left']): return treeForeCast(tree['left'], inData, modelEval)
        else: return modelEval(tree['left'], inData)
    else:
        if isTree(tree['right']): return treeForeCast(tree['right'], inData, modelEval)
        else: return modelEval(tree['right'], inData)
        
def createForeCast(tree, testData, modelEval=regTreeEval):
    """
    对所有测试数据集进行预测
    """
    m=len(testData)
    yHat = mat(zeros((m,1)))
    for i in range(m):
        yHat[i,0] = treeForeCast(tree, mat(testData[i]), modelEval)
    return yHat

if __name__ == "__main__":
    data = loadDataSet("ex0.txt")
    dataMat =mat(data)
    tree = createTree(dataMat)
    print tree
    print getMean(tree)
    
    dataMat =mat(loadDataSet("bikeSpeedVsIq_train.txt"))
    testData = mat(loadDataSet("bikeSpeedVsIq_test.txt"))
    
    #回归树
    tree = createTree(dataMat,  ops=(1,20))
    yHat = createForeCast(tree, testData[:,0])
    print corrcoef(yHat, testData[:,1], rowvar=0)[0,1]
    
    #模型树
    tree = createTree(dataMat, leafType=modelLeaf, errType=modelErr, ops=(1,20))
    yHat = createForeCast(tree, testData[:,0], modelEval=modelTreeEval)
    print corrcoef(yHat, testData[:,1], rowvar=0)[0,1]