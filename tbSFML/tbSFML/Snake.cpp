#include "Snake.h"


Snake::Snake(sf::Vector2f size, sf::Vector2f _pos, std::unique_ptr<sf::Shape> _shape, float _rotation, float _speed, sf::Vector2f _movementDirection)
    : MovingObject(size, _pos, std::move(_shape), _rotation, _speed, _movementDirection)
{
    
}

void Snake::Update(int screenWidth, int screenHeight)
{
	KeyboardInput(screenWidth, screenHeight);
}

void Snake::KeyboardInput(int screenWidth, int screenHeight)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        position.x -= 10.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        position.x += 10.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        position.y -= 10.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        position.y += 10.0f;
    }

	IsOutOfScreen(screenWidth, screenHeight);

	shape->setPosition(position);

}

// Why is size 0, 0 event tough it is assigned in the constructor
void Snake::IsOutOfScreen(int screenWidth, int screenHeight)
{

    if (position.x > screenWidth - size.x)
    {

        position.x = float(screenWidth - size.x);
    }
    else if (position.x < 0)
    {

        position.x = 0;
    }

    if (position.y > screenHeight - size.y)
    {

        position.y = float(screenHeight - size.x);
    }
    else if (position.y < 0)
    {

        position.y = 0;
    }

}