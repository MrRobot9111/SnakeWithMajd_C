#include "SnakeBody.h"
#include "Constants.h"
#include "GridMap.h"
#include <optional>

SnakeBody::SnakeBody(int gridRowIN, int gridColumnIN,  float _rotation, float _speed, sf::Vector2f _movementDirection, sf::Texture* _texture)
{
    // Check if this is correct
    speed = _speed;
    movementDirection = _movementDirection;   
	gridColumn = gridColumnIN;
	gridRow = gridRowIN;
    texture = _texture;
    sprite.setTexture(*texture);  // Set the texture to the sprite

    // Set initial scale based on the size
    sprite.setScale(SNAKE_BODY_SIZE.x / texture->getSize().x, SNAKE_BODY_SIZE.y / texture->getSize().y);

    // Set the origin to the center of the sprite to prevent jumping on rotation
    sprite.setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);

	sprite.setPosition(gridColumn * SNAKE_BODY_SIZE.x, gridRow * SNAKE_BODY_SIZE.y);
    // Set the initial position and rotation of the sprite
    sprite.setRotation(_rotation);

}

// Automatically sets new gridRow and gridColumn
void SnakeBody::SetNewSpritePosition(int newRow, int newCol) 
{
	gridRow = newRow;
	gridColumn = newCol;
    sprite.setPosition(gridColumn * SNAKE_BODY_SIZE.x, gridRow * SNAKE_BODY_SIZE.y);
}


void SnakeBody::Update(int screenWidth, int screenHeight)
{
    
}



void SnakeBody::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}