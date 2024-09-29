#pragma once
#include <SFML/Graphics.hpp>
class CreateObject
{
public:
	sf::Vector2f size;
	sf::Vector2f position;
	std::unique_ptr<sf::Shape> shape;  // Use smart pointer for automatic memory management - automatic memory deletion // Can use sf::Sprite instead if dealing with images, and is the base class in every geometric object
	sf::Sprite sprite;                 // Holds the sprite (image)
	sf::Texture texturePath;               // Texture for sprite or shape
	float rotation;					   // Rotation angle in degrees
	float speed;
	sf::Vector2f movementDirection;

	// https://www.geeksforgeeks.org/virtual-function-cpp/
	// https://www.geeksforgeeks.org/virtual-destructor/

	/*
	
	Deleting a derived class object using a pointer of base class type that has a non-virtual destructor results in undefined behavior. 
	To correct this situation, the base class should be defined with a virtual destructor.
	For example, the following program results in undefined behavior.

	*/

public:
	// Different constructors depending on the use case
	CreateObject();
	CreateObject(sf::Vector2f size, sf::Vector2f _pos, std::unique_ptr<sf::Shape> _shape, float _rotation, float _speed, sf::Vector2f _movementDirection);
	CreateObject(sf::Vector2f size, sf::Vector2f _pos, std::unique_ptr<sf::Shape> _shape, sf::Texture _texturePath, float _rotation, float _speed, sf::Vector2f _movementDirection);
	CreateObject(sf::Vector2f _pos, sf::Sprite _sprite, float _rotation, float _speed, sf::Vector2f _movementDirection);
	virtual ~CreateObject(); // Why virtual? - Children classes will inherit this method

	void Draw(sf::RenderWindow& window);
	virtual void Update(); // Virtual => implementation needed otherwise undefined behavior | could use pure virtual

	// Used to update position - All classes will have the same implementation therefore they are not virtual
	// Shapes have a built in function that handles this
	void SetPosition(float x, float y);
	sf::Vector2f GetPosition() const; // Why the const? - It means that position will not be modified

	bool IsCollided(const CreateObject& other) const;

};

