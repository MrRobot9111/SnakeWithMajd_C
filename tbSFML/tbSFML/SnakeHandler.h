#pragma once
#include <vector>
#include "SnakeBody.h"
#include <deque>
#include "FoodHandler.h"


class SnakeHandler
{
// https://www.w3schools.com/cpp/cpp_data_structures.asp
// https://www.w3schools.com/cpp/cpp_deque.asp
// https://www.w3schools.com/cpp/cpp_vectors.asp

public:
	SnakeBody* snakeHead; 
	std::deque<SnakeBody> snakeBody; // The first element is always the head of the snake
	std::deque<DirectionChange> globalDirectionChanges; // Store the positions of the head's turns
	sf::Texture* texture;
private:
	sf::Clock clock; // starts the clock

public:
	SnakeHandler(sf::Texture* headtexture); // Create the head inside the constructor
	void Grow();
	void Shrink(); // When it hits a power-up it can shrink
	void IsCollidedWithApple(FoodHandler& food); // Should not modify anything
	void IsCollidedWithSelf(SnakeBody snakeBody);
	bool KeydownTimeElapsed();


	// This should only be used on the head of the snake
	void CheckIfOutOfScreen(int screenWidth, int screenHeight);
	void KeyboardInput(int screenWidth, int screenHeight);

	// These are handling the update of the body
	void UpdateBodyPostion();

	void Update(sf::RenderWindow& window, int screenWidth, int screenHeight); // Adjust the whole body's position when moving
	void Draw(sf::RenderWindow& window); // Access the individual body parts and draw them
};

