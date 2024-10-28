#include "SnakeHandler.h"
#include "SnakeBody.h"
#include "Constants.h"
#include "DirectionChange.h"
#include "FoodHandler.h"
#include "GameStatesManager.h"
#include "GameStatesEnum.h"
#include "GridMap.h"
#include <optional>
#include <deque>


SnakeHandler::SnakeHandler(sf::Texture* headTexture2, sf::Texture* bodyTexture2)
{

    this->headTexture = new sf::Texture();
    // Load texture for the head, if needed
    this->headTexture->loadFromFile("img/snake_head.png");

    this->bodyTexture = new sf::Texture();
    this->bodyTexture->loadFromFile("img/circleTexture2.png");

    // Initialize the snake body with only its head
    SnakeBody head(4, 5, 0, SNAKE_SPEED, sf::Vector2f(1, 0), headTexture);
	GridMap::PlaceObjectInGrid(head.gridRow, head.gridColumn, 2);
    snakeBody.push_back(head);

	sf::Vector2i newPosition = CalculateNewPosition(head);

    SnakeBody sn1(4 - newPosition.y, 5 - newPosition.x, 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture);
    GridMap::PlaceObjectInGrid(sn1.gridRow, sn1.gridColumn, 2);
    snakeBody.push_back(sn1);

    SnakeBody sn2(4 - newPosition.y * 2, 5 - newPosition.x * 2, 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture);
    GridMap::PlaceObjectInGrid(sn2.gridRow, sn2.gridColumn, 2);
    snakeBody.push_back(sn2);


    // Set snakeHead pointer to the first element of the deque
    snakeHead = &snakeBody.front(); // Use address-of operator to get a pointer



}

void SnakeHandler::ResetSnakeGrid() 
{
    for (SnakeBody sn : snakeBody) 
    {
        GridMap::PlaceObjectInGrid(sn.gridRow, sn.gridColumn, 0);
    }
}

void SnakeHandler::ResetSnake() 
{
    ResetSnakeGrid();
    snakeBody.clear();

    // Is this the optimal way to reset the snake?

    SnakeBody head(4, 5, 0, SNAKE_SPEED, sf::Vector2f(1, 0), headTexture);
    GridMap::PlaceObjectInGrid(head.gridRow, head.gridColumn, 2);
    snakeBody.push_back(head);

    sf::Vector2i newPosition = CalculateNewPosition(head);

    // Do not forget to place these objects inside of a gridmap

    SnakeBody sn1(4 - newPosition.y, 5 - newPosition.x, 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture);
    GridMap::PlaceObjectInGrid(sn1.gridRow, sn1.gridColumn, 2);
    snakeBody.push_back(sn1);

    SnakeBody sn2(4 - newPosition.y * 2, 5 - newPosition.x * 2, 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture);
    GridMap::PlaceObjectInGrid(sn2.gridRow, sn2.gridColumn, 2);
    snakeBody.push_back(sn2);


    // Set snakeHead pointer to the first element of the deque
    snakeHead = &snakeBody.front(); // Use address-of operator to get a pointer


}

void SnakeHandler::DetermineNewRowColumn(SnakeBody sn) 
{
    // Use enums to handle direction alter

    if (sn.movementDirection == sf::Vector2f(1, 0)) 
    {
        sn.gridColumn++;
        
    }
    else if (sn.movementDirection == sf::Vector2f(-1, 0)) 
    {
        sn.gridColumn--;
    }

    if (sn.movementDirection == sf::Vector2f(0, 1))
    {
        sn.gridRow++;
    }
    else if (sn.movementDirection == sf::Vector2f(0, -1))
    {
        sn.gridRow--;
    }

}

sf::Vector2i SnakeHandler::CalculateNewPosition(SnakeBody sn)
{
    // Use enums to handle direction alter

    if (sn.movementDirection == sf::Vector2f(1, 0))
    {
        return sf::Vector2i(1, 0);

    }
    else if (sn.movementDirection == sf::Vector2f(-1, 0))
    {
        return sf::Vector2i(-1, 0);
    }

    if (sn.movementDirection == sf::Vector2f(0, 1))
    {
        return sf::Vector2i(0, 1);
    }
    else if (sn.movementDirection == sf::Vector2f(0, -1))
    {
        return sf::Vector2i(0, -1);
    }

}

sf::Vector2i SnakeHandler::CalculateNewPosition(SnakeBody* sn)
{
    // Use enums to handle direction alter

    if (sn->movementDirection == sf::Vector2f(1, 0))
    {
        return sf::Vector2i(1, 0);

    }
    else if (sn->movementDirection == sf::Vector2f(-1, 0))
    {
        return sf::Vector2i(-1, 0);
    }

    if (sn->movementDirection == sf::Vector2f(0, 1))
    {
        return sf::Vector2i(0, 1);
    }
    else if (sn->movementDirection == sf::Vector2f(0, -1))
    {
        return sf::Vector2i(0, -1);
    }

}


void SnakeHandler::DetermineNewRowColumn(SnakeBody* sn)
{
    // Use enums to handle direction alter

    if (sn->movementDirection == sf::Vector2f(1, 0))
    {
        sn->gridColumn++;
    }
    else if (sn->movementDirection == sf::Vector2f(-1, 0))
    {
        sn->gridColumn--;
    }

    if (sn->movementDirection == sf::Vector2f(0, 1))
    {
        sn->gridRow++;
    }
    else if (sn->movementDirection == sf::Vector2f(0, -1))
    {
        sn->gridRow--;
    }

}

// Add a delay so that errors do not occur
void SnakeHandler::KeyboardInput(int screenWidth, int screenHeight, GameStatesManager* gameStatesManger )
{

        // Ensure that the snake cannot do a 180 degree turn from current rotation, and that it is not already traveling in that direction
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snakeHead->movementDirection != sf::Vector2f(1, 0) && snakeHead->movementDirection != sf::Vector2f(-1, 0))
        {
            // Store the old movement direction, and the position of the turn

            snakeHead->movementDirection = sf::Vector2f(-1, 0);
            snakeHead->sprite.setRotation(90);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snakeHead->movementDirection != sf::Vector2f(-1, 0) && snakeHead->movementDirection != sf::Vector2f(1, 0))
        {


            snakeHead->movementDirection = sf::Vector2f(1, 0);
            snakeHead->sprite.setRotation(270);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snakeHead->movementDirection != sf::Vector2f(0, 1) && snakeHead->movementDirection != sf::Vector2f(0, -1))
        {



            snakeHead->movementDirection = sf::Vector2f(0, -1);
            snakeHead->sprite.setRotation(180);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snakeHead->movementDirection != sf::Vector2f(0, -1) && snakeHead->movementDirection != sf::Vector2f(0, 1))
        {

            snakeHead->movementDirection = sf::Vector2f(0, 1);
            snakeHead->sprite.setRotation(0);
        }

	UpdateBodyPostion(gameStatesManger);
}


void SnakeHandler::CheckIfOutOfScreen(SnakeBody* snNewHead, sf::Vector2i* newHeadPos, GameStatesManager * gameStatesManager)
{
    // Create the ability to go out of the screen and then return from the other side
    if (newHeadPos->y >= GridMap::columnsWide)
    {
        // The snakes body part that is going to be the new head must have a new grid, row and col, and sprite position
        snNewHead->gridColumn = 0;
        newHeadPos->y = 0;
    }
    else if (newHeadPos->y < 0)
    {
        snNewHead->gridColumn = GridMap::columnsWide - 1;
        newHeadPos->y = GridMap::columnsWide - 1;
        
    }

    if (newHeadPos->x < 0)
    {
        gameStatesManager->currentGameState = GameStatesEnum::GameOver;
        newHeadPos->x = 0;
    }
    else if (newHeadPos->x >= GridMap::rowsWide)
    {
        gameStatesManager->currentGameState = GameStatesEnum::GameOver;
        newHeadPos->x = GridMap::rowsWide - 1;
    }
}

void SnakeHandler::UpdateBodyPostion(GameStatesManager* gameStatesManager) 
{
    // The head is the first element in the deque
    SnakeBody& head = snakeBody.front();

    // Fetch the last body part, which is at the end of the deque
    SnakeBody& lastBodyPart = snakeBody.back();

    // Calculate the change in position (delta) for the head based on its movement direction
    sf::Vector2i headMovementDelta = CalculateNewPosition(head);



    // Determine the new head position based on current head position and movement direction
    sf::Vector2i newHeadPosition = sf::Vector2i(head.gridRow + headMovementDelta.y,
        head.gridColumn + headMovementDelta.x);

    // Clear the grid position of the last body part
    GridMap::PlaceObjectInGrid(lastBodyPart.gridRow, lastBodyPart.gridColumn, 0);

    // Check if the head is going to be outside of the grid
    CheckIfOutOfScreen(&lastBodyPart, &newHeadPosition, gameStatesManager);



    // Check the position of were the head is going to be placed before it is placed there
    IsCollidedWithSelf(gameStatesManager, newHeadPosition);

    // Move the last body part to the new head position and update its direction
    lastBodyPart.SetNewSpritePosition(newHeadPosition.x, newHeadPosition.y);
    lastBodyPart.movementDirection = head.movementDirection;

    // Why do I get gridCol = 10 and gridRow = 7?
    GridMap::PlaceObjectInGrid(lastBodyPart.gridRow, lastBodyPart.gridColumn, 2);

    // Update deque: remove last body part from the back and insert it at the front as the new head
    snakeBody.pop_back();
    snakeBody.push_front(lastBodyPart);

    // `snakeBody.front()` now represents the new head after this update
    snakeHead = &snakeBody.front();

    // Check for collisions with itself after updating the position


}

void SnakeHandler::IsCollidedWithSelf(GameStatesManager* gameStateManager, sf::Vector2i newHeadPos)
{

    // Check in all three directions front, left, right

    // Check if the head's row or col index is the same as another body parts   
    // 2 indicates that there is a body part there 
    if (GridMap::gridMap[newHeadPos.x][newHeadPos.y] == 2) // Could be wrong
    {
		gameStateManager->currentGameState = GameStatesEnum::GameOver;
        return;
    }

}

void SnakeHandler::IsCollidedWithApple(FoodHandler& foodHandler) 
{
    for (Food apple : foodHandler.foodOnScreen)
    {
        if (snakeHead->gridColumn == apple.columnIndex && snakeHead->gridRow == apple.rowIndex) // The problem is that the picture is 50x50 in size, but not the head, for the moment we should use 25
        {
			foodHandler.RemoveApple(apple);
            Grow();
            break;
        }
    }
}


void SnakeHandler::Grow()
{
    // Get the last body part (the tail)
    const SnakeBody& lastBodyPart = snakeBody.back();

	// Calculate the new position by using the direction of the last body part if the direction is x+ then the body part should be column - 1

    sf::Vector2i newPosition = CalculateNewPosition(lastBodyPart);

    // Set the position based on the snakes movement and the last body parts position
    // Switch the placement of gridCol and row

    SnakeBody bodyPart(lastBodyPart.gridRow - newPosition.y, lastBodyPart.gridColumn - newPosition.x, lastBodyPart.sprite.getRotation(), SNAKE_SPEED, lastBodyPart.movementDirection, bodyTexture);
    GridMap::PlaceObjectInGrid(lastBodyPart.gridRow, lastBodyPart.gridColumn, 2);
    snakeBody.push_back(bodyPart);
}

void SnakeHandler::Update(sf::RenderWindow& window, int screenWidth, int screenHeight, GameStatesManager* gameStatesManager)
{
    KeyboardInput(screenWidth, screenHeight, gameStatesManager);
	// Test to spawn more snake parts
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		Grow();
	}

    Draw(window);
}

bool SnakeHandler::KeydownTimeElapsed() 
{

    // Get the elapsed time since the last key press
    sf::Time elapsed = clock.getElapsedTime();

    if (elapsed.asSeconds() >= MOVEMENT_COOLDOWN_TIME)
    {
        clock.restart();
		return true;

	}
	return false;
}

void SnakeHandler::Draw(sf::RenderWindow& window)
{
	for (SnakeBody& body : snakeBody)
	{
		body.Draw(window);
	}
}