#include <raylib.h>
#include <iostream> 
#include "Game.h"
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

    Color darkBlue = {44,44,127,255};
    InitWindow(300,600, "raylib Tetris");
    SetTargetFPS(60);

    Game game = Game();

    while(WindowShouldClose()==false){

        game.HandleInput();

        if(EventTriggered(0.3)){
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkBlue);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}