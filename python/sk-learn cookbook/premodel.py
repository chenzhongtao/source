#!/usr/bin/env python
# coding=utf-8

from sklearn import datasets
import numpy as np
import sklearn.datasets as d
from sklearn import preprocessing

#小的数据集直接加载
boston = datasets.load_boston()
#In [4]: boston.
#boston.DESCR         boston.items         boston.target
#boston.clear         boston.iteritems     boston.update
#boston.copy          boston.iterkeys      boston.values
#boston.data          boston.itervalues    boston.viewitems
#boston.feature_names boston.keys          boston.viewkeys
#boston.fromkeys      boston.pop           boston.viewvalues
#boston.get           boston.popitem
#boston.has_key       boston.setdefault

#housing = datasets.fetch_california_housing()

#downloading Cal. housing from http://lib.stat.cmu.edu/modules.php?op=modload&nam
#e=Downloads&file=index&req=getit&lid=83 to C:\Users\c01843\scikit_learn_data

datasets.get_data_home()
#Out[8]: 'C:\\Users\\c01843\\scikit_learn_data'

X, y = boston.data, boston.target

datasets.make_biclusters
datasets.make_blobs
datasets.make_checkerboard
datasets.make_circles
datasets.make_classification
#datasets.make_biclusters                datasets.make_friedman3                 datasets.make_s_curve
#datasets.make_blobs                     datasets.make_gaussian_quantiles        datasets.make_sparse_coded_signal
#datasets.make_checkerboard              datasets.make_hastie_10_2               datasets.make_sparse_spd_matrix
#datasets.make_circles                   datasets.make_low_rank_matrix           datasets.make_sparse_uncorrelated
#datasets.make_classification            datasets.make_moons                     datasets.make_spd_matrix
#datasets.make_friedman1                 datasets.make_multilabel_classification datasets.make_swiss_roll
#datasets.make_friedman2                 datasets.make_regression

#创建回归数据
reg_data = d.make_regression()
#this will generate a tuple with a 100 x 100 matrix – 100 samples by 100 features

complex_reg_data = d.make_regression(1000, 10, 5, 2, 1.0)
#this will generate a tuple with a 100 x 100 matrix – 100 samples by 100 features.
#However, by default, only 10 features are responsible for the target data generation. The
#second member of the tuple is the target variable.
complex_reg_data[0].shape


classification_set = d.make_classification(weights=[0.1])
np.bincount(classification_set[1])
#array([10, 90])

blobs = d.make_blobs()


#Continuing with the boston dataset
X[:, :3].mean(axis=0) #mean of the first 3 features 前三个特征的平均值，axis=0 对列求均值，结果剩一行
#array([ 3.59376071, 11.36363636, 11.13677866])
X[:, :3].std(axis=0)  #求标准差
#array([ 8.58828355, 23.29939569, 6.85357058])

#归一化处理
X_2 = preprocessing.scale(X[:, :3])
X_2.mean(axis=0)
#array([ 6.34099712e-17, -6.34319123e-16, -2.68291099e-15])
X_2.std(axis=0)
#array([ 1., 1., 1.])

#It's also useful for the center and scaling class to persist across individual scaling
#跟上面的结果是一样的
my_scaler = preprocessing.StandardScaler()
my_scaler.fit(X[:, :3])
my_scaler.transform(X[:, :3]).mean(axis=0)
#array([ 6.34099712e-17, -6.34319123e-16, -2.68291099e-15])

#Preprocessing also contains a MinMaxScaler class, which will scale the data within a
#certain range:   default of 0 and 1
my_minmax_scaler = preprocessing.MinMaxScaler()
my_minmax_scaler.fit(X[:, :3])
my_minmax_scaler.transform(X[:, :3]).max(axis=0)
#array([ 1., 1., 1.])

#It's very simple to change the minimum and maximum values of the MinMaxScaler class
#from its default of 0 and 1, respectively:
my_odd_scaler = preprocessing.MinMaxScaler(feature_range=(-3.14,3.14))

#StandardScaler是对各个特征进行归一化，normalize是对每个样本进行归一化
#可能会影响某些算法：如 where one sample has the values (1, 1, 0), another has (3, 3,
#0), and the final has (1, 1, 0)，归一化后的结果一样，对计算欧式距离影响很大
normalized_X = preprocessing.normalize(X[:, :3])

#Creating idempotent scalar objects
my_useless_scaler = preprocessing.StandardScaler(with_mean=False,
with_std=False)
transformed_sd = my_useless_scaler.fit_transform(X[:, :3]).std(axis=0)
original_sd = X[:, :3].std(axis=0)
np.array_equal(transformed_sd, original_sd)


#稀疏矩阵的处理
#Handling sparse imputations  
matrix = scipy.sparse.eye(1000)
preprocessing.scale(matrix)
#…
#ValueError: Cannot center sparse matrices: pass 'with_mean=False' instead
#See docstring for motivation and alternatives.


#As noted in the error, it is possible to scale a sparse matrix with_std only:
preprocessing.scale(matrix, with_mean=False)
#<1000x1000 sparse matrix of type '<type 'numpy.float64'>'
#with 1000 stored elements in Compressed Sparse Row format>

#可以转为 一般矩阵，可能会内存不够
#The other option is to call todense() on the array. However, this is dangerous because the
#matrix is already sparse for a reason, and it will potentially cause a memory error.



#根据阈值生成二值特征
#Creating binary features through thresholding
#preprocessing.binarize #(a function)
#ff preprocessing.Binarizer #(a class)

new_target = preprocessing.binarize(boston.target,
threshold=boston.target.mean())
new_target[:5]
#array([ 1., 0., 1., 1., 1.])

(boston.target[:5] > boston.target.mean()).astype(int)
#array([1, 0, 1, 1, 1])

bin = preprocessing.Binarizer(boston.target.mean())
new_target = bin.fit_transform(boston.target)
new_target[:5]
#array([ 1., 0., 1., 1., 1.])


#Sparse matrices
from scipy.sparse import coo
spar = coo.coo_matrix(np.random.binomial(1, .25, 100))
preprocessing.binarize(spar, threshold=-1)
#ValueError: Cannot binarize a sparse matrix with threshold < 0

#Working with categorical类别 variables

iris = datasets.load_iris()
X = iris.data
y = iris.target
#Now, with X and Y being as they normally will be, we'll operate on the data as one:
#把 X，y合成一个矩阵
d = np.column_stack((X, y))

#先跳过一些




#Binarizing label features
from sklearn import datasets as d
iris = d.load_iris()
target = iris.target
from sklearn.preprocessing import LabelBinarizer # 二值化类别，这里是三类 1,0,0  0,1,0  0,0,1
label_binarizer = LabelBinarizer()
new_target = label_binarizer.fit_transform(target)
new_target.shape
#(150, 3)
21
new_target[:5]
#array([[1, 0, 0],
#[1, 0, 0],
#[1, 0, 0],
#[1, 0, 0],
#[1, 0, 0]])
new_target[-5:]
#array([[0, 0, 1],
#[0, 0, 1],
#[0, 0, 1],
#[0, 0, 1],
#[0, 0, 1]])

label_binarizer.classes_
#array([0, 1, 2])


#LabelBinarizer converts the vector N x 1 into the vector N x C, where C is the
#cardinality(c为类别数) of the N x 1 dataset
label_binarizer.transform([4])
#[...]
#ValueError: classes [0 1 2] mismatch with the labels [4] found in the
#data

#指定标号来代替默认的0,1
label_binarizer = LabelBinarizer(neg_label=-1000, pos_label=1000)
label_binarizer.fit_transform(target)[:5]
#array([[ 1000, -1000, -1000],
#[ 1000, -1000, -1000],
#[ 1000, -1000, -1000],
#[ 1000, -1000, -1000],
#[ 1000, -1000, -1000]])

#Imputing估算 missing values through various strategies策略

from sklearn import datasets
import numpy as np
iris = datasets.load_iris()
iris_X = iris.data
masking_array = np.random.binomial(1, .25, iris_X.shape).astype(bool)
iris_X[masking_array] = np.nan
masking_array[:5]
#array([[False, False, False, False],
#[False, False, False, False],
#[False, False, False, False],
#[ True, False, False, False],
#[False, False, False, False]], dtype=bool)
iris_X [:5]
#array([[ 5.1, 3.5, 1.4, 0.2],
#[ 4.9, 3. , 1.4, 0.2],
#[ 4.7, 3.2, 1.3, 0.2],
#[ nan, 3.1, 1.5, 0.2],  #使个别数据丢失
#[ 5. , 3.6, 1.4, 0.2]])

from sklearn import preprocessing
impute = preprocessing.Imputer()
iris_X_prime = impute.fit_transform(iris_X)
iris_X_prime[:5]  #估算数据
#array([[ 5.1 , 3.5 , 1.4 , 0.2 ],
#[ 4.9 , 3. , 1.4 , 0.2 ],
#[ 4.7 , 3.2 , 1.3 , 0.2 ],
#[ 5.87923077, 3.1 , 1.5 , 0.2 ],
#[ 5. , 3.6 , 1.4 , 0.2 ]])

iris_X_prime[3, 0]
#5.87923077
iris_X[3, 0]
#nan

#策略
#mean (default)
#median
#most_frequent (the mode)

#使用中值修复数据
impute = preprocessing.Imputer(strategy='median')
iris_X_prime = impute.fit_transform(iris_X)
iris_X_prime[:5]
#array([[ 5.1, 3.5, 1.4, 0.2],
#[ 4.9, 3. , 1.4, 0.2],
#[ 4.7, 3.2, 1.3, 0.2],
#[ 5.8, 3.1, 1.5, 0.2],
#[ 5. , 3.6, 1.4, 0.2]])

# 把无穷大改为 -1
iris_X[np.isnan(iris_X)] = -1
iris_X[:5]
#array([[ 5.1, 3.5, 1.4, 0.2],
#[ 4.9, 3. , 1.4, 0.2],
#[ 4.7, 3.2, 1.3, 0.2],
#[-1. , 3.1, 1.5, 0.2],
#[ 5. , 3.6, 1.4, 0.2]])

#Filling these in is as simple as the following:
#指定哪些数据是丢失的数据
impute = preprocessing.Imputer(missing_values=-1)
iris_X_prime = impute.fit_transform(iris_X)
iris_X_prime[:5]
#array([[ 5.1 , 3.5 , 1.4 , 0.2 ],
#[ 4.9 , 3. , 1.4 , 0.2 ],
#[ 4.7 , 3.2 , 1.3 , 0.2 ],
#[ 5.87923077, 3.1 , 1.5 , 0.2 ],
#[ 5. , 3.6 , 1.4 , 0.2 ]])


#pandas also provides a functionality to fill missing data. It actually might be a bit more flexible灵活,
#but it is less reusable可重复使用的:

import pandas as pd
iris_X[masking_array] = np.nan
iris_df = pd.DataFrame(iris_X, columns=iris.feature_names)
iris_df.fillna(iris_df.mean())['sepal length (cm)'].head(5)
#0 5.100000
#1 4.900000
#2 4.700000
#3 5.879231
#4 5.000000
#Name: sepal length (cm), dtype: float64

iris_df.fillna(iris_df.max())['sepal length (cm)'].head(5)
#0 5.1
#1 4.9
#2 4.7
#3 7.9
#4 5.0
#Name: sepal length (cm), dtype: float64



#Using Pipelines管道 for multiple preprocessing steps

from sklearn import datasets
import numpy as np
mat = datasets.make_spd_matrix(10)
masking_array = np.random.binomial(1, .1, mat.shape).astype(bool)
#数据丢失
mat[masking_array] = np.nan
mat[:4, :4]
#array([[ 0.56716186, -0.20344151, nan, -0.22579163],
#[ nan, 1.98881836, -2.25445983, 1.27024191],
#[ 0.29327486, -2.25445983, 3.15525425, -1.64685403],
#[-0.22579163, 1.27024191, -1.64685403, 1.32240835]])

# 没使用管道
from sklearn import preprocessing
impute = preprocessing.Imputer()
scaler = preprocessing.StandardScaler()
mat_imputed = impute.fit_transform(mat)
mat_imputed[:4, :4]
#array([[ 0.56716186, -0.20344151, -0.80554023, -0.22579163],
#[ 0.04235695, 1.98881836, -2.25445983, 1.27024191],
#[ 0.29327486, -2.25445983, 3.15525425, -1.64685403],
#[-0.22579163, 1.27024191, -1.64685403, 1.32240835]])
mat_imp_and_scaled = scaler.fit_transform(mat_imputed)
#array([[ 2.235e+00, -6.291e-01, 1.427e-16, -7.496e-01],
#[ 0.000e+00, 1.158e+00, -9.309e-01, 9.072e-01],
#[ 1.068e+00, -2.301e+00, 2.545e+00, -2.323e+00],
#[ -1.142e+00, 5.721e-01, -5.405e-01, 9.650e-01]])

#使用管道
from sklearn import pipeline
pipe = pipeline.Pipeline([('impute', impute), ('scaler', scaler)])
pipe
#Pipeline(steps=[('impute', Imputer(axis=0, copy=True, missing_
#values='NaN', strategy='mean', verbose=0)), ('scalar',
#StandardScaler(copy=True, with_mean=True, with_std=True))])

new_mat = pipe.fit_transform(mat)
new_mat [:4, :4]
#array([[ 2.235e+00, -6.291e-01, 1.427e-16, -7.496e-01],
#[ 0.000e+00, 1.158e+00, -9.309e-01, 9.072e-01],
#[ 1.068e+00, -2.301e+00, 2.545e+00, -2.323e+00],
#[ -1.142e+00, 5.721e-01, -5.405e-01, 9.650e-01]])
np.array_equal(new_mat, mat_imp_and_scaled)
#True

#The important ones that allow Pipelines to function are:
    #fit
    #transform
    #fit_transform (a convenience 方便的 method)
    
# pipe has a method, inverse_transform, However, because the impute step doesn't have an
# inverse_transform method, this method call will fail:  
pipe.inverse_transform(new_mat)
#AttributeError: 'Imputer' object has no attribute 'inverse_transform'

#However, this is possible with the scalar object:
scaler.inverse_transform(new_mat) [:4, :4]
#array([[ 0.567, -0.203, -0.806, -0.226],
#[ 0.042, 1.989, -2.254, 1.27 ],
#[ 0.293, -2.254, 3.155, -1.647],
#[-0.226, 1.27 , -1.647, 1.322]])

#Reducing dimensionality with PCA 使用PCA降维

from sklearn import datasets
iris = datasets.load_iris()
iris_X = iris.data

#First, import the decomposition module:
from sklearn import decomposition
#Next, instantiate a default PCA object:
pca = decomposition.PCA()
pca
PCA(copy=True, n_components=None, whiten=False)
iris_pca = pca.fit_transform(iris_X)
iris_pca[:5]
#array([[ -2.684e+00, -3.266e-01, 2.151e-02, 1.006e-03],
#[ -2.715e+00, 1.696e-01, 2.035e-01, 9.960e-02],
#[ -2.890e+00, 1.373e-01, -2.471e-02, 1.930e-02],
#[ -2.746e+00, 3.111e-01, -3.767e-02, -7.596e-02],
#[ -2.729e+00, -3.339e-01, -9.623e-02, -6.313e-02]])

#Now that the PCA has been fit, we can see how well it has done at explaining the variance
#(explained in the following How it works... section):
pca.explained_variance_ratio_  #各个变量的比率
#array([ 0.925, 0.053, 0.017, 0.005])

#For example, with the iris dataset, 92.5 percent of the variance of the
#overall dataset can be explained by the first component.

pca = decomposition.PCA(n_components=2)
iris_X_prime = pca.fit_transform(iris_X)
iris_X_prime.shape
#(150, 2)
#Our data matrix is now 150 x 2, instead of 150 x 4.

#We can see how much of the variance is represented by the two components that remain:
pca.explained_variance_ratio_.sum()
#0.9776

#The PCA object can also be created with the amount of explained variance in mind from
#the start.
#For example least 98 percent of the variance 98%的能量
pca = decomposition.PCA(n_components=.98)
iris_X_prime = pca.fit(iris_X)
pca.explained_variance_ratio_.sum()
#1.0


#Using factor analysis for decomposition 因子分析降维

#Factor analysis is another technique we can use to reduce dimensionality. However, factor
#analysis makes assumptions and PCA does not. The basic assumption is that there are
#implicit features responsible for the features of the dataset.

from sklearn.decomposition import FactorAnalysis
fa = FactorAnalysis(n_components=2)
iris_two_dim = fa.fit_transform(iris.data)
iris_two_dim[:5]
#array([[-1.33125848, 0.55846779],
#[-1.33914102, -0.00509715],
#[-1.40258715, -0.307983 ],
#[-1.29839497, -0.71854288],
#[-1.33587575, 0.36533259]])


#Kernel PCA for nonlinear dimensionality reduction

#产生非线性数据
import numpy as np
A1_mean = [1, 1]
A1_cov = [[2, .99], [1, 1]]
A1 = np.random.multivariate_normal(A1_mean, A1_cov, 50)
A2_mean = [5, 5]
A2_cov = [[2, .99], [1, 1]]
A2 = np.random.multivariate_normal(A2_mean, A2_cov, 50)
A = np.vstack((A1, A2))
B_mean = [5, 0]
B_cov = [[.5, -1], [-.9, .5]]
B = np.random.multivariate_normal(B_mean, B_cov, 100)

kpca = decomposition.KernelPCA(kernel='cosine', n_components=1)
AB = np.vstack((A, B))
AB_transformed = kpca.fit_transform(AB)


#There are several different kernels available as well as the cosine kernel. You can even write
#your own kernel function. The available kernels are:
    #poly (polynomial)
    #rbf (radial basis function)
    #sigmoid
    #cosine
    #precomputed
     
#A word of caution: kernel methods are great to create separability可分离性, but they can also cause
#overfitting过拟合 if used without care.



#Using truncated截断的 SVD to reduce dimensionality

#Truncated Singular奇异的 Value Decomposition分解 (SVD) is a matrix factorization因子分解 technique that
#factors a matrix M into the three matrices U, Σ, and V. This is very similar to PCA, excepting
#that the factorization for SVD is done on the data matrix, whereas for PCA, the factorization
#is done on the covariance协方差 matrix. Typically, SVD is used under the hood to find the principle
#components of a matrix.

from sklearn.datasets import load_iris
iris = load_iris()
iris_data = iris.data
iris_target = iris.target
from sklearn.decomposition import TruncatedSVD
svd = TruncatedSVD(2)
iris_transformed = svd.fit_transform(iris_data)
iris_data[:5]
#array([[ 5.1, 3.5, 1.4, 0.2],
#[ 4.9, 3. , 1.4, 0.2],
#[ 4.7, 3.2, 1.3, 0.2],
#[ 4.6, 3.1, 1.5, 0.2],
#[ 5. , 3.6, 1.4, 0.2]])
iris_transformed[:5]
#array([[ 5.91220352, -2.30344211],
#[ 5.57207573, -1.97383104],
#[ 5.4464847 , -2.09653267],
#[ 5.43601924, -1.87168085],
#[ 5.87506555, -2.32934799]]


from scipy.linalg import svd
D = np.array([[1, 2], [1, 3], [1, 4]])
D
#array([[1, 2],
#[1, 3],
#[1, 4]])
U, S, V = svd(D, full_matrices=False)
U.shape, S.shape, V.shape
#((3, 2), (2,), (2, 2))

#We can reconstruct the original matrix D to confirm U, S, and V as a decomposition:
# 重组
np.dot(U.dot(np.diag(S)), V)
#array([[1, 2],
#[1, 3],
#[1, 4]])

new_S = S[0]
new_U = U[:, 0]
new_U.dot(new_S)
#array([-2.20719466, -3.16170819, -4.11622173])


tsvd = TruncatedSVD(2)
tsvd.fit(iris_data)
tsvd.transform(iris_data)

#One advantage of TruncatedSVD over PCA is that TruncatedSVD can operate on sparse
#matrices while PCA cannot


#Decomposition分解 to classify分类 with DictionaryLearning

from sklearn.decomposition import DictionaryLearning
dl = DictionaryLearning(3)
transformed = dl.fit_transform(iris_data[::2])
transformed[:5]
#array([[ 0. , 6.34476574, 0. ],
#[ 0. , 5.83576461, 0. ],
#[ 0. , 6.32038375, 0. ],
#[ 0. , 5.89318572, 0. ],
#[ 0. , 5.45222715, 0. ]])

#Next, let's fit (not fit_transform) the testing set:
transformed = dl.transform(iris_data[1::2])


#Putting it all together with Pipelines

#Let's briefly load the iris dataset and seed it with some missing values:
from sklearn.datasets import load_iris
import numpy as np
iris = load_iris()
iris_data = iris.data
mask = np.random.binomial(1, .25, iris_data.shape).astype(bool)
iris_data[mask] = np.nan
iris_data[:5]
#array([[ 5.1, 3.5, 1.4, nan],
#[ nan, 3. , 1.4, 0.2],
#[ 4.7, 3.2, 1.3, 0.2],
#[ 4.6, 3.1, 1.5, 0.2],
#[ 5. , 3.6, nan, 0.2]])

#Let's load the required libraries:
from sklearn import pipeline, preprocessing, decomposition
#Next, create the imputer and PCA classes:
pca = decomposition.PCA()
imputer = preprocessing.Imputer()
#Now that we have the classes we need, we can load them into Pipeline:
pipe = pipeline.Pipeline([('imputer', imputer), ('pca', pca)])
iris_data_transformed = pipe.fit_transform(iris_data)
iris_data_transformed[:5]
#array([[ -2.42e+00, -3.59e-01, -6.88e-01, -3.49e-01],
#[ -2.44e+00, -6.94e-01, 3.27e-01, 4.87e-01],
#[ -2.94e+00, 2.45e-01, -1.85e-03, 4.37e-02],
#[ -2.79e+00, 4.29e-01, -8.05e-03, 9.65e-02],
#[ -6.46e-01, 8.87e-01, 7.54e-01, -5.19e-01]])



pipe2 = pipeline.make_pipeline(imputer, pca)
pipe2.steps
#[('imputer', Imputer(axis=0, copy=True, missing_values='NaN',
#strategy='mean', verbose=0)),
#('pca', PCA(copy=True, n_components=None, whiten=False))]

#This is the same object that was created in the more verbose method:
iris_data_transformed2 = pipe2.fit_transform(iris_data)
iris_data_transformed2[:5]
#array([[ -2.42e+00, -3.59e-01, -6.88e-01, -3.49e-01],
#[ -2.44e+00, -6.94e-01, 3.27e-01, 4.87e-01],
#[ -2.94e+00, 2.45e-01, -1.85e-03, 4.37e-02],
#[ -2.79e+00, 4.29e-01, -8.05e-03, 9.65e-02],
#[ -6.46e-01, 8.87e-01, 7.54e-01, -5.19e-01]])

pipe2.set_params(pca_n_components=2)
#Pipeline(steps=[('imputer', Imputer(axis=0, copy=True,
#missing_values='NaN', strategy='mean', verbose=0)),
#('pca', PCA(copy=True, n_components=2, whiten=False))])

iris_data_transformed3 = pipe2.fit_transform(iris_data)
iris_data_transformed3[:5]
#array([[-2.42, -0.36],
#[-2.44, -0.69],
#[-2.94, 0.24],
#[-2.79, 0.43],
#[-0.65, 0.89]])

#Using Gaussian processes for regression

#In this recipe, we'll use the Gaussian process for regression. In the linear models section,
#we saw how representing prior优先的 information on the coefficients系数 was possible using Bayesian
#Ridge Regression. 贝叶斯岭回归

#So, let's use some regression data and walkthrough how Gaussian processes work in scikit-learn:
from sklearn.datasets import load_boston
boston = load_boston()
boston_X = boston.data
boston_y = boston.target
train_set = np.random.choice([True, False], len(boston_y),
#p=[.75, .25])

#Now that we have the data, we'll create a scikit-learn GaussianProcess object. By default,
#it uses a constant regression常回归 function and squared exponential correlation平方指数相关性, which is one of
#the more common choices:
from sklearn.gaussian_process import GaussianProcess
gp = GaussianProcess()
gp.fit(boston_X[train_set], boston_y[train_set])
#GaussianProcess(beta0=None, corr=<function squared_exponential
#at 0x110809488>, normalize=True,
#nugget=array(2.220446049250313e-15),
#optimizer='fmin_cobyla', random_start=1,
#random_state=<mtrand.RandomState object
#at 0x10b9b58b8>, regr=<function constant
#at 0x1108090c8>, storage_mode='full',
#theta0=array([[ 0.1]]), thetaL=None, thetaU=None,
#verbose=False)

#That's a formidable object definition. The following are a couple of things to point out:
#    beta0: This is the regression weight. This defaults in a way such that MLE最大可能性估量
#          （maximum likelihood estimation） is used for estimation估计.
#    corr: This is the correlation function. There are several built-in correlation functions.
#           We'll look at more of them in the following How it works... section.
#    regr: This is the constant regression function.
#    nugget: This is the regularization parameter. It defaults to a very small number.
#           You can either pass one value to be used for each data point or a single value
#           that needs to be applied uniformly一致的.
#    normalize: This defaults to True, and it will center and scale the features.
#           This would be scale is R.


#Okay, so now that we fit the object, let's look at it's performance against the test object:
test_preds = gp.predict(boston_X[~train_set])

#Let's plot the predicted values versus the actual values; then, because we're doing regression,
#it's probably a good idea to look at plotted residuals and a histogram of the residuals:
from matplotlib import pyplot as plt
f, ax = plt.subplots(figsize=(10, 7), nrows=3)
f.tight_layout()
ax[0].plot(range(len(test_preds)), test_preds,
            label='Predicted Values');
ax[0].plot(range(len(test_preds)), boston_y[~train_set],
            label='Actual Values');
ax[0].set_title("Predicted vs Actuals")
ax[0].legend(loc='best')
ax[1].plot(range(len(test_preds)),
            test_preds - boston_y[~train_set]);
ax[1].set_title("Plotted Residuals")
ax[2].hist(test_preds - boston_y[~train_set]);
ax[2].set_title("Histogram of Residuals")



#First, let's try to understand what's going on with the corr function. This function describes
#the relationship between the different pairs of X. The following five different correlation
#functions are offered by scikit-learn:
    #absolute_exponential
    #squared_exponential
    #generalized_exponential
    #cubic
    #linear
    
    
#Let's use a different regr function, apply a different theta0, and look at how the
#predictions differ:
gp = GaussianProcess(regr='linear', theta0=5e-1)
gp.fit(boston_X[train_set], boston_y[train_set]);
linear_preds = gp.predict(boston_X[~train_set])
f, ax = plt.subplots(figsize=(7, 5))
#Let's have a look at the fit:
f.tight_layout()
ax.hist(test_preds - boston_y[~train_set],
        label='Residuals Original', color='b', alpha=.5);
ax.hist(linear_preds - boston_y[~train_set],
        label='Residuals Linear', color='r', alpha=.5);
ax.set_title("Residuals")
ax.legend(loc='best')

#Clearly, the second model's predictions are slightly better for the most part. If we want to sum
#this up, we can look at the MSE of the predictions:
np.power(test_preds - boston_y[~train_set], 2).mean()
#26.254844099612455
np.power(linear_preds - boston_y[~train_set], 2).mean()
#21.938924337056068

test_preds, MSE = gp.predict(boston_X[~train_set], eval_MSE=True)
MSE[:5]
#array([ 11.95314572, 8.48397825, 6.0287539 , 29.20844347,
#0.36427829])


f, ax = plt.subplots(figsize=(7, 5))
n = 20
rng = range(n)
ax.scatter(rng, test_preds[:n])
ax.errorbar(rng, test_preds[:n], yerr=1.96*MSE[:n])
ax.set_title("Predictions with Error Bars")
ax.set_xlim((-1, 21));


#Defining the Gaussian process object directly

#First, we'll import some basic regression data:
from sklearn.datasets import make_regression
X, y = make_regression(1000, 1, 1)
from sklearn.gaussian_process import regression_models

regression_models.constant(X)[:5]
#array([[ 1.],
#[ 1.],
#[ 1.],
#[ 1.],
#[ 1.]])
regression_models.linear(X)[:1]
#array([[ 1., 0.38833572]])
regression_models.quadratic(X)[:1]
#array([[ 1., 0.38833572, 0.15080463]])

#Using stochastic gradient descent for regression

#Stochastic Gradient Descent 随机梯度下降(SGD) is often an unsung
#hero in machine learning.

#If SGD is good on large datasets, we should probably test
#it on a fairly large dataset:
from sklearn import datasets
X, y = datasets.make_regression(int(1e6))
# Just in case the 1e6 throws you off.
print "{:,}".format(int(1e6))
#1,000,000

print "{:,}".format(X.nbytes)
#800,000,000

#There are roughly 1 million bytes in an MB:
X.nbytes / 1e6
#800.0
#So, the number of bytes per data point is:
X.nbytes / (X.shape[0]*X.shape[1])
#8

#So, now that we have the data, we can simply fit a SGDRegressor model:
from sklearn import linear_model
sgd = linear_model.SGDRegressor()
train = np.random.choice([True, False], size=len(y), p=[.75, .25])
sgd.fit(X[train], y[train])
#SGDRegressor(alpha=0.0001, epsilon=0.1, eta0=0.01,
#fit_intercept=True, l1_ratio=0.15,
#learning_rate='invscaling', loss='squared_loss',
#n_iter=5, penalty='l2', power_t=0.25, random_state=None,
#shuffle=False, verbose=0, warm_start=False)

#The relevant variables are as follows:
    # w: This is the coefficient matrix.
    #learning_rate: This shows how big a step to take at each iteration. This might
    #               be important to tune if you aren't getting a good convergence.
    #gradient: This is the matrix of second derivatives.
    #cost: This is the squared error for regression. We'll see later that this
    #        cost function can be adapted to work with classification tasks.
    #        This flexibility is one thing that makes SGD so useful.