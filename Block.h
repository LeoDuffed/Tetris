#ifndef Block_H
#define Block_H
#include <iostream>
#include <vector> 
#include <map> 
#include "Position.h"
#include "Colors.h"
using namespace std;

class Block{
    private:

    int cellSize;
    int rotationState;
    vector <Color> colors;
    int rowOffset;
    int columnOffset;

    public:

    Block();
    ~Block(){}
    int id;
    map<int, vector<Position>> cells;
    void Draw();
    void Move(int rows, int columns);
    vector <Position> GetCellPositions();
    
};

#endif