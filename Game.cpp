#include "Game.h"
#include <random>

Game :: Game(){

    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();

}

Block Game :: GetRandomBlock(){

    if(blocks.empty()){
        blocks = GetAllBlocks();
    }

    int randmoIndex = rand() % blocks.size();
    Block block = blocks[randmoIndex];
    blocks.erase(blocks.begin() + randmoIndex);
    return block;

}

vector <Block> Game::GetAllBlocks(){
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};

}

void Game :: Draw(){

    grid.Draw();
    currentBlock.Draw();

}

void Game :: HandleInput(){

    int keyPress = GetKeyPressed();
    switch(keyPress){

        case KEY_LEFT:
        MoveBlockLeft();
        break;

        case KEY_RIGHT:
        MoveBlockRight();
        break;

        case KEY_DOWN:
        MoveBlockDown();
        break;
    }

}

void Game :: MoveBlockLeft(){

    currentBlock.Move(0,-1);
}

void Game :: MoveBlockRight(){

    currentBlock.Move(0,1);
}

void Game :: MoveBlockDown(){

    currentBlock.Move(1,0);
}