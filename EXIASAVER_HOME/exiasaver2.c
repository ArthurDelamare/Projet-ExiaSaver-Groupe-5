#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "BibliExiaSaver2.h"

int main(int argc, char* argv[], char** envp)
{
  int pid;
  int i;
  
  printf("Je suis le programme 2\n");
  printf("la taille des lettres est: %s\n", getenv("EXIASAVER2_TAILLE"));
  while(1)
    {
      heurePBM();
      pid = fork();
      if (pid==0)
	{
	  execl("Afficheur","EXIASAVER2_PBM/combinaison.pbm",NULL);
	}
      printf("\nl'image s'actualisera dans %s secondes",getenv("EXIASAVER2_SLEEP"));
      wait(NULL);
      for (i=0;i<10;i++)
	{
	  printf(".\n");
	  sleep(1);
	}
    }
  return (0);
}
