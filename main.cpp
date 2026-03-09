#include <raylib.h>
#include <iostream> 
#include <unistd.h>
#include "Game.h"
#include "Colors.h"
#include "SerialPort.h"
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

    Font font = LoadFontEx("/smonogram.ttf", 64, 0, 0);

    // Para comunicacion serial
    SerialPort serial;
    bool serialOk = serial.connectPort("/dev/cu.usbmodemB43A453518882", 9600);
    if(serialOk){
        cout<<"conectado al puerto"<<endl;
        usleep(2000000); // 2 segundos
    } else {
        cout<<"no conectado al puerto"<<endl;
    }

    Game game = Game();
    game.SetSerialPort(&serial);
    game.LoadHighScores();

    while(WindowShouldClose()==false){
        int serialByte = serial.readByte();

        if(serialByte != -1){

            if(serialByte == 0x69){ // i
                game.MoveBlockLeft();
            }

            if(serialByte == 0x64){ // d
                game.MoveBlockRight();
            }

            if(serialByte == 0x72){ // r
                game.RotateBlock();
            }
        }

        game.HandleInput();

        // velocidad de las figuras dependiendo del puntaje
        if (game.score <= 2000) {
            game.dropInterval = 0.25;
        }
            
        if (!game.isPaused && EventTriggered(game.dropInterval)) {
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
            DrawRectangleRounded({320, 450,172,80},0.3,6,lightBlue);
            DrawTextEx(font, "Pausa", {350, 470}, 40, 2, WHITE);
        }

        if(!game.isPaused && !game.gameOver){
            DrawRectangleRounded({320,410,172,180},0.3,6,lightBlue);
            DrawTextEx(font, "Next", {360, 425}, 40,2, WHITE);
            game.DrawNextBlock();
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
