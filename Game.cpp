#include "Game.h"
#include <random>

Game ::Game()
{

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

        case KEY_UP:
        RotateBlock();
        break;
    }

}

void Game :: MoveBlockLeft(){

    currentBlock.Move(0,-1);
    if(IsBLockOutside() || BlockFits() == false){
        currentBlock.Move(0,1);
    }

}

void Game :: MoveBlockRight(){

    currentBlock.Move(0,1);
    if(IsBLockOutside() || BlockFits() == false){
        currentBlock.Move(0,-1);

    }

}

void Game :: MoveBlockDown(){

    currentBlock.Move(1,0);
    if(IsBLockOutside() || BlockFits() == false){
        currentBlock.Move(-1,0);
        LockBlock();
    }

}

bool Game::IsBLockOutside()
{
    vector <Position> tiles = currentBlock.GetCellPositions();

    for(Position item : tiles){
        if(grid.IsCellOutside(item.row, item.column)){
            return true;
        }

    }
    return false;

}

void Game :: RotateBlock(){

    currentBlock.Rotate();
    if (IsBLockOutside() || BlockFits() == false){
        currentBlock.UnduRotation();
    }

}

void Game :: LockBlock(){

    vector <Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles){
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();

}

bool Game :: BlockFits(){
    vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles){
        if(grid.IsCellEmpty(item.row, item.column) == 0){
            return false;
        }
    }
    return true;
}