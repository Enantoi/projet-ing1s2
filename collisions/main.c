#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define NB_TUYEAUX 17
#define LARGEUR_TUYAU 60
#define ECART_TUYAU 180
#define GRAVITE 5
#define SAUT -12

typedef struct {
    int x, y;
    int largeur, hauteur;
    int dejaCompte; // pour compter le score une seule fois
} Tuyau;



typedef struct {
    int x, y;
    int largeur, hauteur;
    int vitesseY;
} Joueur;

int collision(Joueur j, Tuyau t) {
    if (j.x < t.x + t.largeur &&
           j.x + j.largeur > t.x &&
           j.y < t.y + t.hauteur &&
           j.y + j.hauteur > t.y && j.y + j.largeur<t.y+t.hauteur) {
        return 1;
    }
}
void init_un_tuyau(Tuyau* t, int x, int largeur, int y, int hauteur) {
    t->x = x;
    t->largeur = largeur;
    t->dejaCompte = 0;
    t->y = y;
    t->hauteur = hauteur;
}
void init_tuyaux(Tuyau tuyaux[]) {
    /*int trou_y = 100 + rand() % 300;*/
    init_un_tuyau(&tuyaux[0],800,40,10,40);
    init_un_tuyau(&tuyaux[1],900,60,350,80);
    init_un_tuyau(&tuyaux[2],960,40,400,10);
    init_un_tuyau(&tuyaux[3],1000,50,500,30);
    init_un_tuyau(&tuyaux[4],1100,50,550,50);
    init_un_tuyau(&tuyaux[5],3200,100,20,100);
    init_un_tuyau(&tuyaux[6],3300,60,5,50);
    init_un_tuyau(&tuyaux[7],3500,10,200,150);
    init_un_tuyau(&tuyaux[8],3600,150,300,80);
    init_un_tuyau(&tuyaux[9],3700,50,450,50);
    init_un_tuyau(&tuyaux[10],3800,50,500,10);
    init_un_tuyau(&tuyaux[11],4000,50,100,55);
    init_un_tuyau(&tuyaux[12],4100,80,380,35);
    init_un_tuyau(&tuyaux[13],4300,100,550,60);
    init_un_tuyau(&tuyaux[14],4500,50,250,60);
    init_un_tuyau(&tuyaux[15],4800,100,160,80);
}

int main(){
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

    BITMAP* buffer = create_bitmap(800, 600);
    if (!buffer) {
        allegro_message("Erreur buffer");
        return 1;
    }

    Joueur joueur = { 200, 300, 30, 30, 0 };
    Tuyau tuyaux[NB_TUYEAUX];
    init_tuyaux(tuyaux);

    int enVie = 1;
    int score = 0;

    while (!key[KEY_ESC]) {
        clear_to_color(buffer, makecol(255, 255, 255)); // ciel

        if (enVie) {
            // Gravité
            joueur.vitesseY += GRAVITE;
            joueur.y += joueur.vitesseY;

            // Saut
            if (key[KEY_SPACE]) {
                joueur.vitesseY = SAUT;
            }

            // Tuyaux
            for (int i = 0; i < NB_TUYEAUX; i++) {
                tuyaux[i].x -= 8;

                // Tuyau haut
                /*rectfill(buffer, tuyaux[i].x, 0,
                         tuyaux[i].x + LARGEUR_TUYAU, tuyaux[i].hauteur,
                         makecol(34, 139, 34));*/

                // Tuyau bas
                rectfill(buffer, tuyaux[i].x, tuyaux[i].y,
                         tuyaux[i].x + LARGEUR_TUYAU, tuyaux[i].y+200,
                         makecol(0, 0, 0));

                // Collision
                if (collision(joueur, tuyaux[i])==1) {
                    joueur.x-=8;
                }
                else if(collision(joueur, tuyaux[i])==1 && tuyaux[i].y+tuyaux[i].hauteur<joueur.y) {
                    joueur.y=tuyaux[i].y+tuyaux[i].hauteur;
                }

                // Score
                if (!tuyaux[i].dejaCompte && tuyaux[i].x + LARGEUR_TUYAU < joueur.x) {
                    score++;
                    tuyaux[i].dejaCompte = 1;
                }
            }

            if (joueur.y > 600 || joueur.y < 0)
                enVie = 0;
        } else {
            textout_centre_ex(buffer, font, "GAME OVER - Appuie sur ECHAP pour quitter", 400, 250, makecol(255, 0, 0), -1);
        }

        // Joueur
        rectfill(buffer, joueur.x, joueur.y, joueur.x + joueur.largeur, joueur.y + joueur.hauteur, makecol(255, 20, 0));

        // Score
        char texteScore[20];
        sprintf(texteScore, "Score : %d", score);
        textout_ex(buffer, font, texteScore, 10, 10, makecol(0, 0, 0), -1);

        blit(buffer, screen, 0, 0, 0, 0, 800, 600);
        rest(30);
    }

    destroy_bitmap(buffer);
    return 0;
}
END_OF_MAIN();

