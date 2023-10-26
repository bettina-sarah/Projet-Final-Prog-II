#include <iostream>
#include "clients.h"
#include "utils.h"
#include "livres.h" // pour struct Livre_s et chemin fichier livres
#include <fstream>
#include <string>

using namespace std;

extern const string NOM_FICHIER_CLIENTS = ".\\fichiers\\clients.bin";

//maison: "C:\\Users\\betti\\source\\repos\\Projet-Final-Prog-II\\Projet Final Bettina Janesch\\fichiers\\clients.bin";

//ecole: "C:\\Users\\1649508\\source\\repos\\Projet-Final-Prog-II\\Projet Final Bettina Janesch\\fichiers\\clients.bin";

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

	NouveauClient.IDClient = IDNouveauClient; // marche pas ????
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

	// Livres pretés: initialisé a 0
	NouveauClient.NumeroLivresPretes = 0;
	//besoin de faire qq chose au tableau de livres? deja zero techniquement
	
	Fichier.write((char*)&NouveauClient, sizeof(Client_s));

	Fichier.close();

}

int CompterClients()
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
	fstream Fichier;
	bool Trouve = false;
	Fichier.open(NOM_FICHIER_CLIENTS, ios::in | ios::binary);

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	Fichier.read((char*)&ClientTrouve, sizeof(Client_s));
	
	while (!Fichier.eof())
	{
		if (ClientTrouve.IDClient == IDClientRecherche)
		{
			Fichier.seekg(sizeof(Client_s) * ClientTrouve.IDClient, ios::beg);
			Fichier.read((char*)&ClientTrouve, sizeof(Client_s));
			Trouve = true;
			return ClientTrouve;
		}

		Fichier.read((char*)&ClientTrouve, sizeof(Client_s));
	}

	if (!Trouve)
	{
		cout << "Numéro de client invalide.\nAppuyez sur une touche pour continuer...";
	}

	Fichier.close();

}

void AfficherDossierClient(int &IDClientRecherche) // pas bon faut quil loop sur rechercherclient
{
	Client_s LireClient;
	LireClient = RechercherDossierClient(IDClientRecherche);

	if (LireClient.IDClient == IDClientRecherche)
	{
		cout << "\n\n\n+++ DOSSIER DU CLIENT +++\n------------\n";

		cout << "\nID Client: " << LireClient.IDClient << "\nNom client: " << LireClient.NomClient << "\nNuméro téléphone: " << LireClient.NumeroTelephone << "\nAddresse: " << LireClient.Adresse;
		cout << "\nDate inscription: " << LireClient.DateInscription.Annee << "-" << LireClient.DateInscription.Mois << "-" << LireClient.DateInscription.Jour;
		cout << "\nNombre de livres pretés: " << LireClient.NumeroLivresPretes;
		//test:

		cout << "\nTEST:\n";

		for (int i = 0; i < 3; i++)
		{
			cout << "Date pret : " << LireClient.Livres[i].Maintenant.Annee << LireClient.Livres[i].Maintenant.Mois << LireClient.Livres[i].Maintenant.Jour;
			cout << "\nDate retour + 15: " << LireClient.Livres[i].Retour.Annee << LireClient.Livres[i].Retour.Mois << LireClient.Livres[i].Retour.Jour << "\nNuméro livre: ";
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

	bool Retard = false;
	int NombreClients = CompterClients();

	for (int i = 0; i < NombreClients; i++) //parcourir tous les clients A REPARER while(eof) sans fonc rechercher et juste parcourir dans fichier a place?
	{
		ClientRetard = RechercherDossierClient(i);

		if (NombreJours(ClientRetard.Livres[ClientRetard.NumeroLivresPretes].Retour, Aujourdhui()) >= 1)
		{
			Retard = true;
		}

		for (int i = 0; i < ClientRetard.NumeroLivresPretes; i++) // verifier si une des livres est en retard
		{
			if (Retard) // si retard existe  (diff entre date retour et ajd >=1)
			{
				cout << "\n\n\n+++ CLIENTS AVEC DES PRETS EN RETARD +++\n------------\n";
				cout << "Nom (Téléphone)\t\tDate de retour prévue\tJours de retard";
				cout << "\n-----------------------------------------\n";
				cout << "\n" << ClientRetard.NomClient << " ( " << ClientRetard.NumeroTelephone << "\t" << ClientRetard.Livres[i].Retour.Jour << "/";
				cout << ClientRetard.Livres[i].Retour.Mois << "/" << ClientRetard.Livres[i].Retour.Annee << NombreJours(ClientRetard.Livres[i].Retour, Aujourdhui());
				Retard = false; // juste pour afficher 1 livre seulement
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

	if (ClientLoueur.NumeroLivresPretes < 3)
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

	else if (ClientLoueur.NumeroLivresPretes >= 3 ) // donné 100 pour eviter d'avoir ce message en cas d'une structure vide du client/invalide
	{
		cout << "Maximum de locations (3) atteint, location de ce livre non permise.";
	}
}

void Retour(int& IDClientLoueur)
{
	Client_s ClientLoueur;
	Livre_s LivreARetourner;

	ClientLoueur = RechercherDossierClient(IDClientLoueur);

	LivresPretes_s NouveauTableau[3];

	for (int i = 0; i < ClientLoueur.NumeroLivresPretes; i++)
	{
		//2. changer infos livre // 
		LivreARetourner = RechercherLivre(ClientLoueur.Livres[i].NumeroLivre);
		LivreARetourner.EtatPret = false;
		MettreAJourLivre(LivreARetourner, ClientLoueur.Livres[i].NumeroLivre);

		//tableau a zero MARCHE PAS

		ClientLoueur.Livres[i].Maintenant = NouveauTableau[i].Maintenant;
		ClientLoueur.Livres[i].NumeroLivre = NouveauTableau[i].NumeroLivre;
		ClientLoueur.Livres[i].Retour = NouveauTableau[i].Retour;

		//3. push structs dans les fichiers
		MettreAJourClient(ClientLoueur, IDClientLoueur);

	}
	ClientLoueur.NumeroLivresPretes = 0;
	MettreAJourClient(ClientLoueur, IDClientLoueur);

//Si le client est en retard, on retourne le nombre de jours de retard.Vous pouvez calculer le nombre de jours grâce à la fonction NombreJours.
//La fonction NombreJours(Date_s Date1, Date_s Date_2) retourne un int qui correspond au nombre de jours de Date2 – Date 1. 
//Cette fonction est utile pour vérifier le nombre de jours de retard d’un livre.
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


