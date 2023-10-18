#include <iostream>
#include "clients.h"
#include <fstream>

using namespace std;

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

void NouveauClient()
{


}