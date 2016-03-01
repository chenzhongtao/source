#!/usr/bin/env python
# coding=utf-8

#Postmodel Workflw工作流程

#K-fold cross validation k-fold交叉验证,k折交叉验证

N = 1000
holdout = 200
from sklearn.datasets import make_regression
X, y = make_regression(1000, shuffle=True) #shuffle 搅乱

#Now that we have the data, let's hold out 200 points, and then go through the
# fold scheme like we normally would:
X_h, y_h = X[:holdout], y[:holdout]
X_t, y_t = X[holdout:], y[holdout:]
from sklearn.cross_validation import KFold

#Let's create the cross validation object:
kfold = KFold(len(y_t), n_folds=4)
#Now, we can iterate through the k-fold object:
output_string = "Fold: {}, N_train: {}, N_test: {}"
for i, (train, test) in enumerate(kfold):
    print output_string.format(i, len(y_t[train]), len(y_t[test]))
#Fold: 0, N_train: 600, N_test: 200
#Fold: 1, N_train: 600, N_test: 200
#Fold: 2, N_train: 600, N_test: 200
#Fold: 3, N_train: 600, N_test: 200
    
#It's probably clear, but k-fold works by iterating through the folds and holds 
#out 1/n_folds * N, where N for us was len(y_t) .
    
import numpy as np
import pandas as pd
patients = np.repeat(np.arange(0, 100, dtype=np.int8), 8)
measurements = pd.DataFrame({'patient_id': patients,
                                 'ys': np.random.normal(0, 1, 800)})
 
# Now that we have the data, we only want to hold out certain customers 
# instead of data points:
custids = np.unique(measurements.patient_id)
customer_kfold = KFold(custids.size, n_folds=4)
output_string = "Fold: {}, N_train: {}, N_test: {}"
for i, (train, test) in enumerate(customer_kfold):
     train_cust_ids = custids[train]
     training = measurements[measurements.patient_id.isin(
     train_cust_ids)]
     testing = measurements[~measurements.patient_id.isin(
     train_cust_ids)]
     print output_string.format(i, len(training), len(testing))
#Fold: 0, N_train: 600, N_test: 200
#Fold: 1, N_train: 600, N_test: 200
#Fold: 2, N_train: 600, N_test: 200
#Fold: 3, N_train: 600, N_test: 200
     
     
     
     
     
     
#Automatic cross validation
     
#First import the ensemble module and we'll get started:
from sklearn import ensemble
rf = ensemble.RandomForestRegressor(max_features='auto')
#Okay, so now, let's create some regression data:
from sklearn import datasets
X, y = datasets.make_regression(10000, 10)
#Now that we have the data, we can import the cross_validation module and get 
#access to the functions we'll use:
from sklearn import cross_validation
scores = cross_validation.cross_val_score(rf, X, y)
print scores
#[ 0.86823874 0.86763225 0.86986129]     
     
scores = cross_validation.cross_val_score(rf, X, y, verbose=3, cv=4)
#[CV] no parameters to be set
#[CV] no parameters to be set, score=0.872866 - 0.7s
#[CV] no parameters to be set
#[CV] no parameters to be set, score=0.873679 - 0.6s
#[CV] no parameters to be set
#[CV] no parameters to be set, score=0.878018 - 0.7s
#[CV] no parameters to be set
#[CV] no parameters to be set, score=0.871598 - 0.6s
#[Parallel(n_jobs=1)]: Done 1 jobs | elapsed: 0.7s
#[Parallel(n_jobs=1)]: Done 4 out of 4 | elapsed: 2.6s finished      
     
    
    
    
#Cross validation with ShufflSplit
     
import numpy as np
true_loc = 1000
true_scale = 10
N = 1000
dataset = np.random.normal(true_loc, true_scale, N)
import matplotlib.pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
ax.hist(dataset, color='k', alpha=.65, histtype='stepfilled');
ax.set_title("Histogram of dataset");
f.savefig("978-1-78398-948-5_06_06.png")

#Now, let's take the fist half of the data and guess the mean:
from sklearn import cross_validation
holdout_set = dataset[:500]
fitting_set = dataset[500:]
estimate = fitting_set[:N/2].mean()
import matplotlib.pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
ax.set_title("True Mean vs Regular Estimate")
ax.vlines(true_loc, 0, 1, color='r', linestyles='-', lw=5,
              alpha=.65, label='true mean')
ax.vlines(estimate, 0, 1, color='g', linestyles='-', lw=5,
              alpha=.65, label='regular estimate')
ax.set_xlim(999, 1001)
ax.legend()
f.savefig("978-1-78398-948-5_06_07.png")

#Now, we can use ShufflSplit to fi the estimator on several smaller datasets:
from sklearn.cross_validation import ShuffleSplit
shuffle_split = ShuffleSplit(len(fitting_set))
mean_p = []
for train, _ in shuffle_split:
     mean_p.append(fitting_set[train].mean())
     shuf_estimate = np.mean(mean_p)
import matplotlib.pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
ax.vlines(true_loc, 0, 1, color='r', linestyles='-', lw=5,
              alpha=.65, label='true mean')
ax.vlines(estimate, 0, 1, color='g', linestyles='-', lw=5,
              alpha=.65, label='regular estimate')
ax.vlines(shuf_estimate, 0, 1, color='b', linestyles='-', lw=5,
              alpha=.65, label='shufflesplit estimate')
ax.set_title("All Estimates")
ax.set_xlim(999, 1001)
ax.legend(loc=3)


#Stratified 分层的 k-fold
from sklearn import datasets
X, y = datasets.make_classification(n_samples=int(1e3),
                                        weights=[1./11])
#Let's check the overall class weight distribution:
print y.mean()
#0.90300000000000002

from sklearn import cross_validation
n_folds = 50
strat_kfold = cross_validation.StratifiedKFold(y,
                                                   n_folds=n_folds)
shuff_split = cross_validation.ShuffleSplit(n=len(y),
                                                n_iter=n_folds)
kfold_y_props = []
shuff_y_props = []
for (k_train, k_test), (s_train, s_test) in zip(strat_kfold,
                                                    shuff_split):
     kfold_y_props.append(y[k_train].mean())
     shuff_y_props.append(y[s_train].mean())
#Now, let's plot the proportions over each fold:
import matplotlib.pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
ax.plot(range(n_folds), shuff_y_props, label="ShuffleSplit",
            color='k')
ax.plot(range(n_folds), kfold_y_props, label="Stratified",
            color='k', ls='--')
ax.set_title("Comparing class proportions.")
ax.legend(loc='best')





import numpy as np
three_classes = np.random.choice([1,2,3], p=[.1, .4, .5],
                                     size=1000)
import itertools as it
for train, test in cross_validation.StratifiedKFold(three_classes, 5):
    print np.bincount(three_classes[train])
#[ 0 90 314 395]
#[ 0 90 314 395]
#[ 0 90 314 395]
#[ 0 91 315 395]
#[ 0 91 315 396]



#Poor man's grid search

#Let's create the dataset and then get started:
from sklearn import datasets
X, y = datasets.make_classification(n_samples=2000, n_features=10)

#Earlier we said that we'd use grid search to tune two parameters—criteria 
#and max_features. We need to represent those as Python sets, and then use 
#itertools product to iterate through them:
criteria = {'gini', 'entropy'}
max_features = {'auto', 'log2', None}
import itertools as it
parameter_space = it.product(criteria, max_features)

import numpy as np
train_set = np.random.choice([True, False], size=len(y))
from sklearn.tree import DecisionTreeClassifier
accuracies = {}
for criterion, max_feature in parameter_space:
    dt = DecisionTreeClassifier(criterion=criterion,
                                max_features=max_feature)
    dt.fit(X[train_set], y[train_set])
    accuracies[(criterion, max_feature)] = (dt.predict(X[~train_set])
                                            == y[~train_set]).mean()
print accuracies
#{('entropy', None): 0.974609375, ('entropy', 'auto'): 0.9736328125,
#('entropy', 'log2'): 0.962890625, ('gini', None): 0.9677734375, ('gini',
#'auto'): 0.9638671875, ('gini', 'log2'): 0.96875}

#So we now have the accuracies and its performance. Let's visualize the 
#performance:
from matplotlib import pyplot as plt
from matplotlib import cm
cmap = cm.RdBu_r
f, ax = plt.subplots(figsize=(7, 4))
ax.set_xticklabels([''] + list(criteria))
ax.set_yticklabels([''] + list(max_features))
plot_array = []
for max_feature in max_features:
    m = []
    for criterion in criteria:
        m.append(accuracies[(criterion, max_feature)])
        plot_array.append(m)
colors = ax.matshow(plot_array, vmin=np.min(accuracies.values()) -
             0.001, vmax=np.max(accuracies.values()) + 0.001, cmap=cmap)
f.colorbar(colors)


#Brute force grid search














































     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
 