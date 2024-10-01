#include "SnakeBody.h"



SnakeBody::SnakeBody(sf::Vector2f _size, sf::Vector2f _pos, float _rotation, float _speed, sf::Vector2f _movementDirection, sf::Texture& _texture)
{
    // Check if this is correct
    size = _size;
    speed = _speed;
    movementDirection = _movementDirection;   
    position = _pos;
    texture = _texture;

    sprite.setTexture(texture);  // Set the texture to the sprite

    // Set initial scale based on the size
    sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);

    // Set the initial position and rotation of the sprite
    sprite.setPosition(_pos);
    sprite.setRotation(_rotation);

}

void SnakeBody::Update(int screenWidth, int screenHeight)
{
    KeyboardInput(screenWidth, screenHeight);
}

void SnakeBody::KeyboardInput(int screenWidth, int screenHeight)
{

    position += movementDirection * speed;

    // Ensure that the snake cannot do a 180 degree turn from current rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && movementDirection != sf::Vector2f(1, 0))
    {
        movementDirection = sf::Vector2f(-1, 0);
        sprite.setRotation(90);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && movementDirection != sf::Vector2f(-1, 0))
    {
        movementDirection = sf::Vector2f(1, 0);
        sprite.setRotation(270);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && movementDirection != sf::Vector2f(0, 1))
    {
        movementDirection = sf::Vector2f(0, -1);
        sprite.setRotation(180);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && movementDirection != sf::Vector2f(0, -1))
    {
        movementDirection = sf::Vector2f(0, 1);
        sprite.setRotation(0);
    }



    CheckIfOutOfScreen(screenWidth, screenHeight);

    sprite.setPosition(position);

}


void SnakeBody::CheckIfOutOfScreen(int screenWidth, int screenHeight)
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

void SnakeBody::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}