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
    SnakeBody head(4, 5, 270, SNAKE_SPEED, sf::Vector2f(1, 0), headTexture);
    snakeBody.push_back(head);


    snakeBody.push_back(SnakeBody(4, 4, 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture));
    snakeBody.push_back(SnakeBody(4, 3, 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture));


    // Set snakeHead pointer to the first element of the deque
    snakeHead = &snakeBody.front(); // Use address-of operator to get a pointer



}

void SnakeHandler::ResetSnake() 
{
    snakeBody.clear();
	globalDirectionChanges.clear();

    // Is this the optimal way to reset the snake?

    SnakeBody head(4, 5, 270, SNAKE_SPEED, sf::Vector2f(1, 0), headTexture);
    snakeBody.push_back(head);


    snakeBody.push_back(SnakeBody(4, 4, 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture));
    snakeBody.push_back(SnakeBody(4, 3, 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture));


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
    // Update the position using the arrow operator
    DetermineNewRowColumn(snakeHead);

    // Prevent too sharp turns
    if (KeydownTimeElapsed()) 
    {
        // Ensure that the snake cannot do a 180 degree turn from current rotation, and that it is not already traveling in that direction
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snakeHead->movementDirection != sf::Vector2f(1, 0) && snakeHead->movementDirection != sf::Vector2f(-1, 0))
        {
            // Store the old movement direction, and the position of the turn

            snakeHead->movementDirection = sf::Vector2f(-1, 0);
            snakeHead->sprite.setRotation(90);

			// Add the changes to the deque, so that the other body parts can follow

			globalDirectionChanges.push_back({ snakeHead->gridColumn, snakeHead->gridRow, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snakeHead->movementDirection != sf::Vector2f(-1, 0) && snakeHead->movementDirection != sf::Vector2f(1, 0))
        {


            snakeHead->movementDirection = sf::Vector2f(1, 0);
            snakeHead->sprite.setRotation(270);

            // Add the changes to the deque, so that the other body parts can follow

            globalDirectionChanges.push_back({ snakeHead->gridColumn, snakeHead->gridRow, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snakeHead->movementDirection != sf::Vector2f(0, 1) && snakeHead->movementDirection != sf::Vector2f(0, -1))
        {



            snakeHead->movementDirection = sf::Vector2f(0, -1);
            snakeHead->sprite.setRotation(180);

            // Add the changes to the deque, so that the other body parts can follow

            globalDirectionChanges.push_back({ snakeHead->gridColumn, snakeHead->gridRow, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snakeHead->movementDirection != sf::Vector2f(0, -1) && snakeHead->movementDirection != sf::Vector2f(0, 1))
        {

            snakeHead->movementDirection = sf::Vector2f(0, 1);
            snakeHead->sprite.setRotation(0);

            // Add the changes to the deque, so that the other body parts can follow

            globalDirectionChanges.push_back({ snakeHead->gridColumn, snakeHead->gridRow, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
        }
    }



    CheckIfOutOfScreen(screenWidth, screenHeight, gameStatesManger);
	UpdateBodyPostion(gameStatesManger);
}


void SnakeHandler::CheckIfOutOfScreen(int screenWidth, int screenHeight, GameStatesManager * gameStatesManager)
{
    // Create the ability to go out of the screen and then return from the other side
    if (snakeHead->gridColumn > GridMap::columnsWide)
    {
        snakeHead->gridColumn = 0;
        snakeHead->movementDirection = sf::Vector2f(-1, 0); // Reverse the direction and save the new direction to global directions
        globalDirectionChanges.push_back({ snakeHead->gridColumn, snakeHead->gridRow, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
    }
    else if (snakeHead->gridColumn < 0)
    {
        snakeHead->gridColumn = GridMap::columnsWide;
        snakeHead->movementDirection = sf::Vector2f(1, 0); // Reverse the direction and save the new direction to global directions
        globalDirectionChanges.push_back({ snakeHead->gridColumn, snakeHead->gridRow, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
    }

    if (snakeHead->gridRow < 0)
    {
        gameStatesManager->currentGameState = GameStatesEnum::GameOver;
        snakeHead->gridRow = 0;
    }
    else if (snakeHead->gridRow > GridMap::rowsWide)
    {
        gameStatesManager->currentGameState = GameStatesEnum::GameOver;
        snakeHead->gridRow = GridMap::rowsWide;
    }
}

void SnakeHandler::UpdateBodyPostion(GameStatesManager* gameStatesManager) 
{
    bool decreaseIndex = false; // Used to check if the index should be decreased based on if an element was removed or not

    for (size_t i = snakeBody.size() - 1; i > 0; --i)
    {

        SnakeBody& currentPart = snakeBody[i];

        DetermineNewRowColumn(currentPart);

        IsCollidedWithSelf(currentPart, gameStatesManager); // Check if the part has collided with the head
    }
}

void SnakeHandler::IsCollidedWithSelf(SnakeBody snakeBodyPart, GameStatesManager* gameStateManager)
{
    // Check if the head's row or col index is the same as another body parts   
    if (snakeBodyPart.gridColumn == snakeHead->gridColumn && snakeBodyPart.gridRow == snakeHead->gridRow) {
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

    SnakeBody bodyPart(lastBodyPart.gridColumn, lastBodyPart.gridRow, lastBodyPart.sprite.getRotation(), SNAKE_SPEED, lastBodyPart.movementDirection, bodyTexture);
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