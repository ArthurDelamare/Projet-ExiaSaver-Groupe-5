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
  int nbProgramme = 0; //variable stockant le numero du programme a executé
  int pid; //variable permettant de savoir s'il s'agit du proccesus père ou fils
  int fichierChoisi;
  char chemin[256]="";
  
  system("clear");
  if ((argc == 1) || (strcmp(argv[1],"-config") == 0) )
    {
      //détermination aléatoire du programme a lancé
      srand(time(NULL));
      nbProgramme = (rand() % 3) + 1;
      printf("le programme à lancer est le numero %d\n", nbProgramme);
      pid = fork();
      if (pid == 0)
	{
	  if (nbProgramme == 1)
	    {
	      fichierChoisi = (rand() % 5) + 1 ;
	      printf("le fichier a affiche est le %d\n", fichierChoisi);
	      choixFichier(fichierChoisi,chemin);
	      historique(1,chemin,"");
	      execl("EXIASAVER_HOME/exiasaver1",chemin,NULL);
	      exit(1);
	    }
	  else if (nbProgramme == 2)
	    {
	      historique(2,"","");
	      execl("EXIASAVER_HOME/exiasaver2","",NULL);
	      exit(2);
	    }
	  else if (nbProgramme == 3)
	    {
	      historique(3,"","9x10");
	      execl("EXIASAVER_HOME/exiasaver3","9x10",NULL);
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
