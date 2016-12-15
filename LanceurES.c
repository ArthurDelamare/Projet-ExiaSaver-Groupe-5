#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "BibliLanceurES.h"

int main(int argc, char* argv[],char** envp)
{
  if (argc == 2 && strcmp(argv[1],"-config") == 0)
    {
      //Changement des variables d'environnement par l'utilisateur
      choixVarEnv();
    }
    
  //Déclaration de variables utilisées dans ce programme
  //variable stockant le numero du programme a executé
  int nbProgramme = 0;
  //variable permettant de savoir s'il s'agit du proccesus père ou fils
  int pid;
  //variable stockant le numero de l'image PBM à afficher (écran statique)
  int fichierChoisi;
  char chemin[256]="";
  //variable stockant le chemin d'accès d'un executable
  char adresseExe[100];
  
  system("clear");
  if ((argc == 1) || (strcmp(argv[1],"-config") == 0) )
    {
      //détermination aléatoire du programme a lancé
      srand(time(NULL));
      nbProgramme = (rand() % 3) + 1;
      //création d'un processus fils qui exécute l'écran de veille
      pid = fork();
      if (pid == 0)
	{
	  if (nbProgramme == 1)
	    {
	      //Choix aléatoire de l'image PBM à afficher
	      fichierChoisi = (rand() % 5) + 1 ;
	      choixFichier(fichierChoisi,chemin);
	      //détermination du chemin de l'image à afficher
	      strcpy(chemin,strcat(getenv("EXIASAVER1_PBM"),chemin));
	      //Sauvegarde des données dans l'historique
	      historique(1,chemin,"");
	      //détermination du chemin de l'exécutable
	      strcpy(adresseExe,getenv("EXIASAVER_HOME"));
	      //exécution de l'écran de veille statique
	      execl(strcat(adresseExe,"/exiasaver1"),chemin,NULL);
	      exit(1);
	    }
	  else if (nbProgramme == 2)
	    {
	      //Sauvegarde des données dans l'historique
	      historique(2,"","");
	      //détermination du chemin de l'exécutable
	      strcpy(adresseExe,getenv("EXIASAVER_HOME"));
	      //exécution de l'écran de veille dynamique
	      execl(strcat(adresseExe,"/exiasaver2"),"",NULL);
	      exit(2);
	    }
	  else if (nbProgramme == 3)
	    {
	      //Sauvegarde des données dans l'historique
	      historique(3,"","9x10");
	      //détermination du chemin de l'exécutable
	      strcpy(adresseExe,getenv("EXIASAVER_HOME"));
	      execl(strcat(adresseExe,"/exiasaver3"),"9x10",NULL);
	      exit(3);
	    }
	}
      else
	{
	  wait(NULL);
	}
    }
  else if(argc == 2 && strcmp(argv[1],"-stats") == 0)
    {
      statistique();
    }
  else
    {
      printf("les arguments sont incorrect\n");
    }
  return (0);
}
