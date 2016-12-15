#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "BibliExiaSaver2.h"

int main(int argc, char* argv[], char** envp)
{
  //Initalisation des variables
  int pid;
  int i;
  char adresseExe[75];
  char adressePBM[75];
  strcpy(adresseExe,getenv("EXIASAVER_HOME"));
  strcpy(adresseExe,strcat(adresseExe,"/Afficheur"));
  strcpy(adressePBM,getenv("EXIASAVER2_PBM"));
  strcat(adressePBM,"/combinaison.pbm");

    //Création d'une boucle tant que infinie
    while(1)
    {
      //Appelle de la fonction
      heurePBM();
      //Création du processus Fils
      pid = fork();
      if (pid==0)
	{
          //Exécution de l'afficheur
	  execl(adresseExe,adressePBM,NULL);
	}
      printf("\nl'image s'actualisera dans %s secondes",getenv("EXIASAVER2_SLEEP"));
      wait(NULL);
      //Boucle en fonction de la variable d'environnement
      for (i=0;i<atoi(getenv("EXIASAVER2_SLEEP"));i++)
	{
          //Afficher un point
	  printf(".");
	  fflush(stdout);
          //Pause d'une seconde
	  sleep(1);
	}
    }
  return (0);
}
