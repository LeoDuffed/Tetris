#ifndef Block_H
#define Block_H
#include <iostream>
#include <vector> 
#include <map> 
#include "Position.h"
using namespace std;

class Block{
    private:

    int cellSize;
    int rotationState;

    public:

    Block();
    ~Block(){}
    int id;
    map<int, vector<Position>> cells;

};

#endif