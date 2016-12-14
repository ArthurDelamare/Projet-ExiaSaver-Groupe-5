#include <stdio.h>
#include <stdlib.h>

void initTableau(int tab[][80])
{
  int i,j;
  for (j=0;j<23;j++)
    {
      for (i=0;i<80;i++)
	{
	  tab[j][i]=0;
	}
    }
}

void moveDroite(int x,int y,int tab[][80])
{
  //Rangée centrale de l'avion
  tab[y][x]=1;
  tab[y][x+1]=1;
  tab[y][x+2]=1;
  tab[y][x-1]=1;
  tab[y][x-2]=1;
  tab[y][x-3]=1;

  //Queue de l'avion
  tab[y-1][x-3]=1;

  //Ailes de l'avion
  tab[y-1][x+1]=1;
  tab[y-2][x]=1;
  tab[y+1][x+1]=1;
  tab[y+2][x]=1;
  
}
