#ifndef UTILS_H
#define UTILS_H
#include <string>

using namespace std;

struct Date_s {
	int Annee;
	int Mois;
	int Jour;
};

void StringEnTabChar(string Texte, char TabChar[]);
Date_s Aujourdhui();
Date_s AjouterJours(int NbJours, Date_s DateDepart);
int NombreJours(Date_s Date1, Date_s Date2);

#endif

