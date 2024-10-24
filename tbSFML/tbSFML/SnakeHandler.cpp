#include "SnakeHandler.h"
#include "SnakeBody.h"
#include "Constants.h"
#include "DirectionChange.h"
#include "FoodHandler.h"
#include "GameStatesManager.h"
#include "GameStatesEnum.h"
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
    SnakeBody head(sf::Vector2f(400, 500), 0, SNAKE_SPEED, sf::Vector2f(1, 0), headTexture);
    snakeBody.push_back(head);


    // Fixed this, but try more from Chat-GPT 
    sf::Vector2f adjustedPosition = head.position - sf::Vector2f(DISTANCE_OFFSET.x * head.movementDirection.x, DISTANCE_OFFSET.y * head.movementDirection.y);

    snakeBody.push_back(SnakeBody(adjustedPosition, 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture));
    snakeBody.push_back(SnakeBody(adjustedPosition - sf::Vector2f(DISTANCE_OFFSET.x, 0), 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture));


    // Set snakeHead pointer to the first element of the deque
    snakeHead = &snakeBody.front(); // Use address-of operator to get a pointer



}

void SnakeHandler::ResetSnake() 
{
    snakeBody.clear();
	globalDirectionChanges.clear();

    // Is this the optimal way to reset the snake?

    SnakeBody head(sf::Vector2f(400, 500), 0, SNAKE_SPEED, sf::Vector2f(1, 0), headTexture);
    snakeBody.push_back(head);


    // Fixed this, but try more from Chat-GPT 
    sf::Vector2f adjustedPosition = head.position - sf::Vector2f(DISTANCE_OFFSET.x * head.movementDirection.x, DISTANCE_OFFSET.y * head.movementDirection.y);

    snakeBody.push_back(SnakeBody(adjustedPosition, 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture));
    snakeBody.push_back(SnakeBody(adjustedPosition - sf::Vector2f(DISTANCE_OFFSET.x, 0), 0, SNAKE_SPEED, sf::Vector2f(1, 0), this->bodyTexture));


    // Set snakeHead pointer to the first element of the deque
    snakeHead = &snakeBody.front(); // Use address-of operator to get a pointer


}

// Add a delay so that errors do not occur
void SnakeHandler::KeyboardInput(int screenWidth, int screenHeight, GameStatesManager* gameStatesManger )
{
    // Update the position using the arrow operator
    snakeHead->position += snakeHead->movementDirection * snakeHead->speed;

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

			globalDirectionChanges.push_back({ snakeHead->position, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snakeHead->movementDirection != sf::Vector2f(-1, 0) && snakeHead->movementDirection != sf::Vector2f(1, 0))
        {


            snakeHead->movementDirection = sf::Vector2f(1, 0);
            snakeHead->sprite.setRotation(270);

            // Add the changes to the deque, so that the other body parts can follow
            globalDirectionChanges.push_back({ snakeHead->position, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snakeHead->movementDirection != sf::Vector2f(0, 1) && snakeHead->movementDirection != sf::Vector2f(0, -1))
        {



            snakeHead->movementDirection = sf::Vector2f(0, -1);
            snakeHead->sprite.setRotation(180);

            // Add the changes to the deque, so that the other body parts can follow
            globalDirectionChanges.push_back({ snakeHead->position, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snakeHead->movementDirection != sf::Vector2f(0, -1) && snakeHead->movementDirection != sf::Vector2f(0, 1))
        {

            snakeHead->movementDirection = sf::Vector2f(0, 1);
            snakeHead->sprite.setRotation(0);

            // Add the changes to the deque, so that the other body parts can follow
            globalDirectionChanges.push_back({ snakeHead->position, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
        }
    }



    CheckIfOutOfScreen(screenWidth, screenHeight, gameStatesManger);

    // Set the position of the sprite
    snakeHead->sprite.setPosition(snakeHead->position);
	UpdateBodyPostion(gameStatesManger);
}

void SnakeHandler::CheckIfOutOfScreen(int screenWidth, int screenHeight, GameStatesManager* gameStatesManager)
{
    // If the snake is outside the screen, then it is dead
    if (snakeHead->position.x > float(screenWidth + SNAKE_BODY_SIZE.x / 2.f))
    {
        gameStatesManager->currentGameState = GameStatesEnum::GameOver;
        snakeHead->position.x = float(screenWidth + SNAKE_BODY_SIZE.x / 2.f);
    }
    else if (snakeHead->position.x < 0)
    {
        gameStatesManager->currentGameState = GameStatesEnum::GameOver;
        snakeHead->position.x = 0;
    }

    if (snakeHead->position.y > float(screenHeight + SNAKE_BODY_SIZE.y / 2.f))
    {
        gameStatesManager->currentGameState = GameStatesEnum::GameOver;
        snakeHead->position.y = float(screenHeight + SNAKE_BODY_SIZE.y / 2.f);
    }
    else if (snakeHead->position.y < 0)
    {
        gameStatesManager->currentGameState = GameStatesEnum::GameOver;
        snakeHead->position.y = 0;
    }
}

void SnakeHandler::UpdateBodyPostion(GameStatesManager* gameStatesManager) 
{

    // Start from the end of the snake, but exclude the head, which is the first element
    /*
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

				// Set the rotation of the sprite
                currentPart.sprite.setRotation(snakeHead->sprite.getRotation());

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

                currentPart.sprite.setRotation(snakeHead->sprite.getRotation());
            }


            if (currentPart.position.y + movementStep.y > nextPart.movmentDirectionSwitchPosition.y && currentPart.movementDirection.y > 0) {
                // Set the direction to the previous direction, so that the other body pat can follow
                currentPart.previousMovementDirection = currentPart.movementDirection;

                // Adjust to the goal position, and set the movement direction to the same as the next body part
                currentPart.position = nextPart.movmentDirectionSwitchPosition;
                currentPart.movementDirection = nextPart.movementDirection;

                // Set the goal position of the next body part to the current's movmentDirectionSwitchPosition
                currentPart.movmentDirectionSwitchPosition = currentPart.position;

                currentPart.sprite.setRotation(snakeHead->sprite.getRotation());
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

                currentPart.sprite.setRotation(snakeHead->sprite.getRotation());
            }

        }

        snakeBody[i].position += snakeBody[i].movementDirection * snakeBody[i].speed;

        snakeBody[i].sprite.setPosition(snakeBody[i].position); 
    }
    */

    // Start from the end of the snake, but exclude the head, which is the first element
    /*
        for (size_t i = snakeBody.size() - 1; i > 0; --i) 
    {

        SnakeBody& currentPart = snakeBody[i];
        SnakeBody& nextPart = snakeBody[i - 1];

        sf::Vector2f movementStep = currentPart.movementDirection * currentPart.speed;


        if (!globalDirectionChanges.empty()) 
        {
            if (!currentPart.bodyPartdirectionChanges.empty()) 
            {
                // First Direction Change in the list is the oldest one, hence we should start from there
				// Delete the dequeue item once it is reached in the local deque, and once all the body parts of reach it, then remove it entirely from the global deque

				// Move the body part towards the next turning position in the local deque


                // It has overshoot its goal position
				// The first item in the deque is the oldest one
                if (currentPart.position.x + movementStep.x > currentPart.bodyPartdirectionChanges[0].position.x && currentPart.movementDirection.x > 0)
                {
					currentPart.position = currentPart.bodyPartdirectionChanges[0].position;
					currentPart.movementDirection = currentPart.bodyPartdirectionChanges[0].newDirection;

					// Delete the item from the local deque
                    currentPart.bodyPartdirectionChanges.pop_front();
					// Set the hasTravaledDirectionChangesPath item to true, to indicate that the path has been traversed
                    currentPart.hasTravaledDirectionChangesPath.back() = true;
                }

                else if (currentPart.position.x + movementStep.x < currentPart.bodyPartdirectionChanges[0].position.x && currentPart.movementDirection.x < 0)
                {
                    currentPart.position = currentPart.bodyPartdirectionChanges[0].position;
                    currentPart.movementDirection = currentPart.bodyPartdirectionChanges[0].newDirection;

                    // Delete the item from the local deque
                    currentPart.bodyPartdirectionChanges.pop_front();
                    // Set the hasTravaledDirectionChangesPath item to true, to indicate that the path has been traversed
                    currentPart.hasTravaledDirectionChangesPath.back() = true;
                }

                // Check again since they might be deleted above
                if (!currentPart.bodyPartdirectionChanges.empty()) 
                {

                    if (currentPart.position.y + movementStep.y > currentPart.bodyPartdirectionChanges[0].position.y && currentPart.movementDirection.y > 0)
                    {
                        currentPart.position = currentPart.bodyPartdirectionChanges[0].position;
                        currentPart.movementDirection = currentPart.bodyPartdirectionChanges[0].newDirection;

                        // Delete the item from the local deque
                        currentPart.bodyPartdirectionChanges.pop_front();
                        // Set the hasTravaledDirectionChangesPath item to true, to indicate that the path has been traversed
                        currentPart.hasTravaledDirectionChangesPath.back() = true;
                    }

                    else if (currentPart.position.y + movementStep.y < currentPart.bodyPartdirectionChanges[0].position.y && currentPart.movementDirection.y < 0)
                    {
                        currentPart.position = currentPart.bodyPartdirectionChanges[0].position;
                        currentPart.movementDirection = currentPart.bodyPartdirectionChanges[0].newDirection;

                        // Delete the item from the local deque
                        currentPart.bodyPartdirectionChanges.pop_front();
                        // Set the hasTravaledDirectionChangesPath item to true, to indicate that the path has been traversed
                        currentPart.hasTravaledDirectionChangesPath.back() = true;
                    }
                }


				// Check if the last body part has traversed the path correctly, if so then delete the entire global deque item

                if (i == snakeBody.size() - 1)
                {
                    if (currentPart.HasTraveledToGoalPositionCorrect(globalDirectionChanges.size())) 
                    {
                        globalDirectionChanges.clear();
                    }
                }

                
            }
            else if (currentPart.bodyPartdirectionChanges.empty()) 
            {
				// Check if the hasTravaledDirectionChangesPath is set to true, meaning it has reached the goal position, then set the goal variable to false

                // Sets the variable to true if that is the case


                if (currentPart.HasTraveledToGoalPositionCorrect(globalDirectionChanges.size()) && snakeHead->bodyPartdirectionChanges.size() <= currentPart.bodyPartdirectionChanges.size())
                {
                    // continue;
                }
                else 
                {
					// Add all the pending direction changes to the local deque, since they have not been completed
					currentPart.bodyPartdirectionChanges = globalDirectionChanges;
					currentPart.hasTravaledDirectionChangesPath.push_back(false);
                }
            }
        }

        // Change to the movement direction above
		currentPart.position += snakeBody[i].movementDirection * snakeBody[i].speed;;
		snakeBody[i].sprite.setPosition(currentPart.position);
    }
    */

    bool decreaseIndex = false; // Used to check if the index should be decreased based on if an element was removed or not

    for (size_t i = snakeBody.size() - 1; i > 0; --i)
    {

        SnakeBody& currentPart = snakeBody[i];
        SnakeBody& nextPart = snakeBody[i - 1];

        sf::Vector2f movementStep = currentPart.movementDirection * currentPart.speed;
        
		// Decrease the index if an element was removed from the tail - the loop starts at the tail 
        if (decreaseIndex) 
        {
			currentPart.localDirectionChangesIndex--;
        }

        // Set the rotation

	    // Ensure that the index will surpass the size of the deque
        if (!globalDirectionChanges.empty() && currentPart.localDirectionChangesIndex < (globalDirectionChanges.size()))
        {


                if (currentPart.position.x + movementStep.x > globalDirectionChanges[currentPart.localDirectionChangesIndex].position.x && currentPart.movementDirection.x > 0)
                {

                    // Prevent from overshooting position by setting a exact position
                    currentPart.position = globalDirectionChanges[currentPart.localDirectionChangesIndex].position;
                    currentPart.movementDirection = globalDirectionChanges[currentPart.localDirectionChangesIndex].newDirection;

                    // Set the rotation
                    currentPart.sprite.rotate(globalDirectionChanges[currentPart.localDirectionChangesIndex].rotation);

                    // Aim for the next point in the coming iteration
                    currentPart.localDirectionChangesIndex++;


                }

                else if (currentPart.position.x + movementStep.x < globalDirectionChanges[currentPart.localDirectionChangesIndex].position.x && currentPart.movementDirection.x < 0)
                {


                    currentPart.position = globalDirectionChanges[currentPart.localDirectionChangesIndex].position;
                    currentPart.movementDirection = globalDirectionChanges[currentPart.localDirectionChangesIndex].newDirection;

                    // Set the rotation
                    currentPart.sprite.rotate(globalDirectionChanges[currentPart.localDirectionChangesIndex].rotation);

                    currentPart.localDirectionChangesIndex++;



                }



                else if (currentPart.position.y + movementStep.y > globalDirectionChanges[currentPart.localDirectionChangesIndex].position.y && currentPart.movementDirection.y > 0)
                {


                    currentPart.position = globalDirectionChanges[currentPart.localDirectionChangesIndex].position;
                    currentPart.movementDirection = globalDirectionChanges[currentPart.localDirectionChangesIndex].newDirection;

                    // Set the rotation
                    currentPart.sprite.rotate(globalDirectionChanges[currentPart.localDirectionChangesIndex].rotation);

                    currentPart.localDirectionChangesIndex++;



                }

                else if (currentPart.position.y + movementStep.y < globalDirectionChanges[currentPart.localDirectionChangesIndex].position.y && currentPart.movementDirection.y < 0)
                {


                    currentPart.position = globalDirectionChanges[currentPart.localDirectionChangesIndex].position;
                    currentPart.movementDirection = globalDirectionChanges[currentPart.localDirectionChangesIndex].newDirection;


                    // Set the rotation
                    currentPart.sprite.rotate(globalDirectionChanges[currentPart.localDirectionChangesIndex].rotation);

                    currentPart.localDirectionChangesIndex++;


                }

        }

	    // If the last body part, the first in the iteration has an index larger than 0, remove the first item from the global deque
        if (snakeBody.size() - 1 == i && currentPart.localDirectionChangesIndex > 0 && globalDirectionChanges.size() > 0)
        {
		    // Remove the oldest item from the deque, since the last item reached it
            currentPart.localDirectionChangesIndex--;
			globalDirectionChanges.pop_front();
			decreaseIndex = true;
        }

        // Change to the movement direction above
        currentPart.position += snakeBody[i].movementDirection * snakeBody[i].speed;
        snakeBody[i].sprite.setPosition(currentPart.position);
        IsCollidedWithSelf(currentPart, gameStatesManager); // Check if the part has collided with the head
    }
    // Check if the head has collided with an apple
}

void SnakeHandler::IsCollidedWithSelf(SnakeBody snakeBodyPart, GameStatesManager* gameStateManager)
{
    // Check if the heads coordinates are equal or in approximation to any of the body parts
    // This has to be done on each frame, there is no way around it

    // Check the direction of the head
    // https://www.matteboken.se/lektioner/matte-2/logik-och-geometri/avstandsformeln#!/
    float distanceToBodyPart = sqrt(pow((snakeHead->position.x - snakeBodyPart.position.x), 2) + pow((snakeHead->position.y - snakeBodyPart.position.y), 2)); // Working since distance is 
    // Since each body part is 50 wide and the position is based on their centers, then if the distance is less or equal to 50 there is a collision
    if (distanceToBodyPart <= 25) // The problem is that the picture is 50x50 in size, but not the head, for the moment we should use 25
    {
        gameStateManager->currentGameState = GameStatesEnum::GameOver;
    }


}

void SnakeHandler::IsCollidedWithApple(FoodHandler& foodHandler) 
{
    int index = 0;
    for (Food apple : foodHandler.foodOnScreen) 
    {
        float distanceToFood = sqrt(pow((snakeHead->position.x - apple.position.x), 2) + pow((snakeHead->position.y - apple.position.y), 2));
        if (distanceToFood <= 25) // The problem is that the picture is 50x50 in size, but not the head, for the moment we should use 25
        {

			foodHandler.foodOnScreen.remove(apple);
            // Add score in the game to the player 
            Grow();
            break;
        }
   }

}


void SnakeHandler::Grow()
{
    // Distance between body parts

    // Get the last body part (the tail)
    const SnakeBody& lastBodyPart = snakeBody.back();

	// Calculate the new position based on the movement direction of the last body part - a bad idea, it is perhaps better to calculate the new position based on the last body part's position
	// Or even better we create the new body part based on the last body part

    sf::Vector2f adjustedPosition = lastBodyPart.position - sf::Vector2f(DISTANCE_OFFSET.x * lastBodyPart.movementDirection.x, DISTANCE_OFFSET.y * lastBodyPart.movementDirection.y) ;
    
    // Create the new body part and add it to the snake

	// Add all the pending direction changes to the body part, since they will be the same as the last body part

    SnakeBody bodyPart(adjustedPosition, lastBodyPart.sprite.getRotation(), SNAKE_SPEED, lastBodyPart.movementDirection, bodyTexture); // Crashes the game because the texture is null
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