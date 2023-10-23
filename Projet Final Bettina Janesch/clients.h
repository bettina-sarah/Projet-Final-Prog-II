#ifndef CLIENTS_H
#define CLIENTS_H

#include "utils.h" // String en char, ajd, ajout jours, nombre jours

static const int MAX_CHAR = 125; //privé: dans un header. possiblement livres.h aussi

struct LivresPretes_s
{
	int NumeroLivre;
	Date_s Maintenant;
	Date_s Retour;
};

struct Client_s
{
	int IDClient;
	char NomClient[MAX_CHAR];
	char NumeroTelephone[10];
	char Adresse[MAX_CHAR];
	Date_s DateInscription;
	int NumeroLivresPretes; // max 3
	LivresPretes_s Livres[3];
};


const string NOM_FICHIER_CLIENTS = "C:\\Users\\1649508\\source\\repos\\Projet-Final-Prog-II\\Projet Final Bettina Janesch\\fichiers\\clients.bin";

//maison: "C:\\Users\\betti\\source\\repos\\Projet-Final-Prog-II\\Projet Final Bettina Janesch\\fichiers\\clients.bin";

//ecole: 


void NouveauClient(string Nom, string Telephone, string Addresse);

Client_s RechercherDossierClient(int &IDClientRecherche);

void AfficherDossierClient(int &IDClientRecherche);

void MettreAJourClient(int& IDClientRecherche, int& IDLivreRecherche);

void ListeDesClientsEnRetard();

void Location(int& IDClientLoueur, int& IDLivreALouer);

#endif