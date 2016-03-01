#!/usr/bin/env python
# coding=utf-8

import numpy as np

>>> x = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
>>> x[1:7:2] # 基本切片语法是 i:j:k ，i为起始位，j为结束位，k为步长（不为0），默认为1    i<= index< j (切片不包含j这个结束位)
array([1, 3, 5])  # 不包含 7

>>> x[1:111:2]   # 不会报越界
array([1, 3, 5, 7, 9])

>>> x[::]   #全部使用默认值，i默认为0 ， j默认为len(x)，k默认为1
array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])


>>> x[-2:10]  # -1为最后一个，-2为倒数第二个，-3... 
array([8, 9])

>>> x[-3:3:-1] # 步长可以为负数，此时 i > j
array([7, 6, 5, 4])

>>> x[::-1]  # 调换数组的次序
array([9, 8, 7, 6, 5, 4, 3, 2, 1, 0])

>>> x[5:]   #起始位为5，其他使用默认值
array([5, 6, 7, 8, 9])


>>> a=[1,2,3] #普通列表
>>> a[1] #取出元素
2
>>> a[1:2] #切片操作之后即使只有一个元素，也还是列表
[2]

>>> x = np.array([[[1],[2],[3]], [[4],[5],[6]]])  # 2*3*1的三维数组
>>> x.shape
(2, 3, 1)
>>> x[1:2] #取第一维的第二行，其他维不变 变成 1*3*1 ，维度数不变
array([[[4],
        [5],
        [6]]])
>>> x[1:2].shape
(1, 3, 1)

>>> x[1,:,:] #维度数变为2，因为第一个不是切片操作
array([[4],
       [5],
       [6]])
>>> x[1,:,:].shape
(3, 1)

>>> x[...,0] #维度数变为2，因为最后一个不是切片操作
array([[1, 2, 3],
       [4, 5, 6]])

>>> x.ndim  # 维度为3 
3

x[:,np.newaxis,:,:].shape   #插入新的一维
(2, 1, 3, 1)

>>> x[:,np.newaxis,:,:].ndim  # 维数变为4
4

>>> x.reshape(2,1,3,1)  #也可以这样修改维数 = x[:,np.newaxis,:,:]
array([[[[1],
         [2],
         [3]]],


       [[[4],
         [5],
         [6]]]])

x = np.array([[1, 2], [3, 4], [5, 6]])


>>> x[1]   # 取第一行
array([3, 4])
>>> x[1,1] # 取第一行第一列的元素
4
>>> x[:,1] # 取第一列
array([2, 4, 6])
>>>
>>> x[[0,1,1]] #取第0行，1行，1行
array([[1, 2],
       [3, 4],
       [3, 4]])
>>> x[[0, 1, 2], [0, 1, 0]]  #取0
array([1, 4, 5])
>>> x[1,1]  #注意下面和这个的区别
4
>>> x[[1],[1]]
array([4])

>>> x = np.array([[ 0,  1,  2],
                [ 3,  4,  5],
                [ 6,  7,  8],
                [ 9, 10, 11]])
>>> rows = np.array([[0, 0],
                   [3, 3]], dtype=np.intp)
>>> columns = np.array([[0, 2],
                    [0, 2]], dtype=np.intp)
>>> x[rows, columns] # x[[[[0, 0],[3, 3]],[[0, 2],[0, 2]]]]
array([[ 0,  2],
       [ 9, 11]])

rows = np.array([0, 3], dtype=np.intp)
columns = np.array([0, 2], dtype=np.intp)
rows[:, np.newaxis]
x[rows, columns]
x[rows[:, np.newaxis], columns]

>>> rows = np.array([0, 3], dtype=np.intp)
>>> columns = np.array([0, 2], dtype=np.intp)
>>> rows[:, np.newaxis] # 改成2*1数组
array([[0],
       [3]])
>>> x[rows, columns] #取x[0,0],x[3,3]
array([ 0, 11])
>>> x[rows[:, np.newaxis], columns] #取x[0,0],x[0,3],x[3,0],x[3,3]
array([[ 0,  2],
       [ 9, 11]])

>>> x[np.ix_(rows, columns)]
array([[ 0,  2],
       [ 9, 11]])

>>> x[1:2, 1:3]
array([[4, 5]])
>>> x[1:2, [1, 2]]
array([[4, 5]])

>>> x[1:2, 1]
array([4])
>>> x[1:2, 1:2]
array([[4]])

>>> x = np.array([[1., 2.], [np.nan, 3.], [np.nan, np.nan]])
>>> x
array([[  1.,   2.],
       [ NaN,   3.],
       [ NaN,  NaN]])
>>> ~np.isnan(x)   # 布尔数组
array([[ True,  True],
       [False,  True],
       [False, False]], dtype=bool)
>>> x[~np.isnan(x)] # 使用布尔数组取出对应的元素
array([ 1.,  2.,  3.])


>>> x = np.array([1., -1., -2., 3])
>>> x[x < 0] += 20  # 数组中所有小于0的元素都加上20
>>> x
array([  1.,  19.,  18.,   3.])

>>> x = np.array([[0, 1], [1, 1], [2, 2]])
>>> x.sum() #所有元素之和
+7
>>> x.sum(-1) #按行求和
array([1, 2, 4])
>>> x.sum(-2) #按列求和
array([3, 4])

>>> rowsum = x.sum(-1)
>>> x[rowsum <= 2, :]  #按行求和小于等于2的行
array([[0, 1],
       [1, 1]])

>>> x = np.array([[ 0,  1,  2],
                [ 3,  4,  5],
                [ 6,  7,  8],
                [ 9, 10, 11]])
>>> rows = (x.sum(-1) % 2) == 0
>>> rows
array([False,  True, False,  True], dtype=bool)
>>> columns = [0, 2]
>>> x[np.ix_(rows, columns)]
array([[ 3,  5],
       [ 9, 11]])

>>> rows.nonzero()
(array([1, 3]),)
>>> rows.nonzero()[0]
array([1, 3])

>>> rows = rows.nonzero()[0]
>>> x[rows[:, np.newaxis], columns]
array([[ 3,  5],
       [ 9, 11]])



