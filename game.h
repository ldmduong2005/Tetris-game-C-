#pragma once
#include "grid.h"
#include "blocks.cpp"
#include<fstream>

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void Input();
    void MoveBlockDown();
    bool gameOver;
    int score;
    void Reset();
    int high_score;
    Sound clear;



private:
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks()
    {
        return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock(), PBlock(), iBlock()};
    }
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void UpdateScore(int lines);
    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    void CheckScore();
    void SaveHighScore(int Highscore);
    int LoadHighScore();
    
};