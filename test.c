#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "background.h"
#include "enigme_image.h"
#include "image.h"
#include "text.h"
#include "Settings.h"
#include "string.h"


/**
* @file test.c
* @brief Testing Program.
* @author Unfinished Legacy
* @version 0.1
* @date Apr 22, 2022
*
* fonction main
*
*/


int main(int argc, char *argv[])
{
   int x=0,Q=0,C=0,S=0,P=0,h=0,v=128,p=0,partage=0,start,button=2;
   
   char chemin1[2000];
   
   scrolling scroll,scroll1;

   char coortext[10],volume[4],num,compteur[10];

   SDL_Event event,open_settings,move_bg;

   SDL_Surface* fenetre=NULL;

   image bg,play,quit,settings,credits,paper,plus,minus,circle,game;

   text t,vol,fullscreen,name;
   text txt_enigme;

   background test,door,door1,torch,pillar;
   background block1,block2,block3,block4,block5,block6,block7,block8,block9;
   background spike;
   background ledge;
   background death;
   background restart;
   background launch;

   collision obstacle,ground,box;

   int now=0,before=0,interval=33;

   perso personnage,personnage1;

   animation running,standing;

   Uint8 *keystates=SDL_GetKeyState(NULL);

   monkey monkeys;
   
   enigme barrels;

   personne pe,per;

   Uint32 dt;
    
   Uint32 t_prev;

   Ennemi enemy;

   SDL_Rect* pixels=allocate_pixels();

   //init Link with arduino
   //system("stty -F /dev/ttyUSB0 9600 -parenb cs8 -cstopb");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    TTF_Init();
    srand (time(NULL));
    Mix_Music *musics;
    Mix_Chunk *son=NULL;
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
    musics=Mix_LoadMUS("Audio/wowclassic.mp3");
    Mix_PlayMusic(musics,-1);
    son=Mix_LoadWAV("Audio/click.wav");
    if(son==NULL)
    {
       printf("Failed to load : %s ",Mix_GetError());
    }
    fenetre=SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);

    SDL_Rect pospos;
    pospos.x=1750;
    pospos.y=1000;
    pospos.w=170;
    pospos.h=80;

    //Initialisation de l'ennemi
    initEnnemi(&enemy);

    //Initialisation de l'enigme
    init_enigme(&barrels,&monkeys);

    //Initialisation des personnage
    initperso(&pe,fenetre);
    initperso(&per,fenetre);
    init_perso(&personnage1,150,700,"Settings/minus.png");

    //Initialisation des cameras
    init_scroll(&scroll,10,0);
    init_scroll(&scroll1,10,0);

    //Initialisation des backgrounds
    initBack(&test,0,0,"background/test.jpg",NULL,NULL);
    init_mask(&test,"background/mask.jpg",fenetre);
    add_background_pos(&test,2,0,300,1000,600);
    add_background_pos(&test,3,960,0,960,1080);

    initBack(&door,900,700,"animation/door.png",NULL,NULL);
    init_animation(&door,"animation/door.png",0,0,121,240);

    initBack(&door1,1275,980,"animation/door.png",NULL,NULL);
    init_animation(&door1,"animation/door.png",0,0,121,235);

    initBack(&torch,200,600,"background/torch.png",NULL,NULL);
    init_animation(&torch,"background/torch.png",0,0,50,124);

    initBack(&death,0,0,"death_animation/h.png",NULL,NULL);
    init_animation(&death,"death_animation/h.png",0,0,48,100);

    initBack(&restart,410,0,"background/restart.png",NULL,NULL);
    init_restart(&restart,0,0,1099,95);

    initBack(&pillar,3500,180,"background/PILLAR_SPIKES_SPRITE.png",NULL,NULL);
    init_animation(&pillar,"background/PILLAR_SPIKES_SPRITE.png",0,0,300,1000);
    init_mask(&pillar,"background/PILLAR_MASK_SPRITE.png",fenetre);

    initBack(&ledge,6600,200,"background/LEDGE.png",NULL,NULL);
    init_animation(&ledge,"background/LEDGE.png",0,0,75,58);
    init_mask(&ledge,"background/LEDGE_MASK.png",fenetre);
    
    init_launch(&launch);
    
    //Initialisation des blocks
    initBack(&block1,1400,1000,"background/BLOCKS.png",NULL,NULL);
    init_animation(&block1,"background/BLOCKS.png",0,0,75,58);
    init_mask(&block1,"background/block_mask.png",fenetre);
    add_background_pos(&block1,3,1405,1020,65,38);

    initBack(&block2,1450,800,"background/BLOCKS.png",NULL,NULL);
    init_animation(&block2,"background/BLOCKS.png",0,0,75,58);
    init_mask(&block2,"background/block_mask.png",fenetre);
    add_background_pos(&block2,3,1455,820,65,38);

    initBack(&block3,1400,500,"background/BLOCKS.png",NULL,NULL);
    init_animation(&block3,"background/BLOCKS.png",0,0,75,58);
    init_mask(&block3,"background/block_mask.png",fenetre);
    add_background_pos(&block3,3,1405,520,65,38);

    initBack(&block4,3700,500,"background/BLOCKS.png",NULL,NULL);
    init_animation(&block4,"background/BLOCKS.png",0,0,75,58);
    init_mask(&block4,"background/block_mask.png",fenetre);
    add_background_pos(&block4,3,3700,520,65,38);

    initBack(&block5,4700,800,"background/BLOCKS.png",NULL,NULL);
    init_animation(&block5,"background/BLOCKS.png",0,0,75,58);
    init_mask(&block5,"background/block_mask.png",fenetre);
    add_background_pos(&block5,3,4700,820,65,38);

    initBack(&block6,6700,800,"background/BLOCKS.png",NULL,NULL);
    init_animation(&block6,"background/BLOCKS.png",0,0,75,58);
    init_mask(&block6,"background/block_mask.png",fenetre);
    add_background_pos(&block6,3,6700,820,65,38);

    initBack(&block7,6350,920,"background/BLOCKS.png",NULL,NULL);
    init_animation(&block7,"background/BLOCKS.png",0,0,75,58);
    init_mask(&block7,"background/block_mask.png",fenetre);
    add_background_pos(&block7,3,6450,940,65,38);

    initBack(&spike,4615,157,"background/SPIKE_SPRITE.png",NULL,NULL);
    init_animation(&spike,"background/SPIKE_SPRITE.png",0,0,60,88);
    init_mask(&spike,"background/SPIKE_MASK.png",fenetre);
    add_background_pos(&spike,3,4615,157,60,88);

    //Initialisation des obstacles
    init_obstacle(&test,&obstacle,"background/obstacle.png",3500,1100);
    


    //Initialisation du menu
    initBackground(&bg,"background/background.jpg");
    SDL_BlitSurface(bg.img,NULL,fenetre,&bg.pos1);
    menu_button(&play,"Menu/PLAY_DESELECTED.png",200,150,0,0);
    SDL_BlitSurface(play.img,NULL,fenetre,&play.pos1);
    menu_button(&settings,"Menu/SETTINGS_DESELECTED.png",200,350,0,0);
    SDL_BlitSurface(settings.img,NULL,fenetre,&settings.pos1);
    menu_button(&credits,"Menu/CREDITS_DESELECTED.png",200,550,0,0);
    SDL_BlitSurface(credits.img,NULL,fenetre,&credits.pos1);
    menu_button(&quit,"Menu/QUIT_DESELECTED.png",200,750,0,0);
    SDL_BlitSurface(quit.img,NULL,fenetre,&quit.pos1);


    add_pos(&paper,3,1155,350,45,35);
    add_pos(&paper,2,300,200,45,35);


    //Initialisation des textes
    sprintf(volume,"%d",(int)(Mix_VolumeMusic(-1)/1.28));
    init_text(&vol,"Settings/text.ttf",volume,30,1163,360,0,0,0);
    
    init_text(&fullscreen,"Settings/text.ttf","Appuyez sur F pour basculer en plein ecran",30,970,520,0,0,0);

    init_text(&name,"Settings/text.ttf","unfinished legacy",50,1500,10,255,50,50);
    SDL_BlitSurface(name.txt,NULL,fenetre,&name.postext);

    t.fonttext=TTF_OpenFont("Settings/text.ttf",50);
    t.fontcolor.r=255;
    t.fontcolor.g=255;
    t.fontcolor.b=255;
    sprintf(compteur,"%d/5",barrels.score);
    init_text(&txt_enigme,"Settings/text.ttf",compteur,100,960,590,255,255,255);
    
    SDL_Flip(fenetre);
    while (1)
    {
       t_prev=SDL_GetTicks();

       if(pe.pos1.x>4285 && pe.pos1.x<4400 && pe.pos1.y<140 && barrels.done==0 && barrels.launch==0)
       {
          enigme_start(&launch,fenetre);
          barrels.launch=1;
          h=2;
       }

       if(barrels.score==5)
       {
          barrels.done=1;
          h=1;
       }
        if(h==2)
            {
               if(monkeys.status==0)
               {
                  if(monkeys.enig_lvl==0)
                  {
                     afficher_enigme(barrels,fenetre);
                     monkeys.enig_lvl=1;
                     monkeys.random=rand()%3000 +1000;
                     monkeys.enig_start=SDL_GetTicks()+monkeys.random;
                     monkeys.monkey_number=rand()%5 +1;
                     read_monkey(&monkeys);
                  }
                  monkeys.timer=SDL_GetTicks()-(50*(monkeys.niveau));
               }
               monkey_pop(barrels,&monkeys,fenetre);
            }

       if(h==1)
         {
            //FPS
            now=SDL_GetTicks();
               if(now-before<interval)
               {
                  SDL_Delay(interval-(now-before));
               }
               //FPS 

                  //printf("(%d)--[%d]--//--",pe.pos1.x,pe.pos1.y);
                    
                    if(keystates[SDLK_r])
                     {
                        //
                        SDL_BlitSurface(test.img2,NULL,test.img,&test.pos1);
                        //
                        restart.niveau=0;
                        //
                        death.mode=1;
                        death.niveau=0;
                        //
                        pe.pos1.x=200;
                        pe.pos1.y=1120;
                        pe.life=1;
                        //
                        scroll.camera.x=0;
                        scroll.camera.y=480;
                        
                     }

                  collisionPP1(&pe,obstacle,test);
                  color_fix(&pe,test,pixels);
                  dmg_detection(&pe,test,pixels);
                  if(pe.up==0)
                  {
                     fall_check(&pe,test,pixels);
                  }
                     if(pe.life!=-1)
                     {
                        if(death.mode==1)
                        {
                           if(death.niveau==0)
                           {
                              //printf("oijqsd");
                              death.pos2.x=-48;
                              death.niveau=1;
                              death.timer=SDL_GetTicks();
                           }
                        
                           death_animation(&pe,&test,&death,48,100,fenetre,150);
                        }
                        
                     }

                     if(door.niveau==0)
                     {
                           door.niveau=1;
                           door.timer=SDL_GetTicks();
                           torch.timer=SDL_GetTicks();
                           
                     }
                        afficherBack(test,fenetre,scroll);
                              continuous_animation(&test,&torch,"background/torch.png",0,35,87,fenetre,11,1,50);
                             // continuous_animation(&test,&door,"animation/door.png",0,121,240,fenetre,4,1,150);
                   
                              //afficherperso(&pe,test);
                           
                        if(pe.pos1.x>door1.pos1.x-50)
                        {      
                           if(door1.mode!=0)
                           {
                              if(door1.niveau==0)
                              {
                                 door1.niveau=1;
                                 door1.timer=SDL_GetTicks();
                              }
                              object_animation(&test,&door1,"animation/door.png",0,121,240,fenetre,4,start);
                 
                           }
                        }

                              if(pillar.niveau==0)
                              {
                                 block1.niveau=1;
                                 block1.timer=SDL_GetTicks();
                                 block2.niveau=1;
                                 block2.timer=SDL_GetTicks();
                                 block3.niveau=1;
                                 block3.timer=SDL_GetTicks();
                                 block4.niveau=1;
                                 block4.timer=SDL_GetTicks();
                                 block5.niveau=1;
                                 block5.timer=SDL_GetTicks();
                                 block6.niveau=1;
                                 block6.timer=SDL_GetTicks();
                                 block7.niveau=1;
                                 block7.timer=SDL_GetTicks();
                                 pillar.niveau=1;
                                 pillar.timer=SDL_GetTicks();
                                 ledge.niveau=1;
                                 ledge.timer=SDL_GetTicks();
                                 spike.niveau=1;
                                 spike.timer=SDL_GetTicks();
                              }
                              if(pe.life==-1)
                              {
                                 blocks_animation(&test,&spike,&obstacle,"background/SPIKE_SPRITE.png",4615,0,60,88,fenetre,5,50,1000);
                                 pillar_animation(&test,&pillar,&obstacle,"background/PILLAR_SPIKES_SPRITE.png",3500,0,300,1000,fenetre,16,150,500);
                              }
                           //pillar_animation(&test,&pillar,&obstacle,"background/PILLAR_SPIKES_SPRITE.png",3500,0,300,1000,fenetre,16,150,500);
                           blocks_animation(&test,&block1,&obstacle,"background/BLOCKS.png",1450,0,75,58,fenetre,8,50,500);
                           blocks_animation(&test,&block2,&obstacle,"background/BLOCKS.png",1400,0,75,58,fenetre,8,50,700);
                           blocks_animation(&test,&block3,&obstacle,"background/BLOCKS.png",1450,0,75,58,fenetre,8,50,1000);
                           blocks_animation(&test,&block4,&obstacle,"background/BLOCKS.png",3900,0,75,58,fenetre,8,50,1000);
                           blocks_animation(&test,&block5,&obstacle,"background/BLOCKS.png",5300,0,75,58,fenetre,8,50,1000);                           
                           blocks_animation(&test,&block6,&obstacle,"background/BLOCKS.png",6700,0,75,58,fenetre,8,50,1000);
                           blocks_animation(&test,&block7,&obstacle,"background/BLOCKS.png",6450,0,75,58,fenetre,8,50,1500);
                           moving_ledge(&test,&ledge,251,102,10);


                           if(pe.life!=-1)
                           {
                              
                              if(restart.niveau==0)
                              {
                                 restart.niveau=1;
                                 restart.timer=SDL_GetTicks();
                              }
                              restart_animation(&test,&restart,scroll,5,200,100);
                           }
                           /*blocks_animation(&test,&block8,&obstacle,"background/BLOCKS.png",3900,0,75,58,fenetre,8,50,1000);
                           blocks_animation(&test,&block9,&obstacle,"background/BLOCKS.png",3900,0,75,58,fenetre,8,50,1000);*/


                           /*animerEnnemi(&enemy);
            
                           deplacer(&enemy,test);*/
            
            
            
            /*arduinoReadData(&button,chemin1);
            arduinoWriteData(chemin1);*/
//            manette_read(&button);
            
            //printf("(%d)--",button);

            if(!keystates[SDLK_UP])
            {
               if((pe.up==1 || pe.up==2) && pe.jump_ready==0)
               {
                  pe.sommet=pe.saut_x;
                  pe.max_jump=pe.max_jump-(pe.sommet*pe.saut_x);
               }
               pe.jump_ready=1;
            }
            if(keystates[SDLK_UP] && pe.jump_ready==1 && pe.life==-1)
            {
               
               if(pe.up==0)
               {
                  pe.sommet=0;
                  pe.max_jump=200;
                  pe.jump_ready=0;
                  pe.up=1;
                  if(pe.drop_jump==1)
                  {
                     pe.up=2;
                     pe.drop_jump=0;
                  }
                  pe.saut_y=pe.pos1.y;
               }else if(pe.up==1)
               {
                  pe.sommet=0;
                  pe.max_jump=200;
                  pe.jump_ready=0;
                  pe.up=2;
                  pe.saut_y=pe.pos1.y;
                  pe.saut_x=-20;
               }
            }
            if((pe.up==1 || pe.up==2)&& pe.life==-1)
            {
               saut_parabolique(&pe,test,fenetre);
            }else if(pe.right==1 && pe.left==1 && pe.up==0 && pe.life==-1)
            {
               if(pe.fall==0)
               {
                  pe.drop_jump=1;
                  pe.gravite_y=pe.pos1.y;
                  pe.fall=1;
               }
               gravite_parabolique(&pe,test,fenetre);
            }
            if((keystates[SDLK_LSHIFT] && keystates[SDLK_RIGHT]) || (keystates[SDLK_LSHIFT] && keystates[SDLK_LEFT]))
           {
              if(test.scroll==0)
              {
                 test.scroll=1;
                 pe.init_time=SDL_GetTicks();
              }
              sprint_perso1(&pe);
           }
            if(keystates[SDLK_LCTRL])
           {
              slow_perso1(&pe);
           }
            if((keystates[SDLK_RIGHT] || button==1) && pe.life==-1 && pe.collision!=3)
            {  
               pe.dep = 1;
               pe.dr = 0;
              if(!keystates[SDLK_LSHIFT])
              {
                 auto_slow_perso1(&pe);
              }
              //afficherperso(&pe,test);
              deplacerperso(&pe, dt,test);
              animerperso(&pe);
            
 
            }
            if((keystates[SDLK_LEFT] || button==0)&& pe.life==-1 && pe.collision!=1)
            {
              pe.dep = 0;
             pe.dr = 1;
              if(!keystates[SDLK_LSHIFT])
              {
                 auto_slow_perso1(&pe);
              }
              //afficherperso(&pe,test);
               deplacerperso(&pe, dt,test);             
               animerperso(&pe);
               
            }
            if(pe.life==-1)
            {
               afficherperso(&pe,test);
            }
            
            scrolling_perso1(test,&scroll,&pe,keystates);  
            collisionPP1(&pe,obstacle,test);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if(p==1)
            {
               if(partage==0)
               {
                  
                  partage_ecran(&scroll,&scroll1);
                  partage=1;
               }
                  collisionPP1(&per,obstacle,test);
                  color_fix(&per,test,pixels);
                  dmg_detection(&per,test,pixels);
                  if(per.up==0)
                  {
                     fall_check(&per,test,pixels);
                  }
                     if(per.life!=-1)
                     {
                        if(death.mode==1)
                        {
                           if(death.niveau==0)
                           {
                              //printf("oijqsd");
                              death.pos2.x=-48;
                              death.niveau=1;
                              death.timer=SDL_GetTicks();
                           }
                        
                           death_animation(&per,&test,&death,48,100,fenetre,150);
                        }
                        
                     }
            //afficherBack(test,fenetre,scroll1);
            afficher_perso2(test,fenetre,scroll1);


               if(keystates[SDLK_LSHIFT])
                     {
                        //
                        SDL_BlitSurface(test.img2,NULL,test.img,&test.pos1);
                        //
                        restart.niveau=0;
                        //
                        death.mode=1;
                        death.niveau=0;
                        //
                        per.pos1.x=200;
                        per.pos1.y=1120;
                        per.life=1;
                        //
                        scroll1.camera.x=0;
                        scroll1.camera.y=480;
                        
                     }

             if(!keystates[SDLK_w])
            {
               if((per.up==1 || per.up==2) && per.jump_ready==0)
               {
                  per.sommet=per.saut_x;
                  per.max_jump=per.max_jump-(per.sommet*per.saut_x);
               }
               per.jump_ready=1;
            }
            if(keystates[SDLK_w] && per.jump_ready==1 && per.life==-1)
            {
               
               if(per.up==0)
               {
                  per.sommet=0;
                  per.max_jump=200;
                  per.jump_ready=0;
                  per.up=1;
                  if(per.drop_jump==1)
                  {
                     per.up=2;
                     per.drop_jump=0;
                  }
                  per.saut_y=per.pos1.y;
               }else if(per.up==1)
               {
                  per.sommet=0;
                  per.max_jump=200;
                  per.jump_ready=0;
                  per.up=2;
                  per.saut_y=per.pos1.y;
                  per.saut_x=-20;
               }
            }
            if((per.up==1 || per.up==2)&& per.life==-1)
            {
               saut_parabolique(&per,test,fenetre);
            }else if(per.right==1 && per.left==1 && per.up==0 && per.life==-1)
            {
               if(per.fall==0)
               {
                  per.drop_jump=1;
                  per.gravite_y=per.pos1.y;
                  per.fall=1;
               }
               gravite_parabolique(&per,test,fenetre);
            }
            if((keystates[SDLK_LSHIFT] && keystates[SDLK_d]) || (keystates[SDLK_LSHIFT] && keystates[SDLK_a]))
           {
              if(test.scroll==0)
              {
                 test.scroll=1;
                 per.init_time=SDL_GetTicks();
              }
              sprint_perso1(&per);
           }
            if(keystates[SDLK_LCTRL])
           {
              slow_perso1(&per);
           }
            if((keystates[SDLK_d] || button==1) && per.life==-1 && per.collision!=3)
            {  
               per.dep = 1;
               per.dr = 0;
              if(!keystates[SDLK_LSHIFT])
              {
                 auto_slow_perso1(&per);
              }
              //afficherperso(&pe,test);
              deplacerperso(&per, dt,test);
              animerperso(&per);
            
 
            }
            if((keystates[SDLK_a] || button==0)&& per.life==-1 && per.collision!=1)
            {
              per.dep = 0;
              per.dr = 1;
              if(!keystates[SDLK_LSHIFT])
              {
                 auto_slow_perso1(&per);
              }
              //afficherperso(&pe,test);
               deplacerperso(&per, dt,test);             
               animerperso(&per);
               
            }
            if(per.life==-1)
            {
               afficherperso(&per,test);
            }
            
            scrolling_perso1(test,&scroll1,&per,keystates);  
            collisionPP1(&per,obstacle,test);

         }

         
         dt = SDL_GetTicks() - t_prev;    
         SDL_Flip(fenetre);
         before=now;
         }
           
        SDL_PollEvent(&event);

        if(event.type==SDL_QUIT)
        {break;}
        else if(event.type==SDL_KEYDOWN)
        {
           
           if (event.key.keysym.sym==SDLK_f)
           {
              if(h==0)
              {
                 afficher_deselected(&quit,&bg,fenetre,&Q,"Menu/QUIT_DESELECTED.png");
                 afficher_deselected(&credits,&bg,fenetre,&C,"Menu/CREDITS_DESELECTED.png"); 
                 afficher_deselected(&settings,&bg,fenetre,&S,"Menu/SETTINGS_DESELECTED.png");
                 afficher_deselected(&play,&bg,fenetre,&P,"Menu/PLAY_DESELECTED.png");
              }
              SDL_WM_ToggleFullScreen(fenetre);
           }
           else if(event.key.keysym.sym==SDLK_p)
            {
              p=1;
            }
           else if(event.key.keysym.sym==SDLK_h)
           {
              if(h==1)
              {
                 h=2;
              }
           }
           else if(event.key.keysym.sym==SDLK_j)
           {
              if(h==2)
              {
                 h=1;
              }
           }
            else if(event.key.keysym.sym==SDLK_ESCAPE)
               {break;}
            }
            else if(event.type==SDL_MOUSEBUTTONDOWN)
            {
               if((h==2) && (monkeys.status!=0) && (event.button.button==SDL_BUTTON_LEFT) && (monkeys.pos_img.x+monkeys.pos_img.w>event.motion.x && event.motion.x>monkeys.pos_img.x) && (monkeys.pos_img.y+monkeys.pos_img.h>event.motion.y && event.motion.y>monkeys.pos_img.y))
               {
                  Mix_PlayChannel(-1,monkeys.sound,0);
                  barrels.score++;
                  sprintf(compteur,"%d/5",barrels.score);
                  txt_enigme.txt=TTF_RenderText_Solid(txt_enigme.fonttext,compteur,txt_enigme.fontcolor);
                  SDL_BlitSurface(txt_enigme.txt,NULL,fenetre,&txt_enigme.postext);
                  //SDL_BlitSurface(personnage.img,NULL,fenetre,&monkeys.pos_img);
                  SDL_Flip(fenetre);
                  SDL_Delay(2000);
                  afficher_enigme(barrels,fenetre);
                  
                  //SDL_BlitSurface(barrels.img,&monkeys.pos_img,fenetre,&monkeys.pos_img);
               }
             if((h==0) && (event.button.button==SDL_BUTTON_LEFT) && (play.pos1.x+438>event.motion.x && event.motion.x>play.pos1.x) && (play.pos1.y+140>event.motion.y && event.motion.y>play.pos1.y))
               {
                Mix_PlayChannel(-1,son,0);
                h=1;
               }
             else if((h==0) && (event.button.button==SDL_BUTTON_LEFT) && (settings.pos1.x+438>event.motion.x && event.motion.x>settings.pos1.x) && (settings.pos1.y+140>event.motion.y && event.motion.y>settings.pos1.y))
             {
                Mix_PlayChannel(-1,son,0);
                if(x==0)
                {
                   menu_button(&paper,"Settings/paper.png",900,200,0,0);
                   menu_button(&plus,"Settings/plus.png",1253,335,0,0);
                   menu_button(&minus,"Settings/minus.png",1050,360,0,0);
                   menu_button(&circle,"Settings/circle.png",1127,322,0,0);
                   afficher_settings(fenetre,&x,paper,circle,plus,minus,vol,fullscreen);
                   printf("%d",x);
                }
                else if(x==1)
                {
                   close_settings(plus,minus,paper,circle,bg,fenetre,&x);
                }

             }
             else if((h==0) && (event.button.button==SDL_BUTTON_LEFT) && (credits.pos1.x+438>event.motion.x && event.motion.x>credits.pos1.x) && (credits.pos1.y+140>event.motion.y && event.motion.y>credits.pos1.y))
             {
                Mix_PlayChannel(-1,son,0);

             }
             else if((h==0) && (event.button.button==SDL_BUTTON_LEFT) && (quit.pos1.x+438>event.motion.x && event.motion.x>quit.pos1.x) && (quit.pos1.y+140>event.motion.y && event.motion.y>quit.pos1.y))
             {
                break;
             }
             else if((x==1) && (event.button.button==SDL_BUTTON_LEFT) && (minus.pos1.x+50>event.motion.x && event.motion.x>minus.pos1.x) && (minus.pos1.y+50>event.motion.y && event.motion.y>minus.pos1.y))
             {
                diminuer_vol(&vol,volume,&v,&paper,fenetre);
             }
             else if((x==1) && (event.button.button==SDL_BUTTON_LEFT) && (plus.pos1.x+50>event.motion.x && event.motion.x>plus.pos1.x) && (plus.pos1.y+50>event.motion.y && event.motion.y>plus.pos1.y))
             {
                augmenter_vol(&vol,volume,&v,&paper,fenetre);
             }
         }

        else if((event.type==SDL_MOUSEMOTION) && (h==0))
         { 
            sprintf(coortext,"%d,%d",event.motion.x,event.motion.y);
            /*SDL_BlitSurface(bg.img,&pospos,fenetre,&pospos);
            afficher_text(t,coortext,fenetre,fenetre->w-t.txt->w-10,fenetre->h-t.txt->h,t.txt->w+10,t.txt->h);*/
            t.txt=TTF_RenderText_Solid(t.fonttext,coortext,t.fontcolor);
            t.postext.x=fenetre->w-t.txt->w-10;
            t.postext.y=fenetre->h-t.txt->h;
            t.postext.w=t.txt->w+10;
            t.postext.h=t.txt->h;
            SDL_BlitSurface(bg.img,&pospos,fenetre,&pospos);
            SDL_BlitSurface(t.txt,NULL,fenetre,&t.postext);
            SDL_UpdateRect(fenetre,pospos.x,pospos.y,pospos.w,pospos.h);
            if((quit.pos1.x+438>event.motion.x && event.motion.x>quit.pos1.x) && (quit.pos1.y+140>event.motion.y && event.motion.y>quit.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&quit,&bg,fenetre,&Q,"Menu/QUIT_SELECTED.png");
            }else if(Q==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&quit,&bg,fenetre,&Q,"Menu/QUIT_DESELECTED.png");
            }else if((credits.pos1.x+438>event.motion.x && event.motion.x>credits.pos1.x) && (credits.pos1.y+140>event.motion.y && event.motion.y>credits.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&credits,&bg,fenetre,&C,"Menu/CREDITS_SELECTED.png");
            }else if(C==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&credits,&bg,fenetre,&C,"Menu/CREDITS_DESELECTED.png");    
            }else if((settings.pos1.x+438>event.motion.x && event.motion.x>settings.pos1.x) && (settings.pos1.y+140>event.motion.y && event.motion.y>settings.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&settings,&bg,fenetre,&S,"Menu/SETTINGS_SELECTED.png");  
            }else if(S==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&settings,&bg,fenetre,&S,"Menu/SETTINGS_DESELECTED.png");  
            }else if((play.pos1.x+438>event.motion.x && event.motion.x>play.pos1.x) && (play.pos1.y+140>event.motion.y && event.motion.y>play.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&play,&bg,fenetre,&P,"Menu/PLAY_SELECTED.png");
            }else if(P==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&play,&bg,fenetre,&P,"Menu/PLAY_DESELECTED.png");
            }
         }
    }
    free(pixels);
    liberer_enigme(barrels,monkeys);
    Mix_FreeMusic(musics);
    liberer_back(test);
    liberer_back(door);
    liberer_back(door1);
    libere_collision(obstacle);
    liberer_perso(&personnage1);
    liberer_perso1(&pe);
    liberer(bg);
    liberer(play);
    liberer(settings);
    liberer(credits);
    liberer(quit);
    SDL_FreeSurface(fenetre);
    TTF_Quit;
    SDL_Quit;
    return 0;
}
