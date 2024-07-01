#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

/**
* @struct personne
* @brief struct for character
*/

typedef struct 
{
    SDL_Surface *tab[20]; /*!< character images*/
    SDL_Surface *tabvie[4]; /*!< Life bar images*/
    SDL_Rect pos1; /*!< Character position*/
    SDL_Rect posvie; /*!< Life bar*/
    double vitesse; /*!< Speed*/
    double acc; /*!< Accelaration*/
    double gravite_x; /*!< The gravity fonction's x variable*/
    double gravite_y; /*!< The gravity fonction's y variable*/
    double gravite; /*!< Fall speed*/
    int dep;
    int up; /*!< Indicates jumping state*/
    Uint32 dt;
    int dr,num,vie,saut;
    int time,init_time;
    int saut_y; /*!< The jump fonction's x variable*/
    int saut_x; /*!< The jump fonction's y variable*/
    int max_jump; /*!< The jump's maximum height*/
    float pente; /*!< The jump fonction's slope*/
    float gravite_pente; /*!< The gravity fonction's slope*/
    int collision; /*!< Detects collision*/
    int fall; /*!< Indicates falling state*/
    int left,right; /*!< Falling detection*/
    int jump_ready; /*!< Indicates whether you can jump or not*/
    int sommet; /*!< The jump fonction's vortex*/
    int drop_jump;
    int life;

}personne;

#include "ennemi.h"

void initperso(personne *pe,SDL_Surface *screen);
void afficherperso(personne *pe,background b);
void deplacerperso(personne *pe, Uint32 dt, background b);
void animerperso(personne *pe);
void saut_parabolique(personne *pe,background b,SDL_Surface* screen);
void saut(personne *pe);
void auto_slow_perso1(personne *pe);
void slow_perso1(personne *pe);
void liberer_perso1(personne *pe);
void sprint_perso1(personne *pe);
void gravite_parabolique(personne *pe,background b,SDL_Surface* screen);
void death_animation(personne *p,background *b,background *death,int w,int h,SDL_Surface* screen,int ms);
int arduinoWriteData(char chemin1[]);
int arduinoReadData(int *x,char chemin[]);
void manette_read(int *x);

#endif // FONCTION_H_INCLUDED
