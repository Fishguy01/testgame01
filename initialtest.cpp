#include <raylib.h>
#include <iostream> 
using namespace std;

int main()
{
    const float lateral = 1000;
    const float high = 750;

    InitWindow ( lateral, high, "testt file");
    SetTargetFPS(30);

    float centerX = lateral / 2.0f;
    float centerY = high / 2.0f;

    float xmenu = 600;
    float ymenu = 75;

    Rectangle menu = { centerX - xmenu /2, centerY - ymenu /2, xmenu, ymenu };
    Rectangle ExitofGame = { 0, 0, 100, 100 };

    Color menucolor = RED;

    int Schermata = 0;
    
    while ( !WindowShouldClose() )
    {
        bool PressedExit = true;

        Vector2 mouse = GetMousePosition();

        bool Checkifontheblook = CheckCollisionPointRec ( mouse, menu );

        if ( IsMouseButtonPressed ( MOUSE_LEFT_BUTTON ))
        {
            if ( Schermata == 0 && CheckCollisionPointRec ( mouse, menu ))
            {
                Schermata = 1;
            }
            
            if ( Schermata == 1 && CheckCollisionPointRec ( mouse, ExitofGame))
            {
                Schermata = 0;
            }
        }
        
        if ( Checkifontheblook )
        {
            menucolor = GRAY;
        }
        else 
        {
            menucolor = RED;
        }

        BeginDrawing();

        if ( Schermata == 0 )
        {
            DrawRectangleRec( menu, menucolor );
            ClearBackground( BLACK );
            DrawText ("NOME DEL GIOCO", centerX - xmenu /2, 100, 50, WHITE );
            DrawText ("START", centerX - xmenu /2, centerY - ymenu /2 + 15, 50, WHITE );
        } 

        else if ( Schermata == 1 )
        {
            ClearBackground ( BLACK );
            DrawRectangleRec ( ExitofGame, RED );
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}