#include <iostream>
#include "livres.h"
#include "utils.h"
#include <fstream>

using namespace std;

extern const string NOM_FICHIER_LIVRES = ".\\fichiers\\livres.bin";

// prototypes fonctions priv�s

static int CompterLivres();

// fonctions livres

void NouveauLivre(string Titre, string Auteur)
{
	fstream Fichier;
	static int IDNouveauLivre = 0;
	Livre_s NouveauLivre;

	Fichier.open(NOM_FICHIER_LIVRES, ios::app | ios::binary);

	if (Fichier.fail()) {
		cout << "Erreur ouverture !!";
		exit(EXIT_FAILURE);
	}

	// assign numero livre au struct + incrementation

	NouveauLivre.IDLivre = IDNouveauLivre;
	IDNouveauLivre++;

	//string en tab char + mettre dans structure

	StringEnTabChar(Titre, NouveauLivre.Titre);
	StringEnTabChar(Auteur, NouveauLivre.Auteur);

	// bool pr�t = faux
	NouveauLivre.EtatPret = false;

	Fichier.write((char*)&NouveauLivre, sizeof(Livre_s));
	cout << "Livre ajout� avec succ�s.";

	Fichier.close();

}

static int CompterLivres() // utilis� pour avoir le nombre de livres dans le fichier
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
		cout << "Num�ro de livre invalide.\nAppuyez sur une touche pour continuer...\n";
	}
	Fichier.close();
}

void AfficherLivre(int& IDLivreRecherche) // fonction pas n�cessaire? laiss� pour tester seulement
{
	Livre_s LireLivre;
	LireLivre = RechercherLivre(IDLivreRecherche);

	if (LireLivre.IDLivre == IDLivreRecherche)
	{
		cout << "\n\n\n+++ INFORMATION SUR LE LIVRE CHOISI +++\n------------\n";

		cout << "\nID Livre: " << LireLivre.IDLivre << "\nTitre du livre: " << LireLivre.Titre << "\nAuteur/Autrice: " << LireLivre.Auteur << "\n";
		cout << "\n�tat du pret du livre: ";
		if (LireLivre.EtatPret == false)
		{
			cout << "libre";
		}
		else if (LireLivre.EtatPret == true)
		{
			cout << "lou�";
		}
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

	cout << "\n\n\n\t+++ LIVRES PRET�S +++\n-------------------------------\nID\tTitre\n-------------------------------\n";

	for (int i = 0; i < NumeroLivres; i++)
	{
		LivrePrete = RechercherLivre(i);

		if (LivrePrete.EtatPret == true)
		{
			cout << LivrePrete.IDLivre << "\t" << LivrePrete.Titre << "\n";
		}
	}
}

