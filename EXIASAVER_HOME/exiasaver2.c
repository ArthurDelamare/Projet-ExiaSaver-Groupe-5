#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "BibliExiaSaver2.h"

int main(int argc, char* argv[], char** envp)
{
  printf("Je suis le programme 2\n");
  printf("la taille des lettres est: %s\n", getenv("EXIASAVER2_TAILLE"));
  heurePBM();
  execl("Afficheur","EXIASAVER2_PBM/combinaison.pbm",NULL);
  return (0);
}
