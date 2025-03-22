#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "couleur.h"
#include "util.h"
#include "interaction.h"
#include "jeu.h"
#include "terrain.h"
#include "dijkstra.h"

// *********************************************
// Declarations des fonctions autres que le main
// *********************************************

/**
 * @brief Exécute la boucle principale du jeu
 * @name jeu_executer
 * @param terrain le terrain sur lequel le joueur évolue
 * @param joueur_ligne la ligne où se trouve le joueur
 * @param joueur_colonne la colonne où se trouve le joueur
 * @param joueur_carburant la quantité de carburant du joueur
 * @param destination_ligne la ligne de la case à atteindre
 * @param destination_colonne la colonne de la case à atteindre
 */
void jeu_executer(t_terrain terrain, int joueur_ligne, int joueur_colonne, int joueur_carburant, int destination_ligne, int destination_colonne);

// ******************************
// Definition de la fonction main
// ******************************
int main(void)
{
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    // Les données du jeu : terrain, joueur, case de sortie
    t_terrain terrain;
    int joueur_ligne, joueur_colonne, joueur_carburant; // Le joueur
    int destination_ligne, destination_colonne;         // La case de destination

    // Initialisation du jeu
    jeu_init(terrain, &joueur_ligne, &joueur_colonne, &joueur_carburant, &destination_ligne, &destination_colonne);

    // Présentation du jeu
    interaction_presenter_jeu();

    // Boucle principale du jeu
    jeu_executer(terrain, joueur_ligne, joueur_colonne, joueur_carburant, destination_ligne, destination_colonne);

    return 0;
}

// ********************************************
// Definitions des fonctions autres que le main
// ********************************************

/**
 * @brief Exécute la boucle principale du jeu
 * @param terrain le terrain sur lequel le joueur évolue
 * @param joueur_ligne la ligne où se trouve le joueur
 * @param joueur_colonne la colonne où se trouve le joueur
 * @param joueur_carburant la quantité de carburant du joueur
 * @param destination_ligne la ligne de la case à atteindre
 * @param destination_colonne la colonne de la case à atteindre
 */
void jeu_executer(t_terrain terrain, int joueur_ligne, int joueur_colonne, int joueur_carburant, int destination_ligne, int destination_colonne)
{
    while (1)
    {
        // Affichage du terrain
        terrain_afficher(terrain, joueur_ligne, joueur_colonne, destination_ligne, destination_colonne);

        // Affichage des options
        interaction_afficher_options(joueur_carburant);

        // Demande d'une action
        t_action action = interaction_demander_action(joueur_carburant);
        if (action == ACTION_INVALIDE)
        {
            printf("Action invalide. Veuillez reessayer.\n\n");
            continue;
        }

        // Traitement de l'action
        switch (action)
        {
        case ACTION_DEPLACER:
        {
            // Demande d'une direction de déplacement
            t_direction direction = interaction_demander_direction_deplacement();
            if (direction == DIRECTION_ERRONEE)
            {
                printf("Direction invalide. Veuillez reessayer.\n\n");
                continue;
            }

            // Déplacement du joueur
            if (jeu_deplacer_joueur(&joueur_ligne, &joueur_colonne, direction))
            {
                jeu_maj_carburant_joueur(joueur_ligne, joueur_colonne, &joueur_carburant, terrain);
                printf("Deplacement reussi ! Nouvelle position : (%d, %d)\n", joueur_ligne, joueur_colonne);
                printf("Nouveau carburant du joueur : %d\n\n", joueur_carburant);
            }
            else
            {
                printf("Deplacement invalide. Veuillez reessayer.\n\n");
            }
            break;
        }
        case ACTION_ACHETER_BONUS:
        {
            // Achat du bonus de déplacement
            if (joueur_carburant >= 10)
            {
                dijkstra_acheter_bonus(terrain, joueur_ligne, joueur_colonne, &joueur_carburant, destination_ligne, destination_colonne);
            }
            else
            {
                printf("Vous n'avez pas assez de carburant pour acheter ce bonus.\n\n");
            }
            break;
        }
        case ACTION_QUITTER:
        {
            printf("Merci d'avoir joue ! A bientot.\n");
            return;
        }
        default:
        {
            printf("Action non reconnue. Veuillez reessayer.\n\n");
            break;
        }
        }

        // Vérification de fin de jeu
        t_jeu_etat etat = jeu_verifier_fin(joueur_ligne, joueur_colonne, joueur_carburant, destination_ligne, destination_colonne);
        if (etat == JEU_ETAT_VICTOIRE)
        {
            interaction_afficher_victoire(joueur_carburant);
            break;
        }
        else if (etat == JEU_ETAT_ECHEC)
        {
            interaction_afficher_echec();
            break;
        }
    }
}