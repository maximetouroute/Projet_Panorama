#include <gtkmm.h>
#include <iostream>

using namespace Gtk;
using namespace std;

void loadImage1(Image& image1, FileChooserButton& bouton1);
void loadImage2(Image& image2, FileChooserButton& bouton2);

int main(int argc, char* argv[])
{
	/*-------------------------- Initialisation de gtkmm -------------------------*/
	Gtk::Main app(argc, argv);

	/*-------------------------- Création de la fenêtre ------------------------------*/
	Window fenetre;

	/*---------------------- Initialisation de la fenêtre --------------------------*/
	fenetre.set_title("Merginator Deluxe");
	fenetre.set_icon_from_file("img/icon_small.png");
	fenetre.resize(960, 480);
	fenetre.maximize();
	fenetre.set_border_width(20);



	/*---------------------- MISE EN PLACE DU CONTENU DE LA FENÊTRE --------------------*/

	// La barre d'onglets
	Notebook selector;

	/*---------------------- Diverses propriétés de la fenêtre ----------------------------*/

	//S'il y a trop d'onglets, nous pouvons naviguer à l'aide de flèche
	selector.set_scrollable();

	//Ajouter un menu contextuel lors du clic-droit pour la navigation
	selector.popup_enable();

	//Empêcher la barre d'avoir le focus
	selector.set_can_focus(false);

	//Définir le groupe de la barre d'onglets (pour pouvoir échanger des onglets avec d'autres barre d'onglets)
	selector.set_group_name("onglets");



	/*-------------------- Premier onglet ------------------------*/

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

	// Le bouton pour loader le fichier
	Button load1("Charger");

	// On connecte ce bouton à la fonction loadImage1
	load1.signal_clicked().connect(sigc::bind<Image&, FileChooserButton&>(sigc::ptr_fun(loadImage1), image1, file1));

	// On place les boutons dans la table
	buttons1.attach(file1, 1, 2, 0, 1);
	buttons1.attach(load1, 2, 3, 0, 1);

	// On place les boutons et l'image dans la table principale
	table1.attach(buttons1, 0, 1, 0, 1);
	table1.attach(image1, 0, 1, 1, space);

	// On place dans la barre d'onglets la boite
	selector.append_page(table1, "Chargement Image 1");







	/*-------------------- Deuxième onglet ------------------------*/

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

	// Le bouton pour loader le fichier
	Button load2("Charger");

	// On connecte ce bouton à la fonction loadImage1
	load2.signal_clicked().connect(sigc::bind<Image&, FileChooserButton&>(sigc::ptr_fun(loadImage2), image2, file2));

	// On place les boutons dans la table
	buttons2.attach(file2, 1, 2, 0, 1);
	buttons2.attach(load2, 2, 3, 0, 1);

	// On place les boutons et l'image dans la table principale
	table2.attach(buttons2, 0, 1, 0, 1);
	table2.attach(image2, 0, 1, 1, space);

	// On place dans la barre d'onglets la boite
	selector.append_page(table2, "Chargement Image 2");










	/*-------------------- Troisième onglet ------------------------*/

	// La table pour ranger les widgets
	Table table3(space, 1, true);
	table3.set_border_width(20);

	// La table pour ranger les boutons
	Table buttons3(1, 3, true);
	buttons3.set_col_spacings(100);

	// L'image qui contient la fusion
	Image result;

	// Le bouton pour afficher le résultat
	Button fusion("FUSION");

	// CONNECTER LE BOUTON AVEC UNE FONCTION

	// On place les boutons dans la table
	buttons3.attach(fusion, 1, 2, 0, 1);

	// On place les boutons et l'image dans la table principale
	table3.attach(buttons3, 0, 1, 0, 1);
	table3.attach(result, 0, 1, 1, space);

	// On place dans la barre d'onglets la boite
	selector.append_page(table3, "Rendu Panorama");











	/*----- Ajout de la barre d'onglets à la fenêtre -----*/
	fenetre.add(selector);

	/*----- Affichage de tous les widgets -----*/
	fenetre.show_all();

	/*----- Lancement de la boucle principale permettant l'affichage -----*/
	Main::run(fenetre);

	return 0;
}

void loadImage1(Image& image1, FileChooserButton& bouton1)
{
	image1.set(bouton1.get_filename());
}

void loadImage2(Image& image2, FileChooserButton& bouton2)
{
	image2.set(bouton2.get_filename());
}
