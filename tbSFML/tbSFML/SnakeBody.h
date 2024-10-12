#pragma once
#include <vector>
#include "Food.h"
#include <deque>
#include "DirectionChange.h"

class SnakeBody
{
public:
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture* texture;
	sf::Vector2f movementDirection;

	
	sf::Vector2f previousMovementDirection;
	sf::Vector2f movmentDirectionSwitchPosition;

	int localDirectionChangesIndex = 0;

	// Make a deque with the pending changes
	std::deque<DirectionChange> bodyPartdirectionChanges;

	// A check to see if the snake has traveled to path to the goal position for the current global changes, since they will be erased when all parts have traveled to the goal position
	std::deque<bool> hasTravaledDirectionChangesPath;

	// bool reachedGoalPositionCorrect;
	float speed;
	float rotation;
public:
	SnakeBody();
	SnakeBody(sf::Vector2f _pos, float _rotation, float _speed, sf::Vector2f _movementDirection, sf::Texture* _texture, sf::Vector2f movmentDirectionSwitchPosition = sf::Vector2f(-1.0f, -1.0f));
	SnakeBody(sf::Vector2f _pos, float _rotation, float _speed, sf::Vector2f _movementDirection, sf::Texture* _texture, std::deque<DirectionChange> bodyPartdirectionChanges);

	bool HasTraveledToGoalPositionCorrect(int globalDequeSize);

	void Update(int screenWidth, int screenHeight);
	void Draw(sf::RenderWindow& window);
};

