# Projet
Cy-fighters

# git commands
Check des modifs:
`git status`

Check des modifs plus poussé:
`git diff`

Ajouter les modifs pour préparer le commit:
`git add *`

Création du commit:
`git commit -m "Message du commit"`

Premier push des nouvelles branches: 
`git push origin nom-de-la-branche-a-creer-sur-le-serveur"`

Créer le lien entre dev local et serveur git:
`git push --set-upstream origin nom-branche-sur-serveur`

Pusher du code quand la branche est liée: 
`git push`

# MODIFS 16/05/22

#include <stdio.h>

typedef struct{
    char name[50];
    char description[500];
    int att;
    int cd;
    int alt;
}Sort;

typedef Struct{
    char nom[30];
    char description[500]
}Coup;

typedef struct{
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
}Personnage;

int main(){
    do{
        printf("    Bienvenue dans CY Fighters\n    Appuyez sur 'a' pour continuer.\n    Appuyez sur 'b' pour sortir du jeu.");
    while(getchar =! 'a' & getchar=! 'b')}
}
