#include "animation.h"
#include "engine.h"

int date; // curseur pour les anims des moteurs incrémenté dans le main
int current_anim;

void anim_load(int anim){
  current_anim=anim;
}


//renvoie un angle compris entre 0 et MAX_INT
int anim_get_pwm(uint8 eng){
  int leftpoint=date/INTERVAL;
  int rightpoint=(leftpoint+1) % NB_ECHANTILLON;
  int rightrate=date%INTERVAL;
  int leftrate=INTERVAL-rightrate;
  int leftvalue=leftrate*animation[current_anim][eng][leftpoint];
  int rightvalue=rightrate*animation[current_anim][eng][rightpoint];
  int value=(leftvalue+rightvalue)/INTERVAL;
  if (value<MIN_COUNT)
      value=MIN_COUNT;
  if (value>MAX_COUNT)
      value=MAX_COUNT;
  return value;
}


void anim_next_date(int duration){
  date+=duration;
  date%=(NB_ECHANTILLON*INTERVAL);
}
