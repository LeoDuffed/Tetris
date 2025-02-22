#include "Grid.h"
#include "Colors.h"
#include <iostream>
using namespace std;

Grid :: Grid(){

    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Inicializar();
    colors = GetCellColors();

}


Grid :: Grid (int numRows, int numCols, int cellSize){
    this -> numRows = numRows;
    this -> numCols = numCols;
    this -> cellSize = cellSize;

}

void Grid :: setNumRows(int numRows){
    this -> numRows = numRows;
}
void Grid :: setNumCols(int numCols){
    this -> numCols = numCols;
}
void Grid :: setCellSize(int cellSize){
    this -> cellSize = cellSize;
}

int Grid :: getNumRows(){
    return numRows;
}
int Grid :: getNumCols(){
    return numCols;
}
int Grid :: getCellSize(){
    return cellSize;
}

void Grid :: Inicializar(){
    for(int row = 0; row < numRows; row++){
        for(int column = 0; column < numCols; column++){

            grid[row][column] = 0;
        }
    }
}

void Grid :: Print(){
    for(int row = 0; row < numRows; row++){
        for(int column = 0; column < numCols; column++){
            cout << grid[row][column] << " ";
        }
        cout << endl;
    }
}

void Grid :: Draw(){
    for(int row = 0; row < numRows; row++){
        for(int column = 0; column < numCols; column++){
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize+11, row * cellSize+11, cellSize-1, cellSize-1, colors[cellValue]);
        }
    }
}

bool Grid :: IsCellOutside(int row, int column){

    if(row >= 0 && row < numRows && column >= 0 && column < numCols){
        return false;
    }
    return true;

}

bool Grid :: IsCellEmpty(int row, int column){
    
    if(grid[row][column] == 0){
        return true;
    }
    return false;

}

bool Grid :: IsRowFull(int row){

    for(int column = 0; column < numCols; column++){
        if(grid[row][column] == 0){
            return false;
        }
    }
    return true;

}

void Grid :: ClearRow(int row){

    for(int column = 0; column < numCols; column++){
        grid[row][column] = 0;
    }

}
    
void Grid :: MoveRowDown(int row, int numRows){

    for(int column = 0; column < numCols; column++){
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }

}

int Grid :: ClearFullRow(){
    
    int completed = 0;

    for(int row = numRows-1; row >= 0; row--){
        if(IsRowFull(row)){
            AnimatedLineClear(row);
            ClearRow(row);
            completed++;

        } else if(completed > 0){
            MoveRowDown(row, completed);

        }
    }

    return completed;
}

void Grid :: AnimatedLineClear(int row){
    for(int i = 0; i < 4; i++){
        for(int column = 0; column < numCols; column++){
            grid[row][column] = (i % 2 == 0) ? 0 : 7;

        }

        Draw();
        EndDrawing();
        BeginDrawing();
        WaitTime(0.03);

    }

}
