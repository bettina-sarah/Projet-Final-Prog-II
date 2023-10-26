#include <iostream>
#include "clients.h"
#include "utils.h"
#include "livres.h" // pour struct Livre_s et chemin fichier livres
#include <fstream>
#include <string>

using namespace std;

extern const string NOM_FICHIER_CLIENTS = ".\\fichiers\\clients.bin";

struct LivresPretes_s
{
	int NumeroLivre;
	Date_s Maintenant;
	Date_s Retour;
};

struct Client_s
{
	int IDClient;
	char NomClient[MAX_CHAR_CLIENTS];
	char NumeroTelephone[10];
	char Adresse[MAX_CHAR_CLIENTS];
	Date_s DateInscription;
	int NumeroLivresPretes; // max 3
	LivresPretes_s Livres[3];
};

// prototypes fonctions privés

static Client_s RechercherDossierClient(int& IDClientRecherche);

static void MettreAJourClient(Client_s ClientLoueur, int& IDClientRecherche);

static int CompterClients();

//fonctions client

void NouveauClient(string Nom, string Telephone, string Addresse)
{
	fstream Fichier;
	static int IDNouveauClient = 0;
	Client_s NouveauClient;

	Fichier.open(NOM_FICHIER_CLIENTS, ios::app | ios::binary);

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	// assign numero client au struct + incrementation

	NouveauClient.IDClient = IDNouveauClient;
	IDNouveauClient++;

	//string en tab char

	StringEnTabChar(Nom, NouveauClient.NomClient);
	StringEnTabChar(Telephone, NouveauClient.NumeroTelephone);
	StringEnTabChar(Addresse, NouveauClient.Adresse);

	// Date Inscription dans struct

	NouveauClient.DateInscription = Aujourdhui();

	// Livres pretés: initialisé a 0
	NouveauClient.NumeroLivresPretes = 0;
	//besoin de faire qq chose au tableau de livres? deja zero techniquement
	
	Fichier.write((char*)&NouveauClient, sizeof(Client_s));
	cout << "Client ajouté avec succès.\nAppuyez sur une touche pour continuer...";

	Fichier.close();

}

static int CompterClients() // utilisé pour avoir le nombre de clients inscrits
{
	fstream Fichier;
	Client_s ClientCompte;
	int NumeroClients = 0;

	Fichier.open(NOM_FICHIER_CLIENTS, ios::in | ios::binary);

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	Fichier.read((char*)&ClientCompte, sizeof(Client_s));

	while (!Fichier.eof())
	{
		NumeroClients++;
		Fichier.read((char*)&ClientCompte, sizeof(Client_s));
	}

	Fichier.close();
	return NumeroClients;
}

static Client_s RechercherDossierClient(int &IDClientRecherche)
{
	Client_s ClientTrouve;
	Client_s ClientInvalide = { -1, {' '},{' '},{' '}, {0,0,0} ,-1 ,{0,{0,0,0},{0,0,0}} };
	fstream Fichier;
	Fichier.open(NOM_FICHIER_CLIENTS, ios::in | ios::binary);

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	Fichier.read((char*)&ClientTrouve, sizeof(Client_s));
	
	while (!Fichier.eof())
	{
		if (ClientTrouve.IDClient == IDClientRecherche && ClientTrouve.IDClient >=0)
		{

			Fichier.seekg(sizeof(Client_s) * ClientTrouve.IDClient, ios::beg);
			Fichier.read((char*)&ClientTrouve, sizeof(Client_s));
			Fichier.close();
			return ClientTrouve;
		}

		Fichier.read((char*)&ClientTrouve, sizeof(Client_s));
	}

	cout << "\nNuméro de client invalide."; // code executé seulement si struct Client non-trouvable
	Fichier.close();
	return ClientInvalide;// return une struct vide de Client;
}

void AfficherDossierClient(int &IDClientRecherche)
{
	Client_s LireClient;
	LireClient = RechercherDossierClient(IDClientRecherche);

	if (LireClient.IDClient == IDClientRecherche && LireClient.IDClient>=0)
	{
		cout << "\n\n\n+++ DOSSIER DU CLIENT +++\n--------------------------\n";

		cout << "\nID Client: " << LireClient.IDClient << "\nNom client: " << LireClient.NomClient << "\nNuméro téléphone: " << LireClient.NumeroTelephone << "\nAddresse: " << LireClient.Adresse;
		cout << "\nDate inscription: " << LireClient.DateInscription.Annee << "-" << LireClient.DateInscription.Mois << "-" << LireClient.DateInscription.Jour;
		cout << "\nNombre de livres pretés: " << LireClient.NumeroLivresPretes;
		
		
		//test:
		//cout << "\nTEST:\n";

		//for (int i = 0; i < 3; i++)
		//{
		//	cout << "Date pret : " << LireClient.Livres[i].Maintenant.Annee << LireClient.Livres[i].Maintenant.Mois << LireClient.Livres[i].Maintenant.Jour;
		//	cout << "\nDate retour + 15: " << LireClient.Livres[i].Retour.Annee << LireClient.Livres[i].Retour.Mois << LireClient.Livres[i].Retour.Jour << "\nNuméro livre: ";
		//	cout << LireClient.Livres[i].NumeroLivre << "\n\n";
		//}
	}
}

static void MettreAJourClient(Client_s ClientLoueur, int &IDClientRecherche)
{
	fstream Fichier;

	Fichier.open(NOM_FICHIER_CLIENTS, ios::in | ios::out | ios::binary); // au lieu de: 

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	Fichier.seekp(sizeof(Client_s) * ClientLoueur.IDClient, ios::beg);
	Fichier.write((char*)&ClientLoueur, sizeof(Client_s));

	Fichier.close();
} 

// Fonctions locations/retours/retards 

void ListeDesClientsEnRetard() // A REPARER
{
	Client_s ClientRetard;

	int NombreClients = CompterClients();

	cout << "\n\n\n\t\t+++ CLIENTS AVEC DES PRETS EN RETARD +++\n------------------------------------------------------------------\n";
	cout << "Nom (Téléphone)\t\tDate de retour prévue\tJours de retard";
	cout << "\n------------------------------------------------------------------\n";

	for (int j = 0; j < NombreClients; j++) //parcourir tous les clients 0 a x
	{
		ClientRetard = RechercherDossierClient(j); //client 0,1,2...

		if (ClientRetard.NumeroLivresPretes >= 1) // if pour seulement si client a une livre preté au moins
		{
			for (int i = 0; i < ClientRetard.NumeroLivresPretes; i++)
			{
				bool Retard = false;
				if (NombreJours(ClientRetard.Livres[i].Retour, Aujourdhui()) >= 1) // verifier si une des livres est en retard
				{
					Retard = true;
				}


				if (Retard) // si retard existe  (diff entre date retour et ajd >=1)
				{
					cout << "\n" << ClientRetard.NomClient << " ( " << ClientRetard.NumeroTelephone << " ) \t\t" << ClientRetard.Livres[i].Retour.Jour << "/";
					cout << ClientRetard.Livres[i].Retour.Mois << "/" << ClientRetard.Livres[i].Retour.Annee << "\t\t" << NombreJours(ClientRetard.Livres[i].Retour, Aujourdhui()) << "\n";
					Retard = false; // juste pour afficher 1 livre seulement
				}
				else if (!Retard)
				{
					if (j == 0 && i==0) // pour que ca affiche seulement 1 fois
					{
						cout << "Aucun client est en retard présentement.";
					}
					
				}
			}
		}
		else if (ClientRetard.NumeroLivresPretes == 0)
		{
			if (j == 0) // pour que ca affiche seulement 1 fois
		{
			cout << "Aucun client a des livres loués.";
		}
			
		}

	}
} 

void Location(int& IDClientLoueur, int& IDLivreALouer)
{
	Client_s ClientLoueur;
	Livre_s LivreALouer;

	ClientLoueur = RechercherDossierClient(IDClientLoueur);
	LivreALouer = RechercherLivre(IDLivreALouer);

	if (ClientLoueur.NumeroLivresPretes < 3 && ClientLoueur.NumeroLivresPretes >= 0 && LivreALouer.IDLivre == IDLivreALouer) // 2eme condition pour qu'une structure vide rentrera pas dans le bloc de code
	{
		//1. changer infos client
		//1.1. Numero livre loué + date aujourdhui + date retour
		ClientLoueur.Livres[ClientLoueur.NumeroLivresPretes].NumeroLivre = IDLivreALouer;
		ClientLoueur.Livres[ClientLoueur.NumeroLivresPretes].Maintenant = Aujourdhui();
		ClientLoueur.Livres[ClientLoueur.NumeroLivresPretes].Retour = AjouterJours(15, Aujourdhui());

			// 1.2 modifier nombre de livres pretes
		ClientLoueur.NumeroLivresPretes++;
			
		//2. changer infos livre
		LivreALouer.EtatPret = true;

		//3. push structs dans les fichiers
		MettreAJourClient(ClientLoueur, IDClientLoueur);
		MettreAJourLivre(LivreALouer, IDLivreALouer);
		cout << "Pret du livre enregistré.";
	}

	else if (ClientLoueur.NumeroLivresPretes >= 3 )
	{
		cout << "Maximum de locations (3) atteint, location de ce livre non permise.";
	}
}

void Retour(int& IDClientLoueur)
{
	Client_s ClientLoueur;
	Livre_s LivreARetourner;

	ClientLoueur = RechercherDossierClient(IDClientLoueur);

	if (ClientLoueur.IDClient == IDClientLoueur)
	{
		if (ClientLoueur.NumeroLivresPretes >= 1)
		{
			for (int i = 0; i < ClientLoueur.NumeroLivresPretes; i++)
			{
				//2. changer infos livre // 
				LivreARetourner = RechercherLivre(ClientLoueur.Livres[i].NumeroLivre);
				LivreARetourner.EtatPret = false;
				MettreAJourLivre(LivreARetourner, ClientLoueur.Livres[i].NumeroLivre);

				//tableau a zero MARCHE PAS

				ClientLoueur.Livres[i].Maintenant = { 0,0,0 };
				ClientLoueur.Livres[i].NumeroLivre = -1;
				ClientLoueur.Livres[i].Retour = { 0,0,0 };

				//3. push structs dans les fichiers
				MettreAJourClient(ClientLoueur, IDClientLoueur);

			}
			ClientLoueur.NumeroLivresPretes = 0;
			MettreAJourClient(ClientLoueur, IDClientLoueur);
			cout << "Retour des livres enregistré.";
		}

		else if (ClientLoueur.NumeroLivresPretes < 1)
		{
			cout << "Erreur. Client n'a pas des livres à retourner";
		}
	}
}

void MettreClientEnRetard(int Client, int Livre) // fonction test
{
	Client_s ClientRetard;
	Livre_s LivreRetard;

	ClientRetard = RechercherDossierClient(Client);
	LivreRetard = RechercherLivre(Livre);

	for (int i = 0; i < ClientRetard.NumeroLivresPretes; i++)
	{
		if (ClientRetard.Livres[i].NumeroLivre == Livre)
		{
			ClientRetard.Livres[i].Retour.Mois = 9;

			MettreAJourClient(ClientRetard, Client);
		}
	}


}


