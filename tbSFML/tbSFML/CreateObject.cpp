#include "CreateObject.h"

// Problem

CreateObject::CreateObject(sf::Vector2f _size, sf::Vector2f _pos, std::unique_ptr<sf::Shape> _shape, float _rotation, float _speed, sf::Vector2f _movementDirection)
{
	size = _size;
	position = _pos;
	shape = std::move(_shape);  // Use std::move to transfer ownership => one pointer to resource
	rotation = _rotation;
	speed = _speed;
	movementDirection = _movementDirection;

	// Try to set the size if the shape is a rectangle
	if (auto rectShape = dynamic_cast<sf::RectangleShape*>(shape.get())) {
		rectShape->setSize(size);  // Set the size if it's a rectangle
	}
}

CreateObject::CreateObject(sf::Vector2f _size, sf::Vector2f _pos, std::unique_ptr<sf::Shape> _shape, sf::Texture _texturePath, float _rotation, float _speed, sf::Vector2f _movementDirection)
{
	size = _size;
	position = _pos;
	shape = std::move(_shape);  // Use std::move to transfer ownership => one pointer to resource
	texturePath = _texturePath;

	rotation = _rotation;
	speed = _speed;
	movementDirection = _movementDirection;

	// Try to set the size if the shape is a rectangle
	if (auto rectShape = dynamic_cast<sf::RectangleShape*>(shape.get())) {
		rectShape->setSize(size);  // Set the size if it's a rectangle
	}

	shape->setTexture(&texturePath); // Assign the texture to the shape

}

// Suitable for rendering an arrow
CreateObject::CreateObject(sf::Vector2f _pos, sf::Sprite _sprite, float _rotation, float _speed, sf::Vector2f _movementDirection)
{
	position = _pos;
	sprite = _sprite;
	rotation = _rotation;
	speed = _speed;
	movementDirection = _movementDirection;

}

CreateObject::~CreateObject() {
	// If needed, add any cleanup code here
	// In this case, unique_ptr will handle memory management automatically
}

void CreateObject::Update() 
{

}


void CreateObject::SetPosition(float x, float y) {
	position = sf::Vector2f(x, y);
}

sf::Vector2f CreateObject::GetPosition() const {
	return position;
}

void CreateObject::Draw(sf::RenderWindow& window)
{
	// Drawing shape or sprite
	if (shape) {
		window.draw(*shape);  // Dereference the unique_ptr to draw the shape "*"
	}
	else {
		window.draw(sprite);  // Draw sprite if it's a sprite object
	};
}