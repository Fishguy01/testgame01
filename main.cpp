#include <raylib.h>
#include <ctime>
#include <iostream> 
#include "src/Gamestate.h"
#include "src/Player.h"
#include "src/State.cpp"
#include "src/Enemy.h"
#include "src/camera.h"

int main () {

    GameShow state;
    ExitState Exit;

    //const float y = GetScreenHeight();
    //const float x = GetScreenWidth();
    
    const float width = 1000;
    const float high = 550;

    float centerX = width /2;
    float centerY = high /2;

    InitWindow ( width, high, "videogame");
    SetTargetFPS( 30 );

    SetExitKey( KEY_NULL ); 

    state = GameShow :: InitialSchreen;
    Exit = ExitState :: Null;
    The_Protagonist Protagonist;
    The_Enemy Enemy;
    The_Camera Camera;
  
    bool ExitConf = false; 

    while ( !WindowShouldClose() ) {
        if (  ExitConf == true ) 
            goto Getout;
        

        if ( Exit == ExitState :: MenuExit )
            MenuExit ( centerX, centerY, state, Exit );

        else if ( Exit == ExitState :: MenuConfirmExit )
            MenuConfirmExit ( centerX,  centerY, Protagonist, ExitConf, state, Exit );

        else
            switch ( state ) {
                case GameShow :: InitialSchreen:
                    InitialSchreeen ( centerX, centerY, state );
                    break;

                case GameShow :: GamePlay:
                    GamePlay ( centerX, centerY, high, width, Protagonist, Enemy, state, Exit, Camera);
                    break;
            }
    }
    Getout:
    CloseWindow();

    return 0;
}
