#include "SnakeBody.h"
#include "Constants.h"
#include <optional>

// Default constructor
SnakeBody::SnakeBody()
    : position(0, 0), movementDirection(0, 0), speed(1.0f) // Initialize members as needed
{
    // Optionally, set up the sprite and texture if necessary
}


SnakeBody::SnakeBody(sf::Vector2f _pos, float _rotation, float _speed, sf::Vector2f _movementDirection, sf::Texture* _texture, sf::Vector2f _goalPosition)
{
    // Check if this is correct
    speed = _speed;
    movementDirection = _movementDirection;   
    position = _pos;
    texture = _texture;
	movmentDirectionSwitchPosition = _goalPosition;
    sprite.setTexture(*texture);  // Set the texture to the sprite

    // Set initial scale based on the size
    sprite.setScale(SNAKE_BODY_SIZE.x / texture->getSize().x, SNAKE_BODY_SIZE.y / texture->getSize().y);

    // Set the origin to the center of the sprite to prevent jumping on rotation
    sprite.setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);

    // Set the initial position and rotation of the sprite
    sprite.setPosition(_pos);
    sprite.setRotation(_rotation);

}

SnakeBody::SnakeBody(sf::Vector2f _pos, float _rotation, float _speed, sf::Vector2f _movementDirection, sf::Texture* _texture, std::deque<DirectionChange> _bodyPartdirectionChanges)
{
    // Check if this is correct
    speed = _speed;
    movementDirection = _movementDirection;
    position = _pos;
    texture = _texture;
    sprite.setTexture(*texture);  // Set the texture to the sprite

    // Set initial scale based on the size
    sprite.setScale(SNAKE_BODY_SIZE.x / texture->getSize().x, SNAKE_BODY_SIZE.y / texture->getSize().y);

    // Set the origin to the center of the sprite to prevent jumping on rotation
    sprite.setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);

    // Set the initial position and rotation of the sprite
    sprite.setPosition(_pos);
    sprite.setRotation(_rotation);

    bodyPartdirectionChanges = _bodyPartdirectionChanges;
	// hasTravaledDirectionChangesPath.size = bodyPartdirectionChanges.size();
    // reachedGoalPositionCorrect = false;
}

bool SnakeBody::HasTraveledToGoalPositionCorrect(int globalDequeSize)
{
    if (!hasTravaledDirectionChangesPath.empty() && hasTravaledDirectionChangesPath.back() == true)
    {
        return true;
    }
	return false;
}

void SnakeBody::Update(int screenWidth, int screenHeight)
{
    
}



void SnakeBody::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}