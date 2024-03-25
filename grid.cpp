#include "grid.h"
#include <iostream>
#include "colors.h"

Grid::Grid()
{
    Rows = 21;
    Cols = 11;
    cellSize = 50;
    Initialize();
    colors = getcolors();
}

void Grid::Initialize()
{
    for (int row = 0; row < Rows; row++)
    {
        for (int column = 0; column < Cols; column++)
        {
            grid[row][column] = 0;
        }
    }
}


void Grid::Draw()
{
    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0; j < Cols; j++)
        {
            int cellValue = grid[i][j];
            DrawRectangle(j * cellSize + 5, i * cellSize + 8, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int column)
{
    if (row >= 0 && row < Rows && column >= 0 && column < Cols)
    {
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
    if (grid[row][column] == 0)
    {
        return true;
    }
    return false;
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for (int row = Rows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row) const
{
    for (int column = 0; column < Cols; column++)
    {
        if (grid[row][column] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for (int column = 0; column < Cols; column++)
    {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows)
{
    for (int column = 0; column < Cols; column++)
    {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}
