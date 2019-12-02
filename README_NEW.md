# Double-SS

The ground-level details of this project can be read from **README.md**

The heavy keeper paper for the top-k elephant flows can be read from https://www.usenix.org/system/files/conference/atc18/atc18-gong.pdf

Now, assuming that the reader is familiar with the above mentioned things, a brief introduction to the current work on the top of these things is given below

## Introduction

There was a development of the algorithms **Stetch-Frequent** and **Double-Frequent** in the paper https://drive.google.com/open?id=0B5N6fwm0W9F1cHYwOTNCY3Z4YzUwdVdUVWE0T3JLbUl5MzQ4

These algorithms were developed from the **Frequent** algorithm and a very detailed theoretical analysis was carried out for them. Similar to these, an other improvement has been made for the **Space saving** algorithm, named the **Double Space Saving** algorithm (It's construction is similar to the Double Frequent from the Frequent) 

The current scope of this work is to see if these newly developed algorithms exhibit a very improved precision and memory size as compared to the other algorithms (Especially the HeavyKeeper algorithm) for the real-world datasets
