#pragma once
#include "CreateObject.h"

class MovingObject : public CreateObject
{
public:
	virtual void Update(int screenWidth, int screenHeight) = 0;
	MovingObject(sf::Vector2f size, sf::Vector2f _pos, std::unique_ptr<sf::Shape> _shape, float _rotation, float _speed, sf::Vector2f _movementDirection);
	void IsOutOfScreen(int screenWidth, int screenHeight);
};

