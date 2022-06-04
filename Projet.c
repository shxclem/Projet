#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

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

typedef struct {                    // Création de la structure Personnage
    char name[20];
    int att;
    int def;
    int hpmax;
    int dodge;
    int speed;
    int hp;
    int classe;
    int etat;
    int is_available;
    //Sort s;
    //Coup c;
 } Personnage;

Personnage readNouveauPersonnage(char* string, char* delim) {          //Fonction pour créer un nouveau personnage
    char *ptr = strtok(strtok(string, "\n"), delim);
    
    int i = 0;
    
    char tmp_name[20];
    int tmp_att;
    int tmp_def;
    int tmp_hpmax;
    int tmp_dodge;
    int tmp_speed;
    int tmp_hp;
    int tmp_classe;
    int tmp_etat;
    
    while (ptr != NULL)
    {
        switch(i) {
            case 0 : 
                strcpy(tmp_name, ptr);
                break;
            case 1 : 
                tmp_att=atoi(ptr);
                break;
            case 2 : 
                tmp_def=atoi(ptr);
                break;
            case 3 : 
                tmp_hpmax=atoi(ptr);
                break;
            case 4 : 
                tmp_dodge=atoi(ptr);
                break;
            case 5 : 
                tmp_speed=atoi(ptr);
                break;
            case 6 : 
                tmp_hp=atoi(ptr);
                break;
            case 7 : 
                tmp_classe=atoi(ptr);
                break;
            case 8 : 
                tmp_etat=atoi(ptr);
                break;   
        }
        i++;
        ptr = strtok(NULL, delim);
    }

    // créer nouveau personnage
    Personnage newPerso;
    strcpy(newPerso.name, tmp_name);
    newPerso.att = tmp_att;
    newPerso.def = tmp_def;
    newPerso.hpmax = tmp_hpmax;
    newPerso.dodge = tmp_dodge;
    newPerso.speed = tmp_speed;
    newPerso.hp = tmp_hp;
    newPerso.classe = tmp_classe;
    newPerso.etat = tmp_etat;
    newPerso.is_available = 1;
    
    return newPerso;
}

Personnage listePersos[7];                      //On définit la taille de la liste des personnages

void definePersonnnages() {                                         //Procédure permettant de lire la liste des personnages
    FILE* registre = NULL;
    char newPerso[100];
    int i=0; 

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
        listePersos[i]=readNouveauPersonnage(newPerso, " ");
        i+=1;
    }

}

Personnage Equipe1[2];                          //On définit la taille des deux
Personnage Equipe2[2];                          //équipes qui vont s'affronter

void defineEquipe() {                                                                      //Procédure permettant de créer les équipes
    bool equipeDef = false;
    int nmbPersosDispo = sizeof(listePersos)/sizeof(listePersos[0]);
    int equipe_chosing = 1; 
    int d = 0;
    int n;           
    do {
        printf("Joueur %d : Choisissez le numero du personnage que vous souhaitez dans votre equipe ?\n", equipe_chosing);
        printf("Les personnages disponibles sont :\n");
        for(int i=0 ; i<=nmbPersosDispo ; i++) {
            if(listePersos[i].is_available == 1) {
                printf("%d - %s\n",i,listePersos[i].name);
            }
        }
        scanf(" %d", &n);
        if (listePersos[n].is_available == 0) {
                printf("Ce personnage n'est pas disponible \n");
        }
        else {
            if(equipe_chosing == 1) {
                Equipe1[d] = listePersos[n];
                equipe_chosing=2;
            }
            else if(equipe_chosing == 2) {
                Equipe2[d] = listePersos[n];
                equipe_chosing=1;
                d++;
            }
            listePersos[n].is_available=0;
        }
    } while(!equipeDef);
}
int main() {                                                                                                     //Fonction principale 
    int fin = 0;
    printf("\n*--------------- BIENVENUE DANS CY-FIGHTERS ! ---------------*\n\n");                              // affichage du menu
    printf("Que desirez-vous faire ?\n");
    printf("1. Jouer au mode joueur contre joueur\n"
           "2. Quitter\n");

    int c;
    c = getchar();
    if(c != '\n' && c != EOF) {
       int d;
       while((d = getchar()) != '\n' && d != EOF);
    }
    switch(c) {
        case '1':
            printf("Vous avez selectionne le mode joueur contre joueur \n\n");
            printf("Le jeu va commencer par une phase de conception des equipes.\n");
            definePersonnnages();                   
            defineEquipe();
            break;

        case '2':
            printf("A bientot !");
            fin = 1;
            break;

        default:
            printf("Choix errone\n\n");
    }

    return 0;
}
