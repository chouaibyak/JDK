#ifndef CODE_INTERACTION_H
#define CODE_INTERACTION_H

#include <stdbool.h>
#include "jeu.h" // Include the header where t_direction is defined
#include "terrain.h"
// Enumération des actions possibles
typedef enum
{
  ACTION_INVALIDE,      // Action invalide
  ACTION_DEPLACER,      // Déplacer le joueur
  ACTION_ACHETER_BONUS, // Acheter un bonus
  ACTION_QUITTER        // Quitter le jeu
} t_action;

// ************************************
// Déclarations des fonctions publiques
// ************************************

/**
 * @brief Affiche une petite présentation du jeu.
 */
void interaction_presenter_jeu(void);

/**
 * @brief Affiche les options du menu de jeu.
 * Une option non valide sera grisée.
 * @param carburant la quantité de carburant du joueur
 */
void interaction_afficher_options(int carburant);

/**
 * @brief Demande un choix à l'utilisateur sur une des options du menu.
 * @param carburant la quantité de carburant du joueur
 * @return ACTION_DEPLACER, ACTION_ACHETER_BONUS ou ACTION_QUITTER selon l'option choisie par le joueur
 */
t_action interaction_demander_action(int carburant);

/**
 * @brief Demande une direction de déplacement au joueur.
 * @return DIRECTION_ERRONEE si la direction choisie est invalide.
 * DIRECTION_DROITE, DIRECTION_BAS, DIRECTION_HAUT ou DIRECTION_GAUCHE selon le choix du joueur, sinon
 */
t_direction interaction_demander_direction_deplacement(void);

/**
 * @brief Affiche un message d'échec de la mission.
 */
void interaction_afficher_echec(void);

/**
 * @brief Affiche un message de victoire de la mission ainsi que la quantité de
 * carburant restant dans le réservoir du joueur.
 * @param carburant la quantité de carburant du joueur
 */
void interaction_afficher_victoire(int carburant);

/**
 * @brief Vérifie que l'action choisie par le joueur est correcte.
 * @param action l'action choisie par le joueur
 * @param carburant la quantité de carburant du joueur
 * @return action si elle est correcte, ACTION_INVALIDE sinon
 */
t_action interaction_verifier_choix_action(t_action action, int carburant);

#endif // CODE_INTERACTION_H