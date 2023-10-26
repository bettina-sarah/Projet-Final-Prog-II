#include <iostream>
#include "livres.h"
#include "utils.h"
#include <fstream>

using namespace std;

extern const string NOM_FICHIER_LIVRES = ".\\fichiers\\livres.bin";

//maison: "C:\\Users\\betti\\source\\repos\\Projet-Final-Prog-II\\Projet Final Bettina Janesch\\fichiers\\livres.bin";

// ecole: "C:\\Users\\1649508\\source\\repos\\Projet-Final-Prog-II\\Projet Final Bettina Janesch\\fichiers\\livres.bin";

// location / prêt d’un livre implique des données pour le client ET pour le livre!!!!

void NouveauLivre(string Titre, string Auteur)
{
	fstream Fichier;
	static int IDNouveauLivre = 0;
	Livre_s NouveauLivre;
	char CharTitre[MAX_CHAR_LIVRES];
	char CharAuteur[MAX_CHAR_LIVRES];

	Fichier.open(NOM_FICHIER_LIVRES, ios::app | ios::binary);

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	// assign numero livre au struct + incrementation

	NouveauLivre.IDLivre = IDNouveauLivre;
	IDNouveauLivre++;

	//string en tab char + mettre dans structure

	StringEnTabChar(Titre, CharTitre);
	StringEnTabChar(Auteur, CharAuteur);

	for (int i = 0; i < MAX_CHAR_LIVRES; i++)
	{
		NouveauLivre.Titre[i] = CharTitre[i];
	}

	for (int i = 0; i < 10; i++)
	{
		NouveauLivre.Auteur[i] = CharAuteur[i];
	}

	// bool prêt = faux
	NouveauLivre.EtatPret = false;

	Fichier.write((char*)&NouveauLivre, sizeof(Livre_s));

	Fichier.close();

}

static int CompterLivres()
{
	fstream Fichier;
	Livre_s LivreCompte;
	int NumeroLivres = 0;

	Fichier.open(NOM_FICHIER_LIVRES, ios::in | ios::binary);

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	Fichier.read((char*)&LivreCompte, sizeof(Livre_s));

	while (!Fichier.eof())
	{
		NumeroLivres++;
		Fichier.read((char*)&LivreCompte, sizeof(Livre_s));
	}

	Fichier.close();
	return NumeroLivres;
}

Livre_s RechercherLivre(int &IDLivreRecherche)
{
	Livre_s LivreTrouve;
	fstream Fichier;
	Fichier.open(NOM_FICHIER_LIVRES, ios::in | ios::binary);

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	Fichier.read((char*)&LivreTrouve, sizeof(Livre_s));

	while (!Fichier.eof())
	{
		if (LivreTrouve.IDLivre == IDLivreRecherche)
		{
			Fichier.seekg(sizeof(Livre_s) * LivreTrouve.IDLivre, ios::beg);
			Fichier.read((char*)&LivreTrouve, sizeof(Livre_s));
			return LivreTrouve;
		}

		Fichier.read((char*)&LivreTrouve, sizeof(Livre_s));
	}

	if (LivreTrouve.IDLivre < IDLivreRecherche || LivreTrouve.IDLivre != IDLivreRecherche)
	{
		cout << "Numéro de livre invalide.\nAppuyez sur une touche pour continuer...";
	}

	Fichier.close();

}

void AfficherLivre(int& IDLivreRecherche)
{
	Livre_s LireLivre;
	LireLivre = RechercherLivre(IDLivreRecherche);

	if (LireLivre.IDLivre == IDLivreRecherche)
	{
		cout << "\n\n\n+++ INFORMATION SUR LE LIVRE CHOISI +++\n------------\n";

		cout << "\nID Livre: " << LireLivre.IDLivre << "\nTitre du livre: " << LireLivre.Titre << "\nAuteur/Autrice: " << LireLivre.Auteur << "\n";
		cout << "\nÉtat du pret du livre: ";
		if (LireLivre.EtatPret == false)
		{
			cout << "libre";
		}
		else if (LireLivre.EtatPret == true)
		{
			cout << "loué";
		}
	}

	else if (LireLivre.IDLivre < IDLivreRecherche || LireLivre.IDLivre != IDLivreRecherche)
	{
		cout << "Numéro de livre invalide.\nAppuyez sur une touche pour continuer...";
	}

}

void MettreAJourLivre(Livre_s LivreALouer, int& IDLivreRecherche)
{
	fstream Fichier;

	Fichier.open(NOM_FICHIER_LIVRES, ios::in | ios::out | ios::binary);

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	Fichier.seekp(sizeof(Livre_s) * LivreALouer.IDLivre, ios::beg);
	Fichier.write((char*)&LivreALouer, sizeof(Livre_s));

	Fichier.close();

}

void ListeDesLivresPretes()
{
	Livre_s LivrePrete;

	int NumeroLivres = CompterLivres();

	cout << "\n\n\n\t+++ LIVRES PRETÉS +++\n\t------------\nID\tTitre\n------------------\n";

	for (int i = 0; i < NumeroLivres; i++)
	{
		LivrePrete = RechercherLivre(i);

		if (LivrePrete.EtatPret == true)
		{
			cout << LivrePrete.IDLivre << "\t" << LivrePrete.Titre << "\n";
		}
	}
}

