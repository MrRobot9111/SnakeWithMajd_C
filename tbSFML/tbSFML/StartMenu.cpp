#include "StartMenu.h"


StartMenu::StartMenu(float width, float height, sf::Color color)
{
	originalColor = color;

	if (!font.loadFromFile("font/arial.ttf"))
	{
		/*Hantera fel*/
	}

	menuItems[0].setFont(font);
	menuItems[0].setFillColor(color);
	menuItems[0].setString("Play");
	menuItems[0].setPosition(sf::Vector2f(width / 5, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menuItems[1].setFont(font);
	menuItems[1].setFillColor(color);
	menuItems[1].setString("Setting");
	menuItems[1].setPosition(sf::Vector2f(width / 5, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menuItems[2].setFont(font);
	menuItems[2].setFillColor(color);
	menuItems[2].setString("Exit");
	menuItems[2].setPosition(sf::Vector2f(width / 5, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}

void StartMenu::SetColor(sf::Color color) {
	menuItems[0].setFillColor(color);
	menuItems[1].setFillColor(color);
	menuItems[2].setFillColor(color);
}

StartMenu::~StartMenu()
{

}

void StartMenu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menuItems[i]);
	}
}
void StartMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menuItems[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menuItems[selectedItemIndex].setFillColor(sf::Color::Green);
	}
	
}

void StartMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menuItems[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menuItems[selectedItemIndex].setFillColor(sf::Color::Green);
	}

}

