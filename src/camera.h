#pragma once
#include <raylib.h>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include "Player.h"
#include "Enemy.h"

struct The_Camera {
    float Sizex = 100,
          Sizey = 100;

    float Positionx = GetScreenWidth() /2.f,
          Positiony = GetScreenHeight() /2.f;

    float xdir,
          ydir;

    Camera2D camera = { 
        .offset = ( Vector2 ){ GetScreenWidth() /2.f, GetScreenHeight() /2.f },
        .target = ( Vector2 ){ Positionx + ( Sizex /2.f ), Positiony },
        .rotation = 0.0f,
        .zoom = 0.7f,   // 0.7
    };
 
        
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

        if ( camera.zoom < 0.7f ){
            camera.zoom += 0.01f + deltaT;
        }
        if ( camera.zoom > 0.7f ){
            camera.zoom -= 0.01f + deltaT;
        }
        camera.offset = ( Vector2 ){ GetScreenWidth() /2.f, GetScreenHeight() /2.f };
        camera.target = ( Vector2 ){ Positionx + ( Sizex /2.f ), Positiony };
        
 
    }
    
    void EnemyFocus ( The_Protagonist& Protagonist, The_Enemy& Enemy, float deltaT ) {

        float Distancex = - Sizex - Positionx + ( Protagonist.Sizex + Protagonist.Positionx + Enemy.Sizex + Enemy.Positionx ) /2;
        float Distancey = - Sizey - Positiony + ( Protagonist.Sizey + Protagonist.Positiony + Enemy.Sizey + Enemy.Positiony ) /2;
        // fabsf = valore assoluto
        float Redistace = fabsf(( Protagonist.Sizex + Protagonist.Positionx ) - Enemy.Sizex - Enemy.Positionx );
        static float MaxStance = GetScreenWidth() /1.f;
       
        float maxzoom = 0.45f;
        float maxdistance = 1800.f;

        float minzoom = 0.7f;
        float Mindistance = 1800.f;


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

        camera.offset = ( Vector2 ){ GetScreenWidth() /2.f, GetScreenHeight() /2.f };
        camera.target = ( Vector2 ){ Positionx + ( Sizex /2.f ), Positiony };
        
        float t = Clamp( Redistace /maxdistance, 0.f, 1.0f );
        float desiredZoom = minzoom + ( maxzoom - minzoom ) *t; 

        camera.zoom += ( desiredZoom - camera.zoom ) * ( 1.f - expf( -3.f * deltaT ));

        if ( maxdistance < Redistace ){
            MaxStance = GetScreenWidth() /1.f;
            Enemy.follownow = false;
            Enemy.healtshow = false;
        }

    }

    float Clamp ( float input, float minimun, float max ){
        if ( max < input ) {
            return max;
        }
        else if ( minimun > input ) {
            return minimun;
        }
        else {
            return input;
        }
    }

};
