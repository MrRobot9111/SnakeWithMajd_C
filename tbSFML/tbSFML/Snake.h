#pragma once
#include <deque>

#include "MovingObject.h"

// Match each body part with the size of square in the game (10x10)
const float SNAKE_SEGMENT_SIZE = 10.0f;

class Snake : public MovingObject
{
	// Definition, and implementation in .cpp file

// https://www.w3schools.com/cpp/cpp_data_structures.asp
// https://www.w3schools.com/cpp/cpp_deque.asp

private:
	// Coordinates for each body part
	// The first element is the head
	// It should be in the middle of the square, so that a radius calculation can be made to check if collision
	std::deque<sf::Vector2f> body;

public:
	Snake(sf::Vector2f size, sf::Vector2f _pos, std::unique_ptr<sf::Shape> _shape, float _rotation, float _speed, sf::Vector2f _movementDirection);
	void Update(int screenWidth, int screenHeight);
	void KeyboardInput(int screenWidth, int screenHeight);
	void IsOutOfScreen(int screenWidth, int screenHeight);
};

