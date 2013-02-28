#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


int main( void ){
  SDL_Init(SDL_INIT_VIDEO);                                          // Demarre SDL

  SDL_Surface * screen = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE);  //  Sauvegarde Surface Fond d'ecran
  SDL_Rect r = {0,0,screen->w,screen->h};                              //  Rectangle de fond d'écran
  SDL_Rect pt = {320,240,5,5};                                         //  Rectangle de petit point
  
  int keepgoing = 1;                                                   //  controle de boucle "infini"
  SDL_Event event;                                                   // Charge les events


  while (keepgoing)  {
  /************************************** Boucle Infinie ***************************************/
    /*Refresh window*/
    SDL_FillRect( screen , &r , SDL_MapRGB( screen->format ,255,255,255));     // Rafraichit le fond d'ecran
    SDL_FillRect( screen , &pt , SDL_MapRGB (screen->format , 0 , 0 , 0 ));    // Rafraichit le point
    SDL_Flip( screen );                                                      // Recharge l'image sur l'écran

    /* Check for events */
    while(SDL_PollEvent(&event)) { /* Loop until there are no events left on the queue */
      switch(event.type) {         /* Process the appropriate event type */
      case SDL_KEYDOWN:         /* Handle a KEYDOWN event */
	switch(event.key.keysym.sym){
	case SDLK_RIGHT:
	  pt.x+=5;
	  break;
	case SDLK_LEFT:
	  pt.x-=5;
	  break;
	case SDLK_UP:
	  pt.y-=5;
	  break;
	case SDLK_DOWN:
	  pt.y+=5;
	  break;
	default:
	  break;
	}
	break;
      case SDL_QUIT:
	keepgoing=0;
	break;
      default: /* Report an unhandled event */
	break;
      }
      //      SDL_BlitSurface(  ,  ,  ,  );
    }
  /*******************************************************************************************/
  }


  SDL_Quit();    //ferme SDL
  return 0;
}
