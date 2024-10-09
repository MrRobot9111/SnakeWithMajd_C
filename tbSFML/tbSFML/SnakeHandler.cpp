#include "SnakeHandler.h"
#include "SnakeBody.h"
#include "Constants.h"
#include <optional>


/*
float goalX = 0, goalY = 0;
float dirX = 1;
float dirY = 0;
*/

// Set an "unset" position for goalPosition
sf::Vector2f unsetPosition(-1.0f, -1.0f);
const float BODY_PART_DISTANCE = 20.0f;

SnakeHandler::SnakeHandler(sf::Texture* headTexture)
{
    // Initialize the snake body with only its head
    SnakeBody head(sf::Vector2f(400, 500), 0, 1, sf::Vector2f(1, 0), headTexture);
    snakeBody.push_back(head);

    sf::Vector2f distanceOffeset = sf::Vector2f(50.0f, 50.0f);

    sf::Vector2f adjustedPosition = head.position - sf::Vector2f(distanceOffeset.x * head.movementDirection.x, distanceOffeset.y * head.movementDirection.y) + head.position;

    snakeBody.push_back(SnakeBody(adjustedPosition, 0, 1, sf::Vector2f(1, 0), headTexture));
    snakeBody.push_back(SnakeBody(adjustedPosition - distanceOffeset, 0, 1, sf::Vector2f(1, 0), headTexture));


    // Set snakeHead pointer to the first element of the deque
    snakeHead = &snakeBody.front(); // Use address-of operator to get a pointer

    texture = new sf::Texture();
    // Load texture for the head, if needed
    texture->loadFromFile("img/snake_head.png");

    /*
    goalX = snakeBody[0].position.x;
    goalY = snakeBody[0].position.y + 50;
    */
}

// Add a delay so that errors do not occur
void SnakeHandler::KeyboardInput(int screenWidth, int screenHeight)
{
    // Update the position using the arrow operator
    snakeHead->position += snakeHead->movementDirection * snakeHead->speed;

	// Ensure that the snake cannot do a 180 degree turn from current rotation, and that it is not already traveling in that direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snakeHead->movementDirection != sf::Vector2f(1, 0) && snakeHead->movementDirection != sf::Vector2f(-1, 0))
    {
		// Store the old movement direction, and the position of the turn
		snakeHead->previousMovementDirection = snakeHead->movementDirection;
		snakeHead->movmentDirectionSwitchPosition = snakeHead->position;

        snakeHead->movementDirection = sf::Vector2f(-1, 0);
        snakeHead->sprite.setRotation(90);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snakeHead->movementDirection != sf::Vector2f(-1, 0) && snakeHead->movementDirection != sf::Vector2f(1, 0))
    {
        // Store the old movement direction, and the position of the turn
        snakeHead->previousMovementDirection = snakeHead->movementDirection;
        snakeHead->movmentDirectionSwitchPosition = snakeHead->position;

        snakeHead->movementDirection = sf::Vector2f(1, 0);
        snakeHead->sprite.setRotation(270);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snakeHead->movementDirection != sf::Vector2f(0, 1) && snakeHead->movementDirection != sf::Vector2f(0, -1))
    {

        // Store the old movement direction, and the position of the turn
        snakeHead->previousMovementDirection = snakeHead->movementDirection;
        snakeHead->movmentDirectionSwitchPosition = snakeHead->position;

        snakeHead->movementDirection = sf::Vector2f(0, -1);
        snakeHead->sprite.setRotation(180);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snakeHead->movementDirection != sf::Vector2f(0, -1) && snakeHead->movementDirection != sf::Vector2f(0, 1))
    {

        // Store the old movement direction, and the position of the turn
        snakeHead->previousMovementDirection = snakeHead->movementDirection;
        snakeHead->movmentDirectionSwitchPosition = snakeHead->position;

        snakeHead->movementDirection = sf::Vector2f(0, 1);
        snakeHead->sprite.setRotation(0);
    }

    CheckIfOutOfScreen(screenWidth, screenHeight);

    // Set the position of the sprite
    snakeHead->sprite.setPosition(snakeHead->position);
	UpdateBodyPostion();
}

void SnakeHandler::CheckIfOutOfScreen(int screenWidth, int screenHeight)
{
    // If the snake is outside the screen, then it is dead
    if (snakeHead->position.x > float(screenWidth + SNAKE_BODY_SIZE.x / 2.f))
    {
        snakeHead->position.x = float(screenWidth + SNAKE_BODY_SIZE.x / 2.f);
    }
    else if (snakeHead->position.x < 0)
    {
        snakeHead->position.x = 0;
    }

    if (snakeHead->position.y > float(screenHeight + SNAKE_BODY_SIZE.y / 2.f))
    {
        snakeHead->position.y = float(screenHeight + SNAKE_BODY_SIZE.y / 2.f);
    }
    else if (snakeHead->position.y < 0)
    {
        snakeHead->position.y = 0;
    }
}

void SnakeHandler::UpdateBodyPostion() 
{

    // Start from the end of the snake, but exclude the head
    for (size_t i = snakeBody.size() - 1; i > 0; --i)
    {

        SnakeBody& currentPart = snakeBody[i];
        SnakeBody& nextPart = snakeBody[i - 1];

        // The next body part has turned
        if (currentPart.movementDirection != nextPart.movementDirection || currentPart.movementDirection == sf::Vector2f(0.f, 0.f))
        {

            // sf::Vector2f distance = nextPart.movmentDirectionSwitchPosition - currentPart.position;

			// Set the goal position of the current body part to the next's movmentDirectionSwitchPosition

            // Move the body part towards the position were the next body part has turned
            sf::Vector2f movementStep = currentPart.movementDirection * currentPart.speed;

            // It has overshoot its goal position
            if (currentPart.position.x + movementStep.x > nextPart.movmentDirectionSwitchPosition.x && currentPart.movementDirection.x > 0)
            {

				// Set the direction to the previous direction, so that the other body pat can follow
                currentPart.previousMovementDirection = currentPart.movementDirection;

                // Adjust to the goal position, and set the movement direction to the same as the next body part
                currentPart.position = nextPart.movmentDirectionSwitchPosition;
				currentPart.movementDirection = nextPart.movementDirection;

                // Set the goal position of the next body part to the current's movmentDirectionSwitchPosition
                currentPart.movmentDirectionSwitchPosition = currentPart.position;

            }

            else if (currentPart.position.x + movementStep.x < nextPart.movmentDirectionSwitchPosition.x && currentPart.movementDirection.x < 0)
            {
                // Set the direction to the previous direction, so that the other body pat can follow
                currentPart.previousMovementDirection = currentPart.movementDirection;

                // Adjust to the goal position, and set the movement direction to the same as the next body part
                currentPart.position = nextPart.movmentDirectionSwitchPosition;
                currentPart.movementDirection = nextPart.movementDirection;

                // Set the goal position of the next body part to the current's movmentDirectionSwitchPosition
                currentPart.movmentDirectionSwitchPosition = currentPart.position;
            }


            if (currentPart.position.y + movementStep.y > nextPart.movmentDirectionSwitchPosition.y && currentPart.movementDirection.y > 0) {
                // Set the direction to the previous direction, so that the other body pat can follow
                currentPart.previousMovementDirection = currentPart.movementDirection;

                // Adjust to the goal position, and set the movement direction to the same as the next body part
                currentPart.position = nextPart.movmentDirectionSwitchPosition;
                currentPart.movementDirection = nextPart.movementDirection;

                // Set the goal position of the next body part to the current's movmentDirectionSwitchPosition
                currentPart.movmentDirectionSwitchPosition = currentPart.position;
            }

            else if (currentPart.position.y + movementStep.y < nextPart.movmentDirectionSwitchPosition.y && currentPart.movementDirection.y < 0)
            {
                // Set the direction to the previous direction, so that the other body pat can follow
                currentPart.previousMovementDirection = currentPart.movementDirection;

                // Adjust to the goal position, and set the movement direction to the same as the next body part
                currentPart.position = nextPart.movmentDirectionSwitchPosition;
                currentPart.movementDirection = nextPart.movementDirection;

                // Set the goal position of the next body part to the current's movmentDirectionSwitchPosition
                currentPart.movmentDirectionSwitchPosition = currentPart.position;
            }

        }

        snakeBody[i].position += snakeBody[i].movementDirection * snakeBody[i].speed;

        snakeBody[i].sprite.setPosition(snakeBody[i].position); 
    }
    /*
    snakeBody[1].position.x += dirX;
    snakeBody[1].position.y += dirY;
    if (snakeBody[1].position.x > goalX)
    {
        snakeBody[1].position.x = goalX;
        dirX = 0;
        dirY = 1;
    }

    if (snakeBody[1].position.y > goalY)
    {
        snakeBody[1].position.y = goalY;
        dirX = 1;
        dirY = 0;
    }
    */

}

sf::Vector2f SnakeHandler::DetermineDirection(const sf::Vector2f& currentPos, const sf::Vector2f& goalPos) 
{
    if (currentPos.x > goalPos.x)
    {
		return sf::Vector2f(-1, 0);
    }
    else if (currentPos.x < goalPos.x)
    {
        return sf::Vector2f(1, 0);
    }

    if (currentPos.y < goalPos.y)
    {
        return sf::Vector2f(0, 1);
    }
    else if (currentPos.y > goalPos.y)
    {
        return sf::Vector2f(0, -1);
    }

    return sf::Vector2f(0, 0);
}

void SnakeHandler::Grow()
{
    // Distance between body parts
    sf::Vector2f distanceOffeset = sf::Vector2f(20.0f, 20.0f);

    // Get the last body part (the tail)
    const SnakeBody& lastBodyPart = snakeBody.back();

	// Calculate the new position based on the movement direction of the last body part - a bad idea, it is perhaps better to calculate the new position based on the last body part's position
	// Or even better we create the new body part based on the last body part

    sf::Vector2f adjustedPosition = lastBodyPart.position - sf::Vector2f(distanceOffeset.x * lastBodyPart.movementDirection.x, distanceOffeset.y * lastBodyPart.movementDirection.y) ;
    
    // Create the new body part and add it to the snake

    float rotation = lastBodyPart.rotation;

    SnakeBody bodyPart(adjustedPosition, 0, 1, lastBodyPart.movementDirection, texture);
    snakeBody.push_back(bodyPart);
	UpdateBodyPostion(); // We update the the whole body so that the new is slightly behind the old
    // Add the new body part to the back of the snake

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