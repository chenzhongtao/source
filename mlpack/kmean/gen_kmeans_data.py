#!/usr/bin/env python
# coding=utf-8

from sklearn.datasets import make_blobs

n_samples=100
n_features=2
centers=3
blobs_file = "kmean_dataset.csv"
classes_file = "kmean_classes.csv"

blobs, classes = make_blobs(n_samples=n_samples, n_features=n_features, 
                            centers=centers)
#mlpack 数据是按列存放的，矩阵的行数等于文件的列数，但是这里的数据还是按行存放就好(具体要看源码)
with open(blobs_file, "w") as f:
    for index in  range(blobs.shape[0]):
        a = blobs[index]
        b = [str(i) for i in a]
        f.write(",".join(b))
        f.write("\n")
with open(classes_file, "w") as f:
        b = [str(i) for i in classes]
        f.write(",".join(b))
        f.write("\n")