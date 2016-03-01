#!/usr/bin/env python
# coding=utf-8

import numpy as np

>>> x = np.array([[1, 2, 3], [4, 5, 6]], np.int32) #新建一个2*3的数组，指定元素类型
>>> type(x)
<type 'numpy.ndarray'>
>>> x[1,2] # 取第一行第二列的那个元素
>>> type(x[1,2])  # 不是标准的python类型
<type 'numpy.int32'>
6
>>> type(6)    #标准的python
<type 'int'>
>>> y = x[:,1] # y为x的第1列（从0开始数）
>>> y
array([2, 5], dtype=int32)
>>> y[0] = 9 # #这里y并没有重新分配内存，使用的是x的内存，修改y的元素，x同样会修改
>>> y
array([9, 5], dtype=int32)
>>> x
array([[1, 9, 3],
       [4, 5, 6]], dtype=int32)


#Array attributes: Memory layout
>>> x.flags         #Information about the memory layout of the array.  数组的内存设计信息
  C_CONTIGUOUS : True
  F_CONTIGUOUS : False
  OWNDATA : True
  WRITEABLE : True
  ALIGNED : True
  UPDATEIFCOPY : False
>>> x.shape         #Tuple of array dimensions. 数组各个维的长度，这里是2行3列数组
(2, 3)
>>> x.strides       #Tuple of bytes to step in each dimension when traversing an array.#相当于每一维相邻两个元素的地址之差，
                    #x[i,j+1]和x[i,j]相差4，x[i+1,j]和x[i,j]相差12
(12, 4)
>>> x.ndim          #Number of array dimensions. 数组的维度，这里是二维数组
2
>>> x.data          #Python buffer object pointing to the start of the array’s data.
<read-write buffer for 0x2114b10, size 24, offset 0 at 0x22782b0>
>>> x.size          #Number of elements in the array. 数组的元素数目
6
>>> x.itemsize      #Length of one array element in bytes. 每个元素占用多少字节
4
>>> x.nbytes        #Total bytes consumed by the elements of the array. 数组占用的总字节数
24
>>> x.base          #Base object if memory is from some other object. 数组占用的内存是不是其他对象的，如前面 y.bsae 就是 x
>>> y.base
array([[1, 9, 3],
       [4, 5, 6]], dtype=int32)

#Array attributes: Data type
>>> x.dtype     #Data-type of the array’s elements. 数组元素的数据类型
dtype('int32')


#Array attributes: Other attributes

>>> x.T     #Same as self.transpose(), except that self is returned if self.ndim < 2. 数组转置，转置后的数组也是没有重新分配内存 .base 还是x
array([[1, 4],
       [9, 5],
       [3, 6]], dtype=int32)
>>> x.real      #The real part of the array.  #矩阵的实数部分组成一个新的矩阵（重新分配内存）
array([[1, 9, 3],
       [4, 5, 6]], dtype=int32)
>>> x.imag      #The imaginary part of the array. #矩阵的实数部分组成一个新的矩阵（重新分配内存）
array([[0, 0, 0],
       [0, 0, 0]], dtype=int32)
>>> x.flat      #A 1-D iterator over the array. 矩阵一维的迭代对象
<numpy.flatiter object at 0x22b6e10>
>>> x = np.arange(1, 7).reshape(2, 3)
>>> x
array([[1, 2, 3],
       [4, 5, 6]])
>>> x.flat[3]  # 从0数，第三个元素 a.flat相当于把a转成一维的数据
4
>>> type(x.flat[3])
<type 'numpy.int32'>
>>> x.T
array([[1, 4],
       [9, 5],
       [3, 6]], dtype=int32)
>>> x.T.flat[3]
5
>>> x.flat = 3; x   # 全部数据修改
array([[3, 3, 3],
       [3, 3, 3]], dtype=int32)
>>> x.flat[[1,4]] = 1; x   #第1和第4个数据修改
array([[3, 1, 3],
       [3, 1, 3]], dtype=int32)



>>> x.ctypes    #An object to simplify the interaction of the array with the ctypes module.
<numpy.core._internal._ctypes object at 0x2278310>

#Array method:Array conversion

ndarray.item(*args)	#Copy an element of an array to a standard Python scalar and return it.
                    #返回的python标准类型的元素值
                    #当数组只有一个元素是，参数可以为空

>>> x.item(4)       #当参数为一个整数是，把数组看成一维的，类似于x.flat[i]，返回第四个元素
1
>>> type(x.item(4))
<type 'int'>
>>> x.item((1,1))   #当参数为一个元组时，看成行列的，这里和上面是同一个数
1

ndarray.tolist()	#Return the array as a (possibly nested 嵌套) list.
                    #把数组转换成列表

>>> a = np.array([1, 2])
>>> a.tolist()
[1, 2]
>>> a = np.array([[1, 2], [3, 4]])
>>> list(a)
[array([1, 2]), array([3, 4])]
>>> a.tolist()
[[1, 2], [3, 4]]


ndarray.itemset(*args)	#Insert scalar into an array (scalar is cast to array’s dtype, if possible)
                        # 与item类似，item是返回值，这里是修改值
>>> x = np.random.randint(9, size=(3, 3))
>>> x
array([[3, 1, 7],
       [2, 8, 3],
       [8, 5, 3]])
>>> x.itemset(4, 0)  # 把第四个元素修改为0 相当于x.flat[4] = 0
>>> x.itemset((2, 2), 9) #相当于 x[2,2] = 9
>>> x
array([[3, 1, 7],
       [2, 0, 3],
       [8, 5, 9]])

ndarray.setasflat	
ndarray.tostring([order])	#Construct Python bytes containing the raw data bytes in the array.
                            #把数组按照内存的数据转换成字符串类型
>>> x = np.array([[0, 1], [2, 3]], np.int32)
>>> x.tostring("C") # c语言风格的，按行存储
'\x00\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00'
>>> x.tostring("F") # Fortran风格的，按列存储
'\x00\x00\x00\x00\x02\x00\x00\x00\x01\x00\x00\x00\x03\x00\x00\x00'
ndarray.tobytes([order])	#Construct Python bytes containing the raw data bytes in the array.
                            #跟 ndarray.tostring 一样
ndarray.tofile(fid[, sep, format])	Write array to a file as text or binary (default).
                                    #
ndarray.dump(file)	Dump a pickle of the array to the specified file.
ndarray.dumps()	Returns the pickle of the array as a string.
ndarray.astype(dtype[, order, casting, ...])	Copy of the array, cast to a specified type.
ndarray.byteswap(inplace)	Swap the bytes of the array elements
ndarray.copy([order])	Return a copy of the array.
ndarray.view([dtype, type])	New view of array with the same data.
ndarray.getfield(dtype[, offset])	Returns a field of the given array as a certain type.
ndarray.setflags([write, align, uic])	Set array flags WRITEABLE, ALIGNED, and UPDATEIFCOPY, respectively.
ndarray.fill(value)	Fill the array with a scalar value.