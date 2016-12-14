#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
	  if (y>21)
	    {
	      y=y-20;
	    }
	}
      
      printTabPBM(tabTerrain);
      pid = fork();
      if (pid==0)
	{
	  execl("Afficheur","EXIASAVER3_PBM/avion.pbm",NULL);
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
