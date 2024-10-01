#include "Food.h"

Food::Food(sf::Vector2f size, sf::Vector2f position, sf::Texture texture, float rotation) 
{
    this->size = size;
    sprite.setTexture(texture);
    sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
    SetRotation(rotation);  // Set initial rotation
}

void Food::Draw(sf::RenderWindow& window)
{
    window.draw(sprite); 
}