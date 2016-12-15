#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "BibliExiaSaver2.h"

int main(int argc, char* argv[], char** envp)
{
  int pid;
  int i;
  char adresseExe[75];
  char adressePBM[75];
  
  strcpy(adresseExe,getenv("EXIASAVER_HOME"));
  strcpy(adresseExe,strcat(adresseExe,"/Afficheur"));

  strcpy(adressePBM,getenv("EXIASAVER2_PBM"));
  strcat(adressePBM,"/combinaison.pbm");
  
  printf("Je suis le programme 2, %s\n%s\n",adresseExe,adressePBM);
  printf("la taille des lettres est: %s\n", getenv("EXIASAVER2_TAILLE"));
  while(1)
    {
      heurePBM();
      pid = fork();
      if (pid==0)
	{
	  execl(adresseExe,adressePBM,NULL);
	}
      printf("\nl'image s'actualisera dans %s secondes",getenv("EXIASAVER2_SLEEP"));
      wait(NULL);
      for (i=0;i<atoi(getenv("EXIASAVER2_SLEEP"));i++)
	{
	  printf(".");
	  fflush(stdout);
	  sleep(1);
	}
    }
  return (0);
}
