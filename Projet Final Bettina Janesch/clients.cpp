#include <iostream>
#include "clients.h"
#include "utils.h"
#include "livres.h" // pour struct Livre_s et chemin fichier livres
#include <fstream>
#include <string>

using namespace std;

struct LivresPretes_s
{
	int NumeroLivre;
	Date_s Maintenant;
	Date_s Retour;
};

struct Client_s
{
	int IDClient;
	char NomClient[MAX_CHAR];
	char NumeroTelephone[10];
	char Adresse[MAX_CHAR];
	Date_s DateInscription;
	int NumeroLivresPretes; // max 3
	LivresPretes_s Livres[3];
};

static Client_s RechercherDossierClient(int& IDClientRecherche);

static void MettreAJourClient(Client_s ClientLoueur, int& IDClientRecherche);

extern const string NOM_FICHIER_CLIENTS = ".\\fichiers\\clients.bin";

void NouveauClient(string Nom, string Telephone, string Addresse)
{
	fstream Fichier;
	static int IDNouveauClient = 0;
	Client_s NouveauClient;
	char CharNom[MAX_CHAR];
	char CharTelephone[10];
	char CharAddresse[MAX_CHAR];


	Fichier.open(NOM_FICHIER_CLIENTS, ios::app | ios::binary);

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	// assign numero client au struct + incrementation

	NouveauClient.IDClient = IDNouveauClient;
	IDNouveauClient++;

	//string en tab char + mettre dans structure

	StringEnTabChar(Nom, CharNom);
	StringEnTabChar(Telephone, CharTelephone);
	StringEnTabChar(Addresse, CharAddresse);

	for (int i = 0; i < MAX_CHAR; i++)
	{
		NouveauClient.NomClient[i] = CharNom[i];
	}

	for (int i = 0; i < 10; i++)
	{
		NouveauClient.NumeroTelephone[i] = CharTelephone[i];
	}

	for (int i = 0; i < MAX_CHAR; i++)
	{
		NouveauClient.Adresse[i] = CharAddresse[i];
	}

	// Date Inscription dans struct

	NouveauClient.DateInscription = Aujourdhui();

	// Livres pret�s: initialis� a 0
	NouveauClient.NumeroLivresPretes = 0;
	//besoin de faire qq chose au tableau de livres? deja zero techniquement
	
	Fichier.write((char*)&NouveauClient, sizeof(Client_s));
	cout << "Client ajout� avec succ�s.\nAppuyez sur une touche pour continuer...";

	Fichier.close();

}

static int CompterClients()
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

	cout << "Num�ro de client invalide.\nAppuyez sur une touche pour continuer..."; // code execut� seulement si struct Client non-trouvable
	Fichier.close();
	return ClientInvalide;// return une struct vide de Client;
}

void AfficherDossierClient(int &IDClientRecherche) // pas bon faut quil loop sur rechercherclient
{
	Client_s LireClient;
	LireClient = RechercherDossierClient(IDClientRecherche);

	if (LireClient.IDClient == IDClientRecherche && LireClient.IDClient>=0)
	{
		cout << "\n\n\n+++ DOSSIER DU CLIENT +++\n------------\n";

		cout << "\nID Client: " << LireClient.IDClient << "\nNom client: " << LireClient.NomClient << "\nNum�ro t�l�phone: " << LireClient.NumeroTelephone << "\nAddresse: " << LireClient.Adresse;
		cout << "\nDate inscription: " << LireClient.DateInscription.Annee << "-" << LireClient.DateInscription.Mois << "-" << LireClient.DateInscription.Jour;
		cout << "\nNombre de livres pret�s: " << LireClient.NumeroLivresPretes;
		//test:

		cout << "\nTEST:\n";

		for (int i = 0; i < 3; i++)
		{
			cout << "Date pret : " << LireClient.Livres[i].Maintenant.Annee << LireClient.Livres[i].Maintenant.Mois << LireClient.Livres[i].Maintenant.Jour;
			cout << "\nDate retour + 15: " << LireClient.Livres[i].Retour.Annee << LireClient.Livres[i].Retour.Mois << LireClient.Livres[i].Retour.Jour << "\nNum�ro livre: ";
			cout << LireClient.Livres[i].NumeroLivre << "\n\n";
		}
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
	cout << "Nom (T�l�phone)\t\tDate de retour pr�vue\tJours de retard";
	cout << "\n------------------------------------------------------------------\n";

	for (int i = 0; i < NombreClients; i++) //parcourir tous les clients 0 a x
	{
		ClientRetard = RechercherDossierClient(i); //client 0,1,2...

		if (ClientRetard.NumeroLivresPretes >= 1) // if pour seulement si client a une livre pret� au moins
		{
			for (int i = 0; i < ClientRetard.NumeroLivresPretes; i++) // verifier si une des livres est en retard
			{
				bool Retard = false;
				if (NombreJours(ClientRetard.Livres[i].Retour, Aujourdhui()) >= 1) // ca verifie seulement 3eme livre though ? a verifier
				{
					Retard = true;
				}


				if (Retard) // si retard existe  (diff entre date retour et ajd >=1)
				{
					cout << "\n" << ClientRetard.NomClient << " ( " << ClientRetard.NumeroTelephone << " ) \t\t" << ClientRetard.Livres[i].Retour.Jour << "/";
					cout << ClientRetard.Livres[i].Retour.Mois << "/" << ClientRetard.Livres[i].Retour.Annee << "\t\t" << NombreJours(ClientRetard.Livres[i].Retour, Aujourdhui()) << "\n";
					Retard = false; // juste pour afficher 1 livre seulement
				}
			}
		}
	}
} 

void Location(int& IDClientLoueur, int& IDLivreALouer) // faire fonction pour si client vide, erreur
{
	Client_s ClientLoueur;
	Livre_s LivreALouer;

	ClientLoueur = RechercherDossierClient(IDClientLoueur);
	LivreALouer = RechercherLivre(IDLivreALouer);

	if (ClientLoueur.NumeroLivresPretes < 3)
	{
		//1. changer infos client
		//1.1. Numero livre lou� + date aujourdhui + date retour
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

		cout << "Pret du livre enregistr�.";
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
	}

	else if (ClientLoueur.NumeroLivresPretes < 1)
	{
		cout << "Erreur. Client n'a pas des livres � retourner";
	}
}

void MettreClientEnRetard(int Client, int Livre)
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


