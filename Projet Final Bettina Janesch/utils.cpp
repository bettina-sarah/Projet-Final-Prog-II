#define _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include <time.h>
#include "utils.h"

using namespace std;

void StringEnTabChar(string Texte, char TabChar[]) {
	strcpy(TabChar, Texte.c_str());
}

Date_s Aujourdhui() {
	Date_s DateAujourdhui;
	time_t DateSeconde = time(0);
	tm* DateStructure = localtime(&DateSeconde);

	DateAujourdhui.Annee = 1900 + DateStructure->tm_year;
	DateAujourdhui.Mois = 1 + DateStructure->tm_mon;
	DateAujourdhui.Jour = DateStructure->tm_mday;

	return DateAujourdhui;
}

Date_s AjouterJours(int NbJours, Date_s DateDepart) {
	Date_s DateMAJ;
	time_t DateSecondes;

	// Convertir Date_s de depart en structure de date
	struct tm UneDate = {};
	UneDate.tm_year = DateDepart.Annee - 1900;
	UneDate.tm_mon = DateDepart.Mois + 1;
	UneDate.tm_mday = DateDepart.Jour;

	// Convertir structure de date en date_secondes (nb secondes de puis 1900-1-1.0
	DateSecondes = mktime(&UneDate);

	// Ajouter nb jours en secondes à date
	DateSecondes += NbJours * 24 * 60 * 60;

	// Reconvertir date_secondes en structure de date
	UneDate = *localtime(&DateSecondes);

	DateMAJ.Annee = UneDate.tm_year + 1900;
	DateMAJ.Mois = UneDate.tm_mon - 1;
	DateMAJ.Jour = UneDate.tm_mday;
	return DateMAJ;
}
 
int NombreJours(Date_s Date1, Date_s Date2) {
time_t Date1Secondes;
time_t Date2Secondes;

// ***************************
// Convertir Date1 en secondes
// ***************************

struct tm UneDate1 = {};
UneDate1.tm_year = Date1.Annee - 1900;
UneDate1.tm_mon = Date1.Mois + 1;
UneDate1.tm_mday = Date1.Jour;
 
// Convertir structure de date en date_secondes (nb secondes de puis 1900-1-1.0
Date1Secondes = mktime(&UneDate1);
 
// ***************************
// Convertir Date2 en secondes
// ***************************
 
struct tm UneDate2 = {};
UneDate2.tm_year = Date2.Annee - 1900;
UneDate2.tm_mon = Date2.Mois + 1;
UneDate2.tm_mday = Date2.Jour;
 
// Convertir structure de date en date_secondes (nb secondes de puis 1900-1-1.0
Date2Secondes = mktime(&UneDate2);
 
return (Date2Secondes - Date1Secondes) / 24 / 60 / 60;
}

