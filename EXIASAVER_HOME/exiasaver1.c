#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[],char** envp[])
{
  int pid;
  char c;
  
  printf("l'argument 1 est: %s\n", argv[0]);
  
  pid = fork();
  if (pid == 0)
    {
      execl(strcat(getenv("EXIASAVER_HOME"),"/Afficheur"),argv[0],NULL);
    }
  else
    {
      c = getchar();
      system("clear");
    }
  
  return (0);
}
