#include <raylib.h>
#include <ctime>
#include <iostream> 

int Schermata = 0;
int ExitGame = 0;
float ProtPositionx = 500.f;
float ProtPositiony = 300.f;

float Gravity = 983.f;
float Falling = 0.f;

void MenuConfirmExit ( int centerX, int centerY )
{
    float xMenuConfirm = 300,
          yMenuConfirm = 230, 
          xBarConfirm = 265,
          yBarConfirm = 50;
    
    Rectangle MenuConfirm = { centerX - xMenuConfirm /2, centerY - yMenuConfirm /2 + 10, xMenuConfirm + 10, yMenuConfirm },
              BarConfermY = { centerX - xBarConfirm /2, centerY - yBarConfirm /2 + 10, xBarConfirm, yBarConfirm },
              BarConfermN = { centerX - xBarConfirm /2, centerY - yBarConfirm /-2 + 30, xBarConfirm, yBarConfirm };
    
    Color ExitBarColor = RED;

    Vector2 mouse = GetMousePosition ();

    bool OntheExitBar = CheckCollisionPointRec ( mouse, BarConfermY );

    int WordSize = 50;
    const char * textSpeach = "Do you want exit game?";

    if ( IsKeyPressed ( KEY_ESCAPE ))
    {
        ExitGame = 1;
        return;
    }

    if ( Schermata == 0 )
    {
        if ( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ))
        {
            if ( CheckCollisionPointRec ( mouse, BarConfermY ))
            {
                ExitGame = -1;
                return;
            }

            if ( CheckCollisionPointRec ( mouse, BarConfermN ))
            {
                ExitGame = 0;
                return;
            }
        }
    }

    if ( Schermata >= 1 )
    {
        textSpeach = "Exit level?";
        WordSize = 30;

        if ( IsMouseButtonPressed ( MOUSE_LEFT_BUTTON ))
        {
            if ( CheckCollisionPointRec ( mouse, BarConfermY ))
            {
                Schermata = 0;
                ExitGame = 0;
            }

            if ( CheckCollisionPointRec ( mouse, BarConfermN ))
            {
                ExitGame = 1;
            }

        }
    }

    BeginDrawing();

    ClearBackground(Fade (BLACK, 0.6));
    DrawRectangleRec( MenuConfirm, GRAY );

    if ( Schermata >= 1 )
    {
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

void MenuExit ( float centerX, float centerY )
{
    float xMenuExit = 250,
          yMenuExit = 200,
          xBarExit = 215,
          yBarExit = 50;

    Rectangle ExitMenu = { centerX - xMenuExit /2, centerY - yMenuExit /2, xMenuExit, yMenuExit },
              ExitBar = { centerX - xBarExit /2, centerY - yBarExit /2 + 60,  xBarExit, yBarExit };

    Color ExitBarColor;

    Vector2 mouse = GetMousePosition ();

    bool OntheExitBar = CheckCollisionPointRec ( mouse, ExitBar );

    if ( IsKeyPressed ( KEY_ESCAPE ) || Schermata == 0 )
    {
        ExitGame = 0;
        return;
    }

    if ( OntheExitBar == 1 )
        ExitBarColor = RED;
    else 
        ExitBarColor = LIGHTGRAY;

    if (IsMouseButtonReleased ( MOUSE_LEFT_BUTTON ))
        if ( CheckCollisionPointRec ( mouse, ExitBar ))
        {
            ExitGame = 2;
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

void InitialSchreeen ( float centerX, float centerY )
{

    float xmenu = 600;
    float ymenu = 75;

    Rectangle menu = { centerX - xmenu /2, centerY - ymenu /2, xmenu, ymenu };
    Rectangle ExitofGame = { 0, 0, 100, 100 };

    Color menucolor = RED;

    Vector2 mouse = GetMousePosition();

    bool PressedExit = true;
    bool Checkifontheblook = CheckCollisionPointRec ( mouse, menu );

    if ( IsMouseButtonPressed ( MOUSE_LEFT_BUTTON ))
    {
        if ( Schermata == 0 && CheckCollisionPointRec ( mouse, menu ))
        {
            Schermata = 1;
            return;
        }
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

void GamePlay ( float centerX, float centerY, float high )
{
    float ProtSizex = 100,
        ProtSizey = 100;

    static int jump = 0;
    static float xvelocity;

    Rectangle ExitofGame = { 0, 0, 100, 100 },
              Protagonist = { ProtPositionx, ProtPositiony, ProtSizex, ProtSizey },
              Enemy = { 400, 400, 400, 400 };

    Vector2 mouse = GetMousePosition();
    Vector2 Themainbox = { ProtPositionx, ProtPositiony };

    float deltaT = GetFrameTime();

    xvelocity = 10.f;

    if ( IsMouseButtonPressed ( MOUSE_LEFT_BUTTON ))
    {
        if ( CheckCollisionPointRec ( mouse, ExitofGame ))
        {
            ExitGame = 1;
            return;
        }
    }

    if ( ProtPositiony < high - ProtSizey )
    {
        Falling += Gravity * deltaT;
        ProtPositiony += Falling * deltaT;   
    }
    else
    {
        ProtPositiony = high - ProtSizey;
        deltaT = 0.f;
        jump = 0;
    }

    if ( IsKeyDown ( KEY_A )|| IsKeyPressed ( KEY_RIGHT ))
    { 
        if ( IsKeyPressed ( KEY_SPACE ) )
        {
            if ( jump < 1)
            {
                Falling = - 400.f;
                ProtPositiony -= 100.f;
                ProtPositionx -= xvelocity;
                jump++;
            }
            else if ( jump == 1 )
            {
                Falling = - 400.f;
                ProtPositiony -= 50.f;
                jump++;
            }  
        }
        else if ( IsKeyPressed ( KEY_S ))
        {
            Falling = 0.f;
            ProtPositiony += 50.f;
            ProtPositionx += 5.f;
        }
        else 
        ProtPositionx -= xvelocity;
    }
    else if ( IsKeyDown ( KEY_D ) || IsKeyPressed ( KEY_LEFT ))
    {
        if ( IsKeyPressed ( KEY_SPACE ) )
        {
            if ( jump < 1)
            {
                Falling = - 400.f;
                ProtPositiony -= 100.f;
                ProtPositionx += xvelocity;
                jump++;
            }
            else if ( jump == 1 )
            {
                Falling = - 400.f;
                ProtPositiony -= 50.f;
                jump++;
            }   
        }
        else if ( IsKeyPressed ( KEY_S ))
        {
            Falling = 0.f;
            ProtPositiony += 50.f;
            ProtPositionx += 5.f;
        }
        else 
        ProtPositionx += xvelocity;
    }
    else if ( IsKeyDown ( KEY_S ) || IsKeyPressed ( KEY_DOWN ))
    {
        ProtPositiony += (Falling * deltaT) + 20.f;   
    }
    else if ( IsKeyPressed ( KEY_W ) || IsKeyPressed ( KEY_SPACE ))
    {
        if ( jump < 1)
        {
            Falling = - 400.f;
            ProtPositiony -= 100.f;
            jump++;

            if ( IsKeyPressed ( KEY_W ) || IsKeyPressed ( KEY_SPACE ))
            {
                ProtPositiony += Falling * deltaT - xvelocity;   
            }
        }
        else if ( jump == 1 )
        {
            Falling = - 400.f;
            ProtPositiony -= 50.f;
            jump++;

            if ( IsKeyPressed ( KEY_W ) || IsKeyPressed ( KEY_SPACE ))
            {
                ProtPositiony += Falling * deltaT + xvelocity;   
            }
        }      
    }

    BeginDrawing ();

    ClearBackground ( Fade ( BLACK, 0.6f ) );
    DrawRectangleRec ( ExitofGame, RED );
    DrawRectangleRec ( Protagonist, WHITE );
    DrawRectangleRec ( Enemy, YELLOW );

    EndDrawing ();
}


int main ()
{
    const float lateral = 1000;
    const float high = 550;

    float centerX = lateral /2;
    float centerY = high /2;

    InitWindow ( lateral, high, "testt file");
    SetTargetFPS(30);

    SetExitKey( KEY_NULL );

    while ( !WindowShouldClose() )
    {
        if ( WindowShouldClose() )
        {
            ExitGame = 2;
        }

        if ( ExitGame == 2 )
            MenuConfirmExit ( centerX, centerY );
    
        else if ( ExitGame == 1 )
            MenuExit ( centerX, centerY );
                        
        else if ( ExitGame == -1 )
            break;

        else 
        {
            switch ( Schermata )
            {
                case 0:
                    InitialSchreeen ( centerX, centerY );
                    break;
                
                case 1:
                    GamePlay ( centerX, centerY, high );
                    break;
            }
        }
    }
    CloseWindow();

    return 0;
}