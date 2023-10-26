#ifndef CLIENTS_H
#define CLIENTS_H

#include "utils.h" // String en char, ajd, ajout jours, nombre jours

const int MAX_CHAR = 125;//privé: dans un header. possiblement livres.h aussi

extern const string NOM_FICHIER_CLIENTS;

void NouveauClient(string Nom, string Telephone, string Addresse);

void AfficherDossierClient(int &IDClientRecherche);

void ListeDesClientsEnRetard();

void Location(int& IDClientLoueur, int& IDLivreALouer);

void Retour(int& IDClientLoueur);

void MettreClientEnRetard(int Client, int Livre);

#endif