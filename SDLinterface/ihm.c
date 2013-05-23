#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>

int main( int argc, char **argv ){
  SDL_Init(SDL_INIT_JOYSTICK);                                          // Demarre SDL
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

  IPaddress ip;		/* Server address */
  TCPsocket sd;		/* Socket descriptor */
  int quit, len;
  char buffer[512];
 
  /* Simple parameter checking */
  if (argc < 3)
    {
      fprintf(stderr, "Usage: %s host port\n", argv[0]);
      exit(EXIT_FAILURE);
    }
 
  if (SDLNet_Init() < 0)
    {
      fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
      exit(EXIT_FAILURE);
    }
 
  /* Resolve the host we are connecting to */
  if (SDLNet_ResolveHost(&ip, argv[1], atoi(argv[2])) < 0)
    {
      fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
      exit(EXIT_FAILURE);
    }
 
  /* Open a connection with the IP provided (listen on the host's port) */
  if (!(sd = SDLNet_TCP_Open(&ip)))
    {
      fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
      exit(EXIT_FAILURE);
    }
   

  while (keepgoing)  {
  /********************** Boucle Infinie ********************************/
    /* Check for events */
    while(SDL_PollEvent(&event)) { /* Loop until there are no events left on the queue */
      switch(event.type) {         /* Process the appropriate event type */
      case SDL_JOYAXISMOTION:
	/*Valable au moins pour l'Xbox controler*/
	switch(event.jaxis.axis){
	case 0: // droite - gauche pad(s) gauche
	  if(event.jaxis.value/10000 > 0)
	    buffer="D";
	  else 
	    if(event.jaxis.value/10000 < 0)
	      buffer="Q";
	    else
	      buffer="B";
	  break;
	case 1: // haut - bas pad(s) gauche
	  if(event.jaxis.value/10000 > 0)
	    buffer="Z";
	  else 
	    if(event.jaxis.value/10000 < 0)
	      buffer="S";
	    else
	      buffer="B";
	  break;
	default:
	  buffer="B";
	  break;
	}	
	len = strlen(buffer) + 1;
	if (SDLNet_TCP_Send(sd, (void *)buffer, len) < len)
	  {
	    fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
	    exit(EXIT_FAILURE);
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
  SDLNet_TCP_Close(sd);
  SDL_Quit();    //ferme SDL
  return EXIT_SUCCESS;
}
