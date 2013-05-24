#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


int main( void ){
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);                                          // Demarre SDL

  SDL_Surface * screen = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE);  //  Sauvegarde Surface Fond d'ecran
  SDL_Rect r = {0,0,screen->w,screen->h};                              //  Rectangle de fond d'écran
  SDL_Rect pt = {320,240,5,5};                                         //  Rectangle de petit point
  
  int keepgoing = 1;                                                   //  controle de boucle "infini"
  SDL_Event event;                                                   // Charge les events

  /*  Charge le joystick  */
  SDL_Joystick * joy;
  for (int i = 0 ; i < SDL_NumJoysticks() ; i++ ){
    joy=SDL_JoystickOpen(i);
    printf("Detecté joystick %d\n", i );
    printf("Nom:\t%s\n", SDL_JoystickName(i));
    printf("Nombre d'axes :\t%d\n",SDL_JoystickNumAxes(joy));
  }

  printf("current number of joystick : %d\n", SDL_NumJoysticks());
  

  while (keepgoing)  {
  /************************************** Boucle Infinie ***************************************/
    /*Refresh window*/
    SDL_FillRect( screen , &r , SDL_MapRGB( screen->format ,255,255,255));     // Rafraichit le fond d'ecran
    SDL_FillRect( screen , &pt , SDL_MapRGB (screen->format , 0 , 0 , 0 ));    // Rafraichit le point
    SDL_Flip( screen );                                                      // Recharge l'image sur l'écran

    /* Check for events */
    while(SDL_PollEvent(&event)) { /* Loop until there are no events left on the queue */
      switch(event.type) {         /* Process the appropriate event type */
      case SDL_JOYAXISMOTION:
	/*Valable au moins pour l'Xbox controler*/
	switch(event.jaxis.axis){
	case 0: // droite - gauche pad(s) gauche
	  pt.x+=event.jaxis.value/10000;
	  if(event.jaxis.value/10000>0)
	    fprintf(stderr,"Commande : Droite\n");
	  else 
	    if(event.jaxis.value/10000<0)
	      fprintf(stderr,"Commande : Gauche\n");
	    else
	      fprintf(stderr,"Commande : Pas Bouger\n");
	  break;
	case 1: // haut - bas pad(s) gauche
	  pt.y+=event.jaxis.value/10000;
	  if(event.jaxis.value/10000>0)
	    fprintf(stderr,"Commande : Bas\n");
	  else 
	    if(event.jaxis.value/10000<0)
	      fprintf(stderr,"Commande : Haut\n");
	    else
	      fprintf(stderr,"Commande : Pas Bouger\n");
	  break;
	case 2: // gachette gauche
	  break;
	case 3: // droite - gauche pad droit
	  break;
	case 4: // haut - bas pad droit
	  break;
	case 5: // gachette droite
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
    }
  /*******************************************************************************************/
  }
  SDL_Quit();    //ferme SDL
  return 0;
}
