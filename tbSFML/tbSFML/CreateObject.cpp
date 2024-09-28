#include "CreateObject.h"

// Problem
/*
CreateObject::CreateObject(sf::Vector2f _pos, sf::Shape* _shape, float _rotation, float _speed, sf::Vector2f _movementDirection)
{
	position = _pos;
	shape = _shape;
	rotation = _rotation;
	speed = _speed;
	movementDirection = _movementDirection;

}
*/
void CreateObject::draw(sf::RenderWindow& window)
{
	// Why the *shape ???
	window.draw(*shape);
}