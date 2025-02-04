#include "Food.h"

Food::Food(sf::Vector2f size, sf::Vector2f position, sf::Texture* _texture, float rotation)
{
    this->texture = _texture;
    this->size = size;
    this->position = position;
    this->rotation = rotation;

    sprite.setTexture(*texture);  // Set the texture to the sprite

    // Set initial scale based on the size
    sprite.setScale(size.x / texture->getSize().x, size.y / texture->getSize().y);
    sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);

    // Set the initial position and rotation of the sprite
    sprite.setPosition(position);
    sprite.setRotation(rotation);

}

void Food::Draw(sf::RenderWindow& window)
{
    window.draw(sprite); 
}

// Comparison operator
bool Food::operator==(const Food& other) const {
    return position == other.position;
}