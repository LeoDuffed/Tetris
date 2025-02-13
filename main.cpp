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

        if(!game.isPaused && EventTriggered(0.3)){
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkBlue);

        DrawTextEx(font, "T", {323, 40}, 38, 2, RED);
        DrawTextEx(font, "E", {353, 40}, 38, 2, ORANGE);
        DrawTextEx(font, "T", {380, 40}, 38, 2, YELLOW);
        DrawTextEx(font, "R", {410, 40}, 38, 2, GREEN);
        DrawTextEx(font, "I", {440, 40}, 38, 2, cyan);
        DrawTextEx(font, "S", {455, 40}, 38, 2, PURPLE);

        DrawTextEx(font, "Score", {350, 165}, 38, 2, WHITE);

        if(game.gameOver){
            DrawTextEx(font, "GAME", {350, 430}, 40, 2, WHITE);
            DrawTextEx(font, "OVER", {350, 470}, 40, 2, WHITE);

        }

        if(game.isPaused){
            DrawTextEx(font, "En Pausa", {30, 430}, 40, 2, WHITE);
        }

        DrawRectangleRounded({320,210,170,60},0.3,6,lightBlue);
        char scoreText[10];
        snprintf(scoreText, sizeof(scoreText), "%d", game.score); 
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2); 

        float textPosX = 300 + (170 - textSize.x) / 2;

        DrawTextEx(font, scoreText, {textPosX, 225}, 38, 2, WHITE);
        

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    
}