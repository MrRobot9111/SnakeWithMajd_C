#include "SnakeHandler.h"
#include "SnakeBody.h"
#include "Constants.h"

SnakeHandler::SnakeHandler(sf::Texture& headTexture) 
{

	// Initialize the snake body with only its head

    SnakeBody head = SnakeBody(sf::Vector2f(400, 500), 0, 1, sf::Vector2f(0, 0), headTexture);
    snakeBody.push_back(head);
    // Change the variable to load body parts instead
    texture.loadFromFile("img/snake_head.png");

}

void SnakeHandler::KeyboardInput(int screenWidth, int screenHeight)
{

    snakeHead.position += snakeHead.movementDirection * snakeHead.speed;

    // Ensure that the snake cannot do a 180 degree turn from current rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snakeHead.movementDirection != sf::Vector2f(1, 0))
    {
        snakeHead.movementDirection = sf::Vector2f(-1, 0);
        snakeHead.sprite.setRotation(90);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snakeHead.movementDirection != sf::Vector2f(-1, 0))
    {
        snakeHead.movementDirection = sf::Vector2f(1, 0);
        snakeHead.sprite.setRotation(270);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snakeHead.movementDirection != sf::Vector2f(0, 1))
    {
        snakeHead.movementDirection = sf::Vector2f(0, -1);
        snakeHead.sprite.setRotation(180);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snakeHead.movementDirection != sf::Vector2f(0, -1))
    {
        snakeHead.movementDirection = sf::Vector2f(0, 1);
        snakeHead.sprite.setRotation(0);
    }



    CheckIfOutOfScreen(screenWidth, screenHeight);

    snakeHead.sprite.setPosition(snakeHead.position);

}

void SnakeHandler::CheckIfOutOfScreen(int screenWidth, int screenHeight)
{
    // If the snake is outside the screen, then it is dead
    if (snakeHead.position.x > float(screenWidth + SNAKE_BODY_SIZE.x / 2.f))
    {

        snakeHead.position.x = float(screenWidth + SNAKE_BODY_SIZE.x / 2.f);
    }
    else if (snakeHead.position.x < 0)
    {

        snakeHead.position.x = 0;
    }

    if (snakeHead.position.y > float(screenHeight + SNAKE_BODY_SIZE.y / 2.f))
    {

        snakeHead.position.y = float(screenHeight + SNAKE_BODY_SIZE.y / 2.f);
    }
    else if (snakeHead.position.y < 0)
    {

        snakeHead.position.y = 0;
    }

}

void SnakeHandler::Grow()
{


    // Get the last body part (the tail)
    const SnakeBody& lastBodyPart = snakeBody.back();

    // Calculate the new position based on the movement direction of the last body part
    sf::Vector2f adjustedNewPosition = lastBodyPart.position -
        sf::Vector2f(SNAKE_BODY_SIZE.x * lastBodyPart.movementDirection.x,
            SNAKE_BODY_SIZE.y * lastBodyPart.movementDirection.y);

    // Create the new body part and add it to the snake
    SnakeBody bodyPart(adjustedNewPosition, 0, 1, lastBodyPart.movementDirection, texture);

    // Add the new body part to the back of the snake
    snakeBody.push_back(bodyPart);
}

void SnakeHandler::Update(sf::RenderWindow& window, int screenWidth, int screenHeight)
{
    KeyboardInput(screenWidth, screenHeight);
	// Test to spawn more snake parts
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		Grow();
	}

    Draw(window);
}

void SnakeHandler::Draw(sf::RenderWindow& window)
{
	for (SnakeBody& body : snakeBody)
	{
		body.Draw(window);
	}
}