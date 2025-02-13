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
    void LockBlock();
    void Reset(); 
    void UpdateScore(int linesCleared, int moveDownPoints);
    bool BlockFits();

    public: 

    Game();
    ~Game(){}
    Grid grid;
    bool gameOver;
    bool isPaused;
    int score;
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    void PauseGame();
    bool EventTrigger(double interval);

};

#endif