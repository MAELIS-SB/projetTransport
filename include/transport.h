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
Station* creerStation(char nom[]);
void ajouterligne(Ligne ** reseau, Ligne* ligne);
void insererStation(Ligne *ligne, char nom[], int position, int duree);
//autre
int nombreStations(Station *station);
int positionValide(Ligne *ligne, int position);
void ajouterStation(Ligne *ligne, Station *station);
void insererStationDebut(Ligne *ligne, char nom[], int dureeApres);
void insererStationFin(Ligne *ligne, char nom[], int dureeAvant);
void insererStationMilieu(Ligne *ligne, char nom[], int position, int dureeAvant);
//recherche
char* rechercheStationAvant(Ligne *ligne, int position);//pour pouvoir demander la durée à l'utilisateur ensuite
char* rechercheStationApres(Ligne *ligne, int position);
Ligne *rechercherLigne(Ligne *reseau,  char nom[]);

Station *rechercherStationNom(Ligne *ligne, char nom[]);
Station *rechercherStationPos(Ligne *ligne, int position);

void rechercherStationReseau(Ligne *reseau, char nom[]);


//Suppression 

void supprimerStation(Ligne *ligne, char nom[]);

void supprimerLigne(Ligne **reseau, char nom[]);


// Libération mémoire 

void libererStations(Station *tete);

void libererReseau(Ligne *reseau);


#endif
