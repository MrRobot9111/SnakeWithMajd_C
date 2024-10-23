#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3
class GameOver
{
public:
	GameOver(float width, float height);
	~GameOver();

	void draw(sf::RenderWindow& window);
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text GameOverMenuItems[MAX_NUMBER_OF_ITEMS];

};