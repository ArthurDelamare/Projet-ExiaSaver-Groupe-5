#include <stdio.h>
#include <stdlib.h>
#include "BibliES3.h"

int main(int argc, char* argv[], char** envp)
{
  //variables qui détermine la position du point central de l'avion
  int x=40;
  int y=11;
  //tableau à deux dimensions définissant le terrain dans lequel l'avion se déplace
  int tabTerrain[23][80] = {0};

  int i,j;
  
  initTableau(tabTerrain);
  moveDroite(x,y,tabTerrain);
  
  // printf("Je suis le programme 3\n");
  // printf("la position iniatiale de l'avion est: %s\n", argv[0]);

  for(j=0;j<23;j++)
    {
      for(i=0;i<80;i++)
	{
	  printf("%d",tabTerrain[j][i]);
	}
    }

  return (0);
}
