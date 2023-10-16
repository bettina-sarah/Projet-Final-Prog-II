#include <iostream>
#include <string>
#include <conio.h> //getch
#include <stdlib.h> //system cls

using namespace std;

const string Bibliotheque = "Bibliothèque de la MRC St-Clin-de-banlieue";

void main(void)
{
	setlocale(LC_CTYPE, "fr-CA");
	int OptionMenu;
	do
	{
		cout << "\t********\n";
		cout << Bibliotheque;
		cout << "\n\t********\n";
		cout << "\n\n****** MENU ******\n\t1. Nouveau livre\n\t2. Nouveau client\n\t3. Dossier du client\n\t4. Location de livre"
			"\n\t5. Retour des livres\n\t6. Liste des livres prêtés\n\t7. Liste des clients en retard\n\t8. Quitter";
		OptionMenu = _getche();
		switch (OptionMenu)
		{
		case '1':
			break;
		case '2':
			//string NomClient;
			//Client_s NouveauClient;
			//getline(cin, NomClient);
			//transform string en tab char

			break;
		case '3':
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
