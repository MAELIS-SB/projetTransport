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

    afficherStations (station->suiv);
}

void afficherStationsInverse(Station *station){

    if(station == NULL){
        return;
    }
    afficherStationsInverse(station->suiv);

    if(station->suiv != NULL){
        printf(" -> ");
    }
    printf("%s", station->nom);
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

    afficherLignes(reseau->suiv);
}