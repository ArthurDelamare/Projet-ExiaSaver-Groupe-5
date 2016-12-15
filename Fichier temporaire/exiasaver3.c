#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "BibliES3.h"

int main(int argc, char* argv[], char** envp)
{
  //variables qui détermine la position du point central de l'avion
  int x=40;
  int y=11;
  //tableau à deux dimensions définissant le terrain dans lequel l'avion se déplace
  int tabTerrain[23][60] = {0};
  char move = 'd';
  char tempmove;
  int pid;
  //Variable tampon pour récupérer des variables d'environnements et former des chemins utilisés par l'exécutable
  char adresseExe[75];
  char adresseAvion [75];
  //Récupération de la variable d'environnement et concaténation
  strcpy(adresseExe,getenv("EXIASAVER_HOME"));
  strcpy(adresseExe,strcat(adresseExe,"/Afficheur"));
  printf("%s\n",adresseExe);
  strcpy(adresseAvion,getenv("EXIASAVER3_PBM"));
  strcpy(adresseAvion,strcat(adresseAvion,"/avion.pbm"));
  printf("%s\n",adresseAvion);
  
  while(move != 'e')
    {
      //initTableau(tabTerrain);
      if (move == 'd')
	{
	  initTableau(tabTerrain);
	  moveDroite(x,y,tabTerrain);
	  x++;
	}
      else if (move == 'q')
	{
	  initTableau(tabTerrain);
	  moveGauche(x,y,tabTerrain);
	  x--;
	}
      else if (move == 'z')
	{
	  initTableau(tabTerrain);
	  moveHaut(x,y,tabTerrain);
	  y--;
	}
      else if (move == 's')
	{
	  initTableau(tabTerrain);
	  moveBas(x,y,tabTerrain);
	  y++;
	  if (y>19)
	    {
	      y=y-19;
	    }
	}
      
      printTabPBM(tabTerrain);
      pid = fork();
      if (pid==0)
	{
	  execl(adresseExe,adresseAvion,NULL);
	  exit(1);
	}
      else{
	wait(NULL);
	tempmove=getchar();
	if (tempmove == 'z' || tempmove == 's' || tempmove == 'd' || tempmove == 'q' || tempmove == 'e')
	  {
	    move=tempmove;
	  }
      }
    }
  return (0);
}
