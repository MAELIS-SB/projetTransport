#include <stdio.h>
#include <string.h>
#include "transport.h"

Station* rechercherStation(Ligne* ligne, char nom[]) {

    if (ligne == NULL) {
        printf("  [ERREUR] Ligne invalide.\n");
        return NULL;
    }

    Station *actuelle = ligne->stations;

    while (actuelle != NULL) {
        if (strcasecmp(actuelle->nom, nom) == 0) {
            printf("  [OK] Station '%s' trouvee !\n", actuelle->nom);
            return actuelle;
        }
        actuelle = actuelle->suivant;
    }

    printf("  [INFO] Station '%s' introuvable.\n", nom);
    return NULL;
}