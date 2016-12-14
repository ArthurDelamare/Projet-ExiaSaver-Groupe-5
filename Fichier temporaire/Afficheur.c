#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char *argv[])

{

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int col = w.ws_col;
	int row = w.ws_row;
	FILE* fichier = NULL;
	char ligne[255];
	const char s[2] = " ";
	char *token;
	unsigned int n;
	char containerForRow[10];
	char containerForCol[10];
	printf("\033c");  //Clear l'ecran

	fichier = fopen(argv[0], "r"); //Ouvrir le fichier pbm

	if (fichier != NULL) //Si on ouvre le fichier
	{
	fgets(ligne, 255, fichier);
	fgets(ligne, 255, fichier); //On va lire les premieres lignes
	fgets(ligne, 255, fichier);
	strcpy(containerForRow,strtok(ligne,s));
	strcpy(containerForCol,strtok(NULL,s));

	for(n=0; n<(row-atoi(containerForRow))/2; n++)
	{
	printf("\n");
	}
		while(fgets(ligne, 255, fichier) != NULL) //On va lire les 0 et 1
		{
		token = strtok(ligne, s);
		for(n=0; n<(col-atoi(containerForCol))/2; n++)
		{
		putchar(' ');
		}
			while( token != NULL) //Tant qu'il y a des 0 et 1 on continu
			{
				if(strcmp(token,"0") == 0) //On remplace les 0 par des espaces
				{
				printf(" ");
				}
				else if(strcmp(token,"1") == 0) //On remplace les 1 par des carres
				{
				printf("\u2588");
				}
				else
				{
				printf("\n");
				}
			token = strtok(NULL, s);
			}
		}
		for(n=0; n<(row-atoi(containerForRow))/2; n++)
        {
        printf("\n");
        }
	fclose(fichier);
	}	
return 0;
}
