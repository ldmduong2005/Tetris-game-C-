#include "game.h"
#include <random>
#include <iostream>
using namespace std;

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    high_score = LoadHighScore();
    clear = LoadSound("D:/C++/newtetris/clear.mp3");
    SetSoundVolume(clear, 0.2);

  
}
Game::~Game() {
    UnloadSound(clear);
    CloseAudioDevice();
}



Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(515, 560);
        break;
    case 4:
        nextBlock.Draw(515, 560);
        break;
    case 9:
        nextBlock.Draw(550, 560);
        break;
    default:
        nextBlock.Draw(540, 540);
        break;
    }
}

void Game::Input()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
       
        gameOver = false;
        Reset();
    }
    switch (keyPressed)
    {
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

    case KEY_ENTER:
        Reset();
        
        break;
    }
    
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.cellpositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.rotate();
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Undo();
        }
        
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.cellpositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        UpdateScore(rowsCleared);
        PlaySound(clear);
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.cellpositions();
    for (Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false)
        {
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
    score = 0;
}

void Game::UpdateScore(int lines)
{
    switch (lines)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    case 4:
        score += 700;
        break;
    
    default:
        break;
    }
    CheckScore();
    
    
}
void Game::CheckScore() {
    if (score > high_score ) {
        high_score = score;
        SaveHighScore(high_score);
    }
}
void Game::SaveHighScore(int Highscore) {
    ofstream file("highscore_file.txt");
    if (file.is_open()) {
        file << Highscore;
        file.close();
    }
    else {
        cerr << "failed to load"<<endl;
    }
}
int Game::LoadHighScore() {
    int loadscore = 0;
    ifstream file("highscore_file.txt");
    if(file.is_open()) {
        file >> loadscore;
        file.close();
    }
    else {
        cerr << "failed to load"<<endl ;
    }
    return loadscore;
}
