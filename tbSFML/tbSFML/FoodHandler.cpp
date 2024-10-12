#include "FoodHandler.h"
#include "Constants.h"
#include <random>
#include <iostream>
#include <filesystem>

void FoodHandler::SpawnFood(int spawnAmount)
{

	texture = new sf::Texture();
	// Load texture for the head, if needed
	texture->loadFromFile("img/apple.png");



	for (int i = 0; i < spawnAmount; i++) 
	{
		Food foodApple(APPLE_SIZE, GenerateRandomCoordinates(), texture, 0);
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