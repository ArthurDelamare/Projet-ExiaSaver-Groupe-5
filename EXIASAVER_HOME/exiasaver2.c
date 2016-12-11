#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char** envp)
{
  printf("Je suis le programme 2\n");
  printf("la taille des lettres est: %s\n", getenv("EXIASAVER2_TAILLE"));


  return (0);
}
