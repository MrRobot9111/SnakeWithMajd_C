#pragma once
#include <SFML/Graphics.hpp>
class GameObject
{
protected:
	sf::Vector2f _position;
	sf::Shape* shape;  // Can use sf::Sprite instead if dealing with images, and is the base class in every geometric object
	float rotation;    // Rotation angle in degrees

	// https://www.geeksforgeeks.org/virtual-function-cpp/
	// https://www.geeksforgeeks.org/virtual-destructor/

	/*
	
	Deleting a derived class object using a pointer of base class type that has a non-virtual destructor results in undefined behavior. 
	To correct this situation, the base class should be defined with a virtual destructor.
	For example, the following program results in undefined behavior.

	*/

public:
	GameObject();
	virtual ~GameObject(); // Why virtual - look it up

	virtual void draw(sf::RenderWindow& window);
	virtual void update(float deltaTime);

	// Used to update position
	void setPosition(float x, float y);
	sf::Vector2f getPosition() const; // Why the const - look it up

	bool isCollided(const GameObject& other) const;

};

