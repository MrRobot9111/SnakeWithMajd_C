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


SnakeHandler::SnakeHandler(sf::Texture* headTexture)
{
    // Initialize the snake body with only its head
    SnakeBody head(sf::Vector2f(400, 500), 0, 1, sf::Vector2f(0, 0), headTexture);
    snakeBody.push_back(head);

    sf::Vector2f distanceOffeset = sf::Vector2f(20.0f, 20.0f);

    sf::Vector2f adjustedPosition = sf::Vector2f(distanceOffeset.x * head.movementDirection.x, distanceOffeset.y * head.movementDirection.y) + head.position;

    //snakeBody.push_back(SnakeBody(adjustedPosition, 0, 1, sf::Vector2f(0, 0), headTexture));

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

void SnakeHandler::KeyboardInput(int screenWidth, int screenHeight)
{
    // Update the position using the arrow operator
    snakeHead->position += snakeHead->movementDirection * snakeHead->speed;

	// Ensure that the snake cannot do a 180 degree turn from current rotation, and that it is not already traveling in that direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snakeHead->movementDirection != sf::Vector2f(1, 0) && snakeHead->movementDirection != sf::Vector2f(-1, 0))
    {
        snakeHead->movementDirection = sf::Vector2f(-1, 0);
        headTurnPositions.push_back(snakeHead->position);
        snakeHead->sprite.setRotation(90);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snakeHead->movementDirection != sf::Vector2f(-1, 0) && snakeHead->movementDirection != sf::Vector2f(1, 0))
    {
        snakeHead->movementDirection = sf::Vector2f(1, 0);
        headTurnPositions.push_back(snakeHead->position);
        snakeHead->sprite.setRotation(270);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snakeHead->movementDirection != sf::Vector2f(0, 1) && snakeHead->movementDirection != sf::Vector2f(0, -1))
    {
        snakeHead->movementDirection = sf::Vector2f(0, -1);
        headTurnPositions.push_back(snakeHead->position);
        snakeHead->sprite.setRotation(180);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snakeHead->movementDirection != sf::Vector2f(0, -1) && snakeHead->movementDirection != sf::Vector2f(0, 1))
    {
        snakeHead->movementDirection = sf::Vector2f(0, 1);
        headTurnPositions.push_back(snakeHead->position);
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

        // Find out the direct to the next body part, since there can only be a difference in x or y based on the next parts previous position, therefore we need to 
        // check the coordinates to get it working

        // Check the direction where the current body part should move based on the previous
        // The previous position should be stored as a goal position, and when that position is reached (or more), the update the direct, and the new goal position

        // Check to see if the body part has reached its goal position, if so, then update the movement direction

        // Set the movement direction based on the next body part

        // Check if the current body part has reached its goalPosition
        if (currentPart.position == currentPart.goalPosition || currentPart.goalPosition == unsetPosition) {
            // Assign the previous part's last turn position as the goal
            if (!headTurnPositions.empty()) {
                currentPart.goalPosition = headTurnPositions.front();
                currentPart.movementDirection = DetermineDirection(currentPart.position, currentPart.goalPosition);
            }
        }


        // Move the body part towards the goal position
        sf::Vector2f movementStep = currentPart.movementDirection * currentPart.speed;

        // It has overshoot its goal position
        if (currentPart.position.x + movementStep.x > currentPart.goalPosition.x && currentPart.movementDirection.x > 0)
        {
            // Adjust to the goal position
			currentPart.position = currentPart.goalPosition;
        }
        else if (currentPart.position.x + movementStep.x < currentPart.goalPosition.x && currentPart.movementDirection.x < 0)
        {
            currentPart.position = currentPart.goalPosition;
        }

        // It has overshoot its goal position
        if (currentPart.position.y + movementStep.y > currentPart.goalPosition.y && currentPart.movementDirection.y > 0) {
			currentPart.position = currentPart.goalPosition;
		}
        else if (currentPart.position.y + movementStep.y < currentPart.goalPosition.y && currentPart.movementDirection.y < 0)
        {
			currentPart.position = currentPart.goalPosition;
        }

		// If it is the last part of the snake, and it has reached its goals position, remove that goal position
        if (currentPart.position == currentPart.goalPosition && snakeBody.size() - 1 == i && headTurnPositions.size() != 0)
        {
            headTurnPositions.pop_front();
        }
        else if (headTurnPositions.size() == 0) 
        {
			// Set the snakes current position as the goal position
			headTurnPositions.push_back(snakeHead->position);
        }


        // Update before the checks - move it!!!
        snakeBody[i].position += snakeBody[i].movementDirection * snakeBody[i].speed;


        // Move each body part to the position of the part in front of it - better than updating all the body parts direction, position etc...
        //snakeBody[i].position = snakeBody[i - 1].position; // Move to the position of the previous part, but try to 

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