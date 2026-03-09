#ifndef Game_H
#define Game_H
#include <iostream> 
#include "Grid.h"
#include "Blocks.cpp"
#include "SerialPort.h"
#include <vector>
#include <fstream> 
#include <algorithm>
#include <ctime>
#pragma once
using namespace std;

class Game{
    private:

    vector<Block> blocks;
    vector<pair<int, string>> highScores;
    Block currentBlock;
    Block nextBlock;
    bool IsBLockOutside();
    void RotateBlock();
    void LockBlock();
    void Reset(); 
    void UpdateScore(int linesCleared, int moveDownPoints);
    bool BlockFits();
    double lastUpdate;
    double lastDownMoveTime;
    double downMoveDelay;
    
    // comunicacion serial
    string BoolIdToAsciiDigit(const string& bits);
    SerialPort* serialPort;
    void SendNextBlockSerial();
    void SendPauseSerial();
    void SendScoreSerial();

    public: 

    Game();
    ~Game(){}
    Grid grid;
    bool gameOver;
    bool isPaused;
    int score;
    double dropInterval;
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    vector<pair<int, string>>getHighScores();
    void Draw();
    void DrawGhostPiece();
    void DrawNextBlock();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    void PauseGame();
    void LoadHighScores();
    void CheckHighScore();
    void SaveHighScores();
    bool EventTrigger(double interval);

    // Comunicacion serial:
    void SetSerialPort(SerialPort* port);
};

#endif