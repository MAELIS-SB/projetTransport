#include<stdio.h>
#include<string.h>
#include "../include/transport.h"

int nombreStations(Ligne *ligne){

    int count = 0;
    Station *courant = ligne->stations;

    while(courant != NULL){
        count++;
        courant = courant->suiv;
    }
    return count;
}

int positionValide(Ligne *ligne, int position){
    
    int nbStations = nombreStations(ligne);

    // insertion au début
    if(position == 1) return 1;

    // insertion à la fin
    if(position == -1) return 1;

    // insertion au milieu
    if(position > 1 && position <= nbStations)return 1;
    
    return 0;
}

void insererStationDebut(Ligne *ligne, char nom[], int dureeApres){
    Station *station=malloc(sizeof(Station));
    if(station==NULL){
        printf("erreur d'allocation");
        return;
    }
    strcpy(station->nom, nom);
    station->dureeverssuiv =dureeApres;

    station->suiv=ligne->stations;
    ligne->stations=station;
}

void insererStationFin(Ligne *ligne, char nom[], int dureeAvant){
    Station *station=malloc(sizeof(Station));
    if(station==NULL){
        printf("erreur d'allocation");
        return;
    }
    strcpy(station->nom, nom);
    station->dureeverssuiv =0;
    station->suiv=NULL;

    if(ligne->stations == NULL){
        ligne->stations = station;
        return;
    }
    Station *courant=ligne->stations;
    while(courant->suiv!=NULL){
        courant=courant->suiv;
    }
    courant->dureeverssuiv=dureeAvant;
    courant->suiv=station;
    
}

void insererStationMilieu(Ligne *ligne, char nom[], int position, int dureeAvant, int dureeApres){
    Station* station=malloc(sizeof(Station));
    if(station==NULL){
        printf("erreur d'allocation");
        return;
    }
    strcpy(station->nom, nom);
    station->dureeverssuiv =dureeApres;
    Station* courant=ligne->stations;
    Station* precedant=NULL;
    int count=1;//car courant ce trouve à la position 1
    while(count<position){
        precedant=courant;
        courant=courant->suiv;
        count++;
    }
    precedant->dureeverssuiv=dureeAvant;
    precedant->suiv=station;
    station->suiv=courant; 
}


void ajouterStation(Ligne *ligne, char nom[], int position, int dureeAvant, int dureeApres){
    
    
    if(position==1){ //insertion en debut de chaine
        insererStationDebut(ligne, nom, dureeApres);

    }else if(position==-1){ //insertion en fin de chaine
        insererStationFin(ligne, nom, dureeAvant);
        
    }else{
        insererStationMilieu(ligne, nom, position, dureeAvant, dureeApres);
    }
}

Ligne* creerLigne(char nom[]){

    Ligne *ligne = malloc(sizeof(Ligne));

    if(ligne == NULL){
        printf("Erreur d'allocation\n");
        return NULL;
    }

    strcpy(ligne->nom, nom);

    ligne->stations = NULL;
    ligne->suiv = NULL;
    return ligne;
}

void ajouterLigne(Ligne **reseau, Ligne *ligne){

    // si le reseau est vide
    if(*reseau == NULL){
        *reseau = ligne;
        return;
    }

    Ligne *courant = *reseau;

    while(courant->suiv != NULL){
        courant = courant->suiv;
    }
    courant->suiv = ligne;
}