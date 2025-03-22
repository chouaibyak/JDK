

#include "dijkstra.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// ****************************
// Definitions des types prives
// ****************************
// Type pour le tableau des couts qui donne le cout en carburant du plus court chemin du depart a l'une des cases du terrain
typedef int t_couts[NB_LIGNES][NB_COLONNES];

// Type pour le tableau 2D permettant de savoir si une case a deja ete visitee lors de l'algorithme de Dijkstra
typedef bool t_visites[NB_LIGNES][NB_COLONNES];

// Type pour coder la direction d'ou on vient pour atteindre l'une des cases du terrain en suivant le plus court chemin
typedef t_direction t_precedents[NB_LIGNES][NB_COLONNES];

// **********************************
// Declarations des fonctions privees
// **********************************
/**
 * @brief Initialise tous les couts avec le plus grand entier du type int.
 * Initialise egalement le cout de la case du joueur a 0.
 * @name initialiser_couts
 * @param couts le tableau bi-dimensionnel des couts a initialiser
 * @param joueur_ligne la ligne ou se trouve le joueur
 * @param joueur_colonne la colonne ou se trouve le joueur
 */
void initialiser_couts(t_couts couts, int joueur_ligne, int joueur_colonne);

/**
 * @brief Initialise toutes les cases a non visitee.
 * @name initialiser_visitees
 * @param visitees le tableau bi-dimensionnel qui indique, pour chaque case, si elle a deja ete visitee ou non.
 */
void initialiser_visitees(t_visites visitees);

/**
 * @brief Indique si une case donnee a deja ete visitee au cours de l'algorithme.
 * @name est_case_visitee
 * @param visitees le tableau a 2 dimensions qui indique, pour chaque case, si elle a deja ete visitee durant l'algorithme
 * @param case_ligne la ligne de la case a tester
 * @param case_colonne la colonne de la case a tester
 * @return true si la case a deja ete visitee, false sinon
 */
bool est_case_visitee(t_visites visitees, int case_ligne, int case_colonne);

/**
 * @brief Recherche la case non visitee qui possede le plus petit cout.
 * @name choisir_min_dist_non_visitee
 * @param couts le tableau des couts
 * @param visitees le tableau qui indique si une case a deja ete visitee ou pas
 * @param case_choisie_ligne l'adresse ou deposer la ligne de la case choisie
 * @param case_choisie_colonne l'adresse ou deposer la colonne de la case choisie
 */
void choisir_min_dist_non_visitee(t_couts couts, t_visites visitees, int *case_choisie_ligne, int *case_choisie_colonne);

/**
 * @brief Retourne le cout de deplacement pour aller d'une case a une case voisine.
 * @name cout_deplacement
 * @param terrain le terrain qui contient les stations de carburant
 * @param voisin_ligne la ligne de la case voisine vers laquelle on veut aller
 * @param voisin_colonne la colonne de la case voisine vers laquelle on veut aller
 * @return le cout du chemin pour se rendre a la case voisine specifiee en parametre
 * @note le cout pour aller d'une case a l'une de ses voisines est 1 + (9 - carburant dans la case voisine)
 */
int cout_deplacement(const t_terrain terrain, int voisin_ligne, int voisin_colonne);

/**
 * @brief Parcourt les voisins d'une case donnee et met a jour leur cout dans le tableau des couts.
 * @name maj_voisins
 * @param couts le tableau des couts
 * @param visitees le tableau qui indique, pour toute case, si elle a deja ete visitee
 * @param terrain le terrain qui contient les stations de carburant
 * @param precedents le tableau des precedents qui est mis a jour si l'un des chemins ameliore un chemin deja trouve auparavant
 * @param courante_ligne la ligne de la position courante a partir de laquelle on regarde les voisins
 * @param courante_colonne la colonne de la position courante a partir de laquelle on regarde les voisins
 */
void maj_voisins(t_couts couts, t_visites visitees, const t_terrain terrain, t_precedents precedents, int courante_ligne, int courante_colonne);

/**
 * @brief Affiche le tableau des couts
 * @name afficher_couts
 * @param couts le tableau des couts
 * @param visitees le tableau qui indique si une case a deja ete visitee ou pas durant l'algorithme
 * @param joueur_ligne la ligne ou se trouve le joueur
 * @param joueur_colonne la colonne ou se trouve le joueur
 * @param destination_ligne la ligne de la position a atteindre
 * @param destination_colonne la colonne de la position a atteindre
 */
void afficher_couts(t_couts couts, t_visites visitees, int joueur_ligne, int joueur_colonne, int destination_ligne, int destination_colonne);

/**
 * @brief Calcule les 4 premieres cases du plus court chemin en terme de carburant
 * @name calculer_chemin_bonus
 * @param precedents tableau de directions qui indique de quelle direction on vient pour atteindre une case du terrain en suivant le plus court chemin
 * @param depart_ligne la ligne de la case de depart
 * @param depart_colonne la colonne de la case de depart
 * @param destination_ligne la ligne de la case a atteindre
 * @param destination_colonne la colonne de la case a atteindre
 * @param directions les 4 premieres directions (au plus) a suivre sur le plus court chemin du depart a l'arrivee
 * @return le nombre de directions proposees par l'algorithme (normalement 4, mais peut etre plus petit)
 */
int calculer_chemin_bonus(t_precedents precedents, int depart_ligne, int depart_colonne, int destination_ligne, int destination_colonne, t_direction directions[NB_CASES_BONUS]);

/**
 * @brief Algorithme de Dijkstra pour calculer le plus court chemin en partent de la position du joueur pour atteindre
 * la position de destination.
 * @name dijkstra
 * @param terrain la terrain sur lequel le joueur evolue
 * @param joueur_ligne la ligne ou se trouve le joueur
 * @param joueur_colonne la colonne ou se trouve le joueur
 * @param destination_ligne la ligne de la case a atteindre
 * @param destination_colonne la colonne de la case a atteindre
 * @param directions les 4 premieres directions a suivre sur le plus court chemin
 * @return le nombre de directions proposees par l'algorithme (normalement 4, mais peut etre plus petit)
 */
int dijkstra(const t_terrain terrain, int joueur_ligne, int joueur_colonne, int destination_ligne, int destination_colonne, t_direction directions[NB_CASES_BONUS]);

/**
 * @brief Affiche les 4 premieres directions a suivre sur le plus court chemin pour joindre la destination a partir de la position du joueur
 * @name afficher_direction_suggeree
 * @param directions les premieres directions a suivre sur le plus court chemin
 * @param nb le nombre de directions a suivre
 */
void afficher_direction_suggeree(t_direction directions[NB_CASES_BONUS], int nb);

// ***********************************
// Definitions des fonctions publiques
// ***********************************
void dijkstra_acheter_bonus(const t_terrain terrain, int joueur_ligne, int joueur_colonne, int *joueur_carburant, int destination_ligne, int destination_colonne)
{
  if (*joueur_carburant < 10)
  {
    printf("Pas assez de carburant pour acheter le bonus.\n");
    return;
  }

  t_direction directions[NB_CASES_BONUS];
  int nb_directions = dijkstra(terrain, joueur_ligne, joueur_colonne, destination_ligne, destination_colonne, directions);

  if (nb_directions > 0)
  {
    *joueur_carburant -= 10;
    afficher_direction_suggeree(directions, nb_directions);
  }
  else
  {
    printf("Aucun chemin trouve vers la destination.\n");
  }
}

// *********************************
// Definitions des fonctions privees
// *********************************
void initialiser_couts(t_couts couts, int joueur_ligne, int joueur_colonne)
{
  for (int i = 0; i < NB_LIGNES; i++)
  {
    for (int j = 0; j < NB_COLONNES; j++)
    {
      couts[i][j] = INT_MAX;
    }
  }
  couts[joueur_ligne][joueur_colonne] = 0;
}

void initialiser_visitees(t_visites visitees)
{
  for (int i = 0; i < NB_LIGNES; i++)
  {
    for (int j = 0; j < NB_COLONNES; j++)
    {
      visitees[i][j] = false;
    }
  }
}

bool est_case_visitee(t_visites visitees, int case_ligne, int case_colonne)
{
  return visitees[case_ligne][case_colonne];
}

void choisir_min_dist_non_visitee(t_couts couts, t_visites visitees, int *case_choisie_ligne, int *case_choisie_colonne)
{
  int min_cout = INT_MAX;
  *case_choisie_ligne = -1;
  *case_choisie_colonne = -1;

  for (int i = 0; i < NB_LIGNES; i++)
  {
    for (int j = 0; j < NB_COLONNES; j++)
    {
      if (!visitees[i][j] && couts[i][j] < min_cout)
      {
        min_cout = couts[i][j];
        *case_choisie_ligne = i;
        *case_choisie_colonne = j;
      }
    }
  }
}

int cout_deplacement(const t_terrain terrain, int voisin_ligne, int voisin_colonne)
{
  return 1 + (9 - terrain[voisin_ligne][voisin_colonne]);
}

void maj_voisins(t_couts couts, t_visites visitees, const t_terrain terrain, t_precedents precedents, int courante_ligne, int courante_colonne)
{
  int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Haut, Bas, Gauche, Droite

  for (int i = 0; i < 4; i++)
  {
    int voisin_ligne = courante_ligne + directions[i][0];
    int voisin_colonne = courante_colonne + directions[i][1];

    if (voisin_ligne >= 0 && voisin_ligne < NB_LIGNES && voisin_colonne >= 0 && voisin_colonne < NB_COLONNES)
    {
      if (!est_case_visitee(visitees, voisin_ligne, voisin_colonne))
      {
        int nouveau_cout = couts[courante_ligne][courante_colonne] + cout_deplacement(terrain, voisin_ligne, voisin_colonne);

        if (nouveau_cout < couts[voisin_ligne][voisin_colonne])
        {
          couts[voisin_ligne][voisin_colonne] = nouveau_cout;
          precedents[voisin_ligne][voisin_colonne] = i;
        }
      }
    }
  }
}

void afficher_couts(t_couts couts, t_visites visitees, int joueur_ligne, int joueur_colonne, int destination_ligne, int destination_colonne)
{
  printf("Tableau des couts :\n");
  for (int i = 0; i < NB_LIGNES; i++)
  {
    for (int j = 0; j < NB_COLONNES; j++)
    {
      if (i == joueur_ligne && j == joueur_colonne)
      {
        printf("J ");
      }
      else if (i == destination_ligne && j == destination_colonne)
      {
        printf("D ");
      }
      else if (visitees[i][j])
      {
        printf("%d ", couts[i][j]);
      }
      else
      {
        printf("X ");
      }
    }
    printf("\n");
  }
}

int calculer_chemin_bonus(t_precedents precedents, int depart_ligne, int depart_colonne, int destination_ligne, int destination_colonne, t_direction directions[NB_CASES_BONUS])
{
  int nb_directions = 0;
  int ligne = destination_ligne;
  int colonne = destination_colonne;

  while ((ligne != depart_ligne || colonne != depart_colonne) && nb_directions < NB_CASES_BONUS)
  {
    t_direction dir = precedents[ligne][colonne];
    directions[nb_directions] = dir;
    nb_directions++;

    // Mettre à jour la position actuelle en fonction de la direction
    switch (dir)
    {
    case DIRECTION_HAUT:
      ligne++;
      break;
    case DIRECTION_BAS:
      ligne--;
      break;
    case DIRECTION_GAUCHE:
      colonne++;
      break;
    case DIRECTION_DROITE:
      colonne--;
      break;
    }
  }

  // Inverser les directions pour les avoir dans l'ordre du départ à l'arrivée
  for (int i = 0; i < nb_directions / 2; i++)
  {
    t_direction temp = directions[i];
    directions[i] = directions[nb_directions - 1 - i];
    directions[nb_directions - 1 - i] = temp;
  }

  return nb_directions;
}

int dijkstra(const t_terrain terrain, int joueur_ligne, int joueur_colonne, int destination_ligne, int destination_colonne, t_direction directions[NB_CASES_BONUS])
{
  t_couts couts;
  t_visites visitees;
  t_precedents precedents;

  initialiser_couts(couts, joueur_ligne, joueur_colonne);
  initialiser_visitees(visitees);

  while (true)
  {
    int case_choisie_ligne, case_choisie_colonne;
    choisir_min_dist_non_visitee(couts, visitees, &case_choisie_ligne, &case_choisie_colonne);

    if (case_choisie_ligne == -1 || case_choisie_colonne == -1)
    {
      break; // Toutes les cases ont été visitées ou aucun chemin n'est possible
    }

    if (case_choisie_ligne == destination_ligne && case_choisie_colonne == destination_colonne)
    {
      break; // Destination atteinte
    }

    visitees[case_choisie_ligne][case_choisie_colonne] = true;
    maj_voisins(couts, visitees, terrain, precedents, case_choisie_ligne, case_choisie_colonne);
  }

  return calculer_chemin_bonus(precedents, joueur_ligne, joueur_colonne, destination_ligne, destination_colonne, directions);
}

void afficher_direction_suggeree(t_direction directions[NB_CASES_BONUS], int nb)
{
  printf("Directions suggerees : ");
  for (int i = 0; i < nb; i++)
  {
    switch (directions[i])
    {
    case DIRECTION_HAUT:
      printf("Haut ");
      break;
    case DIRECTION_BAS:
      printf("Bas ");
      break;
    case DIRECTION_GAUCHE:
      printf("Gauche ");
      break;
    case DIRECTION_DROITE:
      printf("Droite ");
      break;
    }
  }
  printf("\n");
}