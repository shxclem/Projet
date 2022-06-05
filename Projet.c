#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

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
    int team;
    //Sort s;
    //Coup c;
 } Personnage;

Personnage listePersos[7];                                                                                       //On définit la taille de la liste des personnages
Personnage Fighters[6];

void ajouterPersoEquipe(int equipe, int num, int place) {
    Personnage newMember;
    
    strcpy(newMember.name, listePersos[num].name);
    newMember.att = listePersos[num].att;
    newMember.def = listePersos[num].def;
    newMember.hpmax = listePersos[num].hpmax;
    newMember.dodge = listePersos[num].dodge;
    newMember.speed = listePersos[num].speed;
    newMember.hp = listePersos[num].hp;
    newMember.classe = listePersos[num].classe;
    newMember.etat = listePersos[num].etat;
    newMember.is_available = 1;
    newMember.team = equipe;
    
    Fighters[place] = newMember;

}

void fusionner(int tab[], int debut, int milieu, int fin){
  int indexA, indexB, i;
  int aux[5];
  indexA=debut;
  indexB=fin;
  //remplissage de la partie gauche du tableau aux
  for(i=debut;i<=milieu;i++){
    aux[i]=tab[i];
  }
  // remplissage de la partie droite du tableau aux
  for(i=milieu+1;i<=fin;i++){
    aux[i]=tab[fin-i+milieu+1];
  }
  // tri de tab 
  for(i=debut;i<=fin;i++){
    if(aux[indexA]<aux[indexB]){
      tab[i]=aux[indexA];
      indexA++;
    }
    else{
      tab[i]=aux[indexB];
      indexB--;
    }
  }
}

void trifusionRec(int tab[], int debut, int fin){
  int milieu;
    if(debut<fin){
      milieu=(debut+fin)/2;
    
    //découpe du tableau par la gauche puis par la droite
      trifusionRec(tab, debut,milieu);
      trifusionRec(tab, milieu+1,fin);
  //fusion des sous tableaux
      fusionner(tab, debut, milieu,fin);
      }
}

void trifusion(int tab[], int taille)
{
	trifusionRec (tab, 0,taille-1);
}

Personnage readNouveauPersonnage(char* string, char* delim) {                                                    //Fonction pour créer un nouveau personnage
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

void definePersonnnages() {                                                                                      //Procédure permettant de lire la liste des personnages
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

void defineEquipes() {                                                                                           //Procédure permettant de créer les équipes
    int is_equipeDef = 0;
    int nmbPersosDispo = sizeof(listePersos)/sizeof(listePersos[0]);
    int equipe_chosing = 1; 
    int numPerso = 0;
    int n;           

    do {
        printf("Joueur %d : Choisissez le numero du personnage que vous souhaitez dans votre equipe ?\n", equipe_chosing);
        printf("Les personnages disponibles sont :\n");
        //sleep(1);

        for(int i=0 ; i<=nmbPersosDispo ; i++) {
            if(listePersos[i].is_available) {
                printf("%d - %s\n",i,listePersos[i].name);
            }
        }

        scanf(" %d", &n);

        if (!listePersos[n].is_available) {
                printf("Ce personnage n'est pas disponible \n");
        }
        else {

            if(equipe_chosing == 1) {
                ajouterPersoEquipe(1, n, numPerso);
                equipe_chosing=2;
            }
            else if(equipe_chosing == 2) {
                ajouterPersoEquipe(2, n, numPerso);
                equipe_chosing=1;                
            }
            numPerso++;

            listePersos[n].is_available=0;
        }
        
        if(numPerso == 5){
            is_equipeDef = 1;
        }

    } while(!is_equipeDef);
}

int main() {                                                                                                     //Fonction principale 
    int fin = 0;
    int speed[6];
    printf("\n*--------------- BIENVENUE DANS CY-FIGHTERS ! ---------------*\n\n");                              //Affichage du menu
    //sleep(2);
    printf("Que desirez-vous faire ?\n");
    //sleep(2);
    printf("1. Jouer au mode joueur contre joueur\n"
           "2. Quitter\n");

    int c;
    c = getchar();
    if(c != '\n' && c != EOF) {                                                                                  //On récupère le caractère écrit par l'utilisateur
       int d;
       while((d = getchar()) != '\n' && d != EOF);
    }
    switch(c) {
        case '1':
            printf("Vous avez selectionne le mode joueur contre joueur \n\n"                                               //Sélection des équipes
                   "Le jeu va commencer par une phase de selection des heros.\n");

            //sleep(2);

            definePersonnnages();                   
            defineEquipes();

            printf("La phase de selection est terminee, les equipes sont les suivantes :\n"); 

            //sleep(2);

            printf("EQUIPE 1 : %s, %s, %s\n", Fighters[0].name, Fighters[2].name, Fighters[4].name);
            printf("EQUIPE 2 : %s, %s, %s\n", Fighters[1].name, Fighters[3].name, Fighters[5].name);

            for(int i=0 ; i<=6 ; i++) {                                                                                    //Tri des vitesses pour l'ordre d'attaque
                speed[i]=Fighters[i].speed;
            }

            trifusion(speed, 5);
            for(int j=0 ; j<=5 ; j++){
                printf("%d\n", speed[j]);
            }

            sleep(1);

            printf("Maintenant, que le combat commence !\n");
            printf("**************** DEBUT DU COMBAT ****************\n");                                                  //Début du combat 
            sleep(1);
            int teamAce = 0;
            while(!teamAce) {                                                                                               //Condition de fin de partie
                
                if(Fighters[0].hp <= 0 & Fighters[2].hp <= 0 & Fighters[4].hp <= 0) {
                    teamAce = 1;
                    printf("Les heros de l'equipe 1 sont morts, le joueur 2 remporte la partie !\n ");
                }
                if(Fighters[1].hp <= 0 & Fighters[3].hp <= 0 & Fighters[5].hp <= 0) {
                    teamAce = 1;
                    printf("Les heros de l'equipe 2 sont morts, le joueur 1 remporte la partie !\n ");
                }
            }

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
