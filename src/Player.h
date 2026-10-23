#pragma once
#include <raylib.h>
#include <unordered_map>
#include <iostream>

enum class AttackType {
    None,
    lAttack,
    HAttack,
    MovlAttack,
    MovHAttack,
};

struct AttackData {
    int initial;
    int active;
    int recovery;
    Rectangle hitboxOffset;
    float chargespeed;
    int Damage; 
};

struct The_Protagonist {

    float Sizex = 100,
          Sizey = 100;

    float Positionx = 500.f,
          Positiony = 300.f;

    float dir = 1;
    float xvelocity;
    //speed 
    float walk = 500.f;
    float running = 1200.f;
    float dash = 3000.f;

    float deltaT = 0;
    float Falling = 0.f;
    float Gravity = 983.f;
    int jump = 0;

    int health = 100;
     

    void The_Fall ( float deltaT ) {
         Positiony += Falling * deltaT;
         Falling += deltaT * Gravity;
    } 

    //movement
    void Update ( float deltaT ) {
        bool IsMoving;

        if ( IsKeyPressed ( KEY_LEFT_SHIFT )) {
            xvelocity = dash;
        }
        else if ( IsKeyDown ( KEY_LEFT_SHIFT )) {
            xvelocity = running;
        }
        else {
            xvelocity = walk;
        }
        
        if ( IsKeyDown ( KEY_A )|| IsKeyDown ( KEY_RIGHT )) { 
            dir = -1;
            IsMoving = true;
        }
        else if ( IsKeyDown ( KEY_D ) || IsKeyDown ( KEY_LEFT )) {
            dir = 1;
            IsMoving = true;
        }
        else 
            IsMoving = false;
            
        if ( jump < 1 && IsKeyPressed ( KEY_SPACE ) ) {
            Falling = -400.f;
            Positiony -= 100.f;
            jump++;
        }
        else if ( jump == 1 && IsKeyPressed ( KEY_SPACE )) {
            Falling = -400.f;
            Positiony -= 50.f;
            jump++;
        }  
        

        if ( IsKeyDown ( KEY_S )) {
                Falling = 0.f;
                Positiony += 50.f;
                xvelocity = xvelocity /5;
        }

        AttackSpeed ();
        
        if ( IsMoving == true )
            Positionx +=  dir *xvelocity *deltaT;
    }

    ///Attacks

    int AttackFrame = 0; 
   
    Rectangle fAttack1; 

    AttackType currentAttack = AttackType::None;
  
                    //is form me of futre: if dont remeber is from line 11
        //example: AttackType::lAttack 1)charge 2)TimeofAttack 3)RetreatAtt 4){Hitbox} 5)Damage 6) speedofwalking 


    const std:: unordered_map < AttackType, AttackData > AttackTable {
        { AttackType::lAttack, { 4, 7, 3, { -70, 25, 70, 25 }, 5, 5 }},
        { AttackType::HAttack, { 8, 9, 5, { -50, 20, 70, 40 }, 10, 15 }},
        { AttackType::MovlAttack, { 1, 5, 4, { -90, 35, 90, 35 }, 7, 30 }},

        { AttackType::None, { 0, 0, 0, { 0 }, 0 }}

    };

    int AttackDamage () {
        if ( currentAttack == AttackType::None )
            return 0;
        
        return AttackTable.at ( currentAttack ).Damage;
    }
    
    bool IsAttacking () {
        return currentAttack != AttackType::None;
    }

    bool IsHitBoxesActive () {
        if ( currentAttack == AttackType :: None )
        return false;
        
        const AttackData& data = AttackTable.at ( currentAttack );
        return AttackFrame >= data.initial 
            && AttackFrame <  data.initial + data.active;
   }

    Rectangle HitBoxofAttack () {
        const AttackData& data = AttackTable.at ( currentAttack );

        float x;

        if ( dir == -1 ) 
            x = Positionx + data.hitboxOffset.x;
        else 
            x = Positionx + Sizex;

        return { x, 
                 Positiony + data.hitboxOffset.y,
                 data.hitboxOffset.width,
                 data.hitboxOffset.height
        };
    }

    void SelectAttack ( AttackType selected ) {
        if ( currentAttack != AttackType :: None )
           return;
           
        
        currentAttack = selected;
        AttackFrame = 0;
    }

    void StartAttack () {
        if ( currentAttack ==  AttackType :: None )
            return;

        AttackFrame++;
        const AttackData& data = AttackTable.at( currentAttack );
        int TotFrame = data.active + data.initial + data.recovery;

        if ( AttackFrame > TotFrame ) {
            currentAttack = AttackType :: None;
        }
    }

    void AttackSpeed () {
        if ( currentAttack == AttackType :: None ) 
            return;

        const AttackData& data = AttackTable.at ( currentAttack );

        if ( AttackFrame <= data.initial && AttackFrame >= 0 ) 
            xvelocity = xvelocity /data.chargespeed;

        std :: cout << xvelocity << std:: endl;
    }
};


