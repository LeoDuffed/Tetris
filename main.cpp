#include <raylib.h>
#include <iostream> 
#include "Game.h"
#include "Colors.h"
using namespace std;

double lastUpdateTime = 0;

bool EventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main(){

    InitWindow(500,620, "raylib Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while(WindowShouldClose()==false){

        game.HandleInput();

        if(EventTriggered(0.3)){
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {355, 65}, 38, 2, WHITE);
        DrawRectangleRounded({325,110,170,60},0.3,6,lightBlue);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}