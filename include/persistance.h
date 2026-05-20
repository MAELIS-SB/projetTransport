#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <stdio.h>

#include "transport.h"


void sauvegarderJSON(Ligne *reseau, const char *nomFichier);

void ecrireLigneJSON(FILE *f, Ligne *ligne, int derniereLigne);

void ecrireStationsJSON(FILE *f, Station *station);


Ligne *chargerJSON(const char *nomFichier);


//parsing(operation inverse)

Ligne *parserLigne(char buffer[]);

Station *parserStation(char buffer[]);


#endif