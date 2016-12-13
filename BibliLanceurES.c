#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void choixFichier(int n,char* chemin)
{
  DIR* repPBM;
  struct dirent* fichierLu;
  int i = 0;
  char containerFileName[256];
  
  repPBM = opendir(getenv("EXIASAVER1_PBM"));
  if (repPBM == NULL)
    {
      perror("");
    }

  while(i != n)
    {
      fichierLu = readdir(repPBM);
      if (strcmp(fichierLu->d_name,".")!=0 && strcmp(fichierLu->d_name,"..")!=0)
	{
	  strcpy(containerFileName,fichierLu->d_name);
	  i++;
	}
    }

  closedir(repPBM);
  
  strcat(chemin,"EXIASAVER1_PBM/");
  strcat(chemin,containerFileName);
}


void historique(int typeTimeSaver, char* nomFichierPBM1, char* posAvion)
{
  
  //déclaration structure et variable pour récupérer la date et l'heure
  struct tm temps;
  time_t secondes;
  //variable servant de séparation dans l'utilisation de strtok()
  char sep[2]="/";
  char stockageNom[50];

    
  //place le nombre de secondes écoulées depuis 1970 dans la variable secondes
  time(&secondes);
  //initialise la structure temps à l'aide de la variable secondes
  temps = *localtime(&secondes);

  //écriture du fichier historique
  FILE* fichier;
  fichier = fopen("historique.txt","a");
  if (typeTimeSaver == 1)
    {
      //séparation du nom du fichier du chemin complet
      strcpy(stockageNom,nomFichierPBM1);
      strcat(stockageNom,"/");
      strcpy(stockageNom,strtok(stockageNom,sep));
      strcpy(stockageNom,strtok(NULL,sep));
      
      fprintf(fichier,"%d/%d/%d %d:%d:%d;%d;%s\n",temps.tm_mday,temps.tm_mon+1,temps.tm_year+1900,temps.tm_hour,temps.tm_min,temps.tm_sec,typeTimeSaver,stockageNom);
    }
  else if (typeTimeSaver == 2)
    {
      fprintf(fichier,"%d/%d/%d %d:%d:%d;%d;%s\n",temps.tm_mday,temps.tm_mon+1,temps.tm_year+1900,temps.tm_hour,temps.tm_min,temps.tm_sec,typeTimeSaver,getenv("EXIASAVER2_TAILLE"));
    }
  else if (typeTimeSaver == 3)
    {
      fprintf(fichier,"%d/%d/%d %d:%d:%d;%d;%s\n",temps.tm_mday,temps.tm_mon+1,temps.tm_year+1900,temps.tm_hour,temps.tm_min,temps.tm_sec,typeTimeSaver,posAvion);
    }
  
  fclose(fichier);
}


void choixVarEnv()
{
  
  char newVarEnv[75];
  int choixVarEnv = 1;

  while(choixVarEnv != 0)
  {
  printf("Quel variable d'environnement souhaitez vous changer?\n1: EXIASAVER_HOME\n2: EXIASAVER1_PBM\n3: EXIASAVER2_PBM\n4: EXIASAVER2_TAILLE\n5: EXIASAVER2_SLEEP\n6: EXIASAVER3_PBM\n0: quitter ce menu et lancer le programme\n");
  scanf("%d",&choixVarEnv);
  switch (choixVarEnv)
    {
    case 1:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER_HOME",newVarEnv,1);
      break;
    case 2:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER1_PBM",newVarEnv,1);
      break;
    case 3:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER2_PBM",newVarEnv,1);
      break;
    case 4:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER2_TAILLE",newVarEnv,1);
      break;
    case 5:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER2_SLEEP",newVarEnv,1);
      break;
    case 6:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER3_PBM",newVarEnv,1);
      break;
    default:
      printf("erreur dans la saisie, veuillez réessayer avec une valeur correcte\n");
    }
  system("clear");
  }
   
}

void triBulle(int tab[], int tailleTab)
{
  int i,j, valIntermediaire;

  for (i = tailleTab-1; i>0; i--)
    {
      for (j=1; j<=i;j++)
	{
	  if (tab[j-1]>tab[j])
	    {
	      valIntermediaire = tab[j-1];
	      tab[j-1] = tab[j];
	      tab[j] = valIntermediaire;
	    }
	}
    }
}

void statsTypeTS()
{
  //Tableau destiné à stocker les données brutes sur les termSavers utilisés
  int tableauTypeTS[200] = {0};
  //variable pour la manipulation du fichier historique.txt
  FILE* historique;
  //variable utilisé comme compteur
  int i=0;
  //variable stockant l'addition des différents types d'écrans utilisés
  int type1, type2, type3;
  //Variable permettant de stocker une ligne de l'historique
  char container[100];
  //caractère de séparation pour l'utilisation de strtok()
  char sep[2]=";";
  
  historique = fopen("historique.txt","r");

  //On passe les quatres premiers lignes qui sont des commentaires
  for (i=0;i<4;i++)
    {
      fgets(container,100,historique);
    }

  //Récupération du type d'écran de veille utilisé depuis l'historique puis on place cette donnée dans un tableau
  while((fgets(container,100,historique)) != NULL)
    {
      strcpy(container,strtok(container,sep));
      strcpy(container,strtok(NULL,sep));
      tableauTypeTS[i] = atoi(container);
      i++;
    }
  fclose(historique);

  //Tri du tableau
  triBulle(tableauTypeTS,200);
  
  for(i=0;i<200;i++)
    {
      
      printf("%d - ",tableauTypeTS[i]);
    }
}

void statistique()
{
  //choix d'une statistique par l'utilisateur
  int choixStats;
  printf("Bienvenue dans la partie statistique (effectué sur un échantillon de 50 lancements maximum)\nQuelle est la statistique qui vous intéresse ?\n1: la moyenne de lancement par mois\n2: le pourcentage de lancement selon les types de termSaver\n3: l'image lancée le plus souvent en termSaver statique\n4: les dimensions de PBM les plus fréquentes dans le termSaver dynamique\n");
  scanf("%d",&choixStats);
  statsTypeTS();
}

