#ifndef CLIENTS_H
#define CLIENTS_H

#include "utils.h" // String en char, ajd, ajout jours, nombre jours

const int MAX_CHAR = 125;//privé: dans un header. possiblement livres.h aussi

extern const string NOM_FICHIER_CLIENTS;

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

void NouveauClient(string Nom, string Telephone, string Addresse);

static Client_s RechercherDossierClient(int &IDClientRecherche);

void AfficherDossierClient(int &IDClientRecherche);

static void MettreAJourClient(Client_s ClientLoueur, int& IDClientRecherche);

void ListeDesClientsEnRetard();

void Location(int& IDClientLoueur, int& IDLivreALouer);

void Retour(int& IDClientLoueur);

void MettreClientEnRetard(int Client, int Livre);

#endif