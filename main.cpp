#include <raylib.h>

int main(){

    InitWindow(300,600, "raylib Tetris");

    while(WindowShouldClose()==false){

        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();
}