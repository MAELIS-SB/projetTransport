#include "../include/persistance.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*
 *
 * {
 *   "lignes": [
 *     {
 *       "nom": "Ligne A",
 *       "stations": [
 *         { "nom": "Station 1", "dureeverssuiv": 4 },
 *         { "nom": "Station 2", "dureeverssuiv": 6 }
 *       ]
 *     }
 *   ]
 * }
 * 
 */

static void sauterEspaces(const char **curseur)
{
    while (curseur != NULL && *curseur != NULL && **curseur != '\0' &&
           isspace((unsigned char)**curseur)) {
        (*curseur)++;
    }
}

/* Cherche une cle JSON du type "nom" ou "stations" dans le texte brut */
static const char *chercherCleJSON(const char *buffer, const char *cle)
{
    char motif[128];

    if (buffer == NULL || cle == NULL) {
        return NULL;
    }

    snprintf(motif, sizeof(motif), "\"%s\"", cle);
    return strstr(buffer, motif);
}

/*
 * retrouve le caractere fermant correspondant a un bloc ouvrant
 * cette fonction gere l'imbrication et ignore les caracteres qui se trouvent
 * a l'interieur d'une chaine JSON.
 */
static const char *trouverFermetureBloc(const char *debut, char ouvrant, char fermant){
    int profondeur = 0;
    int dansChaine = 0;
    const char *curseur = debut;

    if (debut == NULL || *debut != ouvrant) {
        return NULL;
    }

    while (*curseur != '\0') {
        if (dansChaine) {
            if (*curseur == '\\' && curseur[1] != '\0') {
                curseur += 2;
                continue;
            }

            if (*curseur == '"') {
                dansChaine = 0;
            }
        } else {
            if (*curseur == '"') {
                dansChaine = 1;
            } else if (*curseur == ouvrant) {
                profondeur++;
            } else if (*curseur == fermant) {
                profondeur--;
                if (profondeur == 0) {
                    return curseur;
                }
            }
        }

        curseur++;
    }

    return NULL;
}


// copie une chaine JSON dans un tableau C

static int copierChaineJSON(const char *debut, char destination[],
                            size_t tailleDestination, const char **finLecture)
{
    size_t index = 0;
    const char *curseur = debut;

    if (debut == NULL || destination == NULL || tailleDestination == 0 ||
        *debut != '"') {
        return 0;
    }

    curseur++;

    while (*curseur != '\0' && *curseur != '"') {
        char caractere = *curseur;

        if (caractere == '\\' && curseur[1] != '\0') {
            curseur++;

            switch (*curseur) {
                case 'n':
                    caractere = '\n';
                    break;
                case 't':
                    caractere = '\t';
                    break;
                case 'r':
                    caractere = '\r';
                    break;
                case '"':
                    caractere = '"';
                    break;
                case '\\':
                    caractere = '\\';
                    break;
                default:
                    caractere = *curseur;
                    break;
            }
        }

        if (index + 1 < tailleDestination) {
            destination[index++] = caractere;
        }

        curseur++;
    }

    if (*curseur != '"') {
        return 0;
    }

    destination[index] = '\0';

    if (finLecture != NULL) {
        *finLecture = curseur + 1;
    }

    return 1;
}

// lit une valeur chaine associee a une cle JSON 
static int extraireChaineDepuisCle(const char *buffer, const char *cle,
                                   char destination[], size_t tailleDestination)
{
    const char *positionCle = chercherCleJSON(buffer, cle);
    const char *deuxPoints;

    if (positionCle == NULL) {
        return 0;
    }

    deuxPoints = strchr(positionCle, ':');
    if (deuxPoints == NULL) {
        return 0;
    }

    deuxPoints++;
    sauterEspaces(&deuxPoints);

    return copierChaineJSON(deuxPoints, destination, tailleDestination, NULL);
}

// lit une valeur entiere associee a une cle JSON
static int extraireEntierDepuisCle(const char *buffer, const char *cle, int *valeur)
{
    const char *positionCle = chercherCleJSON(buffer, cle);
    const char *deuxPoints;
    char *finNombre;
    long resultat;

    if (positionCle == NULL || valeur == NULL) {
        return 0;
    }

    deuxPoints = strchr(positionCle, ':');
    if (deuxPoints == NULL) {
        return 0;
    }

    deuxPoints++;
    sauterEspaces(&deuxPoints);

    resultat = strtol(deuxPoints, &finNombre, 10);
    if (deuxPoints == finNombre) {
        return 0;
    }

    *valeur = (int)resultat;
    return 1;
}

static Ligne *creerLigneLocale(const char *nom){
    Ligne *ligne = (Ligne *)malloc(sizeof(Ligne));

    if (ligne == NULL) {
        return NULL;
    }

    strncpy(ligne->nom, nom != NULL ? nom : "", sizeof(ligne->nom) - 1);
    ligne->nom[sizeof(ligne->nom) - 1] = '\0';
    ligne->stations = NULL;
    ligne->suiv = NULL;

    return ligne;
}

static Station *creerStationLocale(const char *nom, int dureeVersSuiv)
{
    Station *station = (Station *)malloc(sizeof(Station));

    if (station == NULL) {
        return NULL;
    }

    strncpy(station->nom, nom != NULL ? nom : "", sizeof(station->nom) - 1);
    station->nom[sizeof(station->nom) - 1] = '\0';
    station->dureeverssuiv = dureeVersSuiv;
    station->suiv = NULL;

    return station;
}

static void ajouterLigneFin(Ligne **reseau, Ligne *nouvelleLigne)
{
    Ligne *courant;

    if (reseau == NULL || nouvelleLigne == NULL) {
        return;
    }

    if (*reseau == NULL) {
        *reseau = nouvelleLigne;
        return;
    }

    courant = *reseau;
    while (courant->suiv != NULL) {
        courant = courant->suiv;
    }

    courant->suiv = nouvelleLigne;
}

static void ajouterStationFin(Station **stations, Station *nouvelleStation)
{
    Station *courant;

    if (stations == NULL || nouvelleStation == NULL) {
        return;
    }

    if (*stations == NULL) {
        *stations = nouvelleStation;
        return;
    }

    courant = *stations;
    while (courant->suiv != NULL) {
        courant = courant->suiv;
    }

    courant->suiv = nouvelleStation;
}

static void libererStationsLocales(Station *station)
{
    Station *suivante;

    while (station != NULL) {
        suivante = station->suiv;
        free(station);
        station = suivante;
    }
}

static void libererReseauLocal(Ligne *reseau)
{
    Ligne *suivante;

    while (reseau != NULL) {
        suivante = reseau->suiv;
        libererStationsLocales(reseau->stations);
        free(reseau);
        reseau = suivante;
    }
}

Station *parserStation(char buffer[])
{
    char nomStation[100];
    int dureeVersSuiv = 0;
    Station *station;

    if (buffer == NULL) {
        return NULL;
    }

    if (!extraireChaineDepuisCle(buffer, "nom", nomStation, sizeof(nomStation))) {
        return NULL;
    }

    extraireEntierDepuisCle(buffer, "dureeverssuiv", &dureeVersSuiv);

    station = creerStationLocale(nomStation, dureeVersSuiv);
    return station;
}

Ligne *parserLigne(char buffer[]){
    char nomLigne[100];
    Ligne *ligne;
    const char *positionStations;
    const char *debutTableau;
    const char *finTableau;
    const char *curseur;

    if (buffer == NULL) {
        return NULL;
    }

    if (!extraireChaineDepuisCle(buffer, "nom", nomLigne, sizeof(nomLigne))) {
        return NULL;
    }

    ligne = creerLigneLocale(nomLigne);
    if (ligne == NULL) {
        return NULL;
    }

    positionStations = chercherCleJSON(buffer, "stations");
    if (positionStations == NULL) {
        return ligne;
    }

    debutTableau = strchr(positionStations, '[');
    if (debutTableau == NULL) {
        return ligne;
    }

    finTableau = trouverFermetureBloc(debutTableau, '[', ']');
    if (finTableau == NULL) {
        libererReseauLocal(ligne);
        return NULL;
    }

    curseur = debutTableau + 1;

    while (curseur < finTableau) {
        const char *finBloc;
        size_t tailleBloc;
        char *blocStation;
        Station *station;

        while (curseur < finTableau &&
               (isspace((unsigned char)*curseur) || *curseur == ',')) {
            curseur++;
        }

        if (curseur >= finTableau || *curseur != '{') {
            break;
        }

        finBloc = trouverFermetureBloc(curseur, '{', '}');
        if (finBloc == NULL || finBloc > finTableau) {
            libererReseauLocal(ligne);
            return NULL;
        }

        tailleBloc = (size_t)(finBloc - curseur + 1);
        blocStation = (char *)malloc(tailleBloc + 1);
        if (blocStation == NULL) {
            libererReseauLocal(ligne);
            return NULL;
        }

        strncpy(blocStation, curseur, tailleBloc);
        blocStation[tailleBloc] = '\0';

        station = parserStation(blocStation);
        free(blocStation);

        if (station == NULL) {
            libererReseauLocal(ligne);
            return NULL;
        }

        ajouterStationFin(&ligne->stations, station);
        curseur = finBloc + 1;
    }

    return ligne;
}

Ligne *chargerJSON(const char *nomFichier){
    FILE *f;
    long tailleFichier;
    char *contenu;
    const char *positionLignes;
    const char *debutTableau;
    const char *finTableau;
    const char *curseur;
    Ligne *reseau = NULL;

    if (nomFichier == NULL) {
        return NULL;
    }

    f = fopen(nomFichier, "r");
    if (f == NULL) {
        return NULL;
    }

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return NULL;
    }

    tailleFichier = ftell(f);
    if (tailleFichier < 0) {
        fclose(f);
        return NULL;
    }

    if (fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        return NULL;
    }

    contenu = (char *)malloc((size_t)tailleFichier + 1);
    if (contenu == NULL) {
        fclose(f);
        return NULL;
    }

    if ((size_t)tailleFichier > 0 &&
        fread(contenu, 1, (size_t)tailleFichier, f) != (size_t)tailleFichier) {
        free(contenu);
        fclose(f);
        return NULL;
    }

    contenu[tailleFichier] = '\0';
    fclose(f);

    if (contenu[0] == '\0') {
        free(contenu);
        return NULL;
    }

    positionLignes = chercherCleJSON(contenu, "lignes");
    if (positionLignes != NULL) {
        debutTableau = strchr(positionLignes, '[');
    } else {
        debutTableau = strchr(contenu, '[');
    }

    if (debutTableau == NULL) {
        free(contenu);
        return NULL;
    }

    finTableau = trouverFermetureBloc(debutTableau, '[', ']');
    if (finTableau == NULL) {
        free(contenu);
        return NULL;
    }

    curseur = debutTableau + 1;

    while (curseur < finTableau) {
        const char *finBloc;
        size_t tailleBloc;
        char *blocLigne;
        Ligne *ligne;

        while (curseur < finTableau &&
               (isspace((unsigned char)*curseur) || *curseur == ',')) {
            curseur++;
        }

        if (curseur >= finTableau || *curseur != '{') {
            break;
        }

        finBloc = trouverFermetureBloc(curseur, '{', '}');
        if (finBloc == NULL || finBloc > finTableau) {
            libererReseauLocal(reseau);
            free(contenu);
            return NULL;
        }

        tailleBloc = (size_t)(finBloc - curseur + 1);
        blocLigne = (char *)malloc(tailleBloc + 1);
        if (blocLigne == NULL) {
            libererReseauLocal(reseau);
            free(contenu);
            return NULL;
        }

        strncpy(blocLigne, curseur, tailleBloc);
        blocLigne[tailleBloc] = '\0';

        ligne = parserLigne(blocLigne);
        free(blocLigne);

        if (ligne == NULL) {
            libererReseauLocal(reseau);
            free(contenu);
            return NULL;
        }

        ajouterLigneFin(&reseau, ligne);
        curseur = finBloc + 1;
    }

    free(contenu);
    return reseau;
}
