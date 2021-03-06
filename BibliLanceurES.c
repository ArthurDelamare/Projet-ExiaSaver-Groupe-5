#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void choixFichier(int n,char* chemin)
{
  //utilisation de la structure relative au répertoire
  DIR* repPBM;
  struct dirent* fichierLu;
  int i = 0;
  char containerFileName[256];

  //ouverture du répertoire d'image PBM de l'écran statique
  repPBM = opendir(getenv("EXIASAVER1_PBM"));
  if (repPBM == NULL)
    {
      perror("");
    }

  //on lit le repertoire jusqu'au fichier voulu (déterminé aléatoirement préalablement)
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

  //copie d'une partie du chemin dans la variable "chemin"
  strcat(chemin,"/");
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

  //Variable permettant de stocker le chemi d'accès du fichier historique
  char adresseHisto[75];
  strcpy(adresseHisto,getenv("EXIASAVER_HOME"));
  strcat(adresseHisto,"/historique.txt");
  
  //place le nombre de secondes écoulées depuis 1970 dans la variable secondes
  time(&secondes);
  //initialise la structure temps à l'aide de la variable secondes
  temps = *localtime(&secondes);

  //écriture du fichier historique
  FILE* fichier;
  fichier = fopen(adresseHisto,"a");
  if (typeTimeSaver == 1)
    {
      //séparation du nom du fichier du chemin complet
      strcpy(stockageNom,nomFichierPBM1);
      strcat(stockageNom,"/");
      strcpy(stockageNom,strtok(stockageNom,sep));
      strcpy(stockageNom,strtok(NULL,sep));
      strcpy(stockageNom,strtok(NULL,sep));
      strcpy(stockageNom,strtok(NULL,sep));
      strcpy(stockageNom,strtok(NULL,sep));
      strcpy(stockageNom,strtok(NULL,sep));

      //écriture dans l'historique
      fprintf(fichier,"%d/%d/%d %d:%d:%d;%d;%s\n",temps.tm_mday,temps.tm_mon+1,temps.tm_year+1900,temps.tm_hour,temps.tm_min,temps.tm_sec,typeTimeSaver,stockageNom);
    }
  else if (typeTimeSaver == 2)
    {
      //écriture dans l'historique
      fprintf(fichier,"%d/%d/%d %d:%d:%d;%d;%s\n",temps.tm_mday,temps.tm_mon+1,temps.tm_year+1900,temps.tm_hour,temps.tm_min,temps.tm_sec,typeTimeSaver,getenv("EXIASAVER2_TAILLE"));
    }
  else if (typeTimeSaver == 3)
    {
      //écriture dans l'historique
      fprintf(fichier,"%d/%d/%d %d:%d:%d;%d;%s\n",temps.tm_mday,temps.tm_mon+1,temps.tm_year+1900,temps.tm_hour,temps.tm_min,temps.tm_sec,typeTimeSaver,posAvion);
    }
  
  fclose(fichier);
}


void choixVarEnv()
{
  
  char newVarEnv[75];
  int choixVarEnv = 1;

  //Boucle permettant de saisir temporairement une variable d'environnement
  while(choixVarEnv != 0)
  {
  printf("Quel variable d'environnement souhaitez vous changer?\n1: EXIASAVER_HOME\n2: EXIASAVER1_PBM\n3: EXIASAVER2_PBM\n4: EXIASAVER2_TAILLE\n5: EXIASAVER2_SLEEP\n6: EXIASAVER3_PBM\n0: quitter ce menu et lancer le programme\n");
  scanf("%d",&choixVarEnv);
  switch (choixVarEnv)
    {
    case 1:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER_HOME",newVarEnv,1);
      break;
    case 2:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER1_PBM",newVarEnv,1);
      break;
    case 3:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER2_PBM",newVarEnv,1);
      break;
    case 4:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER2_TAILLE",newVarEnv,1);
      break;
    case 5:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER2_SLEEP",newVarEnv,1);
      break;
    case 6:
      printf("Veillez saisir la nouvelle valeur de la variable:\n");
      scanf("%s",newVarEnv);
      setenv("EXIASAVER3_PBM",newVarEnv,1);
      break;
    default:
      printf("erreur dans la saisie, veuillez réessayer avec une valeur correcte\n");
    }
  system("clear");
  }
   
}

void triBulle(int tab[], int tailleTab)
{
  int i,j, valIntermediaire;

  for (i = tailleTab-1; i>0; i--)
    {
      for (j=1; j<=i;j++)
	{
	  if (tab[j-1]>tab[j])
	    {
	      valIntermediaire = tab[j-1];
	      tab[j-1] = tab[j];
	      tab[j] = valIntermediaire;
	    }
	}
    }
}

void statsFreqMois()
{
  //Tableau destiné à stocker la valeur calendaire des mois
  int tableauLancementMois[200] = {0};
  //Tableau destiné à stocker le nombre de lancement
  int tableauAdditionMois[12] = {0};
  //variable pour la manipulation du fichier historique.txt
  FILE* historique;
  //variable permettant de stocker une ligne de l'historique
  char conteneur[100];
  //variable utilisé comme compteur
  int i=0;
  //variable servant de séparation pour strtok()
  char sep[2]="/";
  //variable contenant le chemin d'accès du fichier historique
  char adresseHisto[75];
  strcpy(adresseHisto,getenv("EXIASAVER_HOME"));
  strcat(adresseHisto,"/historique.txt");
  
  historique = fopen(adresseHisto,"r");

  //On passe les quatre lignes de commentaires qui ne doivent pas être analyser
  for(i=0;i<4;i++)
    {
      fgets(conteneur,100,historique);
    }

  //Obtention du mois dans chaque ligne d'historique, puis placement dans un tableau
  while((fgets(conteneur,100,historique)) != NULL)
    {
      strcpy(conteneur,strtok(conteneur,sep));
      strcpy(conteneur,strtok(NULL,sep));
      tableauLancementMois[i]=atoi(conteneur);
      i++;
    }

  //Tri du tableau
  triBulle(tableauLancementMois,200);

  //à chaque analyse d'un mois, incrémentation d'une valeur dans le tableau correspondant au mois analyser
  for(i=0;i<200;i++)
    {
      if (tableauLancementMois[i] != 0)
	{
	  tableauAdditionMois[tableauLancementMois[i]-1]++;
	}
    }

  //Affichage des statistiques
  printf("Voici les nombres de lancements par mois:\nJanvier: %d\nFévrier: %d\nMars: %d\nAvril: %d\nMai: %d\nJuin: %d\nJuillet: %d\nAout: %d\nSeptembre: %d\nOctobre: %d\nNovembre: %d\nDecembre: %d\n",tableauAdditionMois[0],tableauAdditionMois[1],tableauAdditionMois[2],tableauAdditionMois[3],tableauAdditionMois[4],tableauAdditionMois[5],tableauAdditionMois[6],tableauAdditionMois[7],tableauAdditionMois[8],tableauAdditionMois[9],tableauAdditionMois[10],tableauAdditionMois[11]);
  fclose(historique);
}

void statsTypeTS()
{
  //Tableau destiné à stocker les données brutes sur les termSavers utilisés
  int tableauTypeTS[200] = {0};
  //variable pour la manipulation du fichier historique.txt
  FILE* historique;
  //variable utilisé comme compteur
  int i=0;
  //variable stockant l'addition des différents types d'écrans utilisés
  float type1 = 0;
  float type2 = 0;
  float type3 = 0;
  float totalType = 0;
  //Variable permettant de stocker une ligne de l'historique
  char container[100];
  //caractère de séparation pour l'utilisation de strtok()
  char sep[2]=";";
  //chaine de caractère utilisé pour afficher le caractère "%"
  char pourcent[2]="%";
  //Variable contenant le chemin d'accès du fichier historique
  char adresseHisto[75];
  strcpy(adresseHisto,getenv("EXIASAVER_HOME"));
  strcat(adresseHisto,"/historique.txt");
  
  historique = fopen(adresseHisto,"r");

  //On passe les quatres premiers lignes qui sont des commentaires
  for (i=0;i<4;i++)
    {
      fgets(container,100,historique);
    }

  //Récupération du type d'écran de veille utilisé depuis l'historique puis on place cette donnée dans un tableau
  while((fgets(container,100,historique)) != NULL)
    {
      strcpy(container,strtok(container,sep));
      strcpy(container,strtok(NULL,sep));
      tableauTypeTS[i] = atoi(container);
      i++;
    }
  fclose(historique);

  //Tri du tableau
  triBulle(tableauTypeTS,200);

  //incrémentation afin de compter les différents types d'écrans de veille
  for(i=0;i<200;i++)
    {
      if (tableauTypeTS[i] == 1)
	{
	  type1++;
	}
      if (tableauTypeTS[i] == 2)
	{
	  type2++;
	}
      if (tableauTypeTS[i] == 3)
	{
	  type3++;
	}
    }
  totalType = type1+type2+type3;

  printf("Il y a eu %.0f lancements, dont %.2f%s d'écrans statiques, %.2f%s d'écrans dynamiques et %.2f%s d'écrans intéractifs\n", totalType,type1*100/totalType,pourcent,type2*100/totalType,pourcent,type3*100/totalType,pourcent);
  
}

void statsImgStatique()
{
  //Tableau destiné à contenir les nom des images repertoriées dans l'historique
  char tableauImgHisto[200][15];
  //variable permettant de manipuler le fichier historique
  FILE* historique;
  //variable permettant de récupérer et manipuler les lignes de l'historique
  char conteneur[100];
  //variable servant de compteur
  int i;
  //variable utilisé comme séparateur pour strtok()
  char sep[2]=";";
  //variables pour compter l'utilisation des  images
  float pomme = 0;
  float mario = 0;
  float dinosaure = 0;
  float smiley = 0;
  float tasse = 0;
  float totalImg = 0;
  
  char pourcent[2]="%";

  //Variable contenant le chemin d'accès du fichier historique
  char adresseHisto[75];
  strcpy(adresseHisto,getenv("EXIASAVER_HOME"));
  strcat(adresseHisto,"/historique.txt");
 
  historique = fopen(adresseHisto,"r");

  //on sépare les 4 lignes de commentaires qui ne sont pas à analyser
  for(i=0;i<4;i++)
    {
      fgets(conteneur,100,historique);
    }

  //Tant qu'on a pas lu toutes les lignes de l'historique
  while((fgets(conteneur,100,historique)) != NULL)
    {
      //Séparation des données de l'historique et récupération des noms de fichiers lorsqu'il s'agit d'un lancement d'écran statique
      strcpy(conteneur,strtok(conteneur,sep));
      strcpy(conteneur,strtok(NULL,sep));
      if (strcmp(conteneur,"1") ==0)
	{
	  strcpy(conteneur,strtok(NULL,sep));
	  //incrémentation d'une variable précise lorsqu'on détecte le nom d'un des fichiers
	  if (strcmp(conteneur,"pomme.pbm\n") == 0)
	    {
	      pomme++;
	    }
	  else if (strcmp(conteneur,"dinosaure.pbm\n") == 0)
	    {
	      dinosaure++;
	    }
	  else if (strcmp(conteneur,"mario.pbm\n") == 0)
	    {
	      mario++;
	    }
	  else if (strcmp(conteneur,"smiley.pbm\n") == 0)
	    {
	      smiley++;
	    }
	  else if (strcmp(conteneur,"tasse.pbm\n") == 0)
	    {
	      tasse++;
	    }
	}
    }

  //Affichage des résultats
  totalImg = pomme + dinosaure + mario + smiley + tasse;
  printf("Il y a eu un total de %.0f lancements, pour %.2f%s de pomme.pbm, %.2f%s de dinosaure.pbm, %.2f%s de mario.pbm, %.2f%s de smiley.pbm et %.2f%s de tasse.pbm\n",totalImg,pomme*100/totalImg,pourcent,dinosaure*100/totalImg,pourcent,mario*100/totalImg,pourcent,smiley*100/totalImg,pourcent,tasse*100/totalImg,pourcent); 
}

void statistique()
{
  //choix d'une statistique par l'utilisateur
  int choixStats;
  printf("Bienvenue dans la partie statistique (effectué sur un échantillon de 200 lancements maximum)\nQuelle est la statistique qui vous intéresse ?\n1: la moyenne de lancement par mois\n2: le pourcentage de lancement selon les types de termSaver\n3: le pourcentage d'utilisation des différentes images en screenSaver statique\n");
  scanf("%d",&choixStats);
  //Selon le choix de l'utilisateur, lancement d'une des fonctions
  if (choixStats == 1)
    {
      statsFreqMois();
    }
  
  else if (choixStats == 2)
    {
      statsTypeTS();
    }
  else if (choixStats == 3)
    {
      statsImgStatique();
    }
}

