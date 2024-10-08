#pragma once
#include <SFML/Graphics.hpp>
class Food
{
public:
	sf::Vector2f size;
	sf::Vector2f position;  
	sf::Sprite sprite;
	sf::Texture* texture;
	float rotation;		
public:
	Food(sf::Vector2f size, sf::Vector2f position, sf::Texture* _texture, float rotation);
	void SetRotation(float _rotation);
	void SetPosition(sf::Vector2f _position);
	void Rotate(float angleIncrement);
	void Draw(sf::RenderWindow& window);

};

