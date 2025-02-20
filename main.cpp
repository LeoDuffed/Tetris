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

    InitWindow(500,620, "Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("/dCurved Square.ttf", 64, 0, 0);

    Game game = Game();

    while(WindowShouldClose()==false){

        game.LoadHighScores();

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

        if(game.gameOver){
            DrawRectangleRounded({315,440,182,100},0.3,6,lightBlue);
            DrawTextEx(font, "GAME", {350, 455}, 40, 2, WHITE);
            DrawTextEx(font, "OVER", {350, 495}, 40, 2, WHITE);

        }

        if(game.isPaused){
            DrawRectangleRounded({315, 450,182,80},0.3,6,lightBlue);
            DrawTextEx(font, "En Pausa", {320, 470}, 40, 2, WHITE);
        }

        if(!game.isPaused && !game.gameOver){
            DrawRectangleRounded({315,410,182,180},0.3,6,lightBlue);
            DrawTextEx(font, "Next", {360, 420}, 40,2, WHITE);
        }

        DrawTextEx(font, "SCORE", {345, 110}, 38, 2, WHITE);

        DrawRectangleRounded({320,155,170,60},0.3,6,lightBlue);
        char scoreText[10];
        snprintf(scoreText, sizeof(scoreText), "%d", game.score); 
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2); 

        float textPosX = 300 + (170 - textSize.x) / 2;

        DrawTextEx(font, scoreText, {textPosX, 170}, 38, 2, WHITE);

        DrawTextEx(font, "Top",{380, 250},28,2, WHITE);

        vector<pair<int, string>> scores = game.getHighScores();
        for (int i = 0; i < scores.size(); i++) {
            char scoreEntry[50];
            snprintf(scoreEntry, sizeof(scoreEntry), "%d. %s: %d", i + 1, scores[i].second.c_str(), scores[i].first);
            DrawTextEx(font, scoreEntry, (Vector2){320.0f, static_cast<float>(300 + i * 30)}, 24, 2, WHITE);
        }         

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    
}