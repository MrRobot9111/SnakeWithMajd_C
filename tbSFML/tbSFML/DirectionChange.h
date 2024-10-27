#pragma once
#include <optional>
#include <deque>
#include <SFML/Graphics.hpp>

class DirectionChange
{
public:
    int columnIndex;
    int rowIndex;
    sf::Vector2f newDirection; // New movement direction
    float rotation;            // Rotation angle for the sprite
	bool isOutOfScreenXRight = false; // True if the head has exceeded the right side of the screen
    bool isOutOfScreenXLeft = false; // True if the head has exceeded the right side of the screen
};

