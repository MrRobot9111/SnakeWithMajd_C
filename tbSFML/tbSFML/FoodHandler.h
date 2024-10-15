#pragma once
#include <vector>
#include "Food.h"
#include <deque>

class FoodHandler
{
public:
	std::deque<Food> foodOnScreen;

private:
	sf::Vector2f screenSize;
	sf::Texture* texture; // Otherwise the reference will be gone

public:
	void SpawnFood(int spawnAmount);
	sf::Vector2f GenerateRandomCoordinates(); // They must be inside the screen, and not on the snake
	void DrawFood(sf::RenderWindow& window);
	void RemoveApple(Food food);
};

