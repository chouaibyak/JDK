#ifndef CODE_JEU_H
#define CODE_JEU_H

#include <stdbool.h> // Pour le type bool
#include "terrain.h" // Pour le type t_terrain

// Constantes du jeu
#define JOUEUR_CARBURANT_INITIAL 2
#define COUT_DEPLACEMENT_VOISIN 1
#define BONUS_CARBURANT 5
#define TOTAL_CARBURANT_NIVEAU_1 100

// *****************************
// Définitions des types publics
// *****************************

/**
 * @brief Enumération des directions possibles pour le déplacement du joueur.
 */
typedef enum
{
    DIRECTION_ERRONEE = -1, // Direction invalide
    DIRECTION_DROITE,       // Droite
    DIRECTION_BAS,          // Bas
    DIRECTION_HAUT,         // Haut
    DIRECTION_GAUCHE        // Gauche
} t_direction;

/**
 * @brief Enumération des états possibles du jeu.
 */
typedef enum
{
    JEU_ETAT_ECHEC = 1, // Le joueur a perdu
    JEU_ETAT_VICTOIRE,  // Le joueur a gagné
    JEU_ETAT_EN_COURS   // Le jeu est en cours
} t_jeu_etat;

// ************************************
// Déclarations des fonctions publiques
// ************************************

/**
 * @brief Met à jour la quantité de carburant du joueur après un déplacement. Annule la quantité de carburant sur la case du joueur.
 * @param joueur_ligne la ligne où se trouve maintenant le joueur
 * @param joueur_colonne la colonne où se trouve maintenant le joueur
 * @param joueur_carburant l'adresse où placer la nouvelle quantité de carburant du joueur après déplacement
 * @param terrain le terrain sur lequel le joueur s'est déplacé
 */
void jeu_maj_carburant_joueur(int joueur_ligne, int joueur_colonne, int *joueur_carburant, t_terrain terrain);

/**
 * @brief Déplace le joueur dans une direction donnée.
 * @param joueur_ligne l'adresse de la ligne où se trouve le joueur avant le déplacement et qui sera mise à jour
 * @param joueur_colonne l'adresse de la colonne où se trouve le joueur avant le déplacement et qui sera mise à jour
 * @param direction la direction dans laquelle on veut déplacer le joueur
 * @return true si le déplacement a pu se faire dans les limites du terrain, false sinon
 */
bool jeu_deplacer_joueur(int *joueur_ligne, int *joueur_colonne, t_direction direction);

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
void jeu_init(t_terrain terrain, int *joueur_ligne, int *joueur_colonne, int *joueur_carburant, int *destination_ligne, int *destination_colonne);

/**
 * @brief Affiche une direction en toutes lettres.
 * @param direction la direction à afficher
 */
void jeu_afficher_direction(t_direction direction);

/**
 * @brief Récupère une direction saisie sous la forme d'une chaîne de caractères,
 * s'assure qu'elle est valide et retourne la constante correspondante.
 * @param choix une chaîne de caractère constituant un choix de direction du joueur
 * @return DIRECTION_ERRONEE si la chaîne ne correspond pas à l'une des 4 directions.
 * Sinon, retourne DIRECTION_HAUT ou DIRECTION_BAS ou DIRECTION_DROITE ou DIRECTION_GAUCHE selon la direction choisie
 */
t_direction jeu_verifier_choix_deplacement(const char *choix);

/**
 * @brief Calcule la position d'un voisin dans une direction donnée.
 * @param case_ligne la ligne de la case de départ
 * @param case_colonne la colonne de la case de départ
 * @param direction la direction dans laquelle se trouve le voisin
 * @param voisin_ligne l'adresse où placer la ligne du voisin selon la direction
 * @param voisin_colonne l'adresse où placer la colonne du voisin selon la direction
 */
void jeu_calculer_voisin(int case_ligne, int case_colonne, t_direction direction, int *voisin_ligne, int *voisin_colonne);

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
t_jeu_etat jeu_verifier_fin(int joueur_ligne, int joueur_colonne, int joueur_carburant, int destination_ligne, int destination_colonne);

#endif // CODE_JEU_H