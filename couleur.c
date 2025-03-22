
#include "couleur.h"

#include <stdio.h>

#define ESCAPE "\033["

void couleur_set(int style, int couleur_avant_plan, int couleur_arriere_plan)
{
    printf("%s%d;%d;%dm", ESCAPE, style, couleur_avant_plan, couleur_arriere_plan);
}

void couleur_reset(void)
{
    printf("%s0m", ESCAPE);
}
