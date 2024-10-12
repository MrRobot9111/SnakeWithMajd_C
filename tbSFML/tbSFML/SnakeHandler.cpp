#include "SnakeHandler.h"
#include "SnakeBody.h"
#include "Constants.h"
#include "DirectionChange.h"
#include <optional>
#include <deque>


std::deque<DirectionChange> globalDirectionChanges; // Queue of direction changes

SnakeHandler::SnakeHandler(sf::Texture* headTexture)
{
    // Initialize the snake body with only its head
    SnakeBody head(sf::Vector2f(400, 500), 0, 1, sf::Vector2f(1, 0), headTexture);
    snakeBody.push_back(head);


    // Fixed this, but try more from Chat-GPT 
    sf::Vector2f adjustedPosition = head.position - sf::Vector2f(DISTANCE_OFFSET.x * head.movementDirection.x, DISTANCE_OFFSET.y * head.movementDirection.y);

    snakeBody.push_back(SnakeBody(adjustedPosition, 0, 1, sf::Vector2f(1, 0), headTexture));
    snakeBody.push_back(SnakeBody(adjustedPosition - sf::Vector2f(DISTANCE_OFFSET.x, 0), 0, 1, sf::Vector2f(1, 0), headTexture));


    // Set snakeHead pointer to the first element of the deque
    snakeHead = &snakeBody.front(); // Use address-of operator to get a pointer

    texture = new sf::Texture();
    // Load texture for the head, if needed
    texture->loadFromFile("img/snake_head.png");

}

// Add a delay so that errors do not occur
void SnakeHandler::KeyboardInput(int screenWidth, int screenHeight)
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
            snakeHead->previousMovementDirection = snakeHead->movementDirection;
            snakeHead->movmentDirectionSwitchPosition = snakeHead->position;

            snakeHead->movementDirection = sf::Vector2f(-1, 0);
            snakeHead->sprite.setRotation(90);

			// Add the changes to the deque, so that the other body parts can follow

			globalDirectionChanges.push_back({ snakeHead->position, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
			snakeHead->bodyPartdirectionChanges.push_back(globalDirectionChanges.back()); // add the latest change to the body part, and the use it to update the body parts deque
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snakeHead->movementDirection != sf::Vector2f(-1, 0) && snakeHead->movementDirection != sf::Vector2f(1, 0))
        {
            // Store the old movement direction, and the position of the turn
            snakeHead->previousMovementDirection = snakeHead->movementDirection;
            snakeHead->movmentDirectionSwitchPosition = snakeHead->position;

            snakeHead->movementDirection = sf::Vector2f(1, 0);
            snakeHead->sprite.setRotation(270);

            // Add the changes to the deque, so that the other body parts can follow
            globalDirectionChanges.push_back({ snakeHead->position, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
            snakeHead->bodyPartdirectionChanges.push_back(globalDirectionChanges.back()); // add the latest change to the body part, and the use it to update the body parts deque
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snakeHead->movementDirection != sf::Vector2f(0, 1) && snakeHead->movementDirection != sf::Vector2f(0, -1))
        {

            // Store the old movement direction, and the position of the turn
            snakeHead->previousMovementDirection = snakeHead->movementDirection;
            snakeHead->movmentDirectionSwitchPosition = snakeHead->position;

            snakeHead->movementDirection = sf::Vector2f(0, -1);
            snakeHead->sprite.setRotation(180);

            // Add the changes to the deque, so that the other body parts can follow
            globalDirectionChanges.push_back({ snakeHead->position, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
            snakeHead->bodyPartdirectionChanges.push_back(globalDirectionChanges.back()); // add the latest change to the body part, and the use it to update the body parts deque
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snakeHead->movementDirection != sf::Vector2f(0, -1) && snakeHead->movementDirection != sf::Vector2f(0, 1))
        {

            // Store the old movement direction, and the position of the turn
            snakeHead->previousMovementDirection = snakeHead->movementDirection;
            snakeHead->movmentDirectionSwitchPosition = snakeHead->position;

            snakeHead->movementDirection = sf::Vector2f(0, 1);
            snakeHead->sprite.setRotation(0);

            // Add the changes to the deque, so that the other body parts can follow
            globalDirectionChanges.push_back({ snakeHead->position, snakeHead->movementDirection, snakeHead->sprite.getRotation() });
            snakeHead->bodyPartdirectionChanges.push_back(globalDirectionChanges.back()); // add the latest change to the body part, and the use it to update the body parts deque
        }
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

	    // Ensure that the index will surpass the size of the deque
        if (!globalDirectionChanges.empty() && currentPart.localDirectionChangesIndex < (globalDirectionChanges.size()))
        {


                if (currentPart.position.x + movementStep.x > globalDirectionChanges[currentPart.localDirectionChangesIndex].position.x && currentPart.movementDirection.x > 0)
                {

                    // Prevent from overshooting position by setting a exact position
                    currentPart.position = globalDirectionChanges[currentPart.localDirectionChangesIndex].position;
                    currentPart.movementDirection = globalDirectionChanges[currentPart.localDirectionChangesIndex].newDirection;

                    // Aim for the next point in the coming iteration
                    currentPart.localDirectionChangesIndex++;
                }

                else if (currentPart.position.x + movementStep.x < globalDirectionChanges[currentPart.localDirectionChangesIndex].position.x && currentPart.movementDirection.x < 0)
                {


                    currentPart.position = globalDirectionChanges[currentPart.localDirectionChangesIndex].position;
                    currentPart.movementDirection = globalDirectionChanges[currentPart.localDirectionChangesIndex].newDirection;

                    currentPart.localDirectionChangesIndex++;

                }



                else if (currentPart.position.y + movementStep.y > globalDirectionChanges[currentPart.localDirectionChangesIndex].position.y && currentPart.movementDirection.y > 0)
                {


                    currentPart.position = globalDirectionChanges[currentPart.localDirectionChangesIndex].position;
                    currentPart.movementDirection = globalDirectionChanges[currentPart.localDirectionChangesIndex].newDirection;

                    currentPart.localDirectionChangesIndex++;

                }

                else if (currentPart.position.y + movementStep.y < globalDirectionChanges[currentPart.localDirectionChangesIndex].position.y && currentPart.movementDirection.y < 0)
                {


                    currentPart.position = globalDirectionChanges[currentPart.localDirectionChangesIndex].position;
                    currentPart.movementDirection = globalDirectionChanges[currentPart.localDirectionChangesIndex].newDirection;

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
    }




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

    // Get the last body part (the tail)
    const SnakeBody& lastBodyPart = snakeBody.back();

	// Calculate the new position based on the movement direction of the last body part - a bad idea, it is perhaps better to calculate the new position based on the last body part's position
	// Or even better we create the new body part based on the last body part

    sf::Vector2f adjustedPosition = lastBodyPart.position - sf::Vector2f(DISTANCE_OFFSET.x * lastBodyPart.movementDirection.x, DISTANCE_OFFSET.y * lastBodyPart.movementDirection.y) ;
    
    // Create the new body part and add it to the snake

	// Add all the pending direction changes to the body part, since they will be the same as the last body part

    SnakeBody bodyPart(adjustedPosition, lastBodyPart.sprite.getRotation(), 1, lastBodyPart.movementDirection, texture);
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