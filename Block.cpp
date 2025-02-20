#include "Block.h"

Block :: Block(){

    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;

}

void Block :: Draw(int offsetX, int offsetY){

    vector<Position> tiles = GetCellPositions();
    for(Position item: tiles){
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }

}

void Block:: Move(int rows, int columns){

    rowOffset += rows;
    columnOffset += columns;
}

vector<Position> Block :: GetCellPositions(){

    vector <Position> tiles = cells[rotationState];
    vector <Position> movedTiles;
    for(Position item: tiles){
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos);
    }

    return movedTiles;
     
}

void Block :: Rotate(){

    rotationState++;
    if(rotationState == (int)cells.size()){
        rotationState = 0;
    }
    
}

void Block :: UnduRotation(){
    rotationState --;
    if(rotationState == -1){
        rotationState = cells.size() - 1;
    }

}