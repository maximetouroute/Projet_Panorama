
#include "Canvas.h"
#include "Detection.h"
#include "Merge.h"
#include "FlannC.h"
#define GRID_SIZE 128
#define IMAGE_SIZE 512

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

        // Boucle sur les lignes
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
Mat panorama_process(Mat img1, Mat img2)
{
    // L'image finale
    Mat panorama_image;

    /********* Etape 0: Pré-traitement pour se débarasser des informations que l'on veut pas pour la fusion panorama *********/


    // On passe img1 et img2 en noir et blanc

    Mat gray1(img1.rows, img1.cols, CV_8UC1); // CV8UC1 means 8 bits, 1channel.
    Mat gray2(img2.rows, img2.cols, CV_8UC1);

    cvtColor(img1, gray1, CV_RGB2GRAY );
    cvtColor(img2, gray2, CV_RGB2GRAY );


    /********* Etape 1: On découpe la première image en petits éléments carrés *********/


    Mat part_img1[gray1.rows*gray1.cols/GRID_SIZE];
    // Stockage des parties d'images dans un vecteur
    vector<Mat> vect_part_img1;
    // grid_size doit etre adapté aux dimensions de l'image ! (pour l'instant TODO)
    image_to_grid(gray1, vect_part_img1, GRID_SIZE);



    /********* Etape 2: Application de l'algorithme Flann pour repérer les similitudes entre l'image et les parties d'image *********/


    //On stocke tous les FlannC que nous allons faire afin de retrouver la pondération et les keypoints
    vector<FlannC> flann;

    int i = 0;
    for(vector<Mat>::iterator it=vect_part_img1.begin(); it!=vect_part_img1.end() ; it++, i++)
    {
        detection_process(*it);
        FlannC f;
        flann.push_back(f);
        flann[i].flannC_process(*it,img2);
        printf("\n\n\n");
        waitKey(0);
    }


    /********* Etape 3: On repère l'iteration de l'algorithme qui a donné les meilleurs resultats*********/


    //Détermine le meilleure pondération ainsi que l'indice de 'image correspondante
    float meilleure_ponderation=10000;
    int indice_meilleure_ponderation;
    for(int i=0;i<flann.size();i++){
        float ponderation=flann[i].getPonderation();
        if(ponderation<meilleure_ponderation && ponderation!=0){
            meilleure_ponderation=ponderation;
            indice_meilleure_ponderation=i;
        }
    }
    printf("meilleure pondération: %f  image: %d, p:", meilleure_ponderation, indice_meilleure_ponderation);
    //waitKey(0);


    /********* Etape 4: On fusionne les deux images à l'aide des résultats obtenus via la meilleure iteration de l'algorithme *********/

    // TODO: ameliorer cette partie pour qu'elle marche tout le temps (solution: stocker les positions des differents carres ? une classe ?)
    // Recuperation des coordonnees des deux points à superposer (dans le repere de image 2)
    // numero de colonne : le reste de la division de hein.
    int offset_colonnes = indice_meilleure_ponderation % (IMAGE_SIZE/GRID_SIZE);

    // numero de ligne : le nombre de fois truc dans truc.
    int offset_lignes = 0;

    int indice = (IMAGE_SIZE / GRID_SIZE);

    while(indice < indice_meilleure_ponderation)
    {
        indice += (IMAGE_SIZE / GRID_SIZE);
        offset_lignes++;
    }



    int miniature_x = offset_colonnes*GRID_SIZE + flann[indice_meilleure_ponderation].getKeypoints_matched1(0).x;

    int miniature_y = offset_lignes*GRID_SIZE + flann[indice_meilleure_ponderation].getKeypoints_matched1(0).y;

    int image_x =  flann[indice_meilleure_ponderation].getKeypoints_matched2(0).x;

    int image_y = flann[indice_meilleure_ponderation].getKeypoints_matched2(0).y;


    printf("\nminiature x : %i\nminiature y : %i\nx: %i\ny: %i\n", miniature_x, miniature_y, image_x, image_y);
    printf("offset lignes : %i\noffset colonne:%i\n", offset_lignes, offset_colonnes);

    int decalage_x = image_x-miniature_x;
    int decalage_y = image_y-miniature_y;
    panorama_image = merge_process(img1, img2, decalage_x, decalage_y);

    return panorama_image;
}
