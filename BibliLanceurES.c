#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void choixFichier(int n,char* chemin)
{
  DIR* repPBM;
  struct dirent* fichierLu;
  int i = 0;
  char containerFileName[256];
  
  repPBM = opendir(getenv("EXIASAVER1_PBM"));
  if (repPBM == NULL)
    {
      perror("");
    }

  while(i != n)
    {
      fichierLu = readdir(repPBM);
      if (strcmp(fichierLu->d_name,".")!=0 && strcmp(fichierLu->d_name,"..")!=0)
	{
	  strcpy(containerFileName,fichierLu->d_name);
	  i++;
	}
    }

  closedir(repPBM);
  
  strcat(chemin,"EXIASAVER1_PBM/");
  strcat(chemin,containerFileName);
}


void historique(int typeTimeSaver, char* nomFichierPBM1, char* posAvion)
{
  
  //déclaration structure et variable pour récupérer la date et l'heure
  struct tm temps;
  time_t secondes;
  //variable servant de séparation dans l'utilisation de strtok()
  char sep[2]="/";
  char stockageNom[50];

    
  //place le nombre de secondes écoulées depuis 1970 dans la variable secondes
  time(&secondes);
  //initialise la structure temps à l'aide de la variable secondes
  temps = *localtime(&secondes);

  //écriture du fichier historique
  FILE* fichier;
  fichier = fopen("historique.txt","a");
  if (typeTimeSaver == 1)
    {
      //séparation du nom du fichier du chemin complet
      strcpy(stockageNom,nomFichierPBM1);
      strcat(stockageNom,"/");
      strcpy(stockageNom,strtok(stockageNom,sep));
      strcpy(stockageNom,strtok(NULL,sep));
      
      fprintf(fichier,"%d/%d/%d %d:%d:%d;%d;%s\n",temps.tm_mday,temps.tm_mon+1,temps.tm_year+1900,temps.tm_hour,temps.tm_min,temps.tm_sec,typeTimeSaver,stockageNom);
    }
  else if (typeTimeSaver == 2)
    {
      fprintf(fichier,"%d/%d/%d %d:%d:%d;%d;%s\n",temps.tm_mday,temps.tm_mon+1,temps.tm_year+1900,temps.tm_hour,temps.tm_min,temps.tm_sec,typeTimeSaver,getenv("EXIASAVER2_TAILLE"));
    }
  else if (typeTimeSaver == 3)
    {
      fprintf(fichier,"%d/%d/%d %d:%d:%d;%d;%s\n",temps.tm_mday,temps.tm_mon+1,temps.tm_year+1900,temps.tm_hour,temps.tm_min,temps.tm_sec,typeTimeSaver,posAvion);
    }
  
  fclose(fichier);
}
