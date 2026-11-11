#pragma once 

#include <raylib.h>
#include "Player.h"

struct The_Enemy {

    float Sizex = 100.f,
          Sizey = 100.f;

    float Positionx = 500.f,
          Positiony = 300.f;

    float dir = 1.f;
    float xvelocity = 20.f ;

    int stuntime = 0;
    int maxtstun = 10;

    float deltaT = 0;
    float Falling = 0.f;
    float Gravity = 983.f;
    int jump = 0;

    int health = 100;
    int healthcurrent = health;
    bool healtshow = false;
    Color StatusColor = YELLOW;

    bool follownow = false;

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

    Rectangle HealthBar (){
        float barlenght = 225;
        float barwidth;
        float percent;

        percent = float(( 100 * healthcurrent ) / health );
        barwidth = ( barlenght * percent ) /100;

        return {
            GetScreenWidth() - 25 - barwidth,
            35, 
            barwidth, 
            30
        };
    }

    void Update( The_Protagonist& Protagonist, float deltaT ){
        if ( fabsf(( Protagonist.Positionx + Protagonist.Sizex ) - Positionx - Sizex ) > 400 ){
            if ( Protagonist.Positionx > Positionx ){
                dir = -1.f; 
            }
            else {
                dir = 1.f;
            }

            Positionx += dir *xvelocity *deltaT;
        }
    }
};
