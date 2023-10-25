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

static Client_s RechercherDossierClient(int &IDClientRecherche)
{
	Client_s ClientTrouve;

	fstream Fichier;
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
			return ClientTrouve;
		}

		Fichier.read((char*)&ClientTrouve, sizeof(Client_s));
	}

	if (ClientTrouve.IDClient < IDClientRecherche || ClientTrouve.IDClient != IDClientRecherche)
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

	else if (LireClient.IDClient < IDClientRecherche || LireClient.IDClient != IDClientRecherche)
	{
		cout << "Numéro de client invalide.\nAppuyez sur une touche pour continuer...";
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

void ListeDesClientsEnRetard() // A FAIRE
{


} 

// Fonctions locations/retours/retards 

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
		ClientLoueur.Livres[ClientLoueur.NumeroLivresPretes].Retour = AjouterJours(15, ClientLoueur.Livres->Maintenant);

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

void Retour()
{

//On présume qu’un client retourne tous ses livres lors d’un retour.
//Cette fonction modifiera le nombre de livres prêtés(le mettra à zéro).
//Si le client est en retard, on retourne le nombre de jours de retard.Vous pouvez calculer le nombre de jours grâce à la fonction NombreJours.

}


