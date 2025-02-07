#ifndef Grid_H
#define Grid_H
#include <iostream>
using namespace std;

class Grid{
    private:
    
    int numRows;
    int numCols;
    int cellSize;


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

    int grid[20][10];


};

#endif