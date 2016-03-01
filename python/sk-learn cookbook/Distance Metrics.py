#!/usr/bin/env python
# coding=utf-8

#Using KMeans to cluster data

#KMeans is probably one of the most well-known clustering algorithms and, in a 
#larger sense, one of the most well-known unsupervised learning techniques.

from sklearn.datasets import make_blobs
blobs, classes = make_blobs(500, centers=3)

import matplotlib.pyplot as plt
f, ax = plt.subplots(figsize=(7.5, 7.5))
ax.scatter(blobs[:, 0], blobs[:, 1], color=rgb[classes])
rgb = np.array(['r', 'g', 'b'])
ax.set_title("Blobs")

from sklearn.cluster import KMeans
kmean = KMeans(n_clusters=3)
kmean.fit(blobs)
#KMeans(copy_x=True, init='k-means++', max_iter=300, n_clusters=3,
#n_init=10, n_jobs=1, precompute_distances=True,
#random_state=None, tol=0.0001, verbose=0)
kmean.cluster_centers_
array([[ 0.47819567, 1.80819197],
       [ 0.08627847, 8.24102715],
       [ 5.2026125 , 7.86881767]])
       
f, ax = plt.subplots(figsize=(7.5, 7.5))
ax.scatter(blobs[:, 0], blobs[:, 1], color=rgb[classes])
ax.scatter(kmean.cluster_centers_[:, 0],
#kmean.cluster_centers_[:, 1], marker='*', s=250,
#color='black', label='Centers')
ax.set_title("Blobs")
ax.legend(loc='best')

kmean.labels_[:5]
#array([1, 1, 2, 2, 1], dtype=int32)

#We can check whether kmean.labels_ is the same as classes, but because KMeans 
#has no knowledge of the classes going in, it cannot assign the sample index 
#values to both classes:

classes[:5]
#array([0, 0, 2, 2, 0])
#Feel free to swap 1 and 0 in classes to see if it matches up with labels_.
#kmean聚合后的标号没有意义，同一个标号只是代表同一类，这里的0和上面的1是一样的

#The transform function is quite useful in the sense that it will output 
#the distance between each point and centroid:
kmean.transform(blobs)[:5]
#array([[ 6.47297373, 1.39043536, 6.4936008 ],
#[ 6.78947843, 1.51914705, 3.67659072],
#[ 7.24414567, 5.42840092, 0.76940367],
#[ 8.56306214, 5.78156881, 0.89062961],
#[ 7.32149254, 0.89737788, 5.12246797]])



#Optimizing the number of centroids 质心

from sklearn.datasets import make_blobs
import numpy as np
blobs, classes = make_blobs(500, centers=3)
from sklearn.cluster import KMeans
kmean = KMeans(n_clusters=3)
kmean.fit(blobs)
#KMeans(copy_x=True, init='k-means++', max_iter=300, n_clusters=3,
#n_init=10, n_jobs=1, precompute_distances=True,
#random_state=None, tol=0.0001, verbose=0)

#Silhouette distance is the ratio of the difference between in-cluster 
#dissimilarity, the closest out-of-cluster dissimilarity, and the maximum
#of these two values. It can be thought of as a measure of how separate 
#the clusters are.

from sklearn import metrics
silhouette_samples = metrics.silhouette_samples(blobs,
                                                    kmean.labels_)
print np.column_stack((classes[:5], silhouette_samples[:5]))
#array([[ 1., 0.87617292],
#    [ 1., 0.89082363],
#    [ 1., 0.88544994],
#    [ 1., 0.91478369],
#    [ 1., 0.91308287]])
f, ax = plt.subplots(figsize=(10, 5))
ax.set_title("Hist of Silhouette Samples")
ax.hist(silhouette_samples)

silhouette_samples.mean()
#0.57130462953339578

metrics.silhouette_score(blobs, kmean.labels_)
#0.57130462953339578

# first new ground truth
blobs, classes = make_blobs(500, centers=10)
sillhouette_avgs = []
# this could take a while
for k in range(2, 60):
    kmean = KMeans(n_clusters=k).fit(blobs)
    sillhouette_avgs.append(metrics.silhouette_score(blobs,
                                                     kmean.labels_))
f, ax = plt.subplots(figsize=(7, 5))
ax.plot(sillhouette_avgs)


#Assessing cluster correctness 评定聚类的正确性


# We'll create a simple dataset, evaluate the measures of correctness against
# the ground truth in several ways, and then discuss them:
from sklearn import datasets
from sklearn import cluster
blobs, ground_truth = datasets.make_blobs(1000, centers=3,
                                              cluster_std=1.75)
                                              
#Before we walk through the metrics, let's take a look at the dataset:
f, ax = plt.subplots(figsize=(7, 5))
colors = ['r', 'g', 'b']
for i in range(3):
    p = blobs[ground_truth == i]
    ax.scatter(p[:,0], p[:,1], c=colors[i],
    label="Cluster {}".format(i))
ax.set_title("Cluster With Ground Truth")
ax.legend()
f.savefig("9485OS_03-16")

#In order to fit a KMeans model we'll create a KMeans object from the 
#cluster module:
kmeans = cluster.KMeans(n_clusters=3)
kmeans.fit(blobs)
#KMeans(copy_x=True, init='k-means++', max_iter=300, n_clusters=3,
#n_init=10, n_jobs=1, precompute_distances=True,
#random_state=None, tol=0.0001, verbose=0)
kmeans.cluster_centers_
#array([[ 5.18993766, 0.35110059],
#[ 0.18300097, -4.9480336 ],
#[ 10.01421381, -2.26274328]])

#Now that we've fit the model, let's have a look at the cluster centroids:
f, ax = plt.subplots(figsize=(7, 5))
colors = ['r', 'g', 'b']
for i in range(3):
    p = blobs[ground_truth == i]
    ax.scatter(p[:,0], p[:,1], c=colors[i],
    label="Cluster {}".format(i))
ax.scatter(kmeans.cluster_centers_[:, 0],
               kmeans.cluster_centers_[:, 1], s=100, color='black',
               label='Centers')
ax.set_title("Cluster With Ground Truth")
ax.legend()
f.savefig("9485OS_03-17")

for i in range(3):
    print (kmeans.labels_ == ground_truth)[ground_truth == i].astype(int).mean()
#0.0778443113772
#0.990990990991
#0.0570570570571
    
new_ground_truth = ground_truth.copy()
new_ground_truth[ground_truth == 0] = 2
new_ground_truth[ground_truth == 2] = 0
for i in range(3):
    print (kmeans.labels_ == new_ground_truth)[ground_truth == i].astype(int).mean()
#0.919161676647
#0.990990990991
#0.90990990991
    
from sklearn import metrics
metrics.normalized_mutual_info_score(ground_truth, kmeans.labels_)
#0.78533737204433651

#For example, let's look at what happens when the mutual information score itself:
metrics.normalized_mutual_info_score(ground_truth, ground_truth)
#1.0
#Given the name, we can tell that there is probably an unnormalized mutual_info_score:
metrics.mutual_info_score(ground_truth, kmeans.labels_)
#0.78945287371677486


#Using MiniBatch KMeans to handle more data

#MiniBatch KMeans is a faster implementation of KMeans. KMeans is 
#computationally very expensive; the problem is NP-hard.

from sklearn.datasets import make_blobs
blobs, labels = make_blobs(int(1e6), 3)
from sklearn.cluster import KMeans, MiniBatchKMeans
kmeans = KMeans(n_clusters=3)
minibatch = MiniBatchKMeans(n_clusters=3)

#%time kmeans.fit(blobs) #IPython Magic
#CPU times: user 8.17 s, sys: 881 ms, total: 9.05 s Wall time: 9.97 s
#%time minibatch.fit(blobs)  #IPython Magic
#CPU times: user 4.04 s, sys: 90.1 ms, total: 4.13 s Wall time: 4.69 s


# 类中心
kmeans.cluster_centers_[0]
#array([ 1.10522173, -5.59610761, -8.35565134])
minibatch.cluster_centers_[0]
#array([ 1.12071187, -5.61215116, -8.32015587])

#The next question we might ask is how far apart the centers are:
from sklearn.metrics import pairwise
pairwise.pairwise_distances(kmeans.cluster_centers_[0], 
                                minibatch.cluster_centers_[0])

#array([[ 0.03305309]])

#This seems to be very close. The diagonals will contain the cluster center differences:
np.diag(pairwise.pairwise_distances(kmeans.cluster_centers_,
                                        minibatch.cluster_centers_))
#array([ 0.04191979, 0.03133651, 0.04342707])

#batch_size 等于样本数，结果很耗时
minibatch = MiniBatchKMeans(batch_size=len(blobs))
#%time minibatch.fit(blobs)
#CPU times: user 34.6 s, sys: 3.17 s, total: 37.8 s Wall time: 44.6 s


#Quantizing 数字化 an image with KMeans clustering

# in your terminal
#$ wget http://blog.trenthauck.com/assets/headshot.jpg
from scipy import ndimage
img = ndimage.imread("headshot.jpg")
plt.imshow(img)
print img.shape
#(420, 420, 3)

#First, let's reshape our array; it is a NumPy array, and thus trivial to work with:
x, y, z = img.shape
long_img = img.reshape(x*y, z)
long_img.shape
#(176400, 3)

#Now we can start the clustering process.
from sklearn import cluster
k_means = cluster.KMeans(n_clusters=5)
k_means.fit(long_img)

centers = k_means.cluster_centers_
print  centers
#array([[ 142.58775848, 206.12712986, 226.04416873],
#[ 86.29356543, 68.86312505, 54.04770507],
#[ 194.36182899, 172.19845258, 149.65603813],
#[ 24.67768412, 20.45778933, 16.19698314],
#[ 149.27801776, 132.19850659, 115.32729167]])

labels = k_means.labels_
labels[:5]
array([1, 1, 1, 1, 1], dtype=int32)

plt.imshow(centers[labels].reshape(x, y, z))

#Finding the closest objects in the feature space

#First, let's import the pairwise distance function from the metrics module and
# create a dataset to play with:
from sklearn.metrics import pairwise
from sklearn.datasets import make_blobs
points, labels = make_blobs()
#This simplest way to check the distances is pairwise_distances:
distances = pairwise.pairwise_distances(points)

#distances is an N x N matrix with 0s along the diagonals. In the simplest case,
#let's see the distances between each point and the first point:
np.diag(distances) [:5]
#array([ 0., 0., 0., 0., 0.])

distances[0][:5]
#array([ 0., 11.82643041,1.23751545, 1.17612135, 14.61927874])

ranks = np.argsort(distances[0])
ranks[:5]
#array([ 0, 27, 98, 23, 67]) #距离最小的5个下标值

print  points[ranks][:5]
#array([[ 8.96147382, -1.90405304],
#[ 8.75417014, -1.76289919],
#[ 8.78902665, -2.27859923],
#[ 8.59694131, -2.10057667],
#[ 8.70949958, -2.30040991]])

def euclid_distances(x, y):
    return np.power(np.power(x - y, 2).sum(), .5)
print euclid_distances(points[0], points[1])
#11.826430406213145

#There are several other functions available in scikit-learn, but scikit-learn will also use
#distance functions of SciPy. At the time of writing this book, the scikit-learn distance
#functions support sparse matrixes. Check out the SciPy documentation for more
#information on the distance functions:
    # cityblock
    # cosine
    # euclidean
    # l1
    # l2
    # manhattan
pairwise.pairwise_distances([[0, 0], [5, 5]], metric='cityblock')[0]
#array([ 0., 10.])



X = np.random.binomial(1, .5, size=(2, 4)).astype(np.bool)
X
#array([[False, True, False, False],
#[False, False, False, True]], dtype=bool)
print pairwise.pairwise_distances(X, metric='hamming')
#array([[ 0. , 0.25],
#       [ 0.25, 0. ]])


#Probabilistic 概率性的 clustering with Gaussian Mixture混合 Models GMM

import numpy as np
N = 1000

in_m = 72
in_w = 66

s_m = 2
s_w = s_m
m = np.random.normal(in_m, s_m, N)
w = np.random.normal(in_w, s_w, N)
from matplotlib import pyplot as plt
f, ax = plt.subplots(figsize=(7, 5))
ax.set_title("Histogram of Heights")
ax.hist(m, alpha=.5, label="Men");
ax.hist(w, alpha=.5, label="Women");
ax.legend()

random_sample = np.random.choice([True, False], size=m.size)
m_test = m[random_sample]
m_train = m[~random_sample]
w_test = w[random_sample]
w_train = w[~random_sample]

from scipy import stats
m_pdf = stats.norm(m_train.mean(), m_train.std())
w_pdf = stats.norm(w_train.mean(), w_train.std())

print m_pdf.pdf(m[0])
#0.043532673457165431
print w_pdf.pdf(m[0])
#9.2341848872766183e-07

guesses_m = np.ones_like(m_test)
guesses_m[m_pdf.pdf(m_test) < w_pdf.pdf(m_test)] = 0

print guesses_m.mean()
#0.93775100401606426

guesses_w = np.ones_like(w_test)
guesses_w[m_pdf.pdf(w_test) > w_pdf.pdf(w_test)] = 0
print guesses_w.mean()
#0.93172690763052213

#Let's allow the variance to differ between groups. First, create some new data:
s_m = 1
s_w = 4
m = np.random.normal(in_m, s_m, N)
w = np.random.normal(in_w, s_w, N)
#Then, create a training set:
m_test = m[random_sample]
m_train = m[~random_sample]
w_test = w[random_sample]
w_train = w[~random_sample]
f, ax = plt.subplots(figsize=(7, 5))
ax.set_title("Histogram of Heights")
ax.hist(m_train, alpha=.5, label="Men");
ax.hist(w_train, alpha=.5, label="Women");
ax.legend()

m_pdf = stats.norm(m_train.mean(), m_train.std())
w_pdf = stats.norm(w_train.mean(), w_train.std())

class_A = np.random.normal(0, 1, size=(100, 2))
class_B = np.random.normal(4, 1.5, size=(100, 2))
f, ax = plt.subplots(figsize=(7, 5))
ax.scatter(class_A[:,0], class_A[:,1], label='A', c='r')
ax.scatter(class_B[:,0], class_B[:,1], label='B')

from sklearn.mixture import GMM
gmm = GMM(n_components=2)
X = np.row_stack((class_A, class_B))
y = np.hstack((np.ones(100), np.zeros(100)))

train = np.random.choice([True, False], 200)
gmm.fit(X[train])
#GMM(covariance_type='diag', init_params='wmc', min_covar=0.001,
#n_components=2, n_init=1, n_iter=100, params='wmc',
#random_state=None, thresh=0.01)

gmm.fit(X[train])
print gmm.predict(X[train])[:5]
#array([0, 0, 0, 0, 0])

#Using KMeans for outlier detection 异常值检测

from sklearn.datasets import make_blobs
X, labels = make_blobs(100, centers=1)
import numpy as np
from sklearn.cluster import KMeans
kmeans = KMeans(n_clusters=1)
kmeans.fit(X)

f, ax = plt.subplots(figsize=(7, 5))
ax.set_title("Blob")
ax.scatter(X[:, 0], X[:, 1], label='Points')
ax.scatter(kmeans.cluster_centers_[:, 0],
               kmeans.cluster_centers_[:, 1], label='Centroid',
               color='r')
ax.legend()

distances = kmeans.transform(X)
# argsort returns an array of indexes which will sort the array in ascending order
# so we reverse it via [::-1] and take the top five with [:5]
sorted_idx = np.argsort(distances.ravel())[::-1][:5]
f, ax = plt.subplots(figsize=(7, 5))
ax.set_title("Single Cluster")
ax.scatter(X[:, 0], X[:, 1], label='Points')
ax.scatter(kmeans.cluster_centers_[:, 0],
               kmeans.cluster_centers_[:, 1],
               label='Centroid', color='r')
ax.scatter(X[sorted_idx][:, 0], X[sorted_idx][:, 1],
               label='Extreme Value', edgecolors='g',
               facecolors='none', s=100)
ax.legend(loc='best')

#It's easy to remove these points if we like:
new_X = np.delete(X, sorted_idx, axis=0)

#Also, the centroid clearly changes with the removal of these points:
new_kmeans = KMeans(n_clusters=1)
new_kmeans.fit(new_X)

#Let's visualize the difference between the old and new centroids:
f, ax = plt.subplots(figsize=(7, 5))
ax.set_title("Extreme Values Removed")
ax.scatter(new_X[:, 0], new_X[:, 1], label='Pruned Points')
ax.scatter(kmeans.cluster_centers_[:, 0],
               kmeans.cluster_centers_[:, 1], label='Old Centroid',
               color='r', s=80, alpha=.5)
ax.scatter(new_kmeans.cluster_centers_[:, 0],
               new_kmeans.cluster_centers_[:, 1], label='New Centroid',
               color='m', s=80, alpha=.5)
ax.legend(loc='best')

from scipy import stats
emp_dist = stats.multivariate_normal(
                    kmeans.cluster_centers_.ravel())
lowest_prob_idx = np.argsort(emp_dist.pdf(X))[:5]
np.all(X[sorted_idx] == X[lowest_prob_idx])
#True

#Using k-NN for regression

from sklearn import datasets
iris = datasets.load_iris()
print iris.feature_names
#['sepal length (cm)', 'sepal width (cm)', 'petal length (cm)',
#'petal width (cm)']

from sklearn.linear_model import LinearRegression
lr = LinearRegression()
lr.fit(X, y)
print "The MSE is: {:.2}".format(np.power(y - lr.predict(X),2).mean())
#The MSE is: 0.15
#Now, for the k-NN regression, use the following code:
from sklearn.neighbors import KNeighborsRegressor
knnr = KNeighborsRegressor(n_neighbors=10)
knnr.fit(X, y)
print "The MSE is: {:.2}".format(np.power(y - knnr.predict(X),2).mean())
#The MSE is: 0.069

#Let's look at what the k-NN regression does when we tell it to use the closest
# 10 points for regression:
f, ax = plt.subplots(nrows=2, figsize=(7, 10))
ax[0].set_title("Predictions")
ax[0].scatter(X[:, 0], X[:, 1], s=lr.predict(X)*80, 
            label='LR Predictions', color='c', edgecolors='black')
ax[1].scatter(X[:, 0], X[:, 1], s=knnr.predict(X)*80, 
            label='k-NN Predictions', color='m', edgecolors='black')
ax[0].legend()
ax[1].legend()

setosa_idx = np.where(iris.target_names=='setosa')
setosa_mask = iris.target == setosa_idx[0]
print y[setosa_mask][:5]
#array([ 0.2, 0.2, 0.2, 0.2, 0.2])
print knnr.predict(X)[setosa_mask][:5]
#array([ 0.28, 0.17, 0.21, 0.2 , 0.31])
print lr.predict(X)[setosa_mask][:5]
#array([ 0.44636645, 0.53893889, 0.29846368, 0.27338255, 0.32612885])

#Let's manually predict a single point:
example_point = X[0]
#Now, we need to get the 10 closest points to our example_point:
from sklearn.metrics import pairwise
distances_to_example = pairwise.pairwise_distances(X)[0]
ten_closest_points = X[np.argsort(distances_to_example)][:10]
ten_closest_y = y[np.argsort(distances_to_example)][:10]
ten_closest_y.mean()
#0.28000
#We can see that this is very close to what was expected.









































