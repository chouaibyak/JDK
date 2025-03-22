#ifndef CODE_TERRAIN_H
#define CODE_TERRAIN_H

#include <stdbool.h> // Pour le type bool

// Taille du terrain
#define NB_LIGNES 10
#define NB_COLONNES 10

// Quantité maximale de carburant par case de terrain
#define STATION_MAX_CARBURANT 9

// *****************************
// Définitions des types publics
// *****************************

// Le type pour les cases du terrain
typedef int t_terrain[NB_LIGNES][NB_COLONNES];

// ************************************
// Déclarations des fonctions publiques
// ************************************

/**
 * @brief Propose une position de sortie aléatoire pour un terrain de dimensions NB_LIGNES x NB_COLONNES
 * @param sortie_ligne l'adresse où déposer une ligne de sortie aléatoire
 * @param sortie_colonne l'adresse où déposer une colonne de sortie aléatoire
 */
void terrain_generer_position_sortie(int *sortie_ligne, int *sortie_colonne);

/**
 * @brief Propose une position de départ aléatoire pour un terrain de dimensions NB_LIGNES x NB_COLONNES
 * @param destination_ligne la ligne de la sortie actuelle
 * @param destination_colonne la colonne de la sortie actuelle
 * @param depart_ligne l'adresse où déposer la ligne choisie aléatoirement
 * @param depart_colonne l'adresse où déposer la colonne choisie aléatoirement
 * @note La distance Manhattan entre la position de départ et la position de sortie doit être plus grande que 10.
 */
void terrain_generer_position_depart(int destination_ligne, int destination_colonne, int *depart_ligne, int *depart_colonne);

/**
 * @brief Vérifie qu'une position se trouve bien dans les limites du terrain de NB_LIGNES x NB_COLONNES
 * @param position_ligne la ligne de la case à tester
 * @param position_colonne la colonne de la case à tester
 * @return true si la position se trouve à l'intérieur du terrain, false sinon
 */
bool terrain_contient(int position_ligne, int position_colonne);

/**
 * @brief Retourne la quantité de carburant qui se trouve sur une case donnée du terrain
 * @param terrain le terrain
 * @param position_ligne la ligne de la case dont on veut connaître la quantité de carburant
 * @param position_colonne la colonne de la case dont on veut connaître la quantité de carburant
 * @return la quantité de carburant présente à cette position
 */
int terrain_get_carburant(t_terrain terrain, int position_ligne, int position_colonne);

/**
 * @brief Initialise la quantité de carburant sur une case du terrain
 * @param terrain le terrain dont on va modifier une case
 * @param position_ligne la ligne de la case à modifier
 * @param position_colonne la colonne de la case à modifier
 * @param carburant le carburant qui se trouvera dans la case
 */
void terrain_set_carburant(t_terrain terrain, int position_ligne, int position_colonne, int carburant);

/**
 * @brief Initialise toutes les cases d'un terrain à 0 (zéro)
 * @param terrain le terrain dont on veut initialiser les cases
 */
void terrain_init(t_terrain terrain);

/**
 * @brief Crée aléatoirement les stations de carburant sur le terrain. La quantité globale des quantités de carburant des stations est passée en paramètre.
 * @param terrain le terrain sur lequel on veut créer les stations de carburant
 * @param quantite_globale la quantité globale de carburant à allouer sur l'ensemble des stations
 */
void terrain_creer_stations_carburant(t_terrain terrain, int quantite_globale);

/**
 * @brief Affiche la quantité de carburant pour toutes les cases d'un terrain.
 * De plus, présente la case courante et la case de destination avec des couleurs différentes.
 * @param terrain le terrain à afficher
 * @param courante_ligne la ligne de la position de la case courante
 * @param courante_colonne la colonne de la position de la case courante
 * @param destination_ligne la ligne de la position de la case de destination
 * @param destination_colonne la colonne de la position de la case de destination
 */
void terrain_afficher(t_terrain terrain, int courante_ligne, int courante_colonne, int destination_ligne, int destination_colonne);

#endif // CODE_TERRAIN_H