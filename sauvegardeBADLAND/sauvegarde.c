//
// Created by Antoine ece on 4/30/2025.
//

#include "sauvegarde.h"
#include <stdio.h>
#include <string.h>

void sauvegarderJoueur(Joueur personnage) {
    FILE *fichier = fopen("sauvegarde.txt", "w");
    if (fichier == NULL) {
        printf("erreur ouverture fichier de sauvegarde");
        return;
    }
    fprintf(fichier, "%s\n%d\n", personnage.pseudo, personnage.niveau);
    fclose(fichier);
}

    int chargerJoueur(Joueur *personnage) {
        FILE *fichier = fopen("sauvegarde.txt", "r");
        if (!fichier) return 0;
        fscanf(fichier, "%s %d", personnage->pseudo, &personnage->niveau);
        fclose(fichier);
        return 1;
    }

void choixsauvegarde() {

    char choix[10];
    Joueur personnage;
    int joueurexiste = chargerJoueur(&personnage);

    if (joueurexiste) {
        printf("bienvenue %s !\n", personnage.pseudo);
        printf("dernier niveau atteint : %d\n", personnage.niveau);
        printf("1 nouvelle partie\n");
        printf("2 reprendre la partie\n");
        printf("Choix : ");
        fgets(choix, sizeof(choix), stdin);

        if (choix[0] == '1') {
            personnage.niveau = 1;
            printf("nouvelle partie lancee pour %s au niveau 1.\n", personnage.pseudo);
        } else {
            printf("reprise de la partie au niveau %d.\n", personnage.niveau);
        }
    } else {
        printf("nouveau joueur, entrez votre pseudo : ");
        scanf("%s", personnage.pseudo);
        personnage.niveau = 1;
        printf("bienvenue %s ! debut de la partie au niveau 1.\n", personnage.pseudo);
    }
}

