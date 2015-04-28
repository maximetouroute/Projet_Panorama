#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"

using namespace cv;

#ifndef FLANNC_H
#define FLANNC_H


class FlannC
{
    public:
        FlannC();
        virtual ~FlannC();
        float getPonderation();
        Point getKeypoints_matched1(int i);
        Point getKeypoints_matched2(int i);
        void flannC_process( Mat img_1, Mat img_2 );


    private:
        float ponderation;
        int distance_max_x;
        int distance_max_y;
        //les points qui match de la petite image
        vector<Point> keypoints_matched1;
        //les points qui match de la grande image. Les indices correspondent.
        vector<Point> keypoints_matched2;
};

#endif // FLANNC_H
