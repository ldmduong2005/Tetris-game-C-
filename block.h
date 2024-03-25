#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
public:
    Block();
    int id;
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    std::vector<Position> cellpositions();
    void rotate();
    void Undo();
    std::map<int, std::vector<Position>> cells;

private:
    int cellSize;
    int rotation;
    std::vector<Color> colors;
    int newrow;
    int newcolumn;
};
