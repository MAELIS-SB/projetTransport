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

    static int numero=1;
    if(station==NULL){
        numero=1;
        return;
    }

    printf("%d. %s\n",numero,station->nom );

    if(station->suiv!=NULL){

        printf( "   -> %d min\n\n", station->dureeverssuiv);
    }
    numero++;

    afficherStations(station->suiv);
}

void afficherStationsInverse(Station *station){

    static int numero=1;

    if(station==NULL){
        numero=1;
        return;
    }
    afficherStationsInverse(
        station->suiv
    );

    printf("%d. %s\n", numero,station->nom);

    if(station->prec!=NULL){
        printf("   -> %d min\n\n",station->prec->dureeverssuiv);
    }
    numero++;
}

void afficherLignes(Ligne *reseau){
    if(reseau == NULL){
        return;
    }
    printf("\n====================\n");
    printf("LIGNE: %s\n", reseau->nom);
    printf("====================\n");
    printf("Stations: ") ;
    printf("\nORDRE NORMAL\n");
    afficherStations(reseau->stations);
    printf("\nORDRE INVERSE\n");
    afficherStationsInverse(reseau->stations);
    printf("\n");

    afficherLignes(reseau->suiv);
}