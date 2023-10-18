#ifndef CLIENTS_H
#define CLIENTS_H

#include "utils.h" // String en char, ajd, ajout jours, nombre jours

static const int MAX_CHAR = 125; //privé: dans un header. possiblement livres.h aussi

const string NOM_FICHIER_CLIENTS = "C:\\Users\\1649508\\source\\repos\\Projet-Final-Prog-II\\Projet Final Bettina Janesch\\fichiers\\clients.bin";

void NouveauClient(string Nom, string Telephone, string Addresse);

void RechercherDossierClient();

void AfficherDossierClient(int IDClientRecherche);

#endif