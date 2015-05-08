
/*
A faire évoluer : rotation, déformations ?
TODO: images avec dimensions différentes.
*/
Mat merge_process(Mat img1, Mat img2, int offset_x, int offset_y)
{
	// Todo: on considère ici que les deux images ont la même dimension
	//Mat merged_img(img1.rows+img2.rows+offset_y, img1.cols+img2.cols+offset_x);

	// Copy both images into the composite image.
	if (img1.cols != img2.cols || img1.rows != img2.rows) {
		printf("img1 and img2 should be identical size");
	}

	int rows = img1.rows;
	int cols = img1.cols;

	int bordure_x = 300;
	int bordure_y = 300;
	// Création de la matrice destination, qui a une taille supérieure aux deux images
	// offset x2 pour avoir de l'espace des deux côtés
	Mat dst = cvCreateMat(img1.rows + img2.rows + offset_y + bordure_y * 2, img2.cols + img1.cols + offset_x + bordure_x * 2, img1.type());


	// x, y , width, height

	Mat tmp = dst(cv::Rect(bordure_x, bordure_y, cols, rows));
	img1.copyTo(tmp);


	tmp = dst(cv::Rect(bordure_x + img1.cols + offset_x, bordure_y + 0 + offset_y, img2.cols, img2.rows));
	img2.copyTo(tmp);

	return dst;
}


