#pragma once
#include <vector>
#include "Food.h"

class FoodHandler
{
public:
	std::vector<Food> foodOnScreen;
	sf::Vector2f screenSize;

public:
	void SpawnFood(int spawnAmount);
	sf::Vector2f GenerateRandomCoordinates(); // They must be inside the screen, and not on the snake
	void DrawFood(sf::RenderWindow& window);
};

