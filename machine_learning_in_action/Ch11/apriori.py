#!/usr/bin/env python
# coding=utf-8

'''
Created on Mar 24, 2011
Ch 11 code
@author: Peter
'''
from numpy import *

def loadDataSet():
    """
    加载数据集
    """
    return [[1, 3, 4], [2, 3, 5], [1, 2, 3, 5], [2, 5]]

def createC1(dataSet):
    """
    构造集合c1,返回由单物品列表组成的大列表
    """
    C1 = []
    for transaction in dataSet:
        for item in transaction:
            if not [item] in C1:
                C1.append([item])
                
    C1.sort()
    #frozenset是不能修改的set,可以作为字典的key
    return map(frozenset, C1)#use frozen set so we
                            #can use it as a key in a dict    

def scanD(D, Ck, minSupport):
    """
    计算ck的支持度，根据最小支持度选出频繁项候选集列表，和支持度字典
    D：数据集
    Ck：候选项集列表
    minSupport：感兴趣候选项集的最小支持度
    输出：
    retList：频繁项候选集列表
    supportData：支持度字典
    """
    ssCnt = {}
    for tid in D:
        for can in Ck:
            if can.issubset(tid):
                if not ssCnt.has_key(can): ssCnt[can]=1
                else: ssCnt[can] += 1
    numItems = float(len(D))
    retList = []
    supportData = {}
    for key in ssCnt:
        support = ssCnt[key]/numItems
        if support >= minSupport:
            retList.insert(0,key)
        #支持度小于minSupport也计算,应该放到if里面
        #supportData[key] = support
            supportData[key] = support

    return retList, supportData

def aprioriGen(Lk, k): #creates Ck
    """
    生成项元素多一个的候选集 如：{0},{1} -> {0,1}
    LK：元素长度为k-1的频繁项集列表
    k：项集元素个数
    """
    retList = []
    lenLk = len(Lk)
    for i in range(lenLk):
        for j in range(i+1, lenLk):
            # Lk[i] 肯定不等于 Lk[j]
            # 但Lk[i]和Lk[j]只有一个元素不同才能求并集，
            # 这样保证只多一个元素，并且有可能是频繁项，
            # 因为频繁项所有子集也都是频繁项
            # 还有 {1,2}|{1,3} ->{1,2,3}
            # 还有 {1,2}|{2,3} 为空
            # 因为一个k个元素的频繁项有k个子项，每两个求并都可以求得，这样会出现重复，
            # 所以要求前k-2个元素相同，这样只剩两项可以求并，一个是缺少倒数第二个数，一个是缺少最后一个
            L1 = list(Lk[i])[:k-2]
            L2 = list(Lk[j])[:k-2]
            L1.sort()
            L2.sort()
            if L1==L2: #if first k-2 elements are equal
                retList.append(Lk[i] | Lk[j]) #set union
    return retList

def apriori(dataSet, minSupport = 0.5):
    """
    apriori算法
    dataSet：数据集
    minSupport：感兴趣候选项集的最小支持度
    """
    C1 = createC1(dataSet)
    D = map(set, dataSet)
    L1, supportData = scanD(D, C1, minSupport)
    #L1：长度为1的频繁项
    L = [L1]
    k = 2
    while (len(L[k-2]) > 0):
        #Ck：元素长度为k的候选项集
        Ck = aprioriGen(L[k-2], k)
        #Lk：元素长度为k的频繁项
        Lk, supK = scanD(D, Ck, minSupport)#scan DB to get Lk
        #更新支持度字典
        supportData.update(supK)
        L.append(Lk)
        k += 1
    return L, supportData

def generateRules(L, supportData, minConf=0.7):  #supportData is a dict coming from scanD
    """
    L:频繁项集列表
    supportData:支持度字典
    minConf:最小可信度阈值
    """
    bigRuleList = []
    #从1开始，因为单元素项集无法构建关联规则
    for i in range(1, len(L)):#only get the sets with two or more items
        for freqSet in L[i]:
            H1 = [frozenset([item]) for item in freqSet]
            #频繁项集的元素是否超过2
            if (i > 1):
                rulesFromConseq(freqSet, H1, supportData, bigRuleList, minConf)
            else:
                calcConf(freqSet, H1, supportData, bigRuleList, minConf)
    return bigRuleList

def generateRules2(L, supportData, minConf=0.7):  #supportData is a dict coming from scanD
    """
    L:频繁项集列表
    supportData:支持度字典
    minConf:最小可信度阈值
    """
    bigRuleList = []
    #从1开始，因为单元素项集无法构建关联规则
    for i in range(1, len(L)):#only get the sets with two or more items
        for freqSet in L[i]:
            H1 = [frozenset([item]) for item in freqSet]
            #频繁项集的元素是否超过2
            if (i > 1):
                rulesFromConseq2(freqSet, H1, supportData, bigRuleList, minConf)
            else:
                calcConf(freqSet, H1, supportData, bigRuleList, minConf)
    return bigRuleList  

def calcConf(freqSet, H, supportData, brl, minConf=0.7):
    """
    计算可信度
    freqSet:频繁项 如{1,2}
    H:频繁项子项 [1,2]
    supportData:支持度字典
    brl:保存通过检查的 可信度元组
    minConf:最小可信度阈值
    """
    prunedH = [] #create new list to return
    for conseq in H:
        #计算可信度 P->H support(P|H)/support(P) 这里的H为conseq，P为freqSet-conseq
        conf = supportData[freqSet]/supportData[freqSet-conseq] #calc confidence
        if conf >= minConf: 
            print freqSet-conseq,'-->',conseq,'conf:',conf
            brl.append((freqSet-conseq, conseq, conf))
            prunedH.append(conseq)
    return prunedH


def rulesFromConseq(freqSet, H, supportData, brl, minConf=0.7):
    """
    频繁项元素个数大于2,计算可信度
    freqSet:频繁项 如 frozenset{1,2,3}
    H:频繁项子项 [1,2,3]
    supportData:支持度字典
    brl:保存通过检查的 可信度元组
    minConf:最小可信度阈值
    """
    
    #刚开始m =1(generateRules函数调用)，会递归调用增长m
    m = len(H[0])
    if (len(freqSet) > (m + 1)): #try further merging
        Hmp1 = aprioriGen(H, m+1)#create Hm+1 new candidates
        Hmp1 = calcConf(freqSet, Hmp1, supportData, brl, minConf)
        if (len(Hmp1) > 1):    #need at least two sets to merge
            rulesFromConseq(freqSet, Hmp1, supportData, brl, minConf)

def rulesFromConseq2(freqSet, H, supportData, brl, minConf=0.7):
    """
    修改rulesFromConseq函数，感觉有错
    频繁项元素个数大于2,计算可信度
    freqSet:频繁项 如 frozenset{1,2,3}
    H:频繁项子项 [1,2,3]
    supportData:支持度字典
    brl:保存通过检查的 可信度元组
    minConf:最小可信度阈值
    """
    
    #刚开始m =1(generateRules函数调用)，会递归调用增长m
    m = len(H[0])
    if (len(freqSet) > m): #try further merging
        Hmp1 = calcConf(freqSet, H, supportData, brl, minConf)
        Hmp1 = aprioriGen(Hmp1, m+1)#create Hm+1 new candidates
        #if (len(Hmp1) > 1):    #need at least two sets to merge
        rulesFromConseq2(freqSet, Hmp1, supportData, brl, minConf)
            
def pntRules(ruleList, itemMeaning):
    for ruleTup in ruleList:
        for item in ruleTup[0]:
            print itemMeaning[item]
        print "           -------->"
        for item in ruleTup[1]:
            print itemMeaning[item]
        print "confidence: %f" % ruleTup[2]
        print       #print a blank line
        
            
from time import sleep
#暂时注释下面两行
#from votesmart import votesmart
#votesmart.apikey = 'a7fa40adec6f4a77178799fae4441030'

#votesmart.apikey = 'get your api key first'
def getActionIds():
    actionIdList = []; billTitleList = []
    fr = open('recent20bills.txt') 
    for line in fr.readlines():
        billNum = int(line.split('\t')[0])
        try:
            billDetail = votesmart.votes.getBill(billNum) #api call
            for action in billDetail.actions:
                if action.level == 'House' and \
                (action.stage == 'Passage' or action.stage == 'Amendment Vote'):
                    actionId = int(action.actionId)
                    print 'bill: %d has actionId: %d' % (billNum, actionId)
                    actionIdList.append(actionId)
                    billTitleList.append(line.strip().split('\t')[1])
        except:
            print "problem getting bill %d" % billNum
        sleep(1)                                      #delay to be polite
    return actionIdList, billTitleList
        
def getTransList(actionIdList, billTitleList): #this will return a list of lists containing ints
    itemMeaning = ['Republican', 'Democratic']#list of what each item stands for
    for billTitle in billTitleList:#fill up itemMeaning list
        itemMeaning.append('%s -- Nay' % billTitle)
        itemMeaning.append('%s -- Yea' % billTitle)
    transDict = {}#list of items in each transaction (politician) 
    voteCount = 2
    for actionId in actionIdList:
        sleep(3)
        print 'getting votes for actionId: %d' % actionId
        try:
            voteList = votesmart.votes.getBillActionVotes(actionId)
            for vote in voteList:
                if not transDict.has_key(vote.candidateName): 
                    transDict[vote.candidateName] = []
                    if vote.officeParties == 'Democratic':
                        transDict[vote.candidateName].append(1)
                    elif vote.officeParties == 'Republican':
                        transDict[vote.candidateName].append(0)
                if vote.action == 'Nay':
                    transDict[vote.candidateName].append(voteCount)
                elif vote.action == 'Yea':
                    transDict[vote.candidateName].append(voteCount + 1)
        except: 
            print "problem getting actionId: %d" % actionId
        voteCount += 2
    return transDict, itemMeaning

if __name__ == "__main__":
    dataset = loadDataSet()
    L, supportData = apriori(dataset, minSupport = 0.5)
    #print L
    #print supportData
    generateRules(L, supportData, minConf=0.5)
    print "\n\ngenerateRules2:\n"
    generateRules2(L, supportData, minConf=0.5)
    
    