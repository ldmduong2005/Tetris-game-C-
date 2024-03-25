
#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
    Grid();
    void Initialize();
    void Draw();
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();
    int grid[21][11];

private:
    bool IsRowFull(int row) const;
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    int Rows;
    int Cols;
    int cellSize;
    std::vector<Color> colors;
};