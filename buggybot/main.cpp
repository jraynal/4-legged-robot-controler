// Interactive Test Session for LeafLabs Maple
// Copyright (c) 2010 LeafLabs LLC.
//
// Useful for testing Maple features and troubleshooting.
// Communicates over SerialUSB.

#include <string.h>
#include <wirish/wirish.h>

#include <math.h>

#include "engine.h"
#include "animation.h"
//#include "anim_data.cpp"
//#include "animation.cpp"

// ASCII escape character
#define ESC       ((uint8)27)

// Default USART baud rate
#define BAUD     9600

// Pin PWM

void init_all_timers(uint16 prescale);
void enable_usarts(void);
//Global Variables
uint8 servoi;
//int rate=2950;

////Version "NORMALE"
//int enginePin[MAX_ENGINE] = {3,4,5,8,9,10,11,25,16,15};
////Version "DEBUG_1"
int enginePin[MAX_ENGINE] = {3,4,5,9,8,10,11,25,16,15};
////Version "DEBUG_2"
//int enginePin[MAX_ENGINE] = {3,4,5,9,8,10,16,15,11,25};

// Commands

// -- setup() and loop() ------------------------------------------------------

void setup() {
    //Le anim_load devra etre appele quand bouton presse
    anim_load(ANIM_WALK_FORWARD);
    /*
    for(int i = 0 ; i < 41 ; i++) {
        for(int j = 0 ; j < MAX_ENGINE ; j++) {
            animation[0][j][i] = 
              ((animation[0][j][i] - 1900) * 1) + 1900;
        }

        //animation[0][1][i] -= 1000;
        animation[0][8][i] -= 500;
        animation[0][9][i] -= 1000;
        animation[0][7][i] -= 1000;
        animation[0][7][i] = MAX_COUNT + MIN_COUNT - animation[0][7][i];

        //animation[0][6][i] -= 1000;
        //animation[0][6][i] = MAX_COUNT + MIN_COUNT - animation[0][6][i];

        animation[0][5][i] -= 500;
        animation[0][5][i] = MAX_COUNT + MIN_COUNT - animation[0][5][i];
    
        animation[0][4][i] += 500;
        //animation[0][4][i] = MAX_COUNT + MIN_COUNT - animation[0][4][i];
    }
    */
    // Set up the LED to blink
    pinMode(BOARD_LED_PIN, OUTPUT);
              
    // Start up the serial ports
    Serial3.begin(921600);
    SerialUSB.begin();

    // Initialisation pin servo
    
    //disable_usarts();
    init_all_timers(21);

    for (servoi=0;servoi<MAX_ENGINE;servoi++){
        pinMode(enginePin[servoi], PWM);
        pwmWrite(enginePin[servoi], 4000);
    }
}

int counter = 0;

char buffer[2048];
unsigned int cursor = 0;

void loop () {
    
  // test improbable par Nico
  static char anim = 'B';

  if (Serial3.available()){
    switch (SerialUSB.read()){
    case 'B':
      anim = 'B';
      break;
    case 'Z':
      anim = 'Z';
      break;
    case 'Q':
      anim = 'Q';
      break;
    case 'S':
      anim = 'S';
      break;
    case 'D':
      anim = 'D';
      break;
    }
  }
  
  uint8 n_eng;
  if (anim == 'Z'){
    for (n_eng=0;n_eng<MAX_ENGINE;n_eng++) {
      pwmWrite(enginePin[n_eng], anim_get_pwm(n_eng));
      //pwmWrite(enginePin[n_eng], MAX_COUNT_TEST);
    }
  }

  
  
  delay(50);
  anim_next_date(4);
  
  
  toggleLED();
  /*
    while (!SerialUSB.available()) {
    for (servoi=0;servoi<10;servoi++){
    if (rate > 6881)
    rate = 2950;
    rate += 20;
    if (boardUsesPin(servoi))
    continue;
    pwmWrite(boardPWMPins[servoi], rate);
    }
    delay(200);
    }
  */
  /*
    cursor = 0;
    while(Serial3.available() && cursor < sizeof(buffer)) {
    buffer[cursor++] = Serial3.read();
    }
    
    if(cursor > 0) {
    SerialUSB.write(buffer, cursor);
    }
    
    while(SerialUSB.available()) {
    Serial3.write(SerialUSB.read());
    }
  */
  
}
/*
static uint16 init_all_timers_prescale = 0;

static void set_prescale(timer_dev *dev) {
    timer_set_prescaler(dev, init_all_timers_prescale);
}
*/

#define SERVOS_TIMERS_PRESCALE 24
#define SERVOS_TIMERS_OVERFLOW 60000

void initTimer(uint8_t i)
{
    HardwareTimer timer(i);
    timer.pause();
    timer.setPrescaleFactor(SERVOS_TIMERS_PRESCALE);
    timer.setOverflow(SERVOS_TIMERS_OVERFLOW);
    timer.refresh();
    timer.resume();
}

void init_all_timers(uint16 prescale) {
    //init_all_timers_prescale = prescale;
    //timer_foreach(set_prescale);
    initTimer(1);
    initTimer(2);
    initTimer(3);
    initTimer(4);
}


// -- premain() and main() ----------------------------------------------------

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (1) {
        loop();
    }
    return 0;
}
