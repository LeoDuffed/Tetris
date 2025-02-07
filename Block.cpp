#include "Block.h"

Block :: Block(){

    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();

}

void Block :: Draw(){

    vector<Position> tiles = cells[rotationState];
    for(Position item: tiles){
        DrawRectangle(item.column * cellSize, item.row * cellSize, cellSize - 1, cellSize - 1, colors[id]);
    }



}