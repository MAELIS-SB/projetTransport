#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/transport.h"
#include "../include/affichage.h"

int calculerdureetotale(Station *station){
    if (station==NULL){
       return 0;
    }else{
    return station->dureeverssuiv + calculerdureetotale(station->suiv);
    }
}