#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3
class StartMenu
{
public:
	StartMenu(float width, float height, sf::Color color);
	~StartMenu();

	void SetColor(sf::Color color);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

public:
	sf::Color originalColor;
	int selectedItemIndex;
	sf::Font font;
	sf::Text menuItems[MAX_NUMBER_OF_ITEMS];

};