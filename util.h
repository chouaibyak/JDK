#ifndef UTIL_H
#define UTIL_H

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))

int util_generer_nombre_aleatoire(int min, int max);
int util_symetrique(int min, int max, int n);

#endif // UTIL_H