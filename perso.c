
#include "background.h"

/**
* @file perso.c
* @brief Testing Program.
* @author Unfinished Legacy
* @version 0.1
* @date Apr 22, 2022
*
* persos fonctions
*
*/

/**
* @brief To initialize the character
* @param pe the character
* @param screen
* @return nothing
*/
void initperso(personne *pe,SDL_Surface *screen)
{
    pe->pos1.x = 200;  
    pe->pos1.y = 1120; 
    pe->pos1.w =50;
    pe->pos1.h =100;
    pe->posvie.x = 800; 
    pe->posvie.y = 0;
    pe->vitesse = 10;   
    pe->acc = 0;       
    pe->life=1; 
     
    pe->collision=-1;      
    char nomFich[20];
    int i;
    for (i = 0; i < 20; i++) 
    {
        sprintf(nomFich, "sprite_perso/%d.png", i);
        pe->tab[i] = IMG_Load(nomFich);
    }
    char nomvie[20]; 
    int j;
    for (j = 0; j < 4; j++)
    {
        sprintf(nomvie, "sprite_perso/v%d.png", j);
        pe->tabvie[j] = IMG_Load(nomvie);
    }

    pe->dr = 0;
    pe->num = 0;
    pe->vie = 0; 
    pe->saut = 0;

    pe->gravite=1;
    pe->gravite_pente =-0.5;
    pe->gravite_x =20;
    pe->left=0;
    pe->right=0;
    pe->fall=0;

    pe->saut_x=-20;
    pe->max_jump=200;
    pe->pente=-0.5;
    pe->sommet=0;
    pe->up = 0; 
}
/**
* @brief To display the character
* @param pe the character
* @param b the background
* @return nothing
*/
void afficherperso(personne *pe,background b)
{  
    SDL_BlitSurface(b.img2, &pe->pos1, b.img, &pe->pos1);
    SDL_BlitSurface(pe->tab[pe->num], NULL, b.img, &pe->pos1);
    SDL_BlitSurface(pe->tabvie[pe->vie], NULL,b.img, &pe->posvie);
}
/**
* @brief To move the character
* @param pe the character
* @param b the background
* @return nothing
*/
void deplacerperso(personne *pe, Uint32 dt, background b)
{
    if (pe->dep == 1)
    {
        SDL_BlitSurface(b.img2,&pe->pos1,b.img,&pe->pos1);
        pe->pos1.x += pe->acc * dt  + pe->vitesse;
        SDL_BlitSurface(pe->tab[pe->num], NULL, b.img, &pe->pos1);
        //SDL_Flip(b.img);
    }
    else if (pe->dep == 0)
    {
        SDL_BlitSurface(b.img2,&pe->pos1,b.img,&pe->pos1);
        pe->pos1.x -= pe->acc * dt  + pe->vitesse;
        SDL_BlitSurface(pe->tab[pe->num], NULL, b.img, &pe->pos1);
        //SDL_Flip(b.img);
    }
}

void animerperso(personne *pe)
{
    if (pe->dr == 0)
    {
        if (pe->num >= 8)
            pe->num = 0;
        else
            pe->num++;
    }
    else
    {
        if (pe->num == 19 || pe->num < 10)
            pe->num = 10;
        else
            pe->num++;
    }
   
}
/**
* @brief To jump
* @param pe the character
* @param b the background
* @param screen
* @return nothing
*/
void saut_parabolique(personne *pe,background b,SDL_Surface* screen)
{
    
    pe->saut_x=pe->saut_x+1;
    SDL_BlitSurface(b.img2, &pe->pos1, b.img, &pe->pos1);
    pe->pos1.y=pe->saut_y-((pe->pente*(pe->saut_x)*(pe->saut_x))+(pe->sommet*pe->saut_x)+pe->max_jump);
    SDL_BlitSurface(pe->tab[pe->num], NULL, b.img, &pe->pos1);
    SDL_Flip(b.img);

    /*if(pe->saut_x==20 && pe->up==2)
    {
        pe->up=0;
    }*/

}
/**
* @brief To pull u to the ground
* @param pe the character
* @param b the background
* @param screen
* @return nothing
*/
void gravite_parabolique(personne *pe,background b,SDL_Surface* screen)
{
    pe->gravite_x=pe->gravite_x+pe->gravite;
    SDL_BlitSurface(b.img2, &pe->pos1, b.img, &pe->pos1);
    pe->pos1.y=pe->gravite_y-((pe->gravite_pente*(pe->gravite_x)*(pe->gravite_x)));
    SDL_BlitSurface(pe->tab[pe->num], NULL, b.img, &pe->pos1);
    SDL_Flip(b.img);

    /*if(pe->gravite_x==0)
    {
        pe->gravite_x=-35;
        pe->right=0;
        pe->left=0;
    }*/
}

void death_animation(personne *p,background *b,background *death,int w,int h,SDL_Surface* screen,int ms)
{
    int now=SDL_GetTicks();

    if(now>death->timer+(death->niveau*ms))
    {
        death->pos2.x=death->pos2.x+w;
        SDL_BlitSurface( b->img1, &p->pos1, b->img, &p->pos1);
        SDL_BlitSurface( death->img, &death->pos2, b->img,&p->pos1);
        death->niveau++;

        if(death->niveau==17)
        {
            death->mode=0;
        }
    }
}

int arduinoWriteData(char chemin1[])
{
    char chemin[]="/dev/ttyUSB0";
    FILE*f;
    char ch;
    f=fopen(chemin,"w");
    if(f == NULL)
        return(-1);

    
        
        fclose(f);

    return(0);
}

int arduinoReadData(int *x,char chemin1[])
{
    char chemin[]="/dev/ttyUSB0";
    
    FILE*f;
    char ch;
    f=fopen(chemin,"r");

    if(f == NULL)
        return(-1);
    
    do
    {
        ch=fgetc(f);
        printf("(%c)-",ch);
        
    } while (ch!=EOF);
    
    fclose(f);

    return(0);
}

/*void manette_read(int *x)
{
    FILE* f;
    char c;
    f=fopen("manette","r");

    fscanf(f,"%d",x);

    fclose(f);

}*/
/*void saut(personne *pe)
{
    if(pe->saut==0)
    {
        pe->max_jump=pe->pos1.y-100;
    }
    if (pe->saut == 1)
    {
        if (pe->dr == 0)
        {
            pe->pos1.x += pe->v_x;
            pe->pos1.y += pe->v_y;
            pe->v_y += pe->v_grav;
        }
        else if (pe->dr == 1)
        {
            pe->pos1.x -= pe->v_x;
            pe->pos1.y += pe->v_y;
            pe->v_y += pe->v_grav;
        }
    }
    if (pe->pos1.y > 814)
    {
        pe->v_y = -6.5;
        pe->saut = 0;
    }
}*/

void auto_slow_perso1(personne *pe)
{
    if(pe->acc>0)
        {
            pe->acc-=0.001;
        }
    if(pe->acc<0)
    {
        pe->acc=0;
    }
}
void sprint_perso1(personne *pe)
{
    if(pe->acc<0.039)
        {
            pe->time=SDL_GetTicks()-pe->init_time;
            pe->acc+=0.003;
        }  
}
void liberer_perso1(personne *pe)
{
    int i;
    for (i = 0; i < 20; i++) 
    SDL_FreeSurface(pe->tab[i]);

}
void slow_perso1(personne *pe)
{
    if(pe->acc>0)
        {
            pe->acc-=0.01;
        }
    if(pe->acc<0)
    {
        pe->acc=0;
    }
}
