#pragma once
#include <raylib.h>
#include <unordered_map>
#include <iostream>
#include "Player.h"

struct The_Camera {
    float Sizex = 100,
          Sizey = 100;

    float Positionx = GetScreenWidth() /2.f,
          Positiony = GetScreenHeight() /2.f;

    float xdir,
          ydir;

    void followProtagonist ( The_Protagonist& Protagonist, float deltaT ) {

    float Distancex = - Sizex - Positionx + Protagonist.Sizex + Protagonist.Positionx;
    float Distancey = - Sizey - Positiony + Protagonist.Sizey + Protagonist.Positiony;

        float xVelocity = Distancex *5;
        float yVelocity = Distancey *5;


        if ( Distancex != 0 ) {
            xdir = 1.f;
        }
        else 
            xdir = 0;

        if ( Distancex != 0 ) {
            ydir = 1.f;
        }
        else 
            ydir = 0;

            
        Positionx +=  xdir *xVelocity *deltaT;
        Positiony +=  ydir *yVelocity *deltaT;
    }

};
