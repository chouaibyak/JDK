#include <stdio.h>
#include "interaction.h"
#include "couleur.h" // Pour utiliser les couleurs dans l'affichage

// ***********************************
// Définitions des fonctions publiques
// ***********************************

/**
 * @brief Affiche une petite présentation du jeu.
 */
void interaction_presenter_jeu(void)
{
  printf("Bienvenue dans le jeu de deplacement de vehicule !\n");
  printf("Le but est de deplacer votre vehicule sur le terrain pour atteindre la sortie.\n");
  printf("Vous devez gerer votre carburant pour ne pas tomber en panne avant d'atteindre la destination.\n");
  printf("Bonne chance !\n\n");
}

/**
 * @brief Affiche les options du menu de jeu.
 * Une option non valide sera grisée.
 * @param carburant la quantité de carburant du joueur
 */
void interaction_afficher_options(int carburant)
{
  printf("Options disponibles :\n");
  printf("1. Se deplacer\n");
  printf("2. Acheter un bonus de deplacement (cout : 10 litres)\n");
  printf("3. Quitter le jeu\n");

  // Griser l'option d'achat de bonus si le joueur n'a pas assez de carburant
  if (carburant < 10)
  {
    couleur_set(STYLE_DIM, FG_WHITE, BG_BLACK); // Texte grisé
    printf("Option 2 (Acheter un bonus) est grisee car vous n'avez pas assez de carburant.\n");
    couleur_reset();
  }
  printf("\n");
}

/**
 * @brief Demande un choix à l'utilisateur sur une des options du menu.
 * @param carburant la quantité de carburant du joueur
 * @return ACTION_DEPLACER, ACTION_ACHETER_BONUS ou ACTION_QUITTER selon l'option choisie par le joueur
 */
t_action interaction_demander_action(int carburant)
{
  int choix;
  printf("Votre choix : ");
  scanf("%d", &choix);

  switch (choix)
  {
  case 1:
    return ACTION_DEPLACER;
  case 2:
    if (carburant >= 10)
    {
      return ACTION_ACHETER_BONUS;
    }
    else
    {
      return ACTION_INVALIDE;
    }
  case 3:
    return ACTION_QUITTER;
  default:
    return ACTION_INVALIDE;
  }
}

/**
 * @brief Demande une direction de déplacement au joueur.
 * @return DIRECTION_ERRONEE si la direction choisie est invalide.
 * DIRECTION_DROITE, DIRECTION_BAS, DIRECTION_HAUT ou DIRECTION_GAUCHE selon le choix du joueur, sinon
 */
t_direction interaction_demander_direction_deplacement(void)
{
  char choix;
  printf("Choisissez une direction (h: haut, b: bas, g: gauche, d: droite) : ");
  scanf(" %c", &choix);

  switch (choix)
  {
  case 'h':
    return DIRECTION_HAUT;
  case 'b':
    return DIRECTION_BAS;
  case 'g':
    return DIRECTION_GAUCHE;
  case 'd':
    return DIRECTION_DROITE;
  default:
    return DIRECTION_ERRONEE;
  }
}

/**
 * @brief Affiche un message d'échec de la mission.
 */
void interaction_afficher_echec(void)
{
  couleur_set(STYLE_BOLD, FG_RED, BG_BLACK);
  printf("Vous avez epuise votre carburant avant d'atteindre la sortie. Mission echouee !\n");
  couleur_reset();
}

/**
 * @brief Affiche un message de victoire de la mission ainsi que la quantité de
 * carburant restant dans le réservoir du joueur.
 * @param carburant la quantité de carburant du joueur
 */
void interaction_afficher_victoire(int carburant)
{
  couleur_set(STYLE_BOLD, FG_GREEN, BG_BLACK);
  printf("Felicitations ! Vous avez atteint la sortie avec %d litres de carburant restants. Mission accomplie !\n", carburant);
  couleur_reset();
}

/**
 * @brief Vérifie que l'action choisie par le joueur est correcte.
 * @param action l'action choisie par le joueur
 * @param carburant la quantité de carburant du joueur
 * @return action si elle est correcte, ACTION_INVALIDE sinon
 */
t_action interaction_verifier_choix_action(t_action action, int carburant)
{
  if (action == ACTION_ACHETER_BONUS && carburant < 10)
  {
    return ACTION_INVALIDE;
  }
  return action;
}