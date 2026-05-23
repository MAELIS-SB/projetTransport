#include <stdio.h>
#include "transport.h"

void afficherLignes(Ligne* reseau) {

    if (reseau == NULL) {
        printf("  Aucune ligne dans le reseau.\n");
        return;
    }

    int compteur = 1;
    Ligne *l = reseau;

    printf("\n======== RESEAU C-TRANSIT ========\n");

    while (l != NULL) {
        printf("\n  [Ligne %d] : %s\n", compteur, l->nom);

        Station *s = l->stations;
        while (s != NULL) {
            if (s->suivant != NULL)
                printf("     --> %s (%d min)\n", s->nom, s->duree);
            else
                printf("     --> %s [TERMINUS]\n", s->nom);
            s = s->suivant;
        }

        l = l->suivant;
        compteur++;
    }

    printf("\n==================================\n");
    printf("  Total : %d ligne(s).\n", compteur - 1);
    printf("==================================\n\n");
}