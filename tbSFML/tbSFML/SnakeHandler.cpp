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

    this->headTexture->loadFromFile("img/circleTexture2.png");

    this->bodyTexture = new sf::Texture();
    this->bodyTexture->loadFromFile("img/circleTexture2.png");


    SnakeBody head(4, 5, 0, DirectionEnum::Right, headTexture);
	GridMap::PlaceObjectInGrid(head.gridRow, head.gridColumn, 2);
    snakeBody.push_back(head);

	sf::Vector2i newPosition = DirectionToVector(head.movementDirection);

    SnakeBody sn1(4 - newPosition.y, 5 - newPosition.x, 0, DirectionEnum::Right, this->bodyTexture);
    GridMap::PlaceObjectInGrid(sn1.gridRow, sn1.gridColumn, 2);
    snakeBody.push_back(sn1);

    SnakeBody sn2(4 - newPosition.y * 2, 5 - newPosition.x * 2, 0, DirectionEnum::Right, this->bodyTexture);
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

    SnakeBody head(4, 5, 0, DirectionEnum::Right, headTexture);
    GridMap::PlaceObjectInGrid(head.gridRow, head.gridColumn, 2);
    snakeBody.push_back(head);

    sf::Vector2i newPosition = DirectionToVector(head.movementDirection);

    SnakeBody sn1(4 - newPosition.y, 5 - newPosition.x, 0, DirectionEnum::Right, this->bodyTexture);
    GridMap::PlaceObjectInGrid(sn1.gridRow, sn1.gridColumn, 2);
    snakeBody.push_back(sn1);

    SnakeBody sn2(4 - newPosition.y * 2, 5 - newPosition.x * 2, 0, DirectionEnum::Right, this->bodyTexture);
    GridMap::PlaceObjectInGrid(sn2.gridRow, sn2.gridColumn, 2);
    snakeBody.push_back(sn2);


    // Set snakeHead pointer to the first element of the deque
    snakeHead = &snakeBody.front(); // Use address-of operator to get a pointer


}

sf::Vector2i SnakeHandler::DirectionToVector(DirectionEnum direction) 
{
    switch (direction) 
    {
    case DirectionEnum::Up:
        return sf::Vector2i(0, -1); // Move up (decrease y)

    case DirectionEnum::Down:
        return sf::Vector2i(0, 1);  // Move down (increase y)

    case DirectionEnum::Left:
        return sf::Vector2i(-1, 0); // Move left (decrease x)

    case DirectionEnum::Right:
        return sf::Vector2i(1, 0);  // Move right (increase x)

    default:
        return sf::Vector2i(0, 0);  // No movement for an undefined direction
    }
}

void SnakeHandler::DetermineNewRowColumn(SnakeBody sn) 
{

    if (sn.movementDirection == DirectionEnum::Right) 
    {
        sn.gridColumn++;
        
    }
    else if (sn.movementDirection == DirectionEnum::Left) 
    {
        sn.gridColumn--;
    }

    if (sn.movementDirection == DirectionEnum::Down)
    {
        sn.gridRow++;
    }
    else if (sn.movementDirection == DirectionEnum::Up)
    {
        sn.gridRow--;
    }

}


void SnakeHandler::DetermineNewRowColumn(SnakeBody* sn)
{
    if (sn->movementDirection == DirectionEnum::Right)
    {
        sn->gridColumn++;
    }
    else if (sn->movementDirection == DirectionEnum::Left)
    {
        sn->gridColumn--;
    }

    if (sn->movementDirection == DirectionEnum::Down)
    {
        sn->gridRow++;
    }
    else if (sn->movementDirection == DirectionEnum::Up)
    {
        sn->gridRow--;
    }

}

void SnakeHandler::KeyboardInput(int screenWidth, int screenHeight, GameStatesManager* gameStatesManger )
{

        // Ensure that the snake cannot do a 180 degree turn from current rotation, and that it is not already traveling in that direction
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snakeHead->movementDirection != DirectionEnum::Right && snakeHead->movementDirection != DirectionEnum::Left)
        {
            snakeHead->movementDirection = DirectionEnum::Left;
            snakeHead->sprite.setRotation(90);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snakeHead->movementDirection != DirectionEnum::Left && snakeHead->movementDirection != DirectionEnum::Right)
        {


            snakeHead->movementDirection = DirectionEnum::Right;
            snakeHead->sprite.setRotation(270);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snakeHead->movementDirection != DirectionEnum::Down && snakeHead->movementDirection != DirectionEnum::Up)
        {
            snakeHead->movementDirection = DirectionEnum::Up;
            snakeHead->sprite.setRotation(180);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snakeHead->movementDirection != DirectionEnum::Down && snakeHead->movementDirection != DirectionEnum::Up)
        {

            snakeHead->movementDirection = DirectionEnum::Down;
            snakeHead->sprite.setRotation(0);
        }

	UpdateBodyPostion(gameStatesManger);
}


void SnakeHandler::CheckIfOutOfScreen(SnakeBody* snNewHead, sf::Vector2i* newHeadPos, GameStatesManager * gameStatesManager)
{
    // Create the ability to go out of the screen and then return from the other side
    if (newHeadPos->y >= GridMap::columnsWide)
    {
		// By setting the newHeadPos to 0, we can return from the other side, since the new head's row index is going to be set to 0
        newHeadPos->y = 0;
    }
    else if (newHeadPos->y < 0)
    {
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
    sf::Vector2i headMovementDelta = DirectionToVector(head.movementDirection);

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

    GridMap::PlaceObjectInGrid(lastBodyPart.gridRow, lastBodyPart.gridColumn, 2);

    // Update deque: remove last body part from the back and insert it at the front as the new head
    snakeBody.pop_back();
    snakeBody.push_front(lastBodyPart);

    // snakeBody.front() now represents the new head after this update
    snakeHead = &snakeBody.front();
}

void SnakeHandler::IsCollidedWithSelf(GameStatesManager* gameStateManager, sf::Vector2i newHeadPos)
{

    // Check in all three directions front, left, right

    // Check if the head's row or col index is the same as another body parts   
    // 2 indicates that there is a body part there 

    if (GridMap::gridMap[newHeadPos.x][newHeadPos.y] == 2)
    {
		gameStateManager->currentGameState = GameStatesEnum::GameOver;
        return;
    }

}

void SnakeHandler::IsCollidedWithApple(FoodHandler& foodHandler) 
{
    for (Food apple : foodHandler.foodOnScreen)
    {
        if (snakeHead->gridColumn == apple.columnIndex && snakeHead->gridRow == apple.rowIndex)
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

    sf::Vector2i newPosition = DirectionToVector(lastBodyPart.movementDirection);

    // Set the position based on the snakes movement and the last body parts position

    SnakeBody bodyPart(lastBodyPart.gridRow - newPosition.y, lastBodyPart.gridColumn - newPosition.x, lastBodyPart.sprite.getRotation(), lastBodyPart.movementDirection, bodyTexture);
    GridMap::PlaceObjectInGrid(bodyPart.gridRow, bodyPart.gridColumn, 2);
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

void SnakeHandler::Draw(sf::RenderWindow& window)
{
	for (SnakeBody& body : snakeBody)
	{
		body.Draw(window);
	}
}