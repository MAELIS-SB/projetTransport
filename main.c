#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transport.h"

int main() {

    /* ── Création manuelle de stations pour le test ── */

    /* Stations de la Ligne A */
    Station *s3 = malloc(sizeof(Station));
    strcpy(s3->nom, "Marche Central");
    s3->duree   = 0;
    s3->suivant = NULL;

    Station *s2 = malloc(sizeof(Station));
    strcpy(s2->nom, "Universite");
    s2->duree   = 3;
    s2->suivant = s3;

    Station *s1 = malloc(sizeof(Station));
    strcpy(s1->nom, "Gare Centrale");
    s1->duree   = 5;
    s1->suivant = s2;

    /* Création de la Ligne A */
    Ligne *ligneA = malloc(sizeof(Ligne));
    strcpy(ligneA->nom, "Ligne A");
    ligneA->stations = s1;
    ligneA->suivant  = NULL;

    /* Le réseau = juste Ligne A pour le test */
    Ligne *reseau = ligneA;

    /* ── Test afficherLignes ── */
    afficherLignes(reseau);

    /* ── Test rechercherStation ── */
    printf("  Recherche de 'Universite' :\n");
    rechercherStation(ligneA, "Universite");

    printf("\n  Recherche de 'Stade' :\n");
    rechercherStation(ligneA, "Stade");

    /* ── Libération mémoire ── */
    free(s1);
    free(s2);
    free(s3);
    free(ligneA);

    return 0;
}