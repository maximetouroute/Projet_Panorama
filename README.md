# Panorama Merger

A simple panorama stitching Proof of concept in C++ using OpenCV2, [FLANN](http://docs.opencv.org/2.4.11/modules/flann/doc/flann_fast_approximate_nearest_neighbor_search.html), [GTK](https://www.gtk.org/), and a custom overlap detection algorithm.

# Quick overview

## Algorithm flow

We want to merge two pictures from a panorama
1[](https://github.com/maximetouroute/Projet_Panorama/blob/master/readme_img/1.jpg)

For doing so, we split one image onto smaller areas, and turn them in black and white. It optimises a lot computation time.
  
1[](https://github.com/maximetouroute/Projet_Panorama/blob/master/readme_img/2.jpg)

We then look for similarities between each area and the other picture.

1[](https://github.com/maximetouroute/Projet_Panorama/blob/master/readme_img/3.jpg)

For a better estimation, we added a ponderation to avoid wrong estimations such as this one : 

1[](https://github.com/maximetouroute/Projet_Panorama/blob/master/readme_img/4.jpg)

## A quick look at the GUI made with GTK

1[](https://github.com/maximetouroute/Projet_Panorama/blob/master/readme_img/5.jpg)

## Practical example with real & dirty pictures

1[](https://github.com/maximetouroute/Projet_Panorama/blob/master/img/1_g.jpg)
1[](https://github.com/maximetouroute/Projet_Panorama/blob/master/img/1_d.jpg)
And the merged picture : 
1[](https://github.com/maximetouroute/Projet_Panorama/blob/master/img/result.jpg)
