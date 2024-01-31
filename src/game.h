#pragma once
#include "grid.h"
#include "blocks.cpp"
class Game{
    public:
        Game();
        ~Game();
        void Draw();
        void HandleInput();
        void MoveBLockDown();
        bool gameOver;
        int score;
        Music music;
        

    private:
        Block GetRandomBlock();
        vector<Block> GetAllBlocks();
        void MoveBLockLeft();
        void MoveBLockRight();
        void MoveBLockUp();
        bool IsBlockOutside();
        void RotateBlock();
        void LockBlock();
        bool BlockFits();
        void Reset();
        Grid grid;
        void UpdateScore(int linesCleared,int moveDownPoints);
        vector<Block> blocks;
        Block currentBlock;
        Block nextBlock;
        Sound rotateSound;
        Sound clearSound;
};