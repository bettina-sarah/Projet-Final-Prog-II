#include <iostream>
#include <string>
#include <conio.h> //getch
#include <stdlib.h> //system cls
#include "clients.h" // prototypes client
#include "livres.h" // prototypes livres

using namespace std;

void main(void)
{
	setlocale(LC_CTYPE, "fr-CA");
	char OptionMenu;
	string NomLivre;
	string NomAuteur;
	string NomClient;
	string NumeroTelephone;
	string Addresse;
	int IDClient;
	int IDLivre;
	int IDLivreALouer;
	int IDClientLoueur;
	int IDClientRetour;
	
	do
	{
		cout << "****************************************************\n";
		cout << "*    Biblioth�que de la MRC St-Clin-de-banlieue    *";
		cout << "\n****************************************************\n";
		cout << "\n\n****** MENU ******\n\t1. Nouveau livre\n\t2. Nouveau client\n\t3. Dossier du client\n\t4. Location de livre"
			"\n\t5. Retour des livres\n\t6. Liste des livres pr�t�s\n\t7. Liste des clients en retard\n\t8. Quitter";
		cout << "\n9. Afficher Livre (extra)\n*. Mettre un client en retard\n";    // pour tester
		OptionMenu = _getche();
		switch(OptionMenu)
		{
		case '1':
			cout << "\n\n\n\nEntrez le titre du livre: ";
			getline(cin, NomLivre);
			cout << "\nEntrez l'auteur/autrice du livre: ";
			getline(cin, NomAuteur);
			NouveauLivre(NomLivre, NomAuteur);
			cout << "\nAppuyez sur une touche pour continuer...";
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
			OptionMenu = _getche();
			system("cls");
			break;
		case '3':
			cout << "\n\n\n\nEntrez le num�ro du client � afficher: ";
			cin >> IDClient;
			//IDClient = _getche();
			AfficherDossierClient(IDClient);
			cout << "\nAppuyez sur une touche pour continuer...";
			OptionMenu = _getche();
			system("cls");
			break;
		case '4':
			cout << "\n\n\n\nEntrez le num�ro du client qui loue le livre: ";
			cin >> IDClientLoueur;
			cout << "\nEntrez le num�ro du livre � preter: ";
			cin >> IDLivreALouer;
			Location(IDClientLoueur, IDLivreALouer);
			cout << "\nAppuyez sur une touche pour continuer...";
			OptionMenu = _getche();
			system("cls");
			break;
		case '5':
			cout << "\n\n\n\nEntrez le num�ro du client qui retourne tous ses livres: ";
			cin >> IDClientRetour;
			Retour(IDClientRetour);
			cout << "\nAppuyez sur une touche pour continuer...";
			OptionMenu = _getche();
			system("cls");
			break;
		case '6':
			ListeDesLivresPretes();
			cout << "\nAppuyez sur une touche pour continuer...";
			OptionMenu = _getche();
			system("cls");
			break;
		case '7':
			ListeDesClientsEnRetard();
			cout << "\nAppuyez sur une touche pour continuer...";
			OptionMenu = _getche();
			system("cls");
			break;
		case '8':
			system("cls");
			_getch();
			break;
		 //OPTIONS TEST:
		case '9':
			cout << "\n\n\n\nEntrez le num�ro du livre � afficher: "; // option menu pour tester seulement
			cin >> IDLivre;
			//IDLivre = _getche();
			AfficherLivre(IDLivre);
			break;
		case '*':
			cout << "\n\n\n\nEntrez le num�ro du client � mettre en retard: "; // option menu pour tester seulement
			cin >> IDClient;
			cout << "\nEntrez le livre a mettre en retard";
			cin >> IDLivre;
			MettreClientEnRetard(IDClient, IDLivre);
			break;
		} 
	}
	while (OptionMenu != '8');

}
