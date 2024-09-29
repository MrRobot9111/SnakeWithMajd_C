#include "MovingObject.h"

MovingObject::MovingObject(sf::Vector2f size, sf::Vector2f _pos, std::unique_ptr<sf::Shape> _shape, float _rotation, float _speed, sf::Vector2f _movementDirection) : 
	CreateObject(size, _pos, std::move(_shape), _rotation, _speed, _movementDirection) 
{

}