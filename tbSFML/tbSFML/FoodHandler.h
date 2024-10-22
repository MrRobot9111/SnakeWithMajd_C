#pragma once
#include <vector>
#include "Food.h"
#include <deque>
#include <list>

class FoodHandler
{
public:
	std::list<Food> foodOnScreen;

private:
	sf::Vector2f screenSize;
	sf::Texture* texture; // Otherwise the reference will be gone

public:
	void SpawnFood(int spawnAmount);
	sf::Vector2f GenerateRandomCoordinates(); // They must be inside the screen, and not on the snake
	void DrawFood(sf::RenderWindow& window);
	void RemoveApple(Food food); // This will re-spawn the apple in a different position on the screen
	void EnsureAmountOfFoodOnScreen(int spawnAmount); // This will ensure that the amount of food on the screen is stays the same, since it can sometimes less, due to how the snake moves, and the apples are spawned
};

