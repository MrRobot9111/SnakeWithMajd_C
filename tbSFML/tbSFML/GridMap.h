#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
class GridMap
{
public:
	// Map the grid, so that 0 is empty, 1 is food, 2 is snake, and 3 is wall - perhaps enum to handle this
	// Rows, Cols
	static int columnsWide;
	static int rowsWide;
	static std::vector<std::vector<int>> gridMap; 
public:
	static void InitializeGridMap();
	static void DrawGridMap(sf::RenderWindow& window);
	static void PlaceObjectInGrid(int rowIndex, int colIndex, int object); // Change to enum later for object

	// Define the map values, such as 0 = empty, 1 = food, 2 = snake, etc.
	enum GridObjects { EMPTY = 0, FOOD, SNAKE, WALL };

};

