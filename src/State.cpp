#include "Player.h"
#include "Enemy.h"
#include "Gamestate.h"
#include "camera.h"
#include <raylib.h>
#include <iostream>

void InitialSchreeen ( float centerX, float centerY, GameShow& state ) {

    Vector2 mouse = GetMousePosition ();

    float xmenu = 600;
    float ymenu = 75;

    Rectangle menu = { centerX - xmenu /2, centerY - ymenu /2, xmenu, ymenu };
    Rectangle ExitofGame = { 0, 0, 100, 100 };

    Color menucolor = RED;

    bool PressedExit = true;
    bool Checkifontheblook = CheckCollisionPointRec ( mouse, menu );
    

    if ( IsMouseButtonPressed ( MOUSE_LEFT_BUTTON ))
    {
        if ( CheckCollisionPointRec ( mouse, menu ))
        {
            state = GameShow::GamePlay;   
            return;
        }
    }

    if ( IsKeyPressed ( KEY_ENTER ))
    {
            state = GameShow::GamePlay;   
            return;
    }
    if ( Checkifontheblook )
        menucolor = GRAY;
    else 
        menucolor = RED;

    BeginDrawing();

    ClearBackground( BLACK );
    DrawRectangleRec( menu, menucolor );
    DrawText ("NOME DEL GIOCO", centerX - xmenu /2, 100, 50, WHITE );
    DrawText ("START", centerX - xmenu /2, centerY - ymenu /2 + 15, 50, WHITE );

    EndDrawing ();
}

void GamePlay ( float centerX, float centerY, float high, float lateral, The_Protagonist& Protagonist, The_Enemy& Enemy, GameShow& state, ExitState& Exit, The_Camera& Camera ) {

    Vector2 mouse = GetMousePosition ();
   
    Rectangle ExitofGame = { 0, 0, 100, 100 },
              DrawProtagonist = { Protagonist.Positionx, Protagonist.Positiony, Protagonist.Sizex, Protagonist.Sizey },
              Drawenemy = { Enemy.Positionx, Enemy.Positiony, Enemy.Sizex, Enemy.Sizey };
     
    Vector2 Themainbox = { Protagonist.Positionx, Protagonist.Positiony };

    float deltaT = GetFrameTime();

    bool onPlatform = ( Protagonist.Positionx >= 400 + Protagonist.Sizex && Protagonist.Positionx <= 800 + Protagonist.Sizey );

    float platformFloor = high - Protagonist.Sizey  - 400;
    float groundFloor = high - Protagonist.Sizey ;

    float Gravity = 983.f;

    bool hasHit;

    Camera2D camera = { 0 };
    camera.target = ( Vector2 ){ Camera.Positionx + ( Camera.Sizex /2.f ), Camera.Positiony };
    camera.offset = ( Vector2 ){ GetScreenWidth() /2.f, GetScreenHeight() /2.f };
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;
    
    if ( Protagonist.Positiony >= groundFloor ) {
        Protagonist.Positiony = groundFloor;
        Protagonist.deltaT = 0;
        Protagonist.jump = 0;
    }
    else {
        Protagonist.The_Fall ( deltaT );
    }

    
    if ( Enemy.Positiony >= groundFloor ) {
        Enemy.Positiony = groundFloor;
        Enemy.deltaT = 0;
        Enemy.jump = 0;
    }
    else {
        Enemy.The_Fall ( deltaT );
    }



    if ( IsMouseButtonPressed ( MOUSE_LEFT_BUTTON ))
    {
        if ( CheckCollisionPointRec ( mouse, ExitofGame ))
        {
            Exit = ExitState::MenuExit;   
            return;
        }
    }

    Protagonist.Update( deltaT );    

    Camera.followProtagonist( Protagonist, deltaT );

        // use in case for debbugin
        //std:: cout << Protagonist.AttackDamage() << std::endl;
    //Enemy
    
    if ( Enemy.health <= 10 ) {
        Enemy.Sizey = 0.f;
        Enemy.Sizex = 0.f;
    }

    if ( Protagonist.IsAttacking() && hasHit == false && CheckCollisionRecs ( Protagonist.HitBoxofAttack(), Drawenemy )) {
        Enemy.stuntime = 0;
        Enemy.health -= Protagonist.AttackDamage();
        std:: cout << Protagonist.AttackDamage() << std::endl;
        hasHit = true;
    }

    Enemy.HitFlashFrame();

    //Attack
    
    const AttackData test = Protagonist.AttackTable.at ( Protagonist.currentAttack);

    if ( IsKeyPressed ( KEY_B )) {
        Protagonist.SelectAttack ( AttackType :: lAttack );
        hasHit = false;
    }
   
    if ( IsKeyPressed ( KEY_N )) {
        Protagonist.SelectAttack ( AttackType :: HAttack );
        hasHit = false;
    }

    if ( IsKeyPressed ( KEY_B ) && IsKeyPressed ( KEY_LEFT_SHIFT ) ) {
        Protagonist.SelectAttack ( AttackType :: MovlAttack );
        hasHit = false; 
    }


    Protagonist.StartAttack ();
    

        BeginDrawing ();
    
    ClearBackground ( Fade ( BLACK, 0.6f ) );

        BeginMode2D ( camera );

    DrawRectangleRec ( DrawProtagonist , WHITE );
    if ( Protagonist.IsHitBoxesActive () ){
        DrawRectangleRec ( Protagonist.HitBoxofAttack(), RED );
    }


    DrawRectangle ( Camera.Positionx, Camera.Positiony, Camera.Sizex, Camera.Sizey, BLUE ); //Camera
    DrawLine( -10000, groundFloor + Protagonist.Sizey, 100000, groundFloor + Protagonist.Sizey,  LIGHTGRAY );


    DrawRectangleRec ( Drawenemy, Enemy.StatusColor );

        EndMode2D ();


    DrawRectangleRec ( ExitofGame, RED );
        EndDrawing ();
}

void MenuConfirmExit ( int centerX, int centerY, The_Protagonist Protagonist, bool ExitConf , GameShow& state, ExitState& Exit  ) {
    float xMenuConfirm = 300,
          yMenuConfirm = 230, 
          xBarConfirm = 265,
          yBarConfirm = 50;

    Vector2 mouse = GetMousePosition();

    Rectangle MenuConfirm = { centerX - xMenuConfirm /2, centerY - yMenuConfirm /2 + 10, xMenuConfirm + 10, yMenuConfirm },
              BarConfermY = { centerX - xBarConfirm /2, centerY - yBarConfirm /2 + 10, xBarConfirm, yBarConfirm },
              BarConfermN = { centerX - xBarConfirm /2, centerY - yBarConfirm /-2 + 30, xBarConfirm, yBarConfirm };
    
    Color ExitBarColor = RED;

    bool OntheExitBar = CheckCollisionPointRec ( mouse, BarConfermY );

    int WordSize = 50;
    const char * textSpeach = "Do you want exit game?";

    if ( IsKeyPressed ( KEY_ESCAPE ))
    {
       Exit = ExitState :: MenuExit;
        return;
    }

    if ( state == GameShow :: InitialSchreen )
    {
        if ( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ))
        {
            if ( CheckCollisionPointRec ( mouse, BarConfermY ))
            {
                ExitConf  = true;
                return;
            }

            if ( CheckCollisionPointRec ( mouse, BarConfermN ))
            {
                state = GameShow :: InitialSchreen;
                return;
            }
        }
    }

    if ( state != GameShow :: InitialSchreen  )
    {
        textSpeach = "Exit level?";
        WordSize = 30;

        if ( IsMouseButtonPressed ( MOUSE_LEFT_BUTTON ))
        {
            if ( CheckCollisionPointRec ( mouse, BarConfermY ))
            {
                state = GameShow :: InitialSchreen; 
                Exit = ExitState :: Null;
            }

            if ( CheckCollisionPointRec ( mouse, BarConfermN ))
            {
                Exit = ExitState :: MenuExit;
            }

        }
    }

    BeginDrawing();

    ClearBackground(Fade (BLACK, 0.6));
    DrawRectangleRec( MenuConfirm, GRAY );

    if ( state != GameShow :: InitialSchreen ){
        DrawText ( "X Leaving the level may reset ", centerX - xMenuConfirm /2 + 10, centerY - yMenuConfirm /2 + 40, 17, WHITE );
        DrawText ( "from your last checkpoint", centerX - xMenuConfirm /2 + 10, centerY - yMenuConfirm /2 + 52, 17, WHITE );
    }

    DrawText ( textSpeach, centerX - xMenuConfirm /2 + 10, centerY - yMenuConfirm /2 + 15, WordSize, WHITE );


    DrawRectangleRec( BarConfermY, ExitBarColor );
    DrawText ( "Yes",  centerX - xBarConfirm /2, centerY - yBarConfirm /2 + 10, 50, WHITE );
    DrawRectangleRec ( BarConfermN, BLUE );
    DrawText ( "No", centerX - xBarConfirm /2, centerY + yBarConfirm /2 + 30, 50, WHITE );

    EndDrawing();
}

void MenuExit ( float centerX, float centerY , GameShow& state, ExitState& Exit  ) {

   Vector2 mouse = GetMousePosition();

    float xMenuExit = 250,
          yMenuExit = 200,
          xBarExit = 215,
          yBarExit = 50;

    Rectangle ExitMenu = { centerX - xMenuExit /2, centerY - yMenuExit /2, xMenuExit, yMenuExit },
              ExitBar = { centerX - xBarExit /2, centerY - yBarExit /2 + 60,  xBarExit, yBarExit };

    Color ExitBarColor;

    bool OntheExitBar = CheckCollisionPointRec ( mouse, ExitBar );

    if ( IsKeyPressed ( KEY_ESCAPE ) || state == GameShow :: InitialSchreen )
    {
        Exit = ExitState :: Null;
        return;
    }

    if ( OntheExitBar == 1 )
        ExitBarColor = RED;
    else 
        ExitBarColor = LIGHTGRAY;

    if (IsMouseButtonReleased ( MOUSE_LEFT_BUTTON ))
        if ( CheckCollisionPointRec ( mouse, ExitBar ))
        {
            Exit = ExitState :: MenuConfirmExit;
            return;
        }

    BeginDrawing();
    
    
    ClearBackground(BLACK);
    DrawRectangleRec( ExitMenu, GRAY );
    DrawText ( "Pause", centerX - xMenuExit /2 + 10, centerY - yMenuExit /2, 50, WHITE );
    DrawRectangleRec( ExitBar, ExitBarColor );
    DrawText ( "Exit",  centerX - xBarExit /2 + 10, centerY - yBarExit /2 + 60, 50, WHITE );

    EndDrawing();
}
