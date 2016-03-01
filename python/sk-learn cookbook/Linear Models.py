#!/usr/bin/env python
# coding=utf-8



#Fitting a line through data

#First, import the datasets model, then we can load the dataset
import numpy as np
from sklearn import datasets
boston = datasets.load_boston()
boston.data.shape
#(506, 13)
boston.target.shape
#(506,)

#First, import the LinearRegression object and create an object:
from sklearn.linear_model import LinearRegression
lr = LinearRegression()

#it's as easy as passing the independent and dependent variables to
#the fit method of LinearRegression

lr.fit(boston.data, boston.target)
#LinearRegression(copy_X=True, fit_intercept=True, normalize=False)

#Now, to get the predictions, do the following:
predictions = lr.predict(boston.data)

#It's then probably a good idea to look at how close the predictions 
#are to the actual data.
#We can use a histogram to look at the differences. These are called
#the residuals残差

#Let's take a look at the coefficients系数 没有包含常数项w0,
#lr.intercept_ （截距）为常数项:
lr.coef_
#array([ -1.07170557e-01, 4.63952195e-02, 2.08602395e-02,
#2.68856140e+00, -1.77957587e+01, 3.80475246e+00,
#7.51061703e-04, -1.47575880e+00, 3.05655038e-01,
#-1.23293463e-02, -9.53463555e-01, 9.39251272e-03,
#-5.25466633e-01])

#截距
lr.intercept_



#The LinearRegression object can automatically normalize (or scale) the inputs:
lr2 = LinearRegression(normalize=True)
lr2.fit(boston.data, boston.target)
#LinearRegression(copy_X=True, fit_intercept=True, normalize=True)
predictions2 = lr2.predict(boston.data)


#Evaluating评估 the linear regression model

#import matplotlib.pyplot as plt
#f = plt.figure(figsize=(7, 5))
#ax = f.add_subplot(111)
#ax.hist(boston.target - predictions, bins=50)
#ax.set_title("Histogram of Residuals.")
#f.savefig('myfig.png') #保存图片

#Like I mentioned previously, the error terms should be normal, with a mean of 0.
#The residuals残差 are the errors; therefore, this plot should be approximately normal.
#Visually, it's a good fit, though a bit skewed. We can also look at the
#mean of the residuals, which should be very close to 0:
np.mean(boston.target - predictions)
#4.3250427394093058e-15

#Another plot worth looking at is a Q-Q plot. We'll use SciPy here because it has a
#built-in probability plot

#from scipy.stats import probplot
#f = plt.figure(figsize=(7, 5))
#ax = f.add_subplot(111)
#probplot(boston.target - predictions, plot=ax)
#f.savefig('myfig2.png') 


#We can also look at some other metrics度量 of the fit; mean squared error 均方误差(MSE)
#and mean absolute deviation 平均绝对偏差(MAD) are two common metrics. Let's define each
#one in Python and use them. Later in the book, we'll look at how scikit-learn
#has built-in metrics to evaluate the regression models:
def MSE(target, predictions):
    squared_deviation = np.power(target - predictions, 2)
    return np.mean(squared_deviation)
MSE(boston.target, predictions)
#21.897779217687496
def MAD(target, predictions):
    absolute_deviation = np.abs(target - predictions)
    return np.mean(absolute_deviation)
MAD(boston.target, predictions)
#3.2729446379969396

#One thing that's been glossed over a bit is the fact that the coefficients系数
#themselves are random variables, and therefore, they have a distribution.
#Let's use bootstrapping（自举，引导） to look at the distribution of the coefficient for
#the crime rate. Bootstrapping is a very common technique to get an
#understanding of the uncertainty不确定性 of an estimate:
#Bootstrap 非参数统计中一种重要的估计统计量方差进而进行区间估计的统计方法，也称为自助法
#。其核心思想和基本步骤如下：[1] （1）采用重抽样技术从原始样本中抽取一定数量（自己给定）
#的样本，此过程允许重复抽样。 （2）根据抽出的样本计算给定的统计量T。 （3）重复上述N次
#（一般大于1000），得到N个统计量T。 （4）计算上述N个统计量T的样本方差，得到统计量的方差。
n_bootstraps = 1000
len_boston = len(boston.target)
subsample_size = np.int(0.5*len_boston)
#产生subsample_size个随机数（0-len_boston）不重复
subsample = lambda: np.random.choice(np.arange(0, len_boston),
        size=subsample_size)
coefs = np.ones(n_bootstraps) #pre-allocate the space for the coefs
for i in range(n_bootstraps):
    subsample_idx = subsample()
    subsample_X = boston.data[subsample_idx]
    subsample_y = boston.target[subsample_idx]
    lr.fit(subsample_X, subsample_y)
    #LinearRegression(copy_X=True, fit_intercept=True, n_jobs=1, normalize=False)
    coefs[i] = lr.coef_[0]
#Now, we can look at the distribution of the coefficient:
    
#import matplotlib.pyplot as plt
#f = plt.figure(figsize=(7, 5))
#ax = f.add_subplot(111)
#ax.hist(coefs, bins=50)
#ax.set_title("Histogram of the lr.coef_[0].")
#f.savefig('myfig3.png') 

#We might also want to look at the bootstrapped confidence interval:
#percentile计算数组第百分几大的数，0为最小的数，100为最大的数，50为中值
#a=np.percentile(coefs, 100) -> 0.152860288505
#下面两个数为2.5%大的数，和97.5%大的数，也可以说明95%的数分布在这个区间
a=np.percentile(coefs, [2.5, 97.5])
#array([-0.18566145, 0.03142513])


#Using ridge regression to overcome linear regression's shortfalls

#we'll learn about ridge regression岭回归. It is different from vanilla
#linear regression; it introduces a regularization parameter正则化参数 to
#"shrink"收缩 the coefficients. This is useful when the dataset has
#collinear 共线的 factors.


#First,use make_regression to create a simple dataset with three
#predictors, but an effective有效的 rank of 2. Effective rank means
#that while technically the matrix is of full rank满秩, many of the
#columns have a high degree of colinearity同线性:
from sklearn.datasets import make_regression

#样本数为2000，特征数为3， 秩为2,表明有一个特征可以由其他两个特征表示， 10个是噪声样本
reg_data, reg_target = make_regression(n_samples=2000,
n_features=3, effective_rank=2, noise=10)

#First, let's take a look at regular普通的 linear regression:
import numpy as np
n_bootstraps = 1000
len_data = len(reg_data)
subsample_size = np.int(0.75*len_data)
subsample = lambda: np.random.choice(np.arange(0, len_data),
size=subsample_size)

coefs = np.ones((n_bootstraps, 3))
for i in range(n_bootstraps):
    subsample_idx = subsample()
    subsample_X = reg_data[subsample_idx]
    subsample_y = reg_target[subsample_idx]
    lr.fit(subsample_X, subsample_y)
    coefs[i][0] = lr.coef_[0]
    coefs[i][1] = lr.coef_[1]
    coefs[i][2] = lr.coef_[2]

#Follow the same procedure with Ridge, and have a look at the output:
from sklearn.linear_model import Ridge
r = Ridge()
n_bootstraps = 1000
len_data = len(reg_data)
subsample_size = np.int(0.75*len_data)
subsample = lambda: np.random.choice(np.arange(0, len_data),
                        size=subsample_size)
coefs_r = np.ones((n_bootstraps, 3))
for i in range(n_bootstraps):
    subsample_idx = subsample()
    subsample_X = reg_data[subsample_idx]
    subsample_y = reg_target[subsample_idx]
    r.fit(subsample_X, subsample_y)
    coefs_r[i][0] = r.coef_[0]
    coefs_r[i][1] = r.coef_[1]
    coefs_r[i][2] = r.coef_[2]
# carry out the same procedure from above

np.mean(coefs - coefs_r, axis=0)
#coefs_r stores the ridge regression coefficients
#array([ 22.19529525, 49.54961002, 8.27708536])

# variance 方差
np.var(coefs, axis=0)
#array([ 184.50845658, 150.16268077, 263.39096391])
np.var(coefs_r, axis=0)
#array([ 21.35161646, 23.95273241, 17.34020101])

#Optimizing the ridge regression parameter

#Create a regression dataset, and then let's get started:
from sklearn.datasets import make_regression
reg_data, reg_target = make_regression(n_samples=100,
                            n_features=2, effective_rank=1, noise=10)

#In the linear_models module, there is an object called RidgeCV, which
#stands for ridge cross-validation. This performs a cross-validation
#similar to leave-one-out cross-validation (LOOCV).
from sklearn.linear_model import RidgeCV
rcv = RidgeCV(alphas=np.array([.1, .2, .3, .4]))
rcv.fit(reg_data, reg_target)
#RidgeCV(alphas=array([ 0.1, 0.2, 0.3, 0.4]), cv=None,
#fit_intercept=True, gcv_mode=None, loss_func=None,
#normalize=False, score_func=None, scoring=None,
#store_cv_values=False)
rcv.alpha_
#0.10000000000000001
rcv2 = RidgeCV(alphas=np.array([.08, .09, .1, .11, .12]))
rcv2.fit(reg_data, reg_target)
#RidgeCV(alphas=array([ 0.08, 0.09, 0.1 , 0.11, 0.12]), cv=None,
#fit_intercept=True, gcv_mode=None,
#loss_func=None, normalize=False,
#score_func=None, scoring=None,
#store_cv_values=False)
rcv2.alpha_
#0.08
alphas_to_test = np.linspace(0.01, 1)
rcv3 = RidgeCV(alphas=alphas_to_test, store_cv_values=True)
rcv3.fit(reg_data, reg_target)
rcv3.cv_values_.shape
#(100, 50)
smallest_idx = rcv3.cv_values_.mean(axis=0).argmin()
alphas_to_test[smallest_idx]
rcv3.alpha_
#0.01

import sklearn
MAD = sklearn.metrics.make_scorer(MAD, greater_is_better=False)
rcv4 = RidgeCV(alphas=alphas_to_test, store_cv_values=True,
scoring=MAD)
rcv4.fit(reg_data, reg_target)
smallest_idx = rcv4.cv_values_.mean(axis=0).argmin()
print alphas_to_test[smallest_idx]
#0.23223


#Using sparsity 稀疏 to regularize 正规化 models
#The least absolute shrinkage收缩 and selection operator (LASSO) method is very similar
#to ridge regression and LARS（Least-angle regression）. It's similar to Ridge Regression in the sense that we penalize
#our regression by some amount, and it's similar to LARS in that it can be used as a parameter
#selection, and it typically leads to a sparse vector of coefficients.

from sklearn.datasets import make_regression
reg_data, reg_target = make_regression(n_samples=200, n_features=500,
n_informative=5, noise=5)
#Next, we need to import the Lasso object:
from sklearn.linear_model import Lasso
lasso = Lasso()

lasso.fit(reg_data, reg_target)
print np.sum(lasso.coef_ != 0)
#9
lasso_0 = Lasso(0)
lasso_0.fit(reg_data, reg_target)
print np.sum(lasso_0.coef_ != 0)
#500

#Lasso cross-validation
from sklearn.linear_model import LassoCV
lassocv = LassoCV()
lassocv.fit(reg_data, reg_target)

print lassocv.alpha_
#0.380722126078646139

print lassocv.coef_[:5]
#array([0., 42.41, 0.,0., -0.])

print np.sum(lassocv.coef_ != 0)
#11


#Lasso for feature selection
mask = lassocv.coef_ != 0
new_reg_data = reg_data[:, mask]
print new_reg_data.shape
#(200, 11)

#Taking a more fundamental基本的 approach to regularization正则化 with LARS

#Least-angle regression (LARS) is a regression technique that is well suited for 
#high-dimensional problems, that is, p >> n, where p denotes the columns or features 
#and n is the number of samples.

from sklearn.datasets import make_regression
reg_data, reg_target = make_regression(n_samples=200,
                                           n_features=500, n_informative=10, noise=2)
                                           
from sklearn.linear_model import Lars
lars = Lars(n_nonzero_coefs=10)
lars.fit(reg_data, reg_target)
print np.sum(lars.coef_ != 0)
#10

train_n = 100
lars_12 = Lars(n_nonzero_coefs=12)
lars_12.fit(reg_data[:train_n], reg_target[:train_n])
lars_500 = Lars() # it's 500 by default
lars_500.fit(reg_data[:train_n], reg_target[:train_n]);
#Now, to see how well each feature fit the unknown data, do the following:
np.mean(np.power(reg_target[train_n:] - lars_12.predict(reg_data[train_n:]), 2))
#31.527714163321001
np.mean(np.power(reg_target[train_n:] - lars_500.predict(reg_data[train_n:]), 2))
#9.6198147535136237e+30

from sklearn.linear_model import LarsCV
lcv = LarsCV()
lcv.fit(reg_data, reg_target)

print np.sum(lcv.coef_ != 0)
#44


#Using linear methods for classification –logistic regression  逻辑回归

from sklearn.datasets import make_classification
X, y = make_classification(n_samples=1000, n_features=4)

from sklearn.linear_model import LogisticRegression
lr = LogisticRegression()

X_train = X[:-200]
X_test = X[-200:]
y_train = y[:-200]
y_test = y[-200:]

lr.fit(X_train, y_train)
y_train_predictions = lr.predict(X_train)
y_test_predictions = lr.predict(X_test)
(y_train_predictions == y_train).sum().astype(float) / y_train.shape[0]
#0.8662499
(y_test_predictions == y_test).sum().astype(float) / y_test.shape[0]
#0.900000

#There will be a situation where one class is weighted differently from the other classes;两类的样本数差别较大

#样本值为0 占了95%
X, y = make_classification(n_samples=5000, n_features=4, weights=[.95])
sum(y) / (len(y)*1.) #to confirm the class imbalance
#0.0555

X_train = X[:-500]
X_test = X[-500:]
y_train = y[:-500]
y_test = y[-500:]
lr.fit(X_train, y_train)
y_train_predictions = lr.predict(X_train)
y_test_predictions = lr.predict(X_test)
#Now, to see how well our model fits the data, do the following:
print (y_train_predictions == y_train).sum().astype(float) / y_train.shape[0]
#0.96977
print (y_test_predictions == y_test).sum().astype(float) / y_test.shape[0]
# 0.97999

#At first, it looks like we did well, but it turns out that when we always guessed
# that a transaction was not fraud (or class 0 in general) we were right around 95 
# percent of the time. If we look at how well we did in classifying the 1 class, 
# it's not nearly as good: 其实预测的效果不好，特别是样本数少的类
print (y_test[y_test==1] == y_test_predictions[y_test==1]).sum().astype(float) / y_test[y_test==1].shape[0]
#0.583333

#We know that our relative weighting right now is 95 percent nonfraud; 
#let's change this to overweight fraud cases:
lr = LogisticRegression(class_weight={0: .15, 1: .85})
lr.fit(X_train, y_train)
#Let's predict the outputs again:
y_train_predictions = lr.predict(X_train)
y_test_predictions = lr.predict(X_test)
print  (y_test[y_test==1] == y_test_predictions[y_test==1]).sum().astype(float) / y_test[y_test==1].shape[0]
#0.875
#But, at what expense do we do this? To find out, use the following command:
print  (y_test_predictions == y_test).sum().astype(float) / y_test.shape[0]
#0.967999



# Directly applying Bayesian ridge regression 贝叶斯岭回归

from sklearn.datasets import make_regression
X, y = make_regression(1000, 10, n_informative=2, noise=20)
#We can just "throw" ridge regression at the problem with a few simple steps:
from sklearn.linear_model import BayesianRidge
br = BayesianRidge()
br.fit(X, y)
print  br.coef_
#array([0.3000136 , -0.33023408, 68.166673, -0.63228159, 0.07350987,
#-0.90736606, 0.38851709, -0.8085291 , 0.97259451, 68.73538646])

br_alphas = BayesianRidge(alpha_1=10, lambda_1=10)
br_alphas.fit(X, y)
print  br_alphas.coef_
#array([0.30054387, -0.33130025, 68.10432626, -0.63056712,
#0.07751436, -0.90919326, 0.39020878, -0.80822013,
#0.97497567, 68.67409658])


# Using boosting to learn from errors

#Gradient boosting regression is a technique that learns from its mistakes. 
#Essentially, it tries to fit a bunch of weak learners. There are two things to note:
#1 Individually, each learner has poor accuracy, but together they can have very
#good accuracy

#2 They're applied sequentially, which means that each learner becomes an
#expert in the mistakes of the prior learner

#Let's use some basic regression data and see how gradient boosting regression 
#(henceforth, GBR) works:
from sklearn.datasets import make_regression
X, y = make_regression(1000, 2, noise=10)

from sklearn.ensemble import GradientBoostingRegressor as GBR
gbr = GBR()
gbr.fit(X, y)
gbr_preds = gbr.predict(X)

from sklearn.linear_model import LinearRegression
lr = LinearRegression()
lr.fit(X, y)
lr_preds = lr.predict(X)

gbr_residuals = y - gbr_preds
lr_residuals = y - lr_preds

print  np.percentile(gbr_residuals, [2.5, 97.5])
#array([-16.05443674, 17.53946294])
print  np.percentile(lr_residuals, [2.5, 97.5])
#array([-20.05434912, 19.80272884])

n_estimators = np.arange(100, 1100, 350)
gbrs = [GBR(n_estimators=n_estimator) for n_estimator in n_estimators]
residuals = {}
for i, gbr in enumerate(gbrs):
    gbr.fit(X, y)
    residuals[gbr.n_estimators] = y - gbr.predict(X)