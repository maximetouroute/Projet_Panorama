#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

void detection_process(Mat& img)
{
    printf("SALUT\n");
    int i, corner_count = 150;
    IplImage *eig_img, *temp_img;
    CvPoint2D32f *corners;

    //image file
    eig_img = new IplImage(img);
    temp_img = cvCreateImage (img.size(), IPL_DEPTH_32F, 1);
    corners = (CvPoint2D32f *) cvAlloc (corner_count * sizeof (CvPoint2D32f));


    // (3)Corner detection using cvCornerHarris
    corner_count = 150;
    cvGoodFeaturesToTrack (eig_img, &eig_img, eig_img, corners, &corner_count, 0.1, 15, NULL, 3, 1, 0.01);
    cvFindCornerSubPix (eig_img, corners, corner_count,
                      cvSize (3, 3), cvSize (-1, -1), cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));
    // (4)Draw the detected corner
    for (i = 0; i < corner_count; i++)
    cvCircle (eig_img, cvPointFrom32f (corners[i]), 3, CV_RGB (0, 0, 255), 2);

    //Message for debugging
    printf("Harris corner count = %d\n", corner_count);

}
