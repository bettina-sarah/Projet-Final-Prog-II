#ifndef CLIENTS_H
#define CLIENTS_H

#include "utils.h"

const int MAX_CHAR_CLIENTS = 125; //privé: dans un header inclue

extern const string NOM_FICHIER_CLIENTS;

void NouveauClient(string Nom, string Telephone, string Addresse);

void AfficherDossierClient(int &IDClientRecherche);

void ListeDesClientsEnRetard();

void Location(int& IDClientLoueur, int& IDLivreALouer);

void Retour(int& IDClientLoueur);

void MettreClientEnRetard(int Client, int Livre);

#endif