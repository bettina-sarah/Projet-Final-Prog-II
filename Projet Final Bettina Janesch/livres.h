#ifndef LIVRES_H
#define LIVRES_H

#include "utils.h"

extern const string NOM_FICHIER_LIVRES;

const int MAX_CHAR_LIVRES = 125; // static par défaut

struct Livre_s // struct laissé dans le .h parce que la struct est necessaire dans client.cpp
{
	int IDLivre; // a zero
	char Titre[MAX_CHAR_LIVRES];
	char Auteur[MAX_CHAR_LIVRES];
	bool EtatPret;
};

void NouveauLivre(string Titre, string Auteur);

Livre_s RechercherLivre(int& IDLivreRecherche);

void AfficherLivre(int& IDLivreRecherche);

void MettreAJourLivre(Livre_s LivreALouer, int& IDLivreRecherche);

void ListeDesLivresPretes();



#endif