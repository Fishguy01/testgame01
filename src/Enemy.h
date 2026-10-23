#pragma once 

#include <raylib.h>
#include "Player.h"
struct The_Enemy {

    float Sizex = 100.f,
          Sizey = 100.f;

    float Positionx = 500.f,
          Positiony = 300.f;

    float xvelocity = 10.f ;

    int stuntime = 0;
    int maxtstun = 10;

    float deltaT = 0;
    float Falling = 0.f;
    float Gravity = 983.f;
    int jump = 0;

    int health = 100;
    Color StatusColor = YELLOW;

    void The_Fall ( float deltaT ) {
        Falling += deltaT * Gravity;
        Positiony += Falling * deltaT;
    }

    void HitFlashFrame () {
        if ( stuntime > maxtstun ){
            StatusColor = YELLOW;
            return;
        }
            
        StatusColor = PURPLE;
        stuntime++;
    }
};
