#include <iostream>
#include <string>
#include <conio.h> //getch
#include <stdlib.h> //system cls
#include "clients.h" // prototypes client
#include "livres.h" // prototypes livres

using namespace std;

const string Bibliotheque = "Biblioth�que de la MRC St-Clin-de-banlieue";

void main(void)
{
	setlocale(LC_CTYPE, "fr-CA");
	int OptionMenu;
	string NomLivre;
	string NomAuteur;
	string NomClient;
	string NumeroTelephone;
	string Addresse;
	int IDClient;
	int IDLivre;
	int IDLivreALouer;
	int IDClientLoueur;
	do
	{
		cout << "\t********\n";
		cout << Bibliotheque;
		cout << "\n\t********\n";
		cout << "\n\n****** MENU ******\n\t1. Nouveau livre\n\t2. Nouveau client\n\t3. Dossier du client\n\t4. Location de livre"
			"\n\t5. Retour des livres\n\t6. Liste des livres pr�t�s\n\t7. Liste des clients en retard\n\t8. Quitter\n\n";
		cout << "9. Afficher Livre";// pour tester
		OptionMenu = _getche();
		switch(OptionMenu)
		{
		case '1':
			cout << "\n\n\n\nEntrez le titre du livre: ";
			getline(cin, NomLivre);
			cout << "\nEntrez l'auteur/autrice du livre: ";
			getline(cin, NomAuteur);
			NouveauLivre(NomLivre, NomAuteur);
			cout << "Livre ajout� avec succ�s.\nAppuyez sur une touche pour continuer...";
			OptionMenu = _getche();
			system("cls");
			break;
		case '2':
			
			cout << "\n\n\n\nEntrez le nom complet du client: ";
			getline(cin, NomClient);
			cout << "\nEntrez le num�ro de t�l�phone du client: ";
			getline(cin, NumeroTelephone);
			cout << "\nEntrez l'adresse du client: ";
			getline(cin, Addresse);
			NouveauClient(NomClient, NumeroTelephone, Addresse);

			cout << "Client ajout� avec succ�s.\nAppuyez sur une touche pour continuer...";
			OptionMenu = _getche();
			system("cls");
			break;
		case '3':
			cout << "\n\n\n\nEntrez le num�ro du client � afficher: ";
			cin >> IDClient;
			//IDClient = _getche();
			AfficherDossierClient(IDClient);
			//system("cls");
			break;
		case '4':
			cout << "\n\n\n\nEntrez le num�ro du client qui loue le livre: ";
			cin >> IDClientLoueur;
			cout << "\nEntrez le num�ro du livre � preter: ";
			cin >> IDLivreALouer;
			Location(IDLivreALouer, IDClientLoueur);
			cout << "Pret du livre enregistr�.\nAppuyez sur une touche pour continuer...";
			break;
		case '5':
			break;
		case '6':
			break;
		case '7':
			break;
		case '8':
			system("cls");
			_getch();
			break;
		case '9':
			cout << "\n\n\n\nEntrez le num�ro du livre � afficher: "; // option menu pour tester seulement
			cin >> IDLivre;
			//IDLivre = _getche();
			AfficherLivre(IDLivre);
			break;
		} 
	}
	while (OptionMenu != '8');

}
