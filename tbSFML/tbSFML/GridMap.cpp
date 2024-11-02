#include "GridMap.h"
#include "Constants.h"

// Define the static gridMap
std::vector<std::vector<int>> GridMap::gridMap; // Matrix of integers
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

void GridMap::DrawGridMap(sf::RenderWindow& window)
{
	for (int i = 0; i < rowsWide; i++) {
		for (int j = 0; j < columnsWide; j++)
		{
			sf::CircleShape circle(12.5f); 
			circle.setFillColor(sf::Color::Black); 
			circle.setPosition(j * APPLE_SIZE.x, i * APPLE_SIZE.y);
			window.draw(circle);
		}
	}
}

void GridMap::PlaceObjectInGrid(int rowIndex, int colIndex, int object) 
{
	gridMap[rowIndex][colIndex] = object; // Occupy the grid position with the object
}