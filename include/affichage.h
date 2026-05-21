#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "transport.h"


/* =========================
   AFFICHAGE DES LIGNES
   ========================= */

void afficherLignes(Ligne *reseau);


//affichage des stations dans le bon ordre et dans l'ordre inverse
void afficherStations(Ligne *ligne);

//statistique récursives
int compterStations(Station *station);

int calculerDureeTotale(Station *station);

#endif