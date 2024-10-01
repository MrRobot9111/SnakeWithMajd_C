#pragma once
#include <vector>
#include "Food.h"

class SnakeBody
{
public:
	sf::Vector2f size;
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f movementDirection;
	float speed;
public:
	SnakeBody(sf::Vector2f size, sf::Vector2f _pos, float _rotation, float _speed, sf::Vector2f _movementDirection, sf::Texture& _texture);
	SnakeBody();
	void CheckIfOutOfScreen(int screenWidth, int screenHeight);
	void KeyboardInput(int screenWidth, int screenHeight);
	void Update(int screenWidth, int screenHeight);
	void Draw(sf::RenderWindow& window);
};

