#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/transport.h"

int nombreStations(Station *station){

    if(station == NULL){
        return 0;
    }

    return 1 + nombreStations(station->suiv);
}

int positionValide(Ligne *ligne, int position){
    
    int nbStations = nombreStations(ligne->stations);
   
    // insertion au début
    if(position == 1) return 1;

    // insertion à la fin
    if(position == -1 ) return 1;

    // insertion au milieu ou en fin 
    if(position > 1 && position <=nbStations)return 1;
    
    return 0;
}

Station* creerStation(char nom[]){
    Station* station=malloc(sizeof(Station));
    if(station == NULL){
        printf("Erreur d'allocation\n");
        return NULL;
    }

    strcpy(station->nom,nom);
    station->dureeverssuiv=0;
    station->prec=NULL;
    station->suiv=NULL;
    return station;
}

void ajouterStation(Ligne *ligne, Station *station){
    if(ligne->stations==NULL){
        ligne->stations=station;
        return;
    }
    Station* courant=ligne->stations;
    while(courant->suiv!=NULL){
        courant=courant->suiv;
    }
    courant->suiv=station;
    station->prec=courant;
}

void insererStationDebut(Ligne *ligne, char nom[], int dureeApres){
    Station *station=creerStation(nom);
    station->dureeverssuiv =dureeApres;
    
    station->suiv=ligne->stations;

    if(ligne->stations != NULL){
        ligne->stations->prec = station;
    }

    ligne->stations=station;
    printf("ligne inséré avec succès");
}

void insererStationFin(Ligne *ligne, char nom[], int dureeAvant){
    Station *station=creerStation(nom);

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
    station->prec=courant;
    printf("ligne inséré avec succès");
}

void insererStationMilieu(Ligne *ligne, char nom[], int position, int dureeAvant){
    Station *station=creerStation(nom);
    
    Station* courant=ligne->stations;
    
    int count=1;//car courant ce trouve à la position 1
    while(count<position ){
        courant=courant->suiv;
        count++;
    }
    int ancienneDuree = courant->prec->dureeverssuiv;

    courant->prec->dureeverssuiv=dureeAvant;
    station->dureeverssuiv=ancienneDuree-dureeAvant;
    courant->prec->suiv=station;
    station->prec=courant->prec;
    station->suiv=courant;
    courant->prec=station;
    printf("ligne inséré avec succès");
}


void insererStation(Ligne *ligne, char nom[], int position, int duree){
    
    if(position==1){ //insertion en debut de chaine
        insererStationDebut(ligne, nom, duree);

    }else if(position==-1){ //insertion en fin de chaine
        insererStationFin(ligne, nom, duree);
        
    }else{
        insererStationMilieu(ligne, nom, position, duree);
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

//ajouter à la fin du réseau
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

/*on appellera ces fonctions dans le mains pour connaitre la station avant et après la station concernée
les fonctions seront appelées en fonction de la position  */
char* rechercheStationAvant(Ligne *ligne, int position){

    int count=1;
    Station* courant=ligne->stations;
    while(count<position-1){
        courant=courant->suiv;
        count++;
    }
    return courant->nom;
}

char* rechercheStationApres(Ligne *ligne, int position){

    int count=1;
    Station* courant=ligne->stations;
    while(count<position+1){
        courant=courant->suiv;
        count++;
    }
    return courant->nom;
}

void supprimerStation(Ligne *ligne, char nom[]){

    Station *station = rechercherStationNom(ligne, nom);
    if(station == NULL){
        printf("Aucune station %s trouvee\n", nom);
        return;
    }
    // une seule station
    if(station->prec == NULL && station->suiv== NULL){

        ligne->stations = NULL;
    }
    // suppression debut
    else if(station->prec== NULL){

        ligne->stations = station->suiv;
        station->suiv->prec= NULL;
    }
    // suppression fin
    else if(station->suiv== NULL){

        station->prec->suiv= NULL;
        station->prec->dureeverssuiv =0;
    }

    // suppression milieu
    else{

        station->prec->suiv = station->suiv;
        station->suiv->prec= station->prec;
        station->prec->dureeverssuiv += station->dureeverssuiv;
    }
    printf("station supprimé avec succès");

    free(station);
}

void supprimerLigne(Ligne **reseau, char nom[]){

    if(reseau == NULL || *reseau == NULL){
        return;
    }

    Ligne *ligne = rechercherLigne(*reseau, nom);

    // ligne non trouvée
    if(ligne== NULL){
        printf("Aucune ligne nommee %s trouvee\n", nom);
        return;
    }

    // suppression en tête
    if(*reseau ==ligne){

        *reseau =ligne->suiv;

    }else{

        Ligne *courant= *reseau;

        while(courant->suiv != ligne){
            courant= courant->suiv;
        }

        courant->suiv= ligne->suiv;
    }

    libererStations(ligne->stations);
    free(ligne);
    printf("ligne supprimée avec succès");
}

void libererStations(Station *tete){

    Station *courant = tete;

    while(courant != NULL){

        Station *temp = courant;

        courant = courant->suiv;

        free(temp);
    }
}

void libererReseau(Ligne *reseau){

    Ligne *courant = reseau;
    while(courant != NULL){
        Ligne *temp = courant;
        courant = courant->suiv;

        libererStations(temp->stations);

        free(temp);
    }
}

Station *rechercherStationPos(Ligne *ligne, int position){
    Station*courant=ligne->stations;
    int count=1;
    while(count<position){
        courant=courant->suiv;
        count++;
    }
    return courant;
}

Ligne *rechercherLigne(Ligne *reseau, char nom[]){

    Ligne *courant = reseau;
    while(courant != NULL){
        if(strcmp(courant->nom, nom) == 0){
            return courant;
        }

        courant = courant->suiv;
    }

    return NULL;
}

Station *rechercherStationNom(Ligne *ligne, char nom[]){

    Station *courant = ligne->stations;

    while(courant != NULL){
        if(strcmp(courant->nom, nom) == 0){
            return courant;
        }
        courant = courant->suiv;
    }
    return NULL;
}

void rechercherStationReseau(Ligne *reseau, char nom[]){

    Ligne *courant = reseau;


    while(courant != NULL){

        Station* station = rechercherStationNom(courant, nom);

        if(station != NULL){
            printf("la station %s a été trouvé sur la ligne '%s' du réseau ", station->nom, courant->nom);
            return;
            
        }
        courant = courant->suiv;
    }
    printf("cette station n'existe pas");
    
}
