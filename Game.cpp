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
    lastUpdate = 0;
    lastDownMoveTime = 0;
    downMoveDelay = 0.2;
    dropInterval = 0;

    // Comunicacion serial
    serialPort = nullptr;

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
    DrawGhostPiece();
    currentBlock.Draw(11,11);

}

void Game :: DrawNextBlock(){
    nextBlock.Draw(265,500);
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

    if(IsKeyDown(KEY_DOWN)){
        double currentTime = GetTime();
        if (currentTime  - lastDownMoveTime >= downMoveDelay){
            MoveBlockDown();
            lastDownMoveTime = currentTime;
        }

    }
    
    switch(keyPress){

        case KEY_LEFT:
        MoveBlockLeft();
        break;

        case KEY_RIGHT:
        MoveBlockRight();
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

    if (isPaused){
        SendPauseSerial();
    } else {
        SendNextBlockSerial();
        SendScoreSerial();
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

    if(!gameOver){
        currentBlock.Rotate();
        if (IsBLockOutside() || BlockFits() == false){
            currentBlock.UnduRotation();
        }
    }

}

bool Game :: EventTrigger(double interval){

    double currentTime = GetTime();

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
        SendPauseSerial();
        CheckHighScore();
        return;

    }
    nextBlock = GetRandomBlock();
    SendNextBlockSerial();

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
    isPaused = false;

    SendNextBlockSerial();
    SendScoreSerial();
}

void Game :: UpdateScore(int linesCleared, int moveDownPoints){

    int oldScore = score;

    switch (linesCleared){

        case 1: 
        score += 1;
        break;

        case 2: 
        score+=2;
        break;

        case 3:
        score+=3;
        break;

        case 4:
        score+= 4;
        break;

        case 5:
        score+= 5;
        break;

        case 6:
        score+= 6;
        break;

        case 7:
        score+= 7;
        break;

        default:
        break;
    }

    score += moveDownPoints;

    if(score != oldScore){
        SendScoreSerial();
    }
   
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
        cout << "\nNuevo Record!\n6 letras max\nIngresa tu nombre: ";
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

void Game :: DrawGhostPiece(){

    Block ghostBlock = currentBlock;
    int moves = 0;

    while(true){
        ghostBlock.Move(1,0);

        bool collinsion = false;

        for(const Position& pos : ghostBlock.GetCellPositions()){

            if(grid.IsCellOutside(pos.row, pos.column) || !grid.IsCellEmpty(pos.row, pos.column)){
                collinsion = true;
                break;
            }
        }

        if(collinsion){
            ghostBlock.Move(-1, 0);
            break;
        }

        moves++;

        if (moves >= grid.getNumRows()){
            break;
        }

    }

    vector<Position> ghostTiles = ghostBlock.GetCellPositions();
    for(Position item : ghostTiles){
        DrawRectangle(item.column * grid.getCellSize() + 11,item.row * grid.getCellSize() + 11, grid.getCellSize() - 1, grid.getCellSize() - 1, Fade(WHITE, 0.2f));

    }

}

// Comunicacion serial

uint8_t Game::BoolIdToCode(const string& bits) {

    if(bits == "000") return 0;
    if(bits == "001") return 1;
    if(bits == "010") return 2;
    if(bits == "011") return 3;
    if(bits == "100") return 4;
    if(bits == "101") return 5;
    if(bits == "110") return 6;

    return 7; // pausa o error
}

void Game::SetSerialPort(SerialPort* port) {
    serialPort = port;
    SendNextBlockSerial();
    SendScoreSerial();
}

void Game::SendNextBlockSerial() {

    if (serialPort == nullptr || !serialPort->isConnected()) {
        return;
    }

    uint8_t blockCode = BoolIdToCode(nextBlock.boolId);
    uint8_t byteToSend =  blockCode;

    string msg;
    msg += static_cast<char>(byteToSend);

    bool ok = serialPort->sendData(msg);

    if(!ok) cout<<"Error al enviar figura"<<endl;

}

void Game::SendPauseSerial() {
    if (serialPort == nullptr || !serialPort->isConnected()) {
        return;
    }
    
    uint8_t byteToSend = 0x07;
    string msg;
    msg += static_cast<char>(byteToSend);
    serialPort->sendData(msg);

}

void Game::SendScoreSerial(){
    
    if(serialPort == nullptr || !serialPort->isConnected()){
        return;
    }

    uint8_t score7 = static_cast<uint8_t>(min(score, 127));
    uint8_t byteToSend = 0x80 | score7;

    string msg;
    msg += static_cast<char>(byteToSend);

    bool ok = serialPort->sendData(msg);

    cout << "Score actual = " << score
     << " | score7 = " << static_cast<int>(score7)
     << " | byte enviado = " << static_cast<int>(byteToSend)
     << endl;

    if(!ok) cout<<"Error al enviar score"<<endl;

}