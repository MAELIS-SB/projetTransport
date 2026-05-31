#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/transport.h"
#include "../include/affichage.h"

int calculerDureeTotale(Station *station){
    if (station==NULL){
       return 0;
    }else{
    return station->dureeverssuiv + calculerDureeTotale(station->suiv);
    }
}

int compterStations(Station *station){
    if(station==NULL) return 0;
    return 1+compterStations(station->suiv);
}

void afficherStations(Station *station){

    if(station == NULL){
        return;
    }

    printf("%s", station->nom);

    if(station->suiv != NULL){
        printf(" -> ");
    }

    afficherStationsRec(station->suiv);
}

void afficherStationsInverse(Station *station){

    if(station == NULL){
        return;
    }
    afficherStationsInverseRec(station->suiv);
    printf("%s", station->nom);

    if(station->suiv != NULL){
        printf(" -> ");
    }
}

void afficherLignes(Ligne *reseau){
    if(reseau == NULL){
        return;
    }

    printf("%s\n", reseau->nom);
    printf("Stations: ") ;
    afficherStations(reseau->stations);
    printf("\n dans l'ordre inverse on a: ");
    afficherStationsInverse(reseau->stations);
    printf("\n");

    afficherStationsRec(reseau->suiv);
}