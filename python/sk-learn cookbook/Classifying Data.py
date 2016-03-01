#!/usr/bin/env python
# coding=utf-8

#Doing basic classifications with Decision Trees决策树

from sklearn import datasets
X, y = datasets.make_classification(n_samples=1000, n_features=3, n_redundant=0)

from sklearn.tree import DecisionTreeClassifier
dt = DecisionTreeClassifier()
dt.fit(X, y)
#DecisionTreeClassifier(compute_importances=None, criterion='gini',
#max_depth=None, max_features=None,
#max_leaf_nodes=None, min_density=None,
#min_samples_leaf=1, min_samples_split=2,
#random_state=None, splitter='best')
preds = dt.predict(X)
(y == preds).mean()
#1.0

#The first detail we'll look at is max_depth. This is an important parameter. It determines how
#many branches are allowed. This is important because a Decision Tree can have a hard time
#generalizing out-of-sampled data with some sort of regularization. Later, we'll see how we
#can use several shallow Decision Trees to make a better learner. Let's create a more complex
#dataset and see what happens when we allow different max_depth. We'll use this dataset for
#the rest of the recipe

n_features=200
X, y = datasets.make_classification(750, n_features, n_informative=5)

import numpy as np
training = np.random.choice([True, False], p=[.75, .25], size=len(y))

accuracies = []
for x in np.arange(1, n_features+1):
    dt = DecisionTreeClassifier(max_depth=x)
    dt.fit(X[training], y[training])
    preds = dt.predict(X[~training])
    accuracies.append((preds == y[~training]).mean())
import matplotlib.pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
ax.plot(range(1, n_features+1), accuracies, color='k')
ax.set_title("Decision Tree Accuracy")
ax.set_ylabel("% Correct")
ax.set_xlabel("Max Depth")

N = 15
import matplotlib.pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
ax.plot(range(1, n_features+1)[:N], accuracies[:N], color='k')
ax.set_title("Decision Tree Accuracy")
ax.set_ylabel("% Correct")
ax.set_xlabel("Max Depth")

dt_ci = DecisionTreeClassifier(compute_importances=True)
dt.fit(X, y)

#plot the importances
ne0 = dt.feature_importances_ != 0

y_comp = dt.feature_importances_[ne0]
x_comp = np.arange(len(dt.feature_importances_))[ne0]

import matplotlib.pyplot as plt

f, ax = plt.subplots(figsize=(7, 5))
ax.bar(x_comp, y_comp)

#Tuning a Decision Tree model

from sklearn import datasets
X, y = datasets.make_classification(1000, 20, n_informative=3)

from sklearn.tree import DecisionTreeClassifier
dt = DecisionTreeClassifier()
dt.fit(X, y)

#Ok, so now that we have a basic classifier fit, we can view it quite simply:

from StringIO import StringIO
from sklearn import tree
import pydot

str_buffer = StringIO()
tree.export_graphviz(dt, out_file=str_buffer)
graph = pydot.graph_from_dot_data(str_buffer.getvalue())
graph.write("myfile.jpg")

#This is a very complex tree. It will most likely overfit the data. First, 
#let's reduce the max depth value:
dt = DecisionTreeClassifier(max_depth=5)
dt.fit(X, y);

dt = DecisionTreeClassifier(max_depth=5).fit(X, y)

def plot_dt(model, filename):
    str_buffer = StringIO()
tree.export_graphviz(model, out_file=str_buffer)

graph = pydot.graph_from_dot_data(str_buffer.getvalue())
graph.write_jpg(filename)

plot_dt(dt, "myfile.png")

dt = DecisionTreeClassifier(criterion='entropy',
                                max_depth=5).fit(X, y)
plot(dt, "entropy.png")

dt = DecisionTreeClassifier(min_samples_leaf=10,
                                criterion='entropy',
                                max_depth=5).fit(X, y)
  

                              
#Using many Decision Trees – random forests
 
from sklearn import datasets
#Then, create the dataset with 1,000 samples:
X, y = datasets.make_classification(1000)
#Now that we have the data, we can create a classifier object and train it:
from sklearn.ensemble import RandomForestClassifier
rf = RandomForestClassifier()
rf.fit(X, y)                             
                              
print "Accuracy:\t", (y == rf.predict(X)).mean()
#Accuracy: 0.993
print "Total Correct:\t", (y == rf.predict(X)).sum()
#Total Correct: 993
 
#First, we'll look at some of the useful attributes; in this case, since we 
#used defaults, they'll be the object defaults:
 
    #rf.criterion: This is the criterion for how the splits are determined. 
    #        The default is gini.
    #rf.bootstrap: A Boolean that indicates whether we used bootstrap samples 
    #       when training random forest.
    #rf.n_jobs: The number of jobs to train and predict. If you want to use all
    #       the processors, set this to -1. Keep in mind that if your dataset 
    #       isn't very big, it often leads to more overhead in using multiple 
    #       jobs due to the data having to be serialized and moved in between 
    #       processes.
    #rf.max_features: This denotes the number of features to consider when 
    #        making the best split. This will come in handy during the tuning
    #        process.
    #rf.compute_importances: This helps us decide whether to compute the
    #       importance of the features. See the There's more... section of 
    #       this recipe for information on how to use this.
    #rf.max_depth: This denotes how deep each tree can go.                             


probs = rf.predict_proba(X)
import pandas as pd
probs_df = pd.DataFrame(probs, columns=['0', '1'])
probs_df['was_correct'] = rf.predict(X) == y
import matplotlib.pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
probs_df.groupby('0').was_correct.mean().plot(kind='bar', ax=ax)
ax.set_title("Accuracy at 0 class probability")
ax.set_ylabel("% Correct")
ax.set_xlabel("% trees for 0")

#If we want to calculate the feature importance, we need to state it when we create the object.
rf = RandomForestClassifier(compute_importances=True)
rf.fit(X, y)
f, ax = plt.subplots(figsize=(7, 5))
ax.bar(range(len(rf.feature_importances_)),
           rf.feature_importances_)
ax.set_title("Feature Importances")




#Tuning a random forest model



from sklearn import datasets
X, y = datasets.make_classification(n_samples=10000,
                                        n_features=20,
                                        n_informative=15,
                                        flip_y=.5, weights=[.2, .8])                              
                              
import numpy as np
training = np.random.choice([True, False], p=[.8, .2],
size=y.shape)
from sklearn.ensemble import RandomForestClassifier
rf = RandomForestClassifier()
rf.fit(X[training], y[training])
preds = rf.predict(X[~training])
print "Accuracy:\t", (preds == y[~training]).mean()
#Accuracy: 0.652239557121                              
                              
from sklearn.metrics import confusion_matrix #混淆矩阵
max_feature_params = ['auto', 'sqrt', 'log2', .01, .5, .99]
confusion_matrixes = {}
for max_feature in max_feature_params:
    rf = RandomForestClassifier(max_features=max_feature)   
    rf.fit(X[training], y[training])                                                     
    confusion_matrixes[max_feature] = confusion_matrix(y[~training])
    rf.predict(X[~training])).ravel()
                              
#Since I used the ravel method, our 2D confusion matrices are now 1D.
#Now, import pandas and look at the confusion matrix we just created:
import pandas as pd
confusion_df = pd.DataFrame(confusion_matrixes)
import itertools
from matplotlib import pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
confusion_df.plot(kind='bar', ax=ax)
ax.legend(loc='best')
ax.set_title("Guessed vs Correct (i, j) where i is the guess and j is the actual.")
ax.grid()
ax.set_xticklabels([str((i, j)) for i, j in
                        list(itertools.product(range(2), range(2)))]);
ax.set_xlabel("Guessed vs Correct")
ax.set_ylabel("Correct")   


n_estimator_params = range(1, 20)
confusion_matrixes = {}
for n_estimator in n_estimator_params:
    rf = RandomForestClassifier(n_estimators=n_estimator)
    rf.fit(X[training], y[training])
    confusion_matrixes[n_estimator] = confusion_matrix(y[~training],
                                                rf.predict(X[~training])) 

# here's where we'll update the confusion matrix with the
#operation we talked about
accuracy = lambda x: np.trace(x) / np.sum(x, dtype=float)
confusion_matrixes[n_estimator] = accuracy(confusion_matrixes[n_estimator])
accuracy_series = pd.Series(confusion_matrixes)
import itertools
from matplotlib import pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
accuracy_series.plot(kind='bar', ax=ax, color='k', alpha=.75)
ax.grid()
ax.set_title("Accuracy by Number of Estimators")
ax.set_ylim(0, 1) # we want the full scope
ax.set_ylabel("Accuracy")
ax.set_xlabel("Number of Estimators")                                                
                                                
                                                
rf = RandomForestClassifier(n_jobs=4, verbose=True)
rf.fit(X, y)
#[Parallel(n_jobs=4)]: Done 1 out of 4 | elapsed: 0.3s remaining: 0.9s
#[Parallel(n_jobs=4)]: Done 4 out of 4 | elapsed: 0.3s finished
#This will also predict in parallel (verbosely):
rf.predict(X)
#[Parallel(n_jobs=4)]: Done 1 out of 4 | elapsed: 0.0s remaining:
#0.0s
#[Parallel(n_jobs=4)]: Done 4 out of 4 | elapsed: 0.0s finished
#array([1, 1, 0, ..., 1, 1, 1])                                                
                                                
  
                                              
#Classifying data with support vector machines                                                
from sklearn import datasets
X, y = datasets.make_classification() 
                                              
from sklearn.svm import SVC
base_svm = SVC()
base_svm.fit(X, y)

#Let's look at some of the attributes:

    #C: In cases where we don't have a well-separated set, C will scale the error on the
    #margin. As C gets higher, the penalization for the error becomes larger and the SVM
    #will try to find a narrow margin even if it misclassifies more points.
    
    #class_weight: This denotes how much weight to give to each class in the problem.
    #This is given as a dictionary where classes are the keys and values are the weights
    #associated with these classes.
    
    #gamma: This is the gamma parameter for kernels and is supported by rgb, sigmoid,
    #and ploy.
    
    #kernel: This is the kernel to use; we'll use linear in the following How it works...
    #section, but rgb is the popular and default choice.

#First, let's fit the dataset, and then we'll plot what's going on:
X, y = datasets.make_blobs(n_features=2, centers=2)
from sklearn.svm import LinearSVC
svm = LinearSVC()
svm.fit(X, y)


#Now that we've fi the support vector machine, we'll plot its outcome at each 
#point in the graph. This will show us the approximate decision boundary:
from itertools import product
from collections import namedtuple
Point = namedtuple('Point', ['x', 'y', 'outcome'])
decision_boundary = []
xmin, xmax = np.percentile(X[:, 0], [0, 100])
ymin, ymax = np.percentile(X[:, 1], [0, 100])
for xpt, ypt in product(np.linspace(xmin-2.5, xmax+2.5, 20),
                        np.linspace(ymin-2.5, ymax+2.5, 20)):
     p = Point(xpt, ypt, svm.predict([xpt, ypt]))
     decision_boundary.append(p)
import matplotlib.pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
import numpy as np
colors = np.array(['r', 'b'])
for xpt, ypt, pt in decision_boundary:
     ax.scatter(xpt, ypt, color=colors[pt[0]], alpha=.15)
     ax.scatter(X[:, 0], X[:, 1], color=colors[y], s=30)
     ax.set_ylim(ymin, ymax)
     ax.set_xlim(xmin, xmax)
     ax.set_title("A well separated dataset")

#Let's look at another example, but this time the decision boundary will not 
#be so clear:
X, y = datasets.make_classification(n_features=2,
                                         n_classes=2,
                                         n_informative=2,
                                         n_redundant=0)

#As we can see, this is not a problem that will easily be solved by a linear
# classifiation rule.

#While we will not use this in practice, let's have a look at the decision 
#boundary. First, let's retrain the classifir with the new datapoints:

svm.fit(X, y)
xmin, xmax = np.percentile(X[:, 0], [0, 100])
ymin, ymax = np.percentile(X[:, 1], [0, 100])
test_points = np.array([[xx, yy] for xx, yy in
                             product(np.linspace(xmin, xmax),
                             np.linspace(ymin, ymax))])
test_preds = svm.predict(test_points)

import matplotlib.pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
import numpy as np
colors = np.array(['r', 'b'])
ax.scatter(test_points[:, 0], test_points[:, 1],
               color=colors[test_preds], alpha=.25)
ax.scatter(X[:, 0], X[:, 1], color=colors[y])
ax.set_title("A well separated dataset")

#As we saw, the decision line isn't perfect, but at the end of the day, 
#this is the best Linear SVM we will get.


radial_svm = SVC(kernel='rbf')
radial_svm.fit(X, y)
xmin, xmax = np.percentile(X[:, 0], [0, 100])
ymin, ymax = np.percentile(X[:, 1], [0, 100])
test_points = np.array([[xx, yy] for xx, yy in
                             product(np.linspace(xmin, xmax),
                             np.linspace(ymin, ymax))])
test_preds = radial_svm.predict(test_points)
import matplotlib.pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
import numpy as np
colors = np.array(['r', 'b'])
ax.scatter(test_points[:, 0], test_points[:, 1],
               color=colors[test_preds], alpha=.25)
ax.scatter(X[:, 0], X[:, 1], color=colors[y])
ax.set_title("SVM with a radial basis function")

#As we can see, the decision boundary has been altered. We can even pass in our own radial
#basis function, if needed:
def test_kernel(X, y):
     """ Test kernel that returns the exponentiation of the dot of the
     X and y matrices.
    This looks an awful lot like the log hazards if you're familiar with
    survival analysis.
    """
    return np.exp(np.dot(X, y.T))
test_svc = SVC(kernel=test_kernel)
test_svc.fit(X, y)
#SVC(C=1.0, cache_size=200, class_weight=None, coef0=0.0, degree=3,
# gamma=0.0, kernel=<function test_kernel at 0x121fdfb90>,
# max_iter=-1, probability=False, random_state=None,
# shrinking=True, tol=0.001, verbose=False)





#Generalizing 推广 with multiclass classifiation


# When working with linear models such as logistic regression, we need to use
# OneVsRestClassifier. This scheme will create a classifir for each class.

from sklearn import datasets
X, y = datasets.make_classification(n_samples=10000, n_classes=3,
                                        n_informative=3)
from sklearn.tree import DecisionTreeClassifier
dt = DecisionTreeClassifier()
dt.fit(X, y)
dt.predict(X)
#array([1, 1, 0, .., 2, 1, 1])

#Now, let's move on to the case of the multiclass classifir. This will require 
#us to import OneVsRestClassifier. We'll also import LogisticRegression while 
#we're at it:
from sklearn.multiclass import OneVsRestClassifier
from sklearn.linear_model import LogisticRegression

mlr = OneVsRestClassifier(LogisticRegression(), n_jobs=2)
mlr.fit(X, y)
mlr.predict(X)
#array([1, 1, 0, ..., 2, 1, 1])


#If we want to quickly create our own OneVsRestClassifier, how might we do it?

#First, we need to construct a way to iterate through the classes and train a 
#classifir for each classifir. Then, we need to predict each class fist:
import numpy as np
def train_one_vs_rest(y, class_label):
     y_train = (y == class_label).astype(int)
     return y_train
classifiers = []
for class_i in sorted(np.unique(y)):
     l = LogisticRegression()
     y_train = train_one_vs_rest(y, class_i)
     l.fit(X, y_train)
     classifiers.append(l)


#For example, let's predict X[0] :
for classifier in classifiers
    print classifier.predict_proba(X[0])
#[[ 0.90443776 0.09556224]]
#[[ 0.03701073 0.96298927]]
#[[ 0.98492829 0.01507171]]

#As you can see, the second classifir (the one in index 1) has the highest 
#likelihood of being "positive", therefore we'll assign 1 to this point.




#Using LDA for classifiation

#Linear Discriminant判别式 Analysis (LDA) attempts to fi a linear combination of 
#features to predict the outcome variable. LDA is often used as a 
#preprocessing step. We'll walk through both methods in this recipe.

#先跳过


#Working with QDA – a nonlinear LDA
#先跳过


#Using Stochastic Gradient Descent 随机梯度下降 for classifiation

#In regression, we minimized a cost function that penalized 处罚 for bad 
#choices on a continuous scale, but for classifiation, 
#we'll minimize a cost function that penalizes for two (or more) cases.


#First, let's create some very basic data:
from sklearn import datasets
X, y = datasets.make_classification()
#Next, we'll create a SGDClassifier instance:
from sklearn import linear_model
sgd_clf = linear_model.SGDClassifier()

#As usual, we'll fi the model:
sgd_clf.fit(X, y)
#SGDClassifier(alpha=0.0001, class_weight=None, epsilon=0.1, eta0=0.0,
# fit_intercept=True, l1_ratio=0.15,
# learning_rate='optimal', loss='hinge', n_iter=5,
# n_jobs=1, penalty='l2', power_t=0.5, random_state=None,
# shuffle=False, verbose=0, warm_start=False)


#Classifying documents with Naïve Bayes 

#Naïve Bayes is a really interesting model. It's somewhat similar to k-NN 
#in the sense that it makes some assumptions that might oversimplify 
#reality, but still perform well in many cases.



from sklearn.datasets import fetch_20newsgroups
categories = ["rec.autos", "rec.motorcycles"]
newgroups = fetch_20newsgroups(categories=categories)
#take a look
print "\n".join(newgroups.data[:1])
#From: gregl@zimmer.CSUFresno.EDU (Greg Lewis)
#Subject: Re: WARNING.....(please read)...
#Keywords: BRICK, TRUCK, DANGER
#Nntp-Posting-Host: zimmer.csufresno.edu
#Organization: CSU Fresno
#Lines: 33


newgroups.target_names[newgroups.target[:1]]
#'rec.autos'

from sklearn.feature_extraction.text import CountVectorizer
count_vec = CountVectorizer()
bow = count_vec.fit_transform(newgroups.data)

#This matrix is a sparse matrix, which is the length of the number of 
#documents by each word. The document and word value of the matrix are
#the frequency of the particular term:

bow
#<1192x19177 sparse matrix of type '<type 'numpy.int64'>'
# with 164296 stored elements in Compressed Sparse Row format>


#We'll actually need the matrix as a dense array for the Naïve Bayes
# object. So, let's convert it back:
bow = np.array(bow.todense())

words = np.array(count_vec.get_feature_names())
words[bow[0] > 0][:5]
#array([u'10pm', u'1qh336innfl5', u'33', u'93740', u'_____________________
#______________________________________________'],
# dtype='<U79')


#Now, are these the examples in the fist document? Let's check that using the
#following command:
'10pm' in newgroups.data[0].lower()
#True
'1qh336innfl5' in newgroups.data[0].lower()
#True


from sklearn import naive_bayes
clf = naive_bayes.GaussianNB()

#Before we fi the model, let's split the dataset into a training and test set:
mask = np.random.choice([True, False], len(bow))
clf.fit(bow[mask], newgroups.target[mask])
predictions = clf.predict(bow[~mask])

np.mean(predictions == newgroups.target[~mask])
#0.92446043165467628


#We can also extend Naïve Bayes to do multiclass work. Instead of assuming
#a Gaussian likelihood, we'll use a multinomial likelihood.


#First, let's get a third category种类 of data:
from sklearn.datasets import fetch_20newsgroups
mn_categories = ["rec.autos", "rec.motorcycles",
                     "talk.politics.guns"]
mn_newgroups = fetch_20newsgroups(categories=mn_categories)

#We'll need to vectorize this just like the class case:
mn_bow = count_vec.fit_transform(mn_newgroups.data)
mn_bow = np.array(mn_bow.todense())
#Let's create a mask array to train and test:
mn_mask = np.random.choice([True, False], len(mn_newgroups.data))
multinom = naive_bayes.MultinomialNB()
multinom.fit(mn_bow[mn_mask], mn_newgroups.target[mn_mask])
mn_predict = multinom.predict(mn_bow[~mn_mask])
np.mean(mn_predict == mn_newgroups.target[~mn_mask])
#0.96594778660612934


#Label propagation 标签传播 with semi-supervised learning
#先跳过












































































































                                              
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              