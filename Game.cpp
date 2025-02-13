#include "Game.h"
#include <random>

Game ::Game()
{
    
    srand(time(NULL));
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    isPaused = false;

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
    
    if(keyPress == KEY_SPACE){
        PauseGame();
    }

    if(gameOver && keyPress != 0){
        gameOver = false;
        Reset();

    }

    if(isPaused || gameOver){
        return;
    }

    switch(keyPress){

        case KEY_LEFT:
        MoveBlockLeft();
        break;

        case KEY_RIGHT:
        MoveBlockRight();
        break;

        case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0,1);
        break;

        case KEY_UP:
        RotateBlock();
        break;

    }

}

void Game :: MoveBlockLeft(){

    if(!gameOver){
        currentBlock.Move(0,-1);
        if(IsBLockOutside() || BlockFits() == false){
            currentBlock.Move(0,1);
        }
    }

}

void Game :: MoveBlockRight(){

    if(!gameOver){
        currentBlock.Move(0,1);
        if(IsBLockOutside() || BlockFits() == false){
            currentBlock.Move(0,-1);

        }
    }

}

void Game :: MoveBlockDown(){

    if(!gameOver){
        currentBlock.Move(1,0);
        if(IsBLockOutside() || BlockFits() == false){
            currentBlock.Move(-1,0);
            
            EventTrigger(0.4);

            LockBlock();
        }
    }

}

void Game :: PauseGame(){

    isPaused = !isPaused;

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

    if(!gameOver){
        currentBlock.Rotate();
        if (IsBLockOutside() || BlockFits() == false){
            currentBlock.UnduRotation();
        }
    }

}

bool Game :: EventTrigger(double interval){
    double lastUpdate = 0;

    double currentTime =GetTime();
    if(currentTime - lastUpdate >= interval){
        lastUpdate = currentTime;
        return true;
    }
    return false;

}

void Game :: LockBlock(){

    EventTrigger(0.5);
    
    vector <Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles){
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;

    if(BlockFits() == false){

        gameOver = true;
        CheckHighScore();

    }
    nextBlock = GetRandomBlock();

    int rowsCleared = grid.ClearFullRow();
    UpdateScore(rowsCleared, 0);

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

void Game :: Reset(){
    
    grid.Inicializar();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;

}

void Game :: UpdateScore(int linesCleared, int moveDownPoints){

    switch (linesCleared){

        case 1: 
        score += 100;
        break;

        case 2: 
        score+=200;
        break;

        case 3:
        score+=500;
        break;

        case 4:
        score+= 700;
        break;

        case 5:
        score+= 800;
        break;

        case 6:
        score+=800;
        break;

        case 7:
        score+=800;
        break;

        default:
        break;
    }

    score += moveDownPoints;
   
}

vector<pair<int, string>> Game :: getHighScores(){
    return highScores;
}

void Game :: LoadHighScores(){
    highScores.clear();
    ifstream file("highscores.txt");
    string name;
    int score;
    
    while(file >> name >> score){
        highScores.push_back({score, name});
    }

    file.close();
    sort(highScores.rbegin(), highScores.rend());
    if(highScores.size() > 3){
        highScores.resize(3);
    }

}

void Game :: SaveHighScores(){
    ofstream file("highscores.txt");

    for(const auto& entry : highScores){
        file << entry.second << " " << entry.first << endl;
    }

    file.close();

}

void Game :: CheckHighScore(){
    if(score > (highScores.size() < 3 ? 0 : highScores.back().first)){
        cout << "New High Score!\nEnter your name: ";
        string playerName;
        cin >> playerName;
        highScores.push_back({score, playerName});
        sort(highScores.rbegin(), highScores.rend());

        if(highScores.size() > 3){
            highScores.resize(3);
        }

        SaveHighScores();
    }

}