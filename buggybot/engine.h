#ifndef ENGINE_H
#define ENGINE_H

// Ce module controle les moteurs : envoie des pwm en fonction 
// des angles demandes
#define MAX_COUNT 7830
#define MIN_COUNT 1960

enum Engine {
    // patte avant gauche
    ENGINE_SHOULDER_LEFT,
    ENGINE_ARM_TOP_LEFT,
    ENGINE_ARM_MID_LEFT,
    // patte avant droite
    ENGINE_SHOULDER_RIGHT,
    ENGINE_ARM_TOP_RIGHT,
    ENGINE_ARM_MID_RIGHT,
    // patte arriere gauche
    ENGINE_LEG_TOP_LEFT,
    ENGINE_LEG_MID_LEFT,
    // patte arriere droite
    ENGINE_LEG_TOP_RIGHT,
    ENGINE_LEG_MID_RIGHT,
    // Ajouter des moteurs ici

    ////
    MAX_ENGINE
};
/*
struct Engine {
    int pin;
    enum Engine eng;
};

struct Engine* engine_begin(struct Engine* list);
struct Engine* engine_next(struct Engine* list, struct Engine* i);
bool engine_is_end(struct Engine* list, struct Engine* i);
*/


#endif
