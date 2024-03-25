#include "block.h"
#include "position.h"
Block::Block()
{
    cellSize = 50;
    rotation = 0;
    colors = getcolors();
    newrow = 0;
    newcolumn = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = cellpositions();
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int columns)
{
    newrow += rows;
    newcolumn += columns;
}

std::vector<Position> Block::cellpositions()
{
    std::vector<Position> tiles = cells[rotation];
    std::vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPos = Position(item.row + newrow, item.column + newcolumn);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::rotate()
{
    rotation++;
    if (rotation == (int)cells.size())
    {
        rotation = 0;
    }
}

void Block::Undo()
{
    rotation--;
    if (rotation == -1)
    {
        rotation = cells.size() - 1;
    }
}