#include "Food.h"
#include "Constants.h"

Food::Food(int rowIndexIN, int columnIndexIN,  sf::Vector2f size, sf::Texture* _texture, float rotation)
{
    this->texture = _texture;
    this->size = size;
	columnIndex = columnIndexIN;
	rowIndex = rowIndexIN;  
    this->rotation = rotation;

    sprite.setTexture(*texture);  // Set the texture to the sprite

    // Set initial scale based on the size
    sprite.setScale(size.x / texture->getSize().x, size.y / texture->getSize().y);
    sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);

    sprite.setPosition(columnIndex * APPLE_SIZE.x + (APPLE_SIZE.x / 2.f), rowIndex * APPLE_SIZE.y + (APPLE_SIZE.y / 2.f));
    // Set the initial position and rotation of the sprite
    sprite.setRotation(rotation);

}

void Food::Draw(sf::RenderWindow& window)
{
    window.draw(sprite); 
}

// Comparison operator - each row[col] is unique
bool Food::operator==(const Food& other) const {
    return columnIndex == other.columnIndex && rowIndex == other.rowIndex;
}