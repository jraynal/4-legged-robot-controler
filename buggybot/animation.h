#ifndef ANIMATION_H
#define ANIMATION_H

#include "engine.h"

// Ce module doit implémenter les données importés de Blender
#define INTERVAL 5 //meme unite que la date
#define NB_ECHANTILLON 40

enum Anim {
    ANIM_WALK_FORWARD,
    ANIM_WALK_BACKWARD,
    ANIM_WALK_LEFTWARD, 
    ANIM_WALK_RIGHTWARD,
    // Ajouter des animation ici

    ////
    MAX_ANIM
};

typedef unsigned char uint8;
extern int animation[1][10][40];

// Change l'animation courrante
void anim_load(int anim);

// Renvoie l'angle d'un moteur en fonction du temps ecoule 
// depuis le dernier appel
int anim_get_pwm(uint8 eng);
//(Nico renvoie LA PWM à JR pour qu'il l'envoie au moteur)

void anim_next_date(int duration); // change le curseur date

#endif
