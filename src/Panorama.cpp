#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

// Utilisation de variables globales pour le moment.



/*
Retourne le panorama
Paramètres : les deux images à fusionner
*/
Mat panorama_process(Mat img1, Mat img2)
{
    // L'image finale
    Mat panorama_image;


    // Les deux parties d'image sur lesquelles on travaille (comparaison des éléments de chaque image)
    Mat part_img1;
    Mat part_img2;


    // Etape 1: Récupération des parties d'images à analyser

        // Découpage de l'image en petits cubes,
        // préparation pour analyse (Amélioration du contraste par ex.

    // Etape 2: Algorithme de detection des similitudes / Comparaison des parties d'image

    // Le retour de cette étape est : deux cases avec les plus grandes similitudes

}
