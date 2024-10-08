#pragma once
#include <vector>
#include "Food.h"

class SnakeBody
{
public:
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture* texture;
	sf::Vector2f movementDirection;
	sf::Vector2f goalPosition;
	bool hasReachedGoalPosition;
	float speed;
	float rotation;
public:
	SnakeBody();
	SnakeBody(sf::Vector2f _pos, float _rotation, float _speed, sf::Vector2f _movementDirection, sf::Texture* _texture, sf::Vector2f _goalPosition = sf::Vector2f(-1.0f, -1.0f));
	void Update(int screenWidth, int screenHeight);
	void Draw(sf::RenderWindow& window);
};

