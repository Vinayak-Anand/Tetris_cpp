#include "block.h"
using namespace std;
Block::Block(){
    cellSize = 30;
    rotationState = 0;
    colors=GetCellColors();
    rowOffset = 0;
    columnOffset =0;
}

void Block::Draw(int offsetX,int offsetY)
{
    vector<Position> tiles = GetCellPositions();
    for(Position item:tiles){
        DrawRectangle(item.column*cellSize+offsetX,item.row*cellSize+offsetY,cellSize-1,cellSize-1,colors[id]);
    }

}

void Block::Move(int rows,int columns){
    rowOffset+=rows;
    columnOffset+=columns;
}

vector<Position> Block::GetCellPositions(){
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for(Position item:tiles){
        movedTiles.push_back(Position(item.row+rowOffset,item.column+columnOffset));
    }
    return movedTiles;
}
void Block::Rotate(){
    rotationState++;
    if(rotationState == (int)cells.size()){
        rotationState = 0;
    }
}
void Block::UndoRotation(){
    rotationState--;
    if(rotationState == -1){
        rotationState = (int)cells.size()-1;
    }
}