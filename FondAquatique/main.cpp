#define NB_TUYEAUX 4
        #define LARGEUR_TUYAU 60
        #define ECART_TUYAU 180
        #include <allegro.h>
        #include <stdlib.h>
        #include <time.h>
        #include <math.h>

        #define NB_LUCIOLES 20
        #define NB_OISEAUX 5
        #define NB_ARBRES 10
        #define SCROLL_SPEED 1

        typedef struct {
            int x, direction;
            int largeur;
            int hauteur;
        } Arbre;

        typedef struct {
            int x, y;
            int dx, dy;
        } Luciole;

        typedef struct {
            int x, y;
            int dx;
        } Oiseau;

        void dessiner_fond(BITMAP* buffer) {
            // Fond plus clair, ambiance nuit douce
            rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(50, 70, 110));
        }

        void dessiner_arbre_courbe(BITMAP* buffer, Arbre* a) {
            int i;
            float courbe = (a->direction == 0) ? -0.5f : 0.5f;

            int px = a->x;
            int py = SCREEN_H;

            for (i = 0; i < a->hauteur; i++) {
                int nx = a->x + (int)(sin(i * 0.1f) * courbe * i / 8.0f);
                int ny = SCREEN_H - i;
                line(buffer, px, py, nx, ny, makecol(80, 50, 30));
                px = nx;
                py = ny;
            }

            // Feuillage doux et stylé au sommet
            circlefill(buffer, px, py - 5, 15 + rand() % 10, makecol(40, 130 + rand() % 80, 60 + rand() % 40));
        }

        void dessiner_lucioles(Luciole lucioles[], BITMAP* buffer) {
            int i;
            for (i = 0; i < NB_LUCIOLES; ++i) {
                lucioles[i].x += lucioles[i].dx;
                lucioles[i].y += lucioles[i].dy;

                if (lucioles[i].x < 0) lucioles[i].x = SCREEN_W;
                if (lucioles[i].x > SCREEN_W) lucioles[i].x = 0;
                if (lucioles[i].y < 0 || lucioles[i].y > SCREEN_H) lucioles[i].dy *= -1;

                int clignote = 200 + rand() % 55;
                circlefill(buffer, lucioles[i].x, lucioles[i].y, 2, makecol(clignote, clignote, 120));
            }
        }

        void dessiner_oiseaux(Oiseau oiseaux[], BITMAP* buffer) {
            int i;
            for (i = 0; i < NB_OISEAUX; ++i) {
                oiseaux[i].x += oiseaux[i].dx - SCROLL_SPEED;

                if (oiseaux[i].x > SCREEN_W) {
                    oiseaux[i].x = -20;
                    oiseaux[i].y = rand() % 150 + 20;
                }

                // Forme "V"
                line(buffer, oiseaux[i].x, oiseaux[i].y, oiseaux[i].x + 5, oiseaux[i].y - 5, makecol(230, 230, 230));
                line(buffer, oiseaux[i].x + 5, oiseaux[i].y - 5, oiseaux[i].x + 10, oiseaux[i].y, makecol(230, 230, 230));
            }
        }

        int main() {
            int i;

            Luciole lucioles[NB_LUCIOLES];
            Oiseau oiseaux[NB_OISEAUX];
            Arbre arbres[NB_ARBRES];

            srand(time(NULL));
            allegro_init();
            install_keyboard();
            set_color_depth(32);
            set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

            BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
            if (!buffer) {
                allegro_message("Erreur de création du buffer !");
                return 1;
            }

            // Init lucioles
            for (i = 0; i < NB_LUCIOLES; ++i) {
                lucioles[i].x = rand() % SCREEN_W;
                lucioles[i].y = rand() % SCREEN_H;
                lucioles[i].dx = (rand() % 3) - 1;
                lucioles[i].dy = (rand() % 3) - 1;
            }

            // Init oiseaux
            for (i = 0; i < NB_OISEAUX; ++i) {
                oiseaux[i].x = rand() % SCREEN_W;
                oiseaux[i].y = rand() % 150 + 20;
                oiseaux[i].dx = 1 + rand() % 2;
            }

            // Init arbres
            for (i = 0; i < NB_ARBRES; ++i) {
                arbres[i].x = i * (SCREEN_W / NB_ARBRES) + rand() % 50;
                arbres[i].direction = rand() % 2;
                arbres[i].largeur = 8 + rand() % 5;
                arbres[i].hauteur = 250 + rand() % 100;
            }

            while (!key[KEY_ESC]) {
                clear_to_color(buffer, makecol(0, 0, 0));
                dessiner_fond(buffer);

                // Défilement des arbres
                for (i = 0; i < NB_ARBRES; ++i) {
                    arbres[i].x -= SCROLL_SPEED;
                    if (arbres[i].x < -50) {
                        arbres[i].x = SCREEN_W + rand() % 100;
                        arbres[i].direction = rand() % 2;
                        arbres[i].largeur = 8 + rand() % 5;
                        arbres[i].hauteur = 250 + rand() % 100;
                    }
                    dessiner_arbre_courbe(buffer, &arbres[i]);
                }

                dessiner_oiseaux(oiseaux, buffer);
                dessiner_lucioles(lucioles, buffer);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(40);
            }

            destroy_bitmap(buffer);
            return 0;
        }
        END_OF_MAIN();
        /*#include <allegro.h>
        #include <stdlib.h>
        #include <time.h>
        #include <math.h>

        #define NB_POISSONS 10
        #define NB_ALGUES 12

        typedef struct {
            int x, y;
            int dx;
            int couleur;
        } Poisson;

        typedef struct {
            int x;
            float phase;
            int hauteur;
        } Algue;

        void dessiner_fond(BITMAP* buffer) {
            int y;
            for (y = 0; y < SCREEN_H; y++) {
                int bleu = 40 + (y * 80 / SCREEN_H);
                rectfill(buffer, 0, y, SCREEN_W, y + 1, makecol(0, bleu, bleu + 20));
            }
        }

        void dessiner_algues(Algue algues[], BITMAP* buffer, int frame) {
            for (int i = 0; i < NB_ALGUES; i++) {
                int baseX = algues[i].x;
                int baseY = SCREEN_H;
                int h = algues[i].hauteur;
                float p = algues[i].phase;

                int px = baseX;
                int py = baseY;

                for (int j = 0; j < h; j++) {
                    int nx = baseX + sinf((frame * 0.05f) + p + j * 0.1f) * 6;
                    int ny = baseY - j * 4;
                    line(buffer, px, py, nx, ny, makecol(0, 120, 60));
                    px = nx;
                    py = ny;
                }
            }
        }

        void dessiner_poissons(Poisson poissons[], BITMAP* buffer, int frame) {
            for (int i = 0; i < NB_POISSONS; i++) {
                Poisson* p = &poissons[i];

                ellipsefill(buffer, p->x, p->y, 12, 6, p->couleur);  // corps
                triangle(buffer,
                         p->x - p->dx * 10, p->y,
                         p->x - p->dx * 18, p->y - 5,
                         p->x - p->dx * 18, p->y + 5,
                         p->couleur);  // queue

                // Mouvement
                p->x += p->dx;

                // Changement de direction aléatoire
                if (rand() % 300 == 0) {
                    p->dx *= -1;
                }

                // Réapparition de l'autre côté
                if (p->x < -20 || p->x > SCREEN_W + 20) {
                    p->x = (p->dx > 0) ? -20 : SCREEN_W + 20;
                    p->y = rand() % (SCREEN_H - 150) + 50;
                }
            }
        }

        int main() {
            int frame = 0;
            Poisson poissons[NB_POISSONS];
            Algue algues[NB_ALGUES];

            srand(time(NULL));
            allegro_init();
            install_keyboard();
            set_color_depth(32);
            set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

            BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
            if (!buffer) {
                allegro_message("Erreur : buffer non créé !");
                return 1;
            }

            // Init poissons
            for (int i = 0; i < NB_POISSONS; i++) {
                poissons[i].x = rand() % SCREEN_W;
                poissons[i].y = rand() % (SCREEN_H - 150) + 50;
                poissons[i].dx = (rand() % 2) ? 1 : -1;
                poissons[i].couleur = makecol(100 + rand() % 150, 100 + rand() % 150, 255);
            }

            // Init algues
            for (int i = 0; i < NB_ALGUES; i++) {
                algues[i].x = i * (SCREEN_W / NB_ALGUES) + rand() % 20;
                algues[i].phase = rand() % 100 / 10.0f;
                algues[i].hauteur = 10 + rand() % 10;
            }

            while (!key[KEY_ESC]) {
                clear_to_color(buffer, makecol(0, 0, 0));
                dessiner_fond(buffer);
                dessiner_algues(algues, buffer, frame);
                dessiner_poissons(poissons, buffer, frame);

                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(30);
                frame++;
            }

            destroy_bitmap(buffer);
            return 0;
        }
        END_OF_MAIN();*/
        #include <allegro.h>
        #include <stdlib.h>

        /*#define NB_OISEAUX 20

        typedef struct {
            int x, y;
            int taille;
            int dx;
        } Oiseau;

        void dessiner_fond(BITMAP* buffer) {
            for (int y = 0; y < SCREEN_H; y++) {
                int r = 230 - y / 5;
                int g = 220 - y / 6;
                int b = 210 - y / 7;
                rectfill(buffer, 0, y, SCREEN_W, y + 1, makecol(r, g, b));
            }
        }

        void dessiner_soleil(BITMAP* buffer) {
            circlefill(buffer, SCREEN_W - 100, 80, 40, makecol(255, 240, 180));
        }

        void dessiner_nuages(BITMAP* buffer) {
            for (int i = 0; i < 3; i++) {
                int x = 100 + i * 250;
                int y = 120 + (i % 2) * 20;
                ellipsefill(buffer, x, y, 60, 25, makecol(255, 255, 255));
                ellipsefill(buffer, x + 30, y + 10, 40, 20, makecol(240, 240, 240));
                ellipsefill(buffer, x - 30, y + 5, 50, 22, makecol(250, 250, 250));
            }
        }

        void dessiner_oiseau(BITMAP* buffer, Oiseau o) {
            int c = makecol(60, 60, 60);

            // Forme droite vue de face : simple V horizontal
            int t = o.taille;
            int x = o.x;
            int y = o.y;

            // Petit V centré horizontalement
            line(buffer, x - t, y, x, y - t, c);
            line(buffer, x, y - t, x + t, y, c);
        }

        void init_oiseaux(Oiseau oiseaux[]) {
            for (int i = 0; i < NB_OISEAUX; i++) {
                oiseaux[i].x = rand() % SCREEN_W;
                oiseaux[i].y = 50 + rand() % 250;
                oiseaux[i].taille = 4 + rand() % 10;
                oiseaux[i].dx = 1 + rand() % 2;
            }
        }

        void mettre_a_jour_oiseaux(Oiseau oiseaux[]) {
            for (int i = 0; i < NB_OISEAUX; i++) {
                oiseaux[i].x += oiseaux[i].dx;

                if (oiseaux[i].x > SCREEN_W + 20) {
                    oiseaux[i].x = -20;
                    oiseaux[i].y = 50 + rand() % 250;
                }
            }
        }

        int main() {
            Oiseau oiseaux[NB_OISEAUX];

            allegro_init();
            install_keyboard();
            set_color_depth(32);
            set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

            BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
            if (!buffer) {
                allegro_message("Erreur création buffer !");
                return 1;
            }

            init_oiseaux(oiseaux);

            while (!key[KEY_ESC]) {
                clear_to_color(buffer, makecol(0, 0, 0));

                dessiner_fond(buffer);
                dessiner_soleil(buffer);
                dessiner_nuages(buffer);

                for (int i = 0; i < NB_OISEAUX; i++) {
                    dessiner_oiseau(buffer, oiseaux[i]);
                }

                mettre_a_jour_oiseaux(oiseaux);

                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(30);
            }

            destroy_bitmap(buffer);
            return 0;
        }
        END_OF_MAIN();

        typedef struct {
            int x, y;
            int largeur, hauteur;
            int actif;
        } Tuyau;

        typedef struct {
            int x, y;
            int largeur, hauteur;
            int vitesseY;
        } Joueur;

        int collision(Joueur j, Tuyau t) {
            return j.x < t.x + t.largeur &&
                   j.x + j.largeur > t.x &&
                   j.y < t.y + t.hauteur &&
                   j.y + j.hauteur > t.y;
        }
        void init_tuyaux(Tuyau tuyaux[]) {
            for (int i = 0; i < NB_TUYEAUX; i++) {
                int x = 800 + i * 250;
                int trou_y = 100 + rand() % 300;
                tuyaux[i].x = x;
                tuyaux[i].largeur = LARGEUR_TUYAU;
                tuyaux[i].actif = 1;

                // Tuyau du haut
                tuyaux[i].y = 0;
                tuyaux[i].hauteur = trou_y;

                // Tuyau du bas (on l’ajoutera visuellement plus tard)
            }
}*/

