#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void analyse(char portion, char* conteneurChemin)
{
  char tamponVarEnv[75];
  strcpy(tamponVarEnv,getenv("EXIASAVER2_PBM"));
  
  //Vérifie à quel chiffre correspond le caractère envoyé et renvoit un chemin d'accès d'une image PBM
  if (portion == 48)
    {
      strcpy(conteneurChemin,strcat(tamponVarEnv,"/0.pbm"));
    }
  else if (portion == 49)
    {
      strcpy(conteneurChemin,strcat(tamponVarEnv,"/1.pbm"));
    }
  else if (portion == 50)
    {
      strcpy(conteneurChemin,strcat(tamponVarEnv,"/2.pbm"));
    }
  else if (portion == 51)
    {
      strcpy(conteneurChemin,strcat(tamponVarEnv,"/3.pbm"));
    }
  else if (portion == 52)
    {
      strcpy(conteneurChemin,strcat(tamponVarEnv,"/4.pbm"));
    }
  else if (portion == 53)
    {
      strcpy(conteneurChemin,strcat(tamponVarEnv,"/5.pbm"));
    }
  else if (portion == 54)
    {
      strcpy(conteneurChemin,strcat(tamponVarEnv,"/6.pbm"));
    }
  else if (portion == 55)
    {
      strcpy(conteneurChemin,strcat(tamponVarEnv,"/7.pbm"));
    }
  else if (portion == 56)
    {
      strcpy(conteneurChemin,strcat(tamponVarEnv,"/8.pbm"));
    }
  else if (portion == 57)
    {
      strcpy(conteneurChemin,strcat(tamponVarEnv,"/9.pbm"));
    }

}


void heurePBM()
{
  //Variables nécessaire pour récupérer l'heure actuelle
  struct tm heure;
  time_t secondes;
  //Chaine de caractères contenant les heures
  char conteneurHeure[3];
  //Chaine de caractères contenant les minutes
  char conteneurMinutes[3];
  //Chaine de caractères contenant les secondes
  char conteneurSecondes[3];

  //Variables contenant le chemin des images PBM composant l'heure
  char cheminChiffre1[75];
  char cheminChiffre2[75];
  char cheminChiffre3[75];
  char cheminChiffre4[75];
  char cheminChiffre5[75];
  char cheminChiffre6[75];
  char separation1[75];
  char separation2[75];

  char conteneurReec[50];
  int i;
  int nbcaractere;

  //
  char adressePoint[75];
  char adresseCombi[75];
  strcpy(adressePoint,getenv("EXIASAVER2_PBM"));
  strcpy(adresseCombi,adressePoint);
  //
  strcat(adressePoint,"/:.pbm");
  strcat(adresseCombi,"/combinaison.pbm");
  printf("%s - %s\n",adressePoint,adresseCombi);

  //Initialisation de la structure du temps
  time(&secondes);
  heure = *localtime(&secondes);

  //On met les heures, les minutes et les secondes dans des chaines de caractères
  sprintf(conteneurHeure,"%d",heure.tm_hour);
  sprintf(conteneurMinutes,"%d",heure.tm_min);
  sprintf(conteneurSecondes,"%d",heure.tm_sec);

  //Si la longeur de la variable ne contient qu'un seul caractère, alors on rajoute un caractère
  if(strlen(conteneurHeure) == 1)
  {
  conteneurHeure[2] = conteneurHeure[1];
  conteneurHeure[1] = conteneurHeure[0];
  conteneurHeure[0] = '0';
  }

  if(strlen(conteneurMinutes) == 1)
  {
  conteneurMinutes[2] = conteneurMinutes[1];
  conteneurMinutes[1] = conteneurMinutes[0];
  conteneurMinutes[0] = '0';
  }

  if(strlen(conteneurSecondes) == 1)
  {
  conteneurSecondes[2] = conteneurSecondes[1];
  conteneurSecondes[1] = conteneurSecondes[0];
  conteneurSecondes[0] = '0';
  }

  //Chargement des chemins d'accès des fichiers à afficher
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
  FILE* point1;
  FILE* point2;

  //Ouverture du fichier pbm contenant les deux points
  point1 = fopen(adressePoint, "r");
  point2 = fopen(adressePoint, "r");
  //Ouverture et suppression du fichier pbm 
  combinaison = fopen(adresseCombi,"w");
  fprintf(combinaison,"P1\n#Fichier combinant des images PBM pour créer l'image PBM de l'heure\n10 10\n");
  fclose(combinaison);
  //Ouverture des fichiers pbm
  combinaison = fopen(adresseCombi,"a");
  chiffre1 = fopen(cheminChiffre1,"r");
  chiffre2 = fopen(cheminChiffre2,"r");
  chiffre3 = fopen(cheminChiffre3,"r");
  chiffre4 = fopen(cheminChiffre4,"r");
  chiffre5 = fopen(cheminChiffre5,"r");
  chiffre6 = fopen(cheminChiffre6,"r");

  //Lecture des 3 premières lignes
  for(i=0;i<3;i++)
    {
      fgets(conteneurReec,50,chiffre1);
      fgets(conteneurReec,50,chiffre2);
      fgets(conteneurReec,50,chiffre3);
      fgets(conteneurReec,50,chiffre4);
      fgets(conteneurReec,50,chiffre5);
      fgets(conteneurReec,50,chiffre6);
      fgets(separation1, 25, point1);
      fgets(separation2, 25, point2);
    }

  //Lecture des 0 et des 1 
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
      fgets(separation1,25,point1);
      nbcaractere = strlen(separation1);
      separation1[(nbcaractere-1)] = '\0';
      fprintf(combinaison,"%s",separation1);

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
      fgets(separation2,25,point2);
      nbcaractere = strlen(separation2);
      separation2[(nbcaractere-1)] = '\0';
      fprintf(combinaison,"%s",separation2);

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

  //Fermeture des fichiers pbm
  fclose(combinaison);
  fclose(chiffre1);
  fclose(chiffre2);
  fclose(chiffre3);
  fclose(chiffre4);
  fclose(chiffre5);
  fclose(chiffre6);
  fclose(point1);
  fclose(point2);
}
