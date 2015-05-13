#include <gtkmm.h>
#include <iostream>

#include "Panorama.h"

using namespace Gtk;
using namespace cv;
using namespace std;

void loadImage(Image& image, FileChooserButton& file, Mat& imageMatrix);
void fusionImage(Mat& image1, Mat& image2, Mat& resultMatrix, Image& result, Image& matches);

int main(int argc, char* argv[])
{
    /**-------------------------- Initialisation de gtkmm -------------------------*/
    Main app(argc, argv);

    /**-------------------------- Création de la fenêtre ------------------------------*/
    Window fenetre;

    /**---------------------- Initialisation de la fenêtre --------------------------*/
    fenetre.set_title("Merginator Deluxe");
    fenetre.resize(960, 480);
    fenetre.maximize();
    fenetre.set_border_width(20);



    /**---------------------- MISE EN PLACE DU CONTENU DE LA FENÊTRE --------------------*/

    // La barre d'onglets
    Notebook selector;

    /**---------------------- Diverses propriétés de la fenêtre ----------------------------*/

    //S'il y a trop d'onglets, nous pouvons naviguer à l'aide de flèche
    selector.set_scrollable();

    //Ajouter un menu contextuel lors du clic-droit pour la navigation
    selector.popup_enable();

    //Empêcher la barre d'avoir le focus
    selector.set_can_focus(false);

    //Définir le groupe de la barre d'onglets (pour pouvoir échanger des onglets avec d'autres barre d'onglets)
    selector.set_group_name("onglets");



    /**-------------------- Premier onglet ------------------------*/

    // L'entier qui gère la place occupée par les boutons
    int space = 15;

    // La table pour ranger les widgets
    Table table1(space, 1, true);
    table1.set_border_width(20);

    // La table pour ranger les boutons
    Table buttons1(1, 4, true);
    buttons1.set_col_spacings(100);

    // Le bouton pour charger un fichier
    FileChooserButton file1("Sélectionnez une image");

    // L'image 1 chargée
    Image image1;
    Mat image1Matrix;

    // Le bouton pour loader le fichier
    Button load1("Charger");

    // On connecte ce bouton à la fonction loadImage1
    load1.signal_clicked().connect(sigc::bind<Image&, FileChooserButton&, Mat&>(sigc::ptr_fun(loadImage), image1, file1, image1Matrix));

    // On place les boutons dans la table
    buttons1.attach(file1, 1, 2, 0, 1);
    buttons1.attach(load1, 2, 3, 0, 1);

    // On place les boutons et l'image dans la table principale
    table1.attach(buttons1, 0, 1, 0, 1);
    table1.attach(image1, 0, 1, 1, space);

    // On place dans la barre d'onglets la boite
    selector.append_page(table1, "Chargement Image 1");







    /**-------------------- Deuxième onglet ------------------------*/

    // La table pour ranger les widgets
    Table table2(space, 1, true);
    table2.set_border_width(20);

    // La table pour ranger les boutons
    Table buttons2(1, 4, true);
    buttons2.set_col_spacings(100);

    // Le bouton pour charger un fichier
    FileChooserButton file2("Sélectionnez une image");

    // L'image 2 chargée
    Image image2;
    Mat image2Matrix;

    // Le bouton pour loader le fichier
    Button load2("Charger");

    // On connecte ce bouton à la fonction loadImage1
    load2.signal_clicked().connect(sigc::bind<Image&, FileChooserButton&, Mat&>(sigc::ptr_fun(loadImage), image2, file2, image2Matrix));

    // On place les boutons dans la table
    buttons2.attach(file2, 1, 2, 0, 1);
    buttons2.attach(load2, 2, 3, 0, 1);

    // On place les boutons et l'image dans la table principale
    table2.attach(buttons2, 0, 1, 0, 1);
    table2.attach(image2, 0, 1, 1, space);

    // On place dans la barre d'onglets la boite
    selector.append_page(table2, "Chargement Image 2");










    /**-------------------- Troisième onglet ------------------------*/

    // La table pour ranger les widgets
    Table table3(space, 1, true);
    table3.set_border_width(20);

    // La table pour ranger les boutons
    Table buttons3(1, 3, true);
    buttons3.set_col_spacings(100);

    // L'image qui contient la fusion
    Image result;
    Mat resultMatrix;

    // Le bouton pour afficher le résultat
    Button fusion("FUSION");

    // On place les boutons dans la table
    buttons3.attach(fusion, 1, 2, 0, 1);

    // On place les boutons et l'image dans la table principale
    table3.attach(buttons3, 0, 1, 0, 1);
    table3.attach(result, 0, 1, 1, space);

    // On place dans la barre d'onglets la boite
    selector.append_page(table3, "Rendu Panorama");

    /**-------------------- Quatrième onglet ------------------------*/

    // L'image qui contient l'exemple
    Image matches;

    // On place dans la barre d'onglets la boite
    selector.append_page(matches, "Exemple de fonctionnement");


    // On est obligé de faire la connection ici car le quatrième onglet n'était pas créé avant
    fusion.signal_clicked().connect(sigc::bind<Mat&, Mat&, Mat&, Image&, Image&>(sigc::ptr_fun(fusionImage), image1Matrix, image2Matrix, resultMatrix, result, matches));






    /**----- Ajout de la barre d'onglets à la fenêtre -----*/
    fenetre.add(selector);

    /**----- Affichage de tous les widgets -----*/
    fenetre.show_all();

    /**----- Lancement de la boucle principale permettant l'affichage -----*/
    Main::run(fenetre);

    return 0;
}

void loadImage(Image& image, FileChooserButton& file, Mat& imageMatrix)
{
    image.set(file.get_filename());
    imageMatrix = imread(file.get_filename(), CV_LOAD_IMAGE_COLOR);
}

void fusionImage(Mat& image1, Mat& image2, Mat& resultMatrix, Image& result, Image& matches)
{
    resultMatrix = panorama_process(image1, image2);

    Rect rect(250,250,900,600);
    Mat cropResult = resultMatrix(rect);
    resize(cropResult, cropResult, Size(870, 580), 0, 0, INTER_LINEAR);

    imwrite("img/result.jpg", cropResult);

    result.set("img/result.jpg");
    matches.set("img/matches.jpg");
}
