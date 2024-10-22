#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3
class StartMenu
{
public:
	StartMenu(float width, float height);
	~StartMenu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};