#pragma once
#include <vector>
#include "SnakeBody.h"
#include <deque>
#include "FoodHandler.h"
#include "GameStatesManager.h"
#include "GameStatesEnum.h"
#include "DirectionEnum.h"


class SnakeHandler
{
// https://www.w3schools.com/cpp/cpp_data_structures.asp
// https://www.w3schools.com/cpp/cpp_deque.asp
// https://www.w3schools.com/cpp/cpp_vectors.asp

public:
	SnakeBody* snakeHead; 
	std::deque<SnakeBody> snakeBody; // The first element is always the head of the snake
	sf::Texture* headTexture;
	sf::Texture* bodyTexture;

public:
	SnakeHandler(sf::Texture* headtexture, sf::Texture* bodyTexture); // Create the head inside the constructor
	void Grow();
	void Shrink(); // When it hits a power-up it can shrink
	void IsCollidedWithApple(FoodHandler& food); // Should not modify anything
	void IsCollidedWithSelf(GameStatesManager* gameStateManager, sf::Vector2i newHeadPos);


	// Check if whether the new position of the head is outside the screen
	void CheckIfOutOfScreen(SnakeBody* snNewHead, sf::Vector2i* newHeadPos, GameStatesManager* gameStateManager);
	void KeyboardInput(int screenWidth, int screenHeight, GameStatesManager* gameStateManager);

	// These are handling the update of the body
	sf::Vector2i DirectionToVector(DirectionEnum direction); // Convert a direction to a vector
	void DetermineNewRowColumn(SnakeBody sn);
	void DetermineNewRowColumn(SnakeBody* sn);
	void UpdateBodyPostion(GameStatesManager* gameStatesManager);

	void Update(sf::RenderWindow& window, int screenWidth, int screenHeight, GameStatesManager* gameStatesManager); // Adjust the whole body's position when moving
	void Draw(sf::RenderWindow& window); // Access the individual body parts and draw them

	void ResetSnake();
	void ResetSnakeGrid();
};

