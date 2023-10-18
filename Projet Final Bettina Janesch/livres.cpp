#include <iostream>
#include "livres.h"
#include "utils.h"

using namespace std;

// location / prêt d’un livre implique des données pour le client ET pour le livre!!!!

struct Livre_s
{
	int IDLivre; // a zero
	char Titre[MAX_CHAR];
	char Auteur[MAX_CHAR];
	bool EtatPret;
};
