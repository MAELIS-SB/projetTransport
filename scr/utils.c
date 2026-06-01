#include<stdio.h>
#include<string.h>
#include "../include/utils.h"


void lireChaine(char chaine[], int taille){

    fgets(
        chaine,
        taille,
        stdin
    );

    chaine[
        strcspn(
            chaine,
            "\n"
        )
    ] = '\0';
}