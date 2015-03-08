#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/*
Retourne le panorama
Paramètres : les deux images à fusionner
*/
Mat panorama_process(Mat img1, Mat img2)
{
    // L'image finale
    Mat panorama_image;


    // Etape 1: On découpe la première image en petits éléments carrés

    // On place les données
    Mat[] part_img1 = image_to_grid(1O);


    // Etape 2: A l'aide d'un algorithme, on attribue des poids à chaque case

    // Ici, éventuellement prendre que la partie droite de l'image.

    // Plus le poids est élevé, plus la portion d'image a des zones d'intérêt faciles à identifier
    int[] poids_img1;

    // Etape 3: On prend la case de poids le + élevé de l'image 1, et on la teste avec l'image 2
    /* Méthode précise à définir.

    1. Utiliser avec le morceau d'img1 le + probable de coller :
        Par défaut: poids élevé, et sur le coté droit de l'image (à faire évoluer plus tard)
        (celà dépend du sens de fusion (si le morceau est opposé au sens de fusion, ça colle pas.
        Par défaut

    2. Tester la similarité de cet élément avec l'autre image. On s'embête pas et on utilise un algo d'OpenCV pour ça:
        (on fera nous même plus tard si on a le temps)

        http://docs.opencv.org/doc/tutorials/features2d/feature_flann_matcher/feature_flann_matcher.html
        http://stackoverflow.com/questions/15572357/compare-the-similarity-of-two-images-with-opencv

    3. Retourner des valeurs x et y de décalage pour pouvoir coller l'image 2 à l'image 1 (on oublie la rotation pour l'instant)

    4. Afficher les deux images, avec un carré autour des zones repérées

    5. Si la zone correspond pas, permettre à l'utilisateur de cliquer sur un bouton reessayer
    Et ça sera déjà bien.

    */
}

/*
* image_to_grid : convertit une image en grille de petites images
* return: tableau de petites images
*/
Mat[] image_to_grid(int grid_size)
{
}
