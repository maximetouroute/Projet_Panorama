#include "Panorama.h"

Mat img = imread("img/image_1.jpg", CV_LOAD_IMAGE_COLOR);
Mat img2 = imread ("img/image_2.jpg", CV_LOAD_IMAGE_COLOR);

int main(int argc, char *argv[])
{
    // Création d'une fenêtre
	namedWindow("Projet Panorama", CV_WINDOW_AUTOSIZE);

	// Création de deux fenêtres avec les deux images à fusionner
	imshow("image 1", img);
	imshow("image 2", img2);

    panorama_process(img, img2);
	//createTrackbar(" Contour level:", "lena", &thresh, max_thresh, thresh_callback);
	//thresh_callback(0, 0);
    printf("Hola\n");
	waitKey(0);
	return 0;
}
