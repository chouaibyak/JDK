#include "jeu.h"
#include "terrain.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

// ***********************************
// Definitions des fonctions publiques
// ***********************************

/**
 * @brief Met à jour la quantité de carburant du joueur après un déplacement. Annule la quantité de carburant sur la case du joueur.
 * @param joueur_ligne la ligne où se trouve maintenant le joueur
 * @param joueur_colonne la colonne où se trouve maintenant le joueur
 * @param joueur_carburant l'adresse où placer la nouvelle quantité de carburant du joueur après déplacement
 * @param terrain le terrain sur lequel le joueur s'est déplacé
 */
void jeu_maj_carburant_joueur(int joueur_ligne, int joueur_colonne, int *joueur_carburant, t_terrain terrain)
{
  // Récupérer le carburant sur la case actuelle
  int carburant_case = terrain_get_carburant(terrain, joueur_ligne, joueur_colonne);

  // Ajouter le carburant de la case au joueur
  *joueur_carburant += carburant_case;

  // Annuler le carburant sur la case (la case est maintenant vide)
  terrain_set_carburant(terrain, joueur_ligne, joueur_colonne, 0);

  // Soustraire le coût du déplacement
  *joueur_carburant -= COUT_DEPLACEMENT_VOISIN;
}

/**
 * @brief Déplace le joueur dans une direction donnée.
 * @param joueur_ligne l'adresse de la ligne où se trouve le joueur avant le déplacement et qui sera mise à jour
 * @param joueur_colonne l'adresse de la colonne où se trouve le joueur avant le déplacement et qui sera mise à jour
 * @param direction la direction dans laquelle on veut déplacer le joueur
 * @return true si le déplacement a pu se faire dans les limites du terrain, false sinon
 */
bool jeu_deplacer_joueur(int *joueur_ligne, int *joueur_colonne, t_direction direction)
{
  int nouvelle_ligne = *joueur_ligne;
  int nouvelle_colonne = *joueur_colonne;

  // Calculer la nouvelle position en fonction de la direction
  switch (direction)
  {
  case DIRECTION_HAUT:
    nouvelle_ligne--;
    break;
  case DIRECTION_BAS:
    nouvelle_ligne++;
    break;
  case DIRECTION_GAUCHE:
    nouvelle_colonne--;
    break;
  case DIRECTION_DROITE:
    nouvelle_colonne++;
    break;
  default:
    return false; // Direction invalide
  }

  // Vérifier si la nouvelle position est valide
  if (terrain_contient(nouvelle_ligne, nouvelle_colonne))
  {
    *joueur_ligne = nouvelle_ligne;
    *joueur_colonne = nouvelle_colonne;
    return true;
  }

  return false; // Déplacement invalide
}

/**
 * @brief Initialise le terrain de jeu avec les stations de carburant.
 * Initialise la position de destination ainsi que la position initiale du joueur et sa quantité de carburant.
 * @param terrain le terrain sur lequel seront placées les stations de carburant
 * @param joueur_ligne l'adresse de la ligne où positionner le joueur
 * @param joueur_colonne l'adresse de la colonne où positionner le joueur
 * @param joueur_carburant l'adresse où placer la quantité de carburant du joueur
 * @param destination_ligne l'adresse de la ligne de la case à atteindre
 * @param destination_colonne l'adresse de la colonne de la case à atteindre
 */
void jeu_init(t_terrain terrain, int *joueur_ligne, int *joueur_colonne, int *joueur_carburant, int *destination_ligne, int *destination_colonne)
{
  // Initialiser le terrain
  terrain_init(terrain);

  // Générer la position de sortie
  terrain_generer_position_sortie(destination_ligne, destination_colonne);

  // Générer la position de départ
  terrain_generer_position_depart(*destination_ligne, *destination_colonne, joueur_ligne, joueur_colonne);

  // Initialiser le carburant du joueur
  *joueur_carburant = JOUEUR_CARBURANT_INITIAL;

  // Créer les stations de carburant
  terrain_creer_stations_carburant(terrain, TOTAL_CARBURANT_NIVEAU_1);
}

/**
 * @brief Affiche une direction en toutes lettres
 * @param direction la direction à afficher
 */
void jeu_afficher_direction(t_direction direction)
{
  switch (direction)
  {
  case DIRECTION_HAUT:
    printf("haut");
    break;
  case DIRECTION_BAS:
    printf("bas");
    break;
  case DIRECTION_GAUCHE:
    printf("gauche");
    break;
  case DIRECTION_DROITE:
    printf("droite");
    break;
  default:
    printf("direction inconnue");
    break;
  }
}

/**
 * @brief Récupère une direction saisie sous la forme d'une chaîne de caractères,
 * s'assure qu'elle est valide et retourne la constante correspondante.
 * @param choix une chaîne de caractère constituant un choix de direction du joueur
 * @return DIRECTION_ERRONEE si la chaîne ne correspond pas à l'une des 4 directions.
 * Sinon, retourne DIRECTION_HAUT ou DIRECTION_BAS ou DIRECTION_DROITE ou DIRECTION_GAUCHE selon la direction choisie
 */
t_direction jeu_verifier_choix_deplacement(const char *choix)
{
  if (strcmp(choix, "haut") == 0)
  {
    return DIRECTION_HAUT;
  }
  else if (strcmp(choix, "bas") == 0)
  {
    return DIRECTION_BAS;
  }
  else if (strcmp(choix, "gauche") == 0)
  {
    return DIRECTION_GAUCHE;
  }
  else if (strcmp(choix, "droite") == 0)
  {
    return DIRECTION_DROITE;
  }
  else
  {
    return DIRECTION_ERRONEE;
  }
}

/**
 * @brief Calcule la position d'un voisin dans une direction donnée.
 * @param case_ligne la ligne de la case de départ
 * @param case_colonne la colonne de la case de départ
 * @param direction la direction dans laquelle se trouve le voisin
 * @param voisin_ligne l'adresse où placer la ligne du voisin selon la direction
 * @param voisin_colonne l'adresse où placer la colonne du voisin selon la direction
 */
void jeu_calculer_voisin(int case_ligne, int case_colonne, t_direction direction, int *voisin_ligne, int *voisin_colonne)
{
  *voisin_ligne = case_ligne;
  *voisin_colonne = case_colonne;

  switch (direction)
  {
  case DIRECTION_HAUT:
    (*voisin_ligne)--;
    break;
  case DIRECTION_BAS:
    (*voisin_ligne)++;
    break;
  case DIRECTION_GAUCHE:
    (*voisin_colonne)--;
    break;
  case DIRECTION_DROITE:
    (*voisin_colonne)++;
    break;
  default:
    break; // Direction invalide
  }
}

/**
 * @brief Vérifie si le jeu est terminé ou non.
 * @param joueur_ligne la ligne où se trouve le joueur
 * @param joueur_colonne la colonne où se trouve le joueur
 * @param joueur_carburant la quantité de carburant actuel du joueur
 * @param destination_ligne la ligne de la destination
 * @param destination_colonne la colonne de la destination
 * @return JEU_ETAT_VICTOIRE si le joueur a atteint la case d'arrivée.
 * JEU_ETAT_ECHEC si le joueur n'a plus de carburant.
 * JEU_ETAT_EN_COURS si la partie est en cours.
 */
t_jeu_etat jeu_verifier_fin(int joueur_ligne, int joueur_colonne, int joueur_carburant, int destination_ligne, int destination_colonne)
{
  if (joueur_ligne == destination_ligne && joueur_colonne == destination_colonne)
  {
    return JEU_ETAT_VICTOIRE;
  }
  else if (joueur_carburant <= 0)
  {
    return JEU_ETAT_ECHEC;
  }
  else
  {
    return JEU_ETAT_EN_COURS;
  }
}