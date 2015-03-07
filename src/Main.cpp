
#include "Panorama.cpp"



int thresh = 1;
int max_thresh = 10;

Mat img = imread("img/image_1.jpg", CV_LOAD_IMAGE_COLOR);
Mat img2 = imread ("img/imag_2.jpg", CV_LOAD_IMAGE_COLOR);

void thresh_callback(int, void*);
void save(int state, void* userdata);

int main(int argc, char *argv[])
{
    // Création d'une fenêtre
	namedWindow("Projet Panorama", CV_WINDOW_AUTOSIZE);

	// Création de deux fenêtres avec les deux images à fusionner
	imshow("Image 1", img);
	imshow("image 2", img);


	//createTrackbar(" Contour level:", "lena", &thresh, max_thresh, thresh_callback);
	//thresh_callback(0, 0);

	waitKey(0);
	return 0;
}

void thresh_callback(int, void*)
{
	for (int i = 0; i<img.rows; i++)
	{
		img2.at<Vec3b>(i, 0) = Vec3b(0, 0, 0);
	}

	for (int i = 0; i<img.cols; i++)
	{
		img2.at<Vec3b>(0, i) = Vec3b(0, 0, 0);
	}

	for (int i = 1; i<img.rows; i++)
	{
		for (int j = 1; j<img.cols; j++)
		{
			img2.at<Vec3b>(i, j) = thresh*((img.at<Vec3b>(i, j) - img.at<Vec3b>(i - 1, j)) + (img.at<Vec3b>(i, j) - img.at<Vec3b>(i, j - 1)));
		}
	}

	namedWindow("lena2", CV_WINDOW_AUTOSIZE);
	imshow("lena2", img2);
}
