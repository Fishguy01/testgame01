#include <raylib.h>
#include <iostream> 
using namespace std;

int main()
{
    const float lateral = 1000;
    const float high = 750;
    

    Vector2 mouse = GetMousePosition();

    InitWindow ( lateral, high, "testt file");
    SetTargetFPS(30);

    float centerX = lateral / 2.0f;
    float centerY = high / 2.0f;

    float xmenu = 600;
    float ymenu = 75;
    Rectangle menu = { centerX - xmenu /2, centerY - ymenu /2, xmenu, ymenu };
    
    while ( !WindowShouldClose() )
    {

        if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ) 
        {
            cout << "Mouse position: " << mouse.x << ", " << mouse.y << endl;
        }
        BeginDrawing();

        DrawRectangleRec( menu, RED);
        ClearBackground(BLACK);
        DrawText ("NOME DEL GIOCO", centerX - xmenu /2, 100, 50, WHITE );
        DrawText ("START", centerX - xmenu /2, centerY - ymenu /2 + 15, 50, WHITE );
        EndDrawing();
    }

    CloseWindow();

    return 0;
}