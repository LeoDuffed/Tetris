#ifndef Game_H
#define Game_H
#include <iostream> 
#include "Grid.h"
#include "Blocks.cpp"
#include <vector>
#pragma once
using namespace std;

class Game{
    private:

    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool IsBLockOutside();
    void RotateBlock();

    public: 

    Game();
    ~Game(){}
    Grid grid;
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();

};

#endif