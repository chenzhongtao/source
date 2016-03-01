#!/usr/bin/env python
# coding=utf-8

'''
Created on Jun 1, 2011

@author: Peter Harrington
'''
from numpy import *

def loadDataSet(fileName, delim='\t'):
    """
    加载数据
    """
    fr = open(fileName)
    #每个数据一个列表，所有列表放在一个大列表中
    stringArr = [line.strip().split(delim) for line in fr.readlines()]
    datArr = [map(float,line) for line in stringArr]
    return mat(datArr)

def pca(dataMat, topNfeat=9999999):
    """
    pca 算法
    dataMat:数据集
    topNfeat:返回的特征数，或全部特征
    """
    #对列(特征)求均值
    meanVals = mean(dataMat, axis=0)
    #所有数据减去均值
    meanRemoved = dataMat - meanVals #remove mean
    #计算协方差矩阵
    #两个特征 -> 2*2 矩阵
    covMat = cov(meanRemoved, rowvar=0)
    #计算特征值和特征向量
    eigVals,eigVects = linalg.eig(mat(covMat))
    #获取排序的的索引
    eigValInd = argsort(eigVals)            #sort, sort goes smallest to largest
    #反序和取前topNfeat个索引
    eigValInd = eigValInd[:-(topNfeat+1):-1]  #cut off unwanted dimensions
    #取前topNfeat个特征向量
    redEigVects = eigVects[:,eigValInd]       #reorganize eig vects largest to smallest
    #把数据转到新的维度
    lowDDataMat = meanRemoved * redEigVects #transform data into new dimensions
    #还原原来的数据
    reconMat = (lowDDataMat * redEigVects.T) + meanVals
    return lowDDataMat, reconMat

def replaceNanWithMean():
    """
    将数据中的NaN换成平均值
    """
    datMat = loadDataSet('secom.data', ' ')
    numFeat = shape(datMat)[1]
    for i in range(numFeat):
        meanVal = mean(datMat[nonzero(~isnan(datMat[:,i].A))[0],i]) #values that are not NaN (a number)
        datMat[nonzero(isnan(datMat[:,i].A))[0],i] = meanVal  #set NaN values to mean
    return datMat
if __name__ == "__main__":
    dataMat = loadDataSet("testSet.txt")
    lowDMat, reconMat = pca(dataMat, 1)
    