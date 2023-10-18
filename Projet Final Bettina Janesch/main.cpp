#include <iostream>
#include <string>
#include <conio.h> //getch
#include <stdlib.h> //system cls
#include "clients.h" // pour les prototypes de fonc

using namespace std;

const string Bibliotheque = "Bibliothèque de la MRC St-Clin-de-banlieue";

void main(void)
{
	setlocale(LC_CTYPE, "fr-CA");
	int OptionMenu;
	string NomClient;
	string NumeroTelephone;
	string Addresse;
	int IDClient;
	do
	{
		cout << "\t********\n";
		cout << Bibliotheque;
		cout << "\n\t********\n";
		cout << "\n\n****** MENU ******\n\t1. Nouveau livre\n\t2. Nouveau client\n\t3. Dossier du client\n\t4. Location de livre"
			"\n\t5. Retour des livres\n\t6. Liste des livres prêtés\n\t7. Liste des clients en retard\n\t8. Quitter\n\n";
		OptionMenu = _getche();
		switch(OptionMenu)
		{
		case '1':
			break;
		case '2':
			
			cout << "\n\n\n\nEntrez le nom complet du client: ";
			getline(cin, NomClient);
			cout << "\nEntrez le numéro de téléphone du client: ";
			getline(cin, NumeroTelephone);
			cout << "\nEntrez l'adresse du client: ";
			getline(cin, Addresse);
			NouveauClient(NomClient, NumeroTelephone, Addresse);

			cout << "Client ajouté avec succès.\nAppuyez sur une touche pour continuer...";
			OptionMenu = _getche();
			system("cls");
			break;
		case '3':
			cout << "\n\n\n\nEntrez le numéro du client à afficher: ";
			cin >> IDClient;
			IDClient = _getche();
			AfficherDossierClient(IDClient);
			break;
		case '4':
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

		} 
	}
	while (OptionMenu != '8');

}
