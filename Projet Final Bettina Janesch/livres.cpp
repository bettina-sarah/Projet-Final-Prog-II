#include <iostream>
#include "livres.h"
#include "utils.h"
#include <fstream>

using namespace std;

// location / prêt d’un livre implique des données pour le client ET pour le livre!!!!

//struct Livre_s
//{
//	int IDLivre; // a zero
//	char Titre[MAX_CHAR_LIVRES];
//	char Auteur[MAX_CHAR_LIVRES];
//	bool EtatPret;
//};

void NouveauLivre(string Titre, string Auteur)
{
	fstream Fichier;
	string CheminFichier = NOM_FICHIER_LIVRES;
	static int IDNouveauLivre = 0;
	Livre_s NouveauLivre;
	char CharTitre[MAX_CHAR_LIVRES];
	char CharAuteur[MAX_CHAR_LIVRES];

	Fichier.open(CheminFichier, ios::app | ios::binary);

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

Livre_s RechercherLivre(int &IDLivreRecherche)
{
	Livre_s LivreTrouve;

	fstream Fichier;
	string CheminFichier = NOM_FICHIER_LIVRES;

	Fichier.open(CheminFichier, ios::in | ios::binary);

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

void MettreAJourLivre(int& IDLivreRecherche) // A FAIRE
{
	Livre_s LivreALouer;
	fstream Fichier;
	string CheminFichierLivres = NOM_FICHIER_LIVRES;

	LivreALouer = RechercherLivre(IDLivreRecherche);

	Fichier.open(CheminFichierLivres, ios::in | ios::out | ios::binary);

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	Fichier.seekg(sizeof(Livre_s) * LivreALouer.IDLivre, ios::beg);
	Fichier.read((char*)&LivreALouer, sizeof(Livre_s));

	LivreALouer.EtatPret = true;

	Fichier.seekp(sizeof(Livre_s) * LivreALouer.IDLivre, ios::beg);
	Fichier.write((char*)&LivreALouer, sizeof(Livre_s));

	Fichier.close();


	if (LivreALouer.IDLivre < IDLivreRecherche || LivreALouer.IDLivre != IDLivreRecherche)
	{
		cout << "Numéro de livre invalide.\nAppuyez sur une touche pour continuer...";
	}
}

void ListeDesLivresPretes()
{


}