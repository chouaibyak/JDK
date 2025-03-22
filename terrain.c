#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "terrain.h"
#include "util.h" // Pour utiliser util_generer_nombre_aleatoire

// ***********************************
// Definitions des fonctions publiques
// ***********************************

/**
 * @brief Propose une position de sortie aléatoire pour un terrain de dimensions NB_LIGNES x NB_COLONNES
 * @param sortie_ligne l'adresse où déposer une ligne de sortie aléatoire
 * @param sortie_colonne l'adresse où déposer une colonne de sortie aléatoire
 */
void terrain_generer_position_sortie(int *sortie_ligne, int *sortie_colonne)
{
  *sortie_ligne = util_generer_nombre_aleatoire(0, NB_LIGNES - 1);
  *sortie_colonne = util_generer_nombre_aleatoire(0, NB_COLONNES - 1);
}

/**
 * @brief Propose une position de départ aléatoire pour un terrain de dimensions NB_LIGNES x NB_COLONNES
 * @param destination_ligne la ligne de la sortie actuelle
 * @param destination_colonne la colonne de la sortie actuelle
 * @param depart_ligne l'adresse où déposer la ligne choisie aléatoirement
 * @param depart_colonne l'adresse où déposer la colonne choisie aléatoirement
 * @note La distance Manhattan entre la position de départ et la position de sortie doit être plus grande que 10.
 */
void terrain_generer_position_depart(int destination_ligne, int destination_colonne, int *depart_ligne, int *depart_colonne)
{
  int distance;
  do
  {
    *depart_ligne = util_generer_nombre_aleatoire(0, NB_LIGNES - 1);
    *depart_colonne = util_generer_nombre_aleatoire(0, NB_COLONNES - 1);
    distance = abs(*depart_ligne - destination_ligne) + abs(*depart_colonne - destination_colonne);
  } while (distance <= 10);
}

/**
 * @brief Vérifie qu'une position se trouve bien dans les limites du terrain de NB_LIGNES x NB_COLONNES
 * @param position_ligne la ligne de la case à tester
 * @param position_colonne la colonne de la case à tester
 * @return true si la position se trouve à l'intérieur du terrain, false sinon
 */
bool terrain_contient(int position_ligne, int position_colonne)
{
  return (position_ligne >= 0 && position_ligne < NB_LIGNES &&
          position_colonne >= 0 && position_colonne < NB_COLONNES);
}

/**
 * @brief Retourne la quantité de carburant qui se trouve sur une case donnée du terrain
 * @param terrain le terrain
 * @param position_ligne la ligne de la case dont on veut connaître la quantité de carburant
 * @param position_colonne la colonne de la case dont on veut connaître la quantité de carburant
 * @return la quantité de carburant présente à cette position
 */
int terrain_get_carburant(t_terrain terrain, int position_ligne, int position_colonne)
{
  if (terrain_contient(position_ligne, position_colonne))
  {
    return terrain[position_ligne][position_colonne];
  }
  return -1; // Retourne -1 si la position est invalide
}

/**
 * @brief Initialise la quantité de carburant sur une case du terrain
 * @param terrain le terrain dont on va modifier une case
 * @param position_ligne la ligne de la case à modifier
 * @param position_colonne la colonne de la case à modifier
 * @param carburant le carburant qui se trouvera dans la case
 */
void terrain_set_carburant(t_terrain terrain, int position_ligne, int position_colonne, int carburant)
{
  if (terrain_contient(position_ligne, position_colonne))
  {
    terrain[position_ligne][position_colonne] = carburant;
  }
  else
  {
    printf("Position invalide : (%d, %d)\n", position_ligne, position_colonne);
  }
}

/**
 * @brief Initialise toutes les cases d'un terrain à 0 (zéro)
 * @param terrain le terrain dont on veut initialiser les cases
 */
void terrain_init(t_terrain terrain)
{
  for (int i = 0; i < NB_LIGNES; i++)
  {
    for (int j = 0; j < NB_COLONNES; j++)
    {
      terrain[i][j] = 0;
    }
  }
}

/**
 * @brief Crée aléatoirement les stations de carburant sur le terrain. La quantité globale des quantités de carburant des stations est passée en paramètre.
 * @param terrain le terrain sur lequel on veut créer les stations de carburant
 * @param quantite_globale la quantité globale de carburant à allouer sur l'ensemble des stations
 */
void terrain_creer_stations_carburant(t_terrain terrain, int quantite_globale)
{
  while (quantite_globale > 0)
  {
    int ligne = util_generer_nombre_aleatoire(0, NB_LIGNES - 1);
    int colonne = util_generer_nombre_aleatoire(0, NB_COLONNES - 1);
    int carburant = util_generer_nombre_aleatoire(1, STATION_MAX_CARBURANT);

    if (terrain[ligne][colonne] == 0)
    { // Si la case est vide
      terrain[ligne][colonne] = carburant;
      quantite_globale -= carburant;
    }
  }
}

/**
 * @brief Affiche la quantité de carburant pour toutes les cases d'un terrain.
 * De plus, présente la case courante et la case de destination avec des couleurs différentes.
 * @param terrain le terrain à afficher
 * @param courante_ligne la ligne de la position de la case courante
 * @param courante_colonne la colonne de la position de la case courante
 * @param destination_ligne la ligne de la position de la case de destination
 * @param destination_colonne la colonne de la position de la case de destination
 */
void terrain_afficher(t_terrain terrain, int courante_ligne, int courante_colonne, int destination_ligne, int destination_colonne)
{
  for (int i = 0; i < NB_LIGNES; i++)
  {
    for (int j = 0; j < NB_COLONNES; j++)
    {
      if (i == courante_ligne && j == courante_colonne)
      {
        printf("[X] "); // Case courante
      }
      else if (i == destination_ligne && j == destination_colonne)
      {
        printf("[S] "); // Case de destination
      }
      else
      {
        printf("%2d ", terrain[i][j]); // Autres cases
      }
    }
    printf("\n");
  }
}