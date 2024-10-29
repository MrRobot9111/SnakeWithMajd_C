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

	float rotation;
public:
	SnakeBody();
	SnakeBody(int gridRowIN, int gridColumnIN, float _rotation, sf::Vector2f _movementDirection, sf::Texture* _texture);

	void SetNewSpritePosition(int addRow, int addCol);
	void Update(int screenWidth, int screenHeight);
	void Draw(sf::RenderWindow& window);
};

