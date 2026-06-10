#include <raylib.h>
#include <iostream> 
using namespace std;

int main()
{
    const int lateral = 1000;
    const int high = 1000;

    InitWindow ( lateral, high, "testt file");

    SetTargetFPS(30);
    
    while ( !WindowShouldClose() )
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText ("NOME DEL GIOCO", 100, 100, 50, WHITE );
        EndDrawing();
    }

    CloseWindow();

    return 0;
}