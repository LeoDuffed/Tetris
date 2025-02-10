#ifndef Grid_H
#define Grid_H
#pragma once
#include <vector>
#include <raylib.h>
#include <iostream>
using namespace std;

class Grid{
    private:
    
    int numRows;
    int numCols;
    int cellSize;
    vector<Color> colors;
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);


    public:

    Grid();
    ~Grid(){}
    Grid(int numRows, int numCols, int cellSize);
    void setNumRows(int numRows);
    void setNumCols(int numCols);
    void setCellSize(int cellSize);
    int getNumRows();
    int getNumCols();
    int getCellSize();
    int ClearFullRow();

    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);

    void Inicializar();
    void Print();
    void Draw();
    int grid[20][10];


};

#endif