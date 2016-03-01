#!/usr/bin/env python
# coding=utf-8

'''
Created on Oct 12, 2010
Decision Tree Source Code for Machine Learning in Action Ch. 3
@author: Peter Harrington
'''
from math import log
import operator

def createDataSet():
    dataSet = [[1, 1, 'yes'],
               [1, 1, 'yes'],
               [1, 0, 'no'],
               [0, 1, 'no'],
               [0, 1, 'no']]
    labels = ['no surfacing','flippers']
    #change to discrete values
    return dataSet, labels

def calcShannonEnt(dataSet):
    """
    计算给定数据集的香农熵
    公式见p35
    熵越高，混合的数据越多
    """
    numEntries = len(dataSet)
    labelCounts = {}
    for featVec in dataSet: #the the number of unique elements and their occurance
        currentLabel = featVec[-1]
        # 以lable作为字典的键，如何键不在字典中，加入当前键
        if currentLabel not in labelCounts.keys(): labelCounts[currentLabel] = 0
        labelCounts[currentLabel] += 1
    shannonEnt = 0.0
    for key in labelCounts:
        #计算类别出现的概率
        prob = float(labelCounts[key])/numEntries
        shannonEnt -= prob * log(prob,2) #log base 2
    return shannonEnt
    
def splitDataSet(dataSet, axis, value):
    """
    按照给定特征划分数据集
    dataSet：待划分的数据集
    axis：划分数据集的特征(第几列)
    value：特征值
    返回特征值等于value的行，并去掉对应的特征
    """
    retDataSet = []
    for featVec in dataSet:
        if featVec[axis] == value:
            reducedFeatVec = featVec[:axis]     #chop out axis used for splitting 去掉对应的特征
            reducedFeatVec.extend(featVec[axis+1:])
            retDataSet.append(reducedFeatVec)
    return retDataSet
    
def chooseBestFeatureToSplit(dataSet):
    """
    选择最后的数据集划分方式，也就是选择最好的特征
    """
    #特征数
    numFeatures = len(dataSet[0]) - 1      #the last column is used for the labels
    #计算熵
    baseEntropy = calcShannonEnt(dataSet)
    bestInfoGain = 0.0; bestFeature = -1
    for i in range(numFeatures):        #iterate over all the features
        featList = [example[i] for example in dataSet]#create a list of all the examples of this feature 取一列特征
        uniqueVals = set(featList)       #get a set of unique values 
        newEntropy = 0.0
        for value in uniqueVals:
            subDataSet = splitDataSet(dataSet, i, value)
            prob = len(subDataSet)/float(len(dataSet))
            #划分后数据的熵
            newEntropy += prob * calcShannonEnt(subDataSet)
        # 计算信息增益
        infoGain = baseEntropy - newEntropy     #calculate the info gain; ie reduction in entropy
        if (infoGain > bestInfoGain):       #compare this to the best gain so far
            bestInfoGain = infoGain         #if better than current best, set to best
            #选择最大的信息增益对应的特征
            bestFeature = i
    return bestFeature                      #returns an integer

def majorityCnt(classList):
    """
    计算属于哪个类的比较多，就返回哪个类
    """
    classCount={}
    for vote in classList:
        if vote not in classCount.keys(): classCount[vote] = 0
        classCount[vote] += 1
    #按照字典是值排序
    sortedClassCount = sorted(classCount.iteritems(), key=operator.itemgetter(1), reverse=True)
    return sortedClassCount[0][0]

def createTree(dataSet,labels):
    """
    创建树
    """
    # 由于数据整形和字符串，所以这里的dataset用的是python的list
    # 取出最后一列
    classList = [example[-1] for example in dataSet]
    if classList.count(classList[0]) == len(classList):
        # 如果数据就只有一类就直接返回属于这类
        return classList[0]#stop splitting when all of the classes are equal
    #如果特征只剩一个，不用再split了，计算属于哪个类的比较多，就返回属于这个类
    if len(dataSet[0]) == 1: #stop splitting when there are no more features in dataSet
        return majorityCnt(classList)
    bestFeat = chooseBestFeatureToSplit(dataSet)
    bestFeatLabel = labels[bestFeat]
    myTree = {bestFeatLabel:{}}
    del(labels[bestFeat])
    featValues = [example[bestFeat] for example in dataSet]
    uniqueVals = set(featValues)
    for value in uniqueVals:
        subLabels = labels[:]       #copy all of labels, so trees don't mess up existing labels
        #子树
        myTree[bestFeatLabel][value] = createTree(splitDataSet(dataSet, bestFeat, value),subLabels)
    return myTree                            
    
def classify(inputTree,featLabels,testVec):
    firstStr = inputTree.keys()[0] #特征名
    secondDict = inputTree[firstStr]
    featIndex = featLabels.index(firstStr)
    key = testVec[featIndex] #特征值
    valueOfFeat = secondDict[key]
    #如果还有子树
    if isinstance(valueOfFeat, dict): 
        classLabel = classify(valueOfFeat, featLabels, testVec)
    else: classLabel = valueOfFeat
    return classLabel

def storeTree(inputTree,filename):
    """
    保存树
    """
    import pickle
    fw = open(filename,'w')
    pickle.dump(inputTree,fw)
    fw.close()
    
def grabTree(filename):
    """
    从文件读出树
    """
    import pickle
    fr = open(filename)
    return pickle.load(fr)

if __name__ == "__main__":
    dataSet, labels = createDataSet()
    mytree = createTree(dataSet, labels)
    import json
    # {"no surfacing": {"0": "no", "1": {"flippers": {"0": "no", "1": "yes"}}}}
    print json.dumps(mytree)
    print mytree
    
    
