#include "animation.h"
#include "engine.h"

int date; // curseur pour les anims des moteurs incrémenté dans le main
int current_anim;
int anim_loop = 1;
int in_anim = 0;

void anim_load(int anim, int _loop){
  if(!in_anim) {
    current_anim=anim;
    anim_loop = _loop;
    if(!anim_loop) {
      in_anim = 1;
      date = 0;
    }
  }
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
  if(anim_loop) {
    date+=duration;
    date%=(NB_ECHANTILLON*INTERVAL);
  }
  else {
    if(date < NB_ECHANTILLON*INTERVAL)
      date+=duration;
    else
      in_anim = 0;
  }
}
