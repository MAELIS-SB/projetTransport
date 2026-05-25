#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../include/affichage.h"
#include"../include/persistance.h"
#include"../include/transport.h"

int main(){
    Ligne *reseau= chargerJSON("data/reseau.json");

    if(reseau==NULL){
        printf("fichier vide ou erreur de chargement");
    }

    int choix;

    do {

        printf("\n===== MENU =====\n");

        printf("1. Afficher toutes les lignes\n");
        printf("2. Afficher les stations d'une ligne\n");
        printf("3. Duree totale d'une ligne\n");
        printf("4. Ajouter une ligne\n");
        printf("5. Ajouter une station\n");
        printf("6. Supprimer une station\n");
        printf("7. Supprimer une ligne\n");
        printf("8. Nombre de stations d'une ligne\n");
        printf("9. Rechercher une station\n");
        printf("0. Quitter\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        switch(choix) {

            case 1:
                afficherLignes(reseau);
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                break;

            case 7:
                break;

            case 8:
                break;

            case 9:
                break;

            case 0:
                printf("Au revoir...\n");
                break;

            default:
                printf("Choix invalide\n");

        }

    } while(choix != 0);

    sauvegarderJSON(reseau, "data/reseau.json");

    libererReseau(reseau);

    return 0;
}