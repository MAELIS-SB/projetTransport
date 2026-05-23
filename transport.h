#ifndef TRANSPORT_H
#define TRANSPORT_H

typedef struct Station {
    char            nom[100];
    int             duree;
    struct Station *suivant;
} Station;

typedef struct Ligne {
    char           nom[50];
    Station       *stations;
    struct Ligne  *suivant;
} Ligne;

/* Prototypes */
Station* rechercherStation(Ligne* ligne, char nom[]);
void     afficherLignes(Ligne* reseau);

#endif