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

	//Effacer l'ecran
	system("clear");

        //Ouverture du fichier pbm
	fichier = fopen(argv[0], "r");

	//Si on ouvre le fichier
	if (fichier != NULL)
	{
	//Lecture des premieres lignes
	fgets(ligne, 255, fichier);
	fgets(ligne, 255, fichier);
	fgets(ligne, 255, fichier);
	strcpy(containerForRow, strtok(ligne,s));
	strcpy(containerForCol, strtok(NULL, s));

	//Centrage de l'image en fonction des lignes
	for(n=0; n<(row-atoi(containerForRow))/2; n++)
	{
	printf("\n");
	}

		//Lecture des 0 et des 1 et suppression des espaces
		while(fgets(ligne, 255, fichier) != NULL)
		{
		token = strtok(ligne, s);

		//Centrage de l'image en fonction des colonnes
		for(n=0; n<(col-atoi(containerForCol))/2; n++)
		{
		putchar(' ');
		}

			//Tant qu'il y a des 0 et 1 on continu
			while( token != NULL)
			{
				//Remplacement des 0 par des espaces
				if(strcmp(token,"0") == 0)
				{
				printf(" ");
				}
				//Remplacement des 1 par des carres
				else if(strcmp(token,"1") == 0)
				{
				printf("\u2588");
				}
				//Retour à la ligne
				else
				{
				printf("\n");
				}
			token = strtok(NULL, s);
			}
		}
		//Centrage de l'image en fonction des lignes
        for(n=0; n<(row-atoi(containerForRow))/2; n++)
        {
        printf("\n");
        }
    //Fermeture du fichier pbm
	fclose(fichier);
	}
return 0;
}
