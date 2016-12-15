#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
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
  int position = 0;

  //Afficher aléatoirement le sens de l'avion 
  srand(time(NULL));
  position = (rand() % 4) + 1;

  if(position == 1)
  {
  	move ='d';
  }
  if(position == 2)
  {
  	move = 'q';
  }
  if(position == 3)
  {
  	move = 's';
  }
  if(position == 4)
  {
  	move = 'z';
  }


  //Variable tampon pour récupérer des variables d'environnements et former des chemins utilisés par l'exécutable
  char adresseExe[75];
  char adresseAvion [75];
  //Récupération de la variable d'environnement et concaténation
  strcpy(adresseExe,getenv("EXIASAVER_HOME"));
  strcpy(adresseExe,strcat(adresseExe,"/Afficheur"));
  strcpy(adresseAvion,getenv("EXIASAVER3_PBM"));
  strcpy(adresseAvion,strcat(adresseAvion,"/avion.pbm"));

  //Tant que l'utilisateur n'appuie pas sur la touche e,le programme continue
  while(move != 'e')
    {
      //Si l'utilisateur appuie sur la touche d, l'avion va à droite
      if (move == 'd')
	{
	  initTableau(tabTerrain);
	  moveDroite(x,y,tabTerrain);
	  x++;

    if (x>59)
    {
      x=x-59;
    }
	}
      //Si l'utilisateur appuie sur la touche q, l'avion va à gauche
      else if (move == 'q')
	{
	  initTableau(tabTerrain);
	  moveGauche(x,y,tabTerrain);
	  x--;

    if (x<0)
    {
      x=x+59;
    }
	}
      //Si l'utilisateur appuie sur la touche z, l'avion va en haut
      else if (move == 'z')
	{
	  initTableau(tabTerrain);
	  moveHaut(x,y,tabTerrain);
	  y--;

    if (y<0)
    {
      y=y+19;
    }
	}
      //Si l'utilisateur appuie sur la touche s, l'avion va en bas
      else if (move == 's')
	{
	  initTableau(tabTerrain);
	  moveBas(x,y,tabTerrain);
	  y++;
          //Si l'avion touche le bas du tableau, il apparait en haut
	  if (y>19)
	    {
	      y=y-19;
	    }
	}

      printTabPBM(tabTerrain);
      //Création du processus Fils
      pid = fork();
      if (pid==0)
	{
	  //Exécutionde l'afficheur
	  execl(adresseExe,adresseAvion,NULL);
	  exit(1);
	}
      else{
	//Sinon on attend
	wait(NULL);
	tempmove=getchar();
	//Si la variable tempmove est égale à z, s, d, q ou e alors la lettre enregistrée est égale au déplacement
	if (tempmove == 'z' || tempmove == 's' || tempmove == 'd' || tempmove == 'q' || tempmove == 'e')
	  {
	    move=tempmove;
	  }
      }
    }
  return (0);
}
