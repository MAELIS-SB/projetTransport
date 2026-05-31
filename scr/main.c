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
        printf("2. Rechercher une ligne et afficher ses stations \n");
        printf("3. Duree totale nécessaire pour parcourir une ligne\n");
        printf("4. nombre de stations d'une ligne\n");
        printf("5. Ajouter une ligne\n");
        printf("6. Ajouter une station\n");
        printf("7. Supprimer une station\n");
        printf("8. Supprimer une ligne\n");
        printf("9. Nombre de stations d'une ligne\n");
        printf("10. Rechercher une station\n");

        printf("0. Quitter\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        switch(choix) {

            case 1:{
                afficherLignes(reseau);
                break;
            }
            case 2:{
                char nomLigne[100];
                printf("entrer le nom de la ligne\n");
                scanf("%s",nomLigne);
                Ligne *ligne=rechercherLigne(reseau, nomLigne);
                if (ligne==NULL){
                    printf(" cette ligne n'existe pas\n");
                    break;
                }
                afficherStations(ligne->stations);
                printf("et dans l'ordre inverse on a \n");
                afficherStationsInverse(ligne->stations);
                break;
            }
            case 3:{
                char nomLigne[100];
                printf("entrer le nom de la ligne\n");
                scanf("%s",nomLigne);
                Ligne *ligne=rechercherLigne(reseau, nomLigne);
                if (ligne==NULL){
                    printf(" cette ligne n'existe pas\n");
                    break;
                }
                int duree=calculerDureeTotale(ligne->stations);
                printf(" la durée nécessaire pour parcourrir entièrement cette ligne est de %d \n",duree);
                break;
            }
            case 4:{
                char nomLigne[100];
                printf("entrer le nom de la ligne \n");
                scanf("%s",nomLigne);
                Ligne *ligne=rechercherLigne(reseau, nomLigne);
                if (ligne==NULL){
                    printf(" cette ligne n'existe pas\n");
                    break;
                }
                int n=compterStations(ligne->stations);
                printf(" cette ligne a %d stations \n",n);
                break;
            }
            case 5:{
                char nomLigne[100];
                printf("entrer le nom de la nouvelle ligne\n");
                scanf("%s",nomLigne);
                Ligne *ligne=rechercherLigne(reseau, nomLigne);
                if (ligne!=NULL){
                printf(" cette ligne existe déjà \n");
                    break;
                }
                ligne=creerLigne(nomLigne);
                int n;
                printf("entrer le nombre de station de cette nouvelle ligne\n");
                scanf("%d",&n);
                char nom[100];
                
                for(int i=1; i<n; i++){
                    printf("entrer le nom de la station %d \n",i);
                    scanf("%s", nom);
                    Station*station= creerStation(nom);
                    printf("entrer la durée nécesaire pour aller vers la station suivante");
                    scanf("%d", &station->dureeverssuiv);printf("ligne ajoutee avec succes\n");
                    ajouterStation(ligne, station);
                    
                }
            
                printf("entrer le nom de la dernière station \n");
                scanf("%s", nom);
                Station*station= creerStation(nom);
                ajouterStation(ligne, station);
                ajouterLigne(&reseau, ligne);
                printf("ligne ajoutee avec succes\n");

                break;
            }
            case 6:{
                char nomLigne[100];
                printf("entrer le nom de la ligne dans laquelle vous souhaitez ajouter une station\n");
                scanf("%s",nomLigne);
                Ligne *ligne=rechercherLigne(reseau, nomLigne);
                if (ligne==NULL){
                    printf(" cette ligne n'existe pas\n");
                    break;
                }

                char nom[100];
                int position;
                
                printf("entrer le nom de la nouvelle station que vous souhaitez insérez\n");
                scanf("%s", nom);
                printf("entrer la position à laquelle vous souhaitez insérer la nouvelle station entrer:\n");
                printf("1 pour une insertion en debut\n");
                printf("-1 pour une insertion en fin de chaine\n");
                printf("un nombre indicant la position à laquelle vous souhaitez faire l'insertion\n");
                scanf("%d",&position);
                
                while(!positionValide(ligne, position)){
                    printf("position non valide entrer une nouvelle\n");
                    scanf("%d",&position);
                }
                
                if(position==1){
                    int dureeApres;
                    printf("vous souhaitez insérez une station à la position %d donc avant %s\n", position, ligne->stations->nom);
                    printf("entrer la durée separant la nouvelle station %s et %s\n", nom, ligne->stations->nom);
                    scanf("%d", &dureeApres);
                    insererStationDebut(ligne, nom, dureeApres);
                }else if(position==-1){
                    int dureeAvant;
                    Station*courant=ligne->stations;
                    while(courant->suiv!=NULL){
                        courant=courant->suiv;
                    }
                    printf("vous souhaitez insérez une station en fin de liste c'est à dire après %s\n", courant->nom);
                    printf("entrer la durée separant %s et la nouvelle station %s\n", courant->nom, nom);
                    scanf("%d", &dureeAvant);
                    insererStationFin(ligne, nom, dureeAvant);
                }else{
                    Station*courant= rechercherStationPos(ligne, position);
                    int dureeAvant;
                    printf("vous souhaitez insérez une station à la position %d donc entre %s et %s\n", position, courant->prec->nom, courant->nom);
                    printf("entrer la durée separant %s et la nouvelle station %s\n", courant->prec->nom, nom);
                    scanf("%d", &dureeAvant);
                    if(dureeAvant>= courant->prec->dureeverssuiv){
                        printf("cette duree n'est pas valide car duree separant %s et %s est %d\n", courant->prec->nom, courant->nom, courant->prec->dureeverssuiv);
                        break;
                    }
                    insererStationMilieu(ligne, nom, position, dureeAvant);
                }
                break;
            }
            case 7:{
                char nomLigne[100];
                printf("entrer le nom de la ligne sur laquelle se trouve le station que vous souhaitez supprimer\n");
                scanf("%s", nomLigne);
                Ligne*ligne=rechercherLigne(reseau, nomLigne);
                if(ligne==NULL){
                    printf("cette ligne n'existe pas");
                    break;
                }
                char nomStation[100];
                printf("entrer le nom de la station à supprimer");
                scanf("%s", nomStation);
                supprimerStation(ligne, nomStation);
                break;
            }
            case 8:{
                char nomLigne[100];
                printf("entrer le nom de la ligne que vous souhaitez supprimer\n");
                scanf("%s", nomLigne);
                
                supprimerLigne(&reseau, nomLigne);
        
                break;
            }
            case 9:{
                char nomLigne[100];
                printf("entrer le nom de la ligne \n");
                scanf("%s", nomLigne);
                Ligne*ligne=rechercherLigne(reseau, nomLigne);
                if(ligne==NULL){
                    printf("cette ligne n'existe pas");
                    break;
                }
                int n=compterStations(ligne->stations);
                printf("la ligne %s possède %d stations\n", ligne->nom, n);
                break;
            }
            case 10:{
                char nomStation[100];
                printf("entrer le nom de la station à supprimer");
                scanf("%s", nomStation);
                rechercherStationReseau(reseau, nomStation);
                break;
            }
            
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