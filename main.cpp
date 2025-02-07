#include <raylib.h>
#include <iostream> 
#include "Grid.h"

using namespace std;

int main(){

    Color darkBlue = {44,44,127,255};
    InitWindow(300,600, "raylib Tetris");
    SetTargetFPS(60);

    Grid grid = Grid();
    grid.Print();

    while(WindowShouldClose()==false){

        BeginDrawing();
        ClearBackground(darkBlue);

        EndDrawing();
    }

    CloseWindow();
}