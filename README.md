# Panorama Merger

A simple panorama stitching Proof of concept in C++ using OpenCV2, [FLANN](http://docs.opencv.org/2.4.11/modules/flann/doc/flann_fast_approximate_nearest_neighbor_search.html), [GTK](https://www.gtk.org/), and a custom overlap detection algorithm

# Quick overview

## Algorithm flow

We want to merge two pictures from a panorama
1[]()

For doing so, we split one image onto smaller areas, and turn them in black and white. It optimises a lot computation time.

1[]()

We then look for similarities between each area and the other picture.

1[]()

For a better estimation, we added a ponderation to avoid wrong estimations such as this one : 

1[]()

## A quick look at the GUI made with GTK

1[]()

## Practical example with real dirty world data (camera phone)

1[]()
1[]()
