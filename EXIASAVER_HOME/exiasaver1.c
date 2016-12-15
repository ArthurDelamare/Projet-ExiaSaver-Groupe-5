#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[],char** envp[])
{
  //Initialisation des variables
  int pid;
  char c;

  //Création du processus Fils
  pid = fork();
  if (pid == 0)
    {
      //On combine la variable d'environement "EXIASAVER_HOME" avec "/Afficheur" pour exécuter
      execl(strcat(getenv("EXIASAVER_HOME"),"/Afficheur"),argv[0],NULL);
    }
  else
    {
      //Pause tant qu'une touche n'est pas entrée
      c = getchar();
      system("clear");
    }

  return (0);
}
