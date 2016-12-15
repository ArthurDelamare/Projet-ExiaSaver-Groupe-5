#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  if (y+2<19)
    {
      tab[y+2][x]=1;  
    }
  else if (y+2>19)
    {
      tab[y+2-19][x]=1;
    }
  if (y+1<19)
    {
      tab[y+1][x]=1;
      tab[y+1][x+1]=1;
      tab[y+1][x-1]=1;
    }
  else if (y+1>19)
    {
      tab[y+1-19][x]=1;
      tab[y+1-19][x+1]=1;
      tab[y+1-19][x-1]=1;
    }
  if (y<19)
    {
      tab[y][x]=1;
      tab[y][x-2]=1;
      tab[y][x+2]=1;
    }
  else if (y>19)
    {
      tab[y-19][x]=1;
      tab[y-19][x-2]=1;
    }
  if (y-1>0)
    {
      tab[y-1][x]=1;
    }
  if (y-2>0)
    {
      tab[y-2][x]=1;
    }
  
  //Queue de l'avion
  if (y-3>0)
    {
      tab[y-3][x+1]=1;
      tab[y-3][x]=1;
    }
}

void printTabPBM(int tab[23][60])
{
  FILE* avion;
  int i,j;
  //Variable tampon permettant de définir le chemin d'accès à l'image PBM
  char adresseAvion[75];
  strcpy(adresseAvion,getenv("EXIASAVER3_PBM"));
  strcpy(adresseAvion,strcat(adresseAvion,"/avion.pbm"));
 
  avion = fopen(adresseAvion,"w");
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
