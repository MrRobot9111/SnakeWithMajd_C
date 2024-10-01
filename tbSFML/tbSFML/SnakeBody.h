#pragma once
#include <vector>
#include "Food.h"

class SnakeBody
{
public:
	sf::Vector2f pos;
	sf::RectangleShape rectangleBody;
	sf::Texture texture;
public:
	SnakeBody();
};

