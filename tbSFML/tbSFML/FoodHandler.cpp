#include "FoodHandler.h"
#include <random>

void FoodHandler::SpawnFood(int spawnAmount)
{
	sf::Texture texture;
	texture.loadFromFile("img/tych.png");
	for (int i = 0; i < spawnAmount; i++) 
	{
		Food foodApple(sf::Vector2f(50, 50), GenerateRandomCoordinates(), texture, 0);
		foodOnScreen.push_back(foodApple);
	}

}

sf::Vector2f FoodHandler::GenerateRandomCoordinates() 
{
	float randomNumX = rand() % 1000;
	float randomNumY = rand() % 1000;

	return sf::Vector2f(randomNumX, randomNumY);
}

void FoodHandler::DrawFood(sf::RenderWindow& window)
{
	for(Food food : foodOnScreen) 
	{
		food.Draw(window);
	}
}