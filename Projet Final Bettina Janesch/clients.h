#ifndef CLIENTS_H
#define CLIENTS_H

#include "utils.h" // String en char, ajd, ajout jours, nombre jours

static const int MAX_CHAR = 125; //priv�: dans un header. possiblement livres.h aussi

const string NOM_FICHIER_CLIENTS = "C:\\Users\\betti\\source\\repos\\Projet-Final-Prog-II\\Projet Final Bettina Janesch\\fichiers\\clients.bin";

//"C:\\Users\\1649508\\source\\repos\\Projet-Final-Prog-II\\Projet Final Bettina Janesch\\fichiers\\clients.bin";

void NouveauClient(string Nom, string Telephone, string Addresse);

Client_s RechercherDossierClient(int IDClientRecherche);

void AfficherDossierClient(int IDClientRecherche);

#endif