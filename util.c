#include "util.h"
#include <stdlib.h>

int util_generer_nombre_aleatoire(int min, int max)
{
  return min + rand() % (max - min + 1);
}

int util_symetrique(int min, int max, int n)
{
  return max - (n - min);
}