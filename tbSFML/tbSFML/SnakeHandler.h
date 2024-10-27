#pragma once
#include <vector>
#include "SnakeBody.h"
#include <deque>
#include "FoodHandler.h"
#include "GameStatesManager.h"
#include "GameStatesEnum.h"


class SnakeHandler
{
// https://www.w3schools.com/cpp/cpp_data_structures.asp
// https://www.w3schools.com/cpp/cpp_deque.asp
// https://www.w3schools.com/cpp/cpp_vectors.asp

public:
	SnakeBody* snakeHead; 
	std::deque<SnakeBody> snakeBody; // The first element is always the head of the snake
	std::deque<DirectionChange> globalDirectionChanges; // Store the positions of the head's turns
	sf::Texture* headTexture;
	sf::Texture* bodyTexture;
private:
	sf::Clock clock; // starts the clock

public:
	SnakeHandler(sf::Texture* headtexture, sf::Texture* bodyTexture); // Create the head inside the constructor
	void Grow();
	void Shrink(); // When it hits a power-up it can shrink
	void IsCollidedWithApple(FoodHandler& food); // Should not modify anything
	void IsCollidedWithSelf(SnakeBody snakeBody, GameStatesManager* gameStateManager);
	bool KeydownTimeElapsed();


	// This should only be used on the head of the snake
	void CheckIfOutOfScreen(int screenWidth, int screenHeight, GameStatesManager* gameStateManager);
	void KeyboardInput(int screenWidth, int screenHeight, GameStatesManager* gameStateManager);

	// These are handling the update of the body
	sf::Vector2i DetermineNewRowColumn(SnakeBody sn);
	void DetermineNewRowColumn(SnakeBody* sn);
	void UpdateBodyPostion(GameStatesManager* gameStatesManager);

	void Update(sf::RenderWindow& window, int screenWidth, int screenHeight, GameStatesManager* gameStatesManager); // Adjust the whole body's position when moving
	void Draw(sf::RenderWindow& window); // Access the individual body parts and draw them

	void ResetSnake();
};

