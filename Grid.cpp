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
            DrawRectangle(column * cellSize+1, row * cellSize+1, cellSize-1, cellSize-1, colors[cellValue]);
        }
    }
}

bool Grid :: IsCellOutside(int row, int column){

    if(row >= 0 && row < numRows && column >= 0 && column < numCols){
        return false;
    }
    return true;
}
