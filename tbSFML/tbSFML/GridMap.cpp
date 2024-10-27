#include "GridMap.h"
#include "Constants.h"

// Define the static gridMap
std::vector<std::vector<int>> GridMap::gridMap;
int GridMap::columnsWide;
int GridMap::rowsWide;

void GridMap::InitializeGridMap()
{
    int rows = SCREEN_SIZE.y / SNAKE_BODY_SIZE.y;
    int cols = SCREEN_SIZE.x / SNAKE_BODY_SIZE.x;
	gridMap.resize(rows, std::vector<int>(cols, 0));
	columnsWide = cols;
	rowsWide = rows;
}

void GridMap::PlaceObjectInGrid(int rowIndex, int colIndex, int object) 
{
	// Problem with row and colIndex being mixed up
	gridMap[rowIndex][colIndex] = object; // Occupy the grid position with the object
}