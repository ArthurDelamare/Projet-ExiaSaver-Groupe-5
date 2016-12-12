#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void analyse(char portion, char* conteneurChemin)
{
  //vérifie à quel chiffre correspond le caractère envoyé et renvoit un chemin d'accès d'une image PBM, à optimiser avec un switch dans le futur
  if (portion == 48)
    {
      strcpy(conteneurChemin,"EXIASAVER2_PBM/0.pbm");
    }
  else if (portion == 49)
    {
      strcpy(conteneurChemin,"EXIASAVER2_PBM/1.pbm");
    }
  else if (portion == 50)
    {
      strcpy(conteneurChemin,"EXIASAVER2_PBM/2.pbm");
    }
  else if (portion == 51)
    {
      strcpy(conteneurChemin,"EXIASAVER2_PBM/3.pbm");
    }
  else if (portion == 52)
    {
      strcpy(conteneurChemin,"EXIASAVER2_PBM/4.pbm");
    }
  else if (portion == 53)
    {
      strcpy(conteneurChemin,"EXIASAVER2_PBM/5.pbm");
    }
  else if (portion == 54)
    {
      strcpy(conteneurChemin,"EXIASAVER2_PBM/6.pbm");
    }
  else if (portion == 55)
    {
      strcpy(conteneurChemin,"EXIASAVER2_PBM/7.pbm");
    }
  else if (portion == 56)
    {
      strcpy(conteneurChemin,"EXIASAVER2_PBM/8.pbm");
    }
  else if (portion == 57)
    {
      strcpy(conteneurChemin,"EXIASAVER2_PBM/9.pbm");
    }
}


void heurePBM()
{
  //variables nécessaire pour récupérer l'heure actuelle
  struct tm heure;
  time_t secondes;
  //chaine de caractères contenant les heures
  char conteneurHeure[3];
  //chaine de caractères contenant les minutes
  char conteneurMinutes[3];
  //chaine de caractères contenant les secondes
  char conteneurSecondes[3];

  //variables contenant le chemin des images PBM composant l'heure
  char cheminChiffre1[25];
  char cheminChiffre2[25];
  char cheminChiffre3[25];
  char cheminChiffre4[25];
  char cheminChiffre5[25];
  char cheminChiffre6[25];

  char conteneurReec[50];
  int i;
  int nbcaractere;
  
  //initialisation de la structure du temps
  time(&secondes);
  heure = *localtime(&secondes);

  //on met les heures, les minutes et les secondes dans des chaines de caractères
  sprintf(conteneurHeure,"%d",heure.tm_hour);
  sprintf(conteneurMinutes,"%d",heure.tm_min);
  sprintf(conteneurSecondes,"%d",heure.tm_sec);

  //chargement des chemins d'accès des fichiers à afficher
  analyse(conteneurHeure[0],cheminChiffre1);
  printf("le chemin du premier chiffre à afficher est %s\n",cheminChiffre1);
  analyse(conteneurHeure[1],cheminChiffre2);
  printf("le chemin du second chiffre à afficher est %s\n",cheminChiffre2);
  analyse(conteneurMinutes[0],cheminChiffre3);
  printf("le chemin du troisieme chiffre à afficher est %s\n",cheminChiffre3);
  analyse(conteneurMinutes[1],cheminChiffre4);
  printf("le chemin du quatrieme chiffre à afficher est %s\n",cheminChiffre4);
  analyse(conteneurSecondes[0],cheminChiffre5);
  printf("le chemin du cinquieme chiffre à afficher est %s\n",cheminChiffre5);
  analyse(conteneurSecondes[1],cheminChiffre6);
  printf("le chemin du cinquieme chiffre à afficher est %s\n",cheminChiffre6);

  //Déclaration des fichiers à utiliser
  FILE* chiffre1;
  FILE* chiffre2;
  FILE* chiffre3;
  FILE* chiffre4;
  FILE* chiffre5;
  FILE* chiffre6;
  FILE* combinaison;

  combinaison = fopen("EXIASAVER2_PBM/combinaison.pbm","w");
  fprintf(combinaison,"P1\n#Fichier combinant des images PBM pour créer l'image PBM de l'heure\n10 10\n");
  fclose(combinaison);

  combinaison = fopen("EXIASAVER2_PBM/combinaison.pbm","a");
  chiffre1 = fopen(cheminChiffre1,"r");
  chiffre2 = fopen(cheminChiffre2,"r");
  chiffre3 = fopen(cheminChiffre3,"r");
  chiffre4 = fopen(cheminChiffre4,"r");
  chiffre5 = fopen(cheminChiffre5,"r");
  chiffre6 = fopen(cheminChiffre6,"r");

  for(i=0;i<3;i++)
    {
      fgets(conteneurReec,50,chiffre1);
      fgets(conteneurReec,50,chiffre2);
      fgets(conteneurReec,50,chiffre3);
      fgets(conteneurReec,50,chiffre4);
      fgets(conteneurReec,50,chiffre5);
      fgets(conteneurReec,50,chiffre6);
    }

  for(i=0;i<5;i++)
    {
      fgets(conteneurReec,50,chiffre1);
      nbcaractere = strlen(conteneurReec);
      conteneurReec[(nbcaractere-1)] = '\0';
      fprintf(combinaison,"%s",conteneurReec);

      fprintf(combinaison,"0 ");

      fgets(conteneurReec,50,chiffre2);
      nbcaractere = strlen(conteneurReec);
      conteneurReec[(nbcaractere-1)] = '\0';
      fprintf(combinaison,"%s",conteneurReec);

      fprintf(combinaison,"0 ");
      
      fgets(conteneurReec,50,chiffre3);
      nbcaractere = strlen(conteneurReec);
      conteneurReec[(nbcaractere-1)] = '\0';
      fprintf(combinaison,"%s",conteneurReec);

      fprintf(combinaison,"0 ");

      fgets(conteneurReec,50,chiffre4);
      nbcaractere = strlen(conteneurReec);
      conteneurReec[(nbcaractere-1)] = '\0';
      fprintf(combinaison,"%s",conteneurReec);

      fprintf(combinaison,"0 ");

      fgets(conteneurReec,50,chiffre5);
      nbcaractere = strlen(conteneurReec);
      conteneurReec[(nbcaractere-1)] = '\0';
      fprintf(combinaison,"%s",conteneurReec);

      fprintf(combinaison,"0 ");

      fgets(conteneurReec,50,chiffre6);
      nbcaractere = strlen(conteneurReec);
      conteneurReec[(nbcaractere-1)] = '\0';
      fprintf(combinaison,"%s\n",conteneurReec);
    }
  fclose(combinaison);
  fclose(chiffre1);
  fclose(chiffre2);
  fclose(chiffre3);
  fclose(chiffre4);
  fclose(chiffre5);
  fclose(chiffre6);
  
}




