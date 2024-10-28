#pragma once
#include <vector>
#include "Food.h"
#include <deque>
#include "DirectionChange.h"

class SnakeBody
{
public:
	int gridColumn;
	int gridRow;

	sf::Sprite sprite;
	sf::Texture* texture;
	sf::Vector2f movementDirection;

	int localDirectionChangesIndex = 0;

	// bool reachedGoalPositionCorrect;
	float speed;
	float rotation;
public:
	SnakeBody();
	SnakeBody(int gridRowIN, int gridColumnIN, float _rotation, float _speed, sf::Vector2f _movementDirection, sf::Texture* _texture);

	void SetNewSpritePosition(int addRow, int addCol);
	void Update(int screenWidth, int screenHeight);
	void Draw(sf::RenderWindow& window);
};

