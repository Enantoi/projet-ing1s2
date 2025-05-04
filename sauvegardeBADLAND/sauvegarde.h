//
// Created by Antoine ece on 4/30/2025.
//

#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
typedef struct {
    char pseudo[50];
    int niveau;
} Joueur;

void sauvegarderJoueur(Joueur personnage);
int chargerJoueur(Joueur *personnage);
void choixsauvegarde();
#endif //SAUVEGARDE_H
