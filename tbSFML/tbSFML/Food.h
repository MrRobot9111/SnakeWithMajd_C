#pragma once
#include <SFML/Graphics.hpp>
class Food
{
public:
	sf::Vector2f size;
	int columnIndex;
	int rowIndex;
	sf::Sprite sprite;
	sf::Texture* texture;
	float rotation;		
public:
	Food(int rowIndex, int columnIndex, sf::Vector2f size, sf::Texture* _texture, float rotation);
	void SetRotation(float _rotation);
	void SetPosition(sf::Vector2f _position);
	void Rotate(float angleIncrement);
	void Draw(sf::RenderWindow& window);

	bool operator==(const Food& other) const; // Compare two objects

};

