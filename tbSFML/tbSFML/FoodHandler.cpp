#include "FoodHandler.h"
#include "Constants.h"
#include <random>
#include <iostream>
#include "GridMap.h"
#include <filesystem>


void FoodHandler::SpawnFood(int spawnAmount)
{

	texture = new sf::Texture();
	// Load texture for the head, if needed
	texture->loadFromFile("img/apple2.png");



	for (int i = 0; i < spawnAmount; i++) 
	{

		sf::Vector2i rowColumn = GenerateRandomCoordinates();

		Food foodApple(rowColumn.x, rowColumn.y, APPLE_SIZE, texture, 0);
		foodOnScreen.push_back(foodApple);
		GridMap::PlaceObjectInGrid(foodApple.rowIndex, foodApple.columnIndex, 1); // 1 because it is an apple
	}

}

sf::Vector2i FoodHandler::GenerateRandomCoordinates() 
{
	// Ensure that the food is spawned on an empty space
	while (true) 
	{
		int columIndex = rand() % GridMap::columnsWide;
		int rowIndex = rand() % GridMap::rowsWide;

		// 0 means that the grid position is empty
		if (GridMap::gridMap[rowIndex][columIndex] == 0) 
		{
			return sf::Vector2i(rowIndex, columIndex);
			break;
		}

	}

	return sf::Vector2i(0, 0);
}

void FoodHandler::RemoveApple(Food food) 
{
	foodOnScreen.remove(food);
	GridMap::PlaceObjectInGrid(food.rowIndex, food.columnIndex, 0);
	EnsureAmountOfFoodOnScreen(5);
}


void FoodHandler::DrawFood(sf::RenderWindow& window)
{
	for(Food food : foodOnScreen) 
	{
		food.Draw(window);
	}
}

void FoodHandler::EnsureAmountOfFoodOnScreen(int spawnAmount) 
{
	if (foodOnScreen.size() != spawnAmount) 
	{
		int missingApples = spawnAmount - foodOnScreen.size();
		SpawnFood(missingApples);
	}
}