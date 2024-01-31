#include "grid.h"
#include <iostream>
#include "colors.h"
#include "position.h"
#include "game.h"
using namespace std;
Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors=GetCellColors();
}

void Grid::Initialize()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int col = 0; col < numCols; col++)
        {
            grid[row][col] = 0;
        }
    }
}

void Grid::Print()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int col = 0; col < numCols; col++)
        {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}


void Grid::Draw(){
    for(int row=0;row<numRows;row++){
        for(int column=0;column<numCols;column++){
               int cellValue = grid[row][column]; 
               DrawRectangle(column*cellSize+11,row*cellSize+11,cellSize-1,cellSize-1,colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int column)
{
    if(row>=0 && row<numRows && column>=0 && column<numCols){
        return false;
    }   
    return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
    if(grid[row][column] == 0){
        return true;
    }
    return false;
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for(int row = numRows-1; row >= 0; row--)
    {
        if(IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if(completed > 0)
        {
            MoveRowDown(row,completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row)
{
    for(int col = 0; col < numCols; col++)
    {
        if(grid[row][col] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row){
    for(int col = 0; col < numCols; col++)
    {
        grid[row][col] = 0;
    }
}

void Grid::MoveRowDown(int row,int numRows){
    for(int col = 0; col < numCols; col++)
    {
        grid[row+numRows][col] = grid[row][col];
        grid[row][col] = 0;
    }
}