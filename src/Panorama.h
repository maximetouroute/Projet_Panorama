
#include "Canvas.h"
#include "Detection.h"
#define GRID_SIZE 128

using namespace cv;
using namespace std;


/*
* image_to_grid : convertit une image en grille de petites images
* return: tableau de petites images
*/
void image_to_grid(Mat img, vector<Mat>& mat_array, int grid_size)
{
    // Pour l'instant, ne gère que le cas parfait où la grille peut se former sans problèmes !
    //Mat* mat_array= (Mat*) malloc(sizeof(Mat) * (img.rows*img.cols/grid_size));
   // Mat mat_array[img.rows*img.cols/GRID_SIZE];
    if(img.rows % grid_size != 0)
    {
        printf("Warning : image_to_grid() taille de grille pas compatible avec l'image :\n---> grid:%i pixelslignes:%i\n", grid_size, img.rows);
    }
    else if(img.cols % grid_size != 0)
    {
        printf("Warning : image_to_grid() taille de grille pas compatible avec l'image :\n---> grid:%i pixelscols:%i\n", grid_size, img.cols);
    }
    else // Cas parfait
    {

        int index = 0;

        for(int i = 0 ; i < img.rows ; i+=grid_size )
        {
            //Boucle sur les colonnes
            for(int j = 0 ; j < img.cols ; j+=grid_size, index++)
            {

                // La zone de crop.
                // x           y           width       height
                Rect roi (j, i, grid_size, grid_size);
                printf("%i,%i\n", j, i);
                // Crop de la zone voulue.
                mat_array.push_back( img(roi).clone() );

            }
        }
    }
}


/*
Retourne le panorama
Paramètres : les deux images à fusionner
*/
void panorama_process(Mat img1, Mat img2)
{
    // L'image finale
    Mat panorama_image;

    // Etape 0: Faire un process pour se débarasser des informations que l'on veut pas pour la fusion panorama.
    // noir et blanc ?
    // Image de detection de contours ?

    Mat gray1(img1.rows, img1.cols, CV_8UC1); // CV8UC1 means 8 bits, 1channel.
    Mat gray2(img2.rows, img2.cols, CV_8UC1);

    cvtColor(img1, gray1, CV_RGB2GRAY );

    cvtColor(img2, gray2, CV_RGB2GRAY );

    // Etape 1: On découpe la première image en petits éléments carrés

    Mat part_img1[gray1.rows*gray1.cols/GRID_SIZE];

    // Stockage des parties d'images dans un vecteur
    vector<Mat> vect_part_img1;

    image_to_grid(gray1, vect_part_img1, GRID_SIZE); // grid_size doit etre compatible avec l'image ! (pour l'instant TODO)

    for(vector<Mat>::iterator it=vect_part_img1.begin(); it!=vect_part_img1.end(); it++){
        detection_process(*it);
    }

    imshow("grid", makeCanvas(vect_part_img1, 512, 4));
    imshow("img2 gray", gray2);



    // Etape 2: A l'aide d'un algorithme, on attribue des poids à chaque case



    // Plus le poids est élevé, plus la portion d'image a des zones d'intérêt faciles à identifier
  // int poids_img1[100];

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

    printf("Hola sortie\n");
}






