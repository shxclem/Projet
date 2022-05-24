#include <stdio.h>
#include <string.h>

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
    Sort s;
    Coup c;
 } Personnage;

Personnage readPersonnage() {
    Personnage perso;
    // Personnage.name[20] = 
    // Personnage.att = 
    // Personnage.def =
    // Personnage.hpmax =
    // Personnage.dodge =
    // Personnage.dodge =
    // Personnage.speed =
    // Personnage.hp =
    // Personnage.classe =
    // Personnage.etat =
    strcpy(perso.name,"Zed");
    return perso;
}

int main() {
    Personnage p ;
    // do{
    //     printf("    Bienvenue dans CY Fighters\n    Appuyez sur 'a' pour continuer.\n    Appuyez sur 'b' pour sortir du jeu.");
    // while (getchar =! 'a' & getchar=! 'b')}
    int main() {

   Personnage p = {
      "Zed",   //name
      0.5,     //att
      0.5,     //def
      100,     //hpmax
      0.5,     //dodge
      0.5,     //speed
      100,     //hp
      0,       //classe
      0        //etat
   };

   printf("\nPerso créé : %s\n", p.name);

   return 0;
}
