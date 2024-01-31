#include "game.h"
#include <random>
Game::Game(){
    grid=Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver=false;
    score=0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound= LoadSound("Sounds/rotate.mp3");
    clearSound= LoadSound("Sounds/clear.mp3");
}
Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}
Block Game::GetRandomBlock(){
    if(blocks.size() == 0){
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

vector<Block> Game::GetAllBlocks(){
    return {IBlock(),JBlock(),LBlock(),OBlock(),SBlock(),TBlock(),ZBlock()};
}
void Game::Draw(){
    grid.Draw();
    currentBlock.Draw(11,11);
    switch (nextBlock.id)
    {
    case 3:
    nextBlock.Draw(255,250);
        break;
    case 4:
    nextBlock.Draw(255,230);
        break;
    
    default:
    nextBlock.Draw(270,220);
        break;
    }
}
void Game::HandleInput(){
    int keypressed = GetKeyPressed();
    if(gameOver && keypressed !=0){
        gameOver=false;
        Reset();
    }
        switch(keypressed){
            case KEY_LEFT:
                MoveBLockLeft();
                break;
            case KEY_RIGHT:
                MoveBLockRight();
                break;
            case KEY_UP:
                RotateBlock();
                break;
            case KEY_DOWN:
                MoveBLockDown();
                UpdateScore(0,1);
                break;

        }
    }

void Game::MoveBLockLeft(){
 if(!gameOver){
    currentBlock.Move(0,-1);
    if(IsBlockOutside() || BlockFits()==false){
        currentBlock.Move(0,1);
    }
 }
}
void Game::MoveBLockRight(){
    if(!gameOver){
    currentBlock.Move(0,1);
    if(IsBlockOutside() || BlockFits()==false){
        currentBlock.Move(0,-1);
    }}
}
void Game::MoveBLockDown(){
    if(!gameOver){
    currentBlock.Move(1,0);
    if(IsBlockOutside() || BlockFits()==false){
        currentBlock.Move(-1,0);
        LockBlock();
    }}
}
void Game::MoveBLockUp(){
    if(!gameOver){
    currentBlock.Move(-1,0);
    if(IsBlockOutside() || BlockFits()==false){
        currentBlock.Move(1,0);
    }}
}
bool Game::IsBlockOutside(){
    vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item:tiles){
        if(grid.IsCellOutside(item.row,item.column)){
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{ if(!gameOver){
    currentBlock.Rotate();
    if(IsBlockOutside() || BlockFits()==false){
        currentBlock.UndoRotation();
    
    }
    else{
        PlaySound(rotateSound);
    }
}

}
void Game::LockBlock()  {
    vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item:tiles){
        grid.grid[item.row][item.column]= currentBlock.id;
    }
    currentBlock=nextBlock;
    if(BlockFits()==false){
        gameOver=true;
    }
    nextBlock=GetRandomBlock();
    int rowsCleared=grid.ClearFullRows();
    if(rowsCleared>0){
        PlaySound(clearSound);
        UpdateScore(rowsCleared,0);
    }
    
}
bool Game::BlockFits(){
    vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item:tiles){
        if(grid.IsCellEmpty(item.row,item.column) == false){
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score=0;
}

void Game::UpdateScore(int linesCleared,int moveDownPoints){
    switch(linesCleared){
        case 1:
          score+=100;
          break;
        case 2:
            score+=300;
            break;
        case 3:
            score+=500;
        default:
            break;
        
    }
    score += moveDownPoints;
}