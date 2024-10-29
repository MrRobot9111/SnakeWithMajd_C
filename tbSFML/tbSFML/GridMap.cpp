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

void GridMap::DrawGridMap(sf::RenderWindow& window)
{
	for (int i = 0; i < rowsWide; i++) {
		for (int j = 0; j < columnsWide; j++)
		{
			sf::CircleShape circle(12.5f); // Circle with a radius of 50 pixels
			circle.setFillColor(sf::Color::Black); // Set color to green
			circle.setPosition(j * APPLE_SIZE.x, i * APPLE_SIZE.y); // Set position to the center of the window (adjust if needed)
			window.draw(circle);
		}
	}
}

void GridMap::PlaceObjectInGrid(int rowIndex, int colIndex, int object) 
{
	// Problem with row and colIndex being mixed up
	gridMap[rowIndex][colIndex] = object; // Occupy the grid position with the object
}