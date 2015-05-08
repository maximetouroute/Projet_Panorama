#include "Panorama.h"

Mat img = imread("img/image_1.jpg", CV_LOAD_IMAGE_COLOR);
Mat img2 = imread ("img/image_2.jpg", CV_LOAD_IMAGE_COLOR);

int main(int argc, char *argv[])
{
	Mat panorama_image = panorama_process(img, img2);

	imshow("Image Panorama Finale ", panorama_image);
	waitKey(0);
	return 0;
}
