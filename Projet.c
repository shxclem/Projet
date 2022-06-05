#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

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
} Personnage;

Personnage listePersos[8];                                                                                       //On définit la taille de la liste des personnages
Personnage Fighters[6];

void ajouterPersoEquipe(int equipe, int num, int place) {                                                        //Ajouter un perso dans une équipe
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

void fusionner(Personnage tab[], int debut, int milieu, int fin){                                                //Procédures 
    int indexA, indexB, i;
    Personnage aux[6];
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
        if(aux[indexA].speed>aux[indexB].speed){
            tab[i]=aux[indexA];
            indexA++;
        }
        else{
            tab[i]=aux[indexB];
            indexB--;
        }
    }
}

void trifusionRec(Personnage tab[], int debut, int fin){                                                         //de
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

void trifusion(Personnage tab[], int taille)                                                                     //tri
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

        for(int i=0 ; i<nmbPersosDispo ; i++) {
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
        
        if(numPerso == 6){
            is_equipeDef = 1;
        }

    } while(!is_equipeDef);
}

int checkTeamAce() {                                                                                             //Fonction retournant si une équipe est éliminée ou non
    int hp_equipe1 = 0; 
    int hp_equipe2 = 0;

    for(int i=0 ; i<=5 ; i++) {
        if(Fighters[i].team == 1) {
            hp_equipe1 = hp_equipe1 + Fighters[i].hp;
        }
        else if(Fighters[i].team == 2) {
            hp_equipe2 = hp_equipe2 + Fighters[i].hp;
        }
    }

    if(hp_equipe1 == 0) {
        return 1;
    }
    else if(hp_equipe2 == 0) {
        return 2;
    }
    else {
        return 0;
    }
}

void attack(int attacker, int attacked) {                                                                        //Procédure qui correspond à une attaque
    int rnd;
    rnd = (rand())%101;

    if (rnd < Fighters[attacked].dodge ) {
        printf("Quelle agilite, %s evite l'attaque !\n", Fighters[attacked].name);
        sleep(1);
    }

    else {
        sleep(1);
        float damage_reduction = ((float)Fighters[attacker].att) * ((float)Fighters[attacked].def / 100);
        int damage = Fighters[attacker].att - damage_reduction;
        Fighters[attacked].hp = Fighters[attacked].hp - damage;
        printf("En plein de le mille ! %s souffre et perd %d hp !\n\n", Fighters[attacked].name, damage);
        sleep(1);

        if(Fighters[attacked].hp <=0 ) {
            Fighters[attacked].hp = 0;
            printf("%s n'a plus aucun pv, il succombe !\n", Fighters[attacked].name);
            sleep(1);
        }
    }
}

int main() {                                                                                                     //Fonction principale 
    int fin = 0;

    printf("\n*--------------- BIENVENUE DANS CY-FIGHTERS ! ---------------*\n\n");                              //Affichage du menu
    sleep(2);
    printf("Que desirez-vous faire ?\n");
    sleep(2);
    printf("1. Jouer au mode joueur contre joueur\n"
           "2. Quitter\n");

    int c;
    c = getchar(); 
    if(c != '\n' && c != EOF) {                                                                                  //On récupère le caractère écrit par l'utilisateur
       int d;
       while((d = getchar()) != '\n' && d != EOF);
    }

    switch(c) {                                                                                                     //Différents choix possibles

        case '1':                                                                                                          //L'utilisateur a décidé de jouer
            printf("Vous avez selectionne le mode joueur contre joueur.\n\n"                                               //Sélection des équipes
                   "Le jeu va commencer par une phase de selection des heros.\n");

            sleep(2);

            definePersonnnages();                   
            defineEquipes();

            printf("La phase de selection est terminee, les equipes sont les suivantes :\n"); 

            sleep(2);

            printf("EQUIPE 1 : %s, %s, %s\n", Fighters[0].name, Fighters[2].name, Fighters[4].name);                        //Affichage des équipes
            printf("EQUIPE 2 : %s, %s, %s\n", Fighters[1].name, Fighters[3].name, Fighters[5].name);

            sleep(3);

            trifusion(Fighters, 6);

            sleep(1);

            printf("\nMaintenant, que le combat commence !\n\n");
            printf("**************** DEBUT DU COMBAT ****************\n\n");                                                  //Début du combat 

            sleep(1);

            int teamAce = 0;
            int a;
            srand(time(NULL));

            while(teamAce == 0) {                                                                                               //Condition de fin de partie

                for(int i=0 ; i<=5 ; i++) {                                                                                     //Déroulement du combat
                    if((Fighters[i].hp > 0) & (teamAce == 0)) {  
                        int attDone = 0;
            
                        do {
                            sleep(1);
                            printf("C'est au tour de %s d'attaquer.\n\n", Fighters[i].name);
                            sleep(1);
                            printf("Joueur %d, ecrivez le numero du heros que vous souhaitez attaquer ?\n", Fighters[i].team);

                            for(int j=0 ; j<=5 ; j++) {                                                                         //Affichage des cibles possibles
                                    if(Fighters[j].team != Fighters[i].team ) {
                                        printf("%d - %s (%d hp)\n", j, Fighters[j].name, Fighters[j].hp);
                                    }
                            }
                
                            scanf("%d", &a);                                                                                    //Choix du joueur
                            if((a < 0) || (a > 5)) {
                                printf("Erreur, veuillez cibler un personnage disponible.\n");
                                sleep(1);
                            }

                            else if(Fighters[a].team == Fighters[i].team) {
                                printf("Ce heros fait partie de votre equipe, il vaudrait mieux attaquer vos adversaires !\n");
                                sleep(1);
                            }

                            else if(Fighters[a].hp <= 0) {
                                printf("Ce personnage est deja mort, veuillez en viser un autre. \n");
                                sleep(1);
                            }

                            else {
                                attack(i, a);
                                teamAce = checkTeamAce();                                                                       //Une équipe est-elle éliminée 
                                attDone = 1;
                            }

       
                        } while(attDone == 0);
                    }   
                } 
            }
            printf("L'equipe %d a ete eliminee !\n", teamAce );                                                                 //Fin du jeu
            sleep(2);
            if(teamAce == 1) {
                printf("Joueur 2, c'est vous le meilleur, bravo pour votre victoire !\n");
            }
            else {
                printf("Joueur 1, c'est vous le meilleur, bravo pour votre victoire !");
            }

            break;

        case '2':                                                                                                               //L'utilisateur a décidé de quitter le programme

            printf("A bientot !");
            fin = 1;
            break;

        default:                                                                                                                //Le caractère écrit ne correspond à rien
            printf("Choix errone.\n\n");
    }

    return 0;
}
