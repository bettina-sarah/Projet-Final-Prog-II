#ifndef LIVRES_H
#define LIVRES_H

#include "utils.h" // String en char, ajd, ajout jours, nombre jours

const string NOM_FICHIER_LIVRES = "C:\\Users\\betti\\source\\repos\\Projet-Final-Prog-II\\Projet Final Bettina Janesch\\fichiers\\livres.bin";

//maison: 

// ecole: "C:\\Users\\1649508\\source\\repos\\Projet-Final-Prog-II\\Projet Final Bettina Janesch\\fichiers\\livres.bin";

static const int MAX_CHAR_LIVRES = 125;

struct Livre_s
{
	int IDLivre; // a zero
	char Titre[MAX_CHAR_LIVRES];
	char Auteur[MAX_CHAR_LIVRES];
	bool EtatPret;
};

void NouveauLivre(string Titre, string Auteur);

Livre_s RechercherLivre(int& IDLivreRecherche);

void AfficherLivre(int& IDLivreRecherche);

void MettreAJourLivre(int& IDLivreRecherche);

void ListeDesLivresPretes();



#endif