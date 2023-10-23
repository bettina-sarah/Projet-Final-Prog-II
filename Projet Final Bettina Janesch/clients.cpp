#include <iostream>
#include "clients.h"
#include "utils.h"
#include <fstream>
#include <string>

using namespace std;

//struct LivresPretes_s
//{
//	int NumeroLivre;
//	Date_s Maintenant;
//	Date_s Retour;
//};

//struct Client_s
//{
//	int IDClient;
//	char NomClient[MAX_CHAR];
//	char NumeroTelephone[10];
//	char Adresse[MAX_CHAR];
//	Date_s DateInscription;
//	int NumeroLivresPretes; // max 3
//	LivresPretes_s Livres[3];
//};

void NouveauClient(string Nom, string Telephone, string Addresse)
{
	fstream Fichier;
	string CheminFichier = NOM_FICHIER_CLIENTS;
	static int IDNouveauClient = 0;
	Client_s NouveauClient;
	char CharNom[MAX_CHAR];
	char CharTelephone[10];
	char CharAddresse[MAX_CHAR];


	Fichier.open(CheminFichier, ios::app | ios::binary);

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

Client_s RechercherDossierClient(int &IDClientRecherche)
{
	Client_s ClientTrouve;

	fstream Fichier;
	string CheminFichier = NOM_FICHIER_CLIENTS;

	Fichier.open(CheminFichier, ios::in | ios::binary);

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
			return ClientTrouve;
		}


		Fichier.read((char*)&ClientTrouve, sizeof(Client_s));
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
	}

	else if (LireClient.IDClient < IDClientRecherche || LireClient.IDClient != IDClientRecherche)
	{
		cout << "Numéro de client invalide.\nAppuyez sur une touche pour continuer...";
	}

}

void MettreAJourClient(int& IDClientRecherche) // A FAIRE
{


} 

void ListeDesClientsEnRetard() // A FAIRE
{


} 
