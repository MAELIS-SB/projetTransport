#ifndef TRANSPORT_H
#define TRANSPORT_H

typedef struct Station{
    char nom[100];
    //durée séparant les deux stations consécutives
    int dureeverssuiv;
    struct Station* suiv;
}Station;

//une ligne est constituée de plusieurs stations et pointe vers une autre
typedef struct Ligne{
    char nom[100];
    Station *stations;
    struct Ligne* suiv;
}Ligne;

Ligne* creerligne(char nom[]);
Station* creerstation(char nom[], int duree);//va prendre des données venant de l'utilisateurs spour créer les stations constituants la ligne

//ajout
void ajouterligne(Ligne ** reseau, Ligne* nouvlig);
void ajouterStation(Ligne *ligne, char nom[], int position, int durreeAvant, int dureeApres);
 
//recherche
char* rechercheStationAvant(Ligne *ligne, int position);//pour pouvoir demander la durée à l'utilisateur ensuite
char* rechercheStationApres(Ligne *ligne, int position);
Ligne *rechercherLigne(Ligne *reseau,  char nom[]);

Station *rechercherStation(Ligne *ligne, char nom[]);

Station *rechercherStationReseau(Ligne *reseau, char nom[]);


//Suppression 

void supprimerStation(Ligne *ligne, char nom[]);

void supprimerLigne(Ligne **reseau, char nom[]);


// Libération mémoire 

void libererStations(Station *tete);

void libererReseau(Ligne *reseau);


#endif
