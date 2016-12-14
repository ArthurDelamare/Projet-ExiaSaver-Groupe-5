#include <stdio.h>
#include <stdlib.h>

void initTableau(int tab[][60])
{
  int i,j;
  for (j=0;j<23;j++)
    {
      for (i=0;i<60;i++)
	{
	  tab[j][i]=0;
	}
    }
}

void moveDroite(int x,int y,int tab[23][60])
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

void moveGauche(int x, int y,int tab[23][60])
{
  //Rangée centrale de l'avion
  tab[y][x]=1;
  tab[y][x+1]=1;
  tab[y][x+2]=1;
  tab[y][x+3]=1;
  tab[y][x-1]=1;
  tab[y][x-2]=1;

  //Queue de l'avion
  tab[y-1][x+3]=1;

  //Ailes de l'avion
  tab[y-1][x-1]=1;
  tab[y-2][x]=1;
  tab[y+1][x-1]=1;
  tab[y+2][x]=1;

}

void moveHaut(int x, int y,int tab[23][60])
{
 
 //Rangée centrale de l'avion
  tab[y][x]=1;
  tab[y-1][x]=1;
  tab[y-2][x]=1;
  tab[y+1][x]=1;
  tab[y+2][x]=1;
  tab[y+3][x]=1;

  //Queue de l'avion
  tab[y+3][x-1]=1;

  //Ailes de l'avion
  tab[y-1][x-1]=1;
  tab[y][x-2]=1;
  tab[y-1][x+1]=1;
  tab[y][x+2]=1;
  
}

void moveBas(int x, int y,int tab[23][60])
{
 
 //Rangée centrale de l'avion
  tab[y][x]=1;
  tab[y+1][x]=1;
  tab[y+2][x]=1;
  tab[y-1][x]=1;
  tab[y-2][x]=1;
  tab[y-3][x]=1;

  //Queue de l'avion
  tab[y-3][x+1]=1;

  //Ailes de l'avion
  tab[y+1][x+1]=1;
  tab[y][x-2]=1;
  tab[y+1][x-1]=1;
  tab[y][x+2]=1;
  
}

void printTabPBM(int tab[23][60])
{
  FILE* avion;
  int i,j;
  
  avion = fopen("EXIASAVER3_PBM/avion.pbm","w");
  fprintf(avion,"P1\n#Image PBM d'un avion utilisé dans l'écran de veille statique\n23 60\n");

  for(j=0;j<23;j++)
    {
      for (i=0;i<60;i++)
	{
	  fprintf(avion,"%d ",tab[j][i]);
	}
      fprintf(avion,"\n");
    }
  

 fclose(avion);
}
