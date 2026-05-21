#ifndef TRANSPORT_H
#define TRANSPORT_H

typedef struct Station{
    char nom[100];
    //durée séparant les deux stations consécutives
    int dureeverssuiv;
    struct Station *prec;
    struct Station* suiv;
}Station;

//une ligne est constituée de plusieurs stations et pointe vers une autre
typedef struct Ligne{
    char nom[100];
    Station *stations;
    struct Ligne* suiv;
}Ligne;

Ligne* creerligne(char nom[]);

//ajout
void ajouterligne(Ligne ** reseau, Ligne* ligne);
void ajouterStation(Ligne *ligne, char nom[], int position, int dureeAvant, int dureeApres);
//autre
int nombreStations(Ligne *ligne);
int positionValide(Ligne *ligne, int position);
void insererStationDebut(Ligne *ligne, char nom[], int dureeApres);
void insererStationFin(Ligne *ligne, char nom[], int dureeAvant);
void insererStationMilieu(Ligne *ligne, char nom[], int position, int dureeAvant, int dureeApres);
//recherche
char* rechercheStationAvant(Ligne *ligne, int position);//pour pouvoir demander la durée à l'utilisateur ensuite
char* rechercheStationApres(Ligne *ligne, int position);
Ligne *rechercherLigne(Ligne *reseau,  char nom[]);

Station *rechercherStationNom(Ligne *ligne, char nom[]);
Station *rechercherStationPos(Ligne *ligne, int position);

Station *rechercherStationReseau(Ligne *reseau, char nom[]);


//Suppression 

void supprimerStation(Ligne *ligne, char nom[]);

void supprimerLigne(Ligne **reseau, char nom[]);


// Libération mémoire 

void libererStations(Station *tete);

void libererReseau(Ligne *reseau);


#endif
