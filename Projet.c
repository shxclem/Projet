#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// typedef struct {
//     char name[50];
//     char description[500];
//     int att;
//     int cd;
//     int alt;
// } Sort;

// typedef Struct {
//     char nom[30];
//     char description[500];
// } Coup;

typedef struct {
    char name[20];
    float att;
    float def;
    float hpmax;
    float dodge;
    float speed;
    float hp;
    int classe;
    int etat;
    //Sort s;
    //Coup c;
 } Personnage;

int split(char* string, char* delim) {
    char *ptr = strtok(strtok(string, "\n"), delim);

    while (ptr != NULL)
    {
        printf("'%s'\n", ptr);
        ptr = strtok(NULL, delim);
    }

// créer un tableau

    return 0;
}

int readPersonnage() {
    FILE* registre = NULL;
    char newPerso[100];

    //ouvrir le fichier 
    registre=fopen("Persos.txt","r");
    if (registre == NULL) {
        printf("Erreur d'ouverture de fichier");
        printf("code d'erreur = %d \n", errno);
        printf("Message d'erreur = %s \n", strerror(errno));
        exit(1);
    }

    //lire le fichier ligne par ligne dans une boucle
    while(fgets(newPerso , 99 , registre) != NULL) {
        split(newPerso, " ");
    }

    //Pour chaque ligne instancier un perso de la classe Personnage
    return 0;
}

int main() {
    Personnage p ;
    readPersonnage();
    // do{
    //     printf("    Bienvenue dans CY Fighters\n    Appuyez sur 'a' pour continuer.\n    Appuyez sur 'b' pour sortir du jeu.");
    // while (getchar =! 'a' & getchar=! 'b')
   return 0;
}
