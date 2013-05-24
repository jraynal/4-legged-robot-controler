#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>

#define DB(n) fprintf(stderr,#n"\n");

TCPsocket init_net(char *adresse, char *port, IPaddress *ip){
  TCPsocket sd;
  /* Simple parameter checking */
  DB(net : initialize)
  if (SDLNet_Init() < 0)
    {
      fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
      exit(EXIT_FAILURE);
    }
  DB(net : resolve host)
  printf("%s (%s)\n", adresse, port);
  /* Resolve the host we are connecting to */
  if (SDLNet_ResolveHost(ip, adresse, atoi(port) < 0))
    {
      fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
      exit(EXIT_FAILURE);
    }
 
  DB(net : Open IP)
  /* Open a connection with the IP provided (listen on the host's port) */
    if (!(sd = SDLNet_TCP_Open(ip)))
    {
      fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
      exit(EXIT_FAILURE);
    } 
  fprintf(stderr,"Connection enabled\n");
  return sd;
}

char *capture_event(char *buffer, SDL_Event event){
  fprintf(stderr,"loop : capture event\n");
  switch(event.type) {         /* Process the appropriate event type */
  case SDL_JOYAXISMOTION:
    /*Valable au moins pour l'Xbox controler*/
    switch(event.jaxis.axis){
    case 0: // droite - gauche pad(s) gauche
      if(event.jaxis.value/10000 > 0)
	buffer[0]='D';
      else 
	if(event.jaxis.value/10000 < 0)
	  buffer[0]='Q';
	else
	  buffer[0]='B';
      fprintf(stderr,"envoi : %s\n",buffer);
      break;
    case 1: // haut - bas pad(s) gauche
      if(event.jaxis.value/10000 > 0)
	buffer[0]='Z';
      else 
	if(event.jaxis.value/10000 < 0)
	  buffer[0]='S';
	else
	  buffer[0]='B';
      fprintf(stderr,"envoi : %s\n",buffer);
      break;
    default:
      buffer[0]='B';
      fprintf(stderr,"envoi : %s\n",buffer);
      break;
    }
  default:
    break;
  }
  return buffer;
}

int main( void ){
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);                      // Demarre SDL
  int keepgoing = 1;                                // Controle de boucle "infini"
  SDL_Event event;                                  // Charge les events

  IPaddress ip;		/* Server address */
  TCPsocket sd = init_net("10.0.0.1","3000",&ip);		/* Socket descriptor */
  int len;
  char buffer[512];
 

  /*  Charge le joystick  */
  SDL_Joystick * joy;
  for (int i = 0 ; i < SDL_NumJoysticks() ; i++ ){
    joy=SDL_JoystickOpen(i);
    printf("Joystick : detected %d\n", i );
    printf("Joystick : Nom:\t%s\n", SDL_JoystickName(i));
    printf("Joystick : axes :\t%d\n",SDL_JoystickNumAxes(joy));
  }
  printf("Joystick : number : %d\n", SDL_NumJoysticks());

  while (keepgoing){
    /********************** Boucle Infinie ********************************/
    /* Check for events */
    while(SDL_PollEvent(&event)) { /* Loop until there are no events left on the queue */
      capture_event(buffer, event);
      len = strlen(buffer) + 1;
      if (SDLNet_TCP_Send(sd, (void *)buffer, len) < len){
	  fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
	  exit(EXIT_FAILURE);
	}
    }
  }
  /************************************************************************/
  fprintf(stderr,"Closing connection\n");
  SDLNet_TCP_Close(sd);
  SDL_Quit();    //ferme SDL
  return EXIT_SUCCESS;
}
