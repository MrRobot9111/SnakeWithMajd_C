#include "GameOver.h"

GameOver::GameOver(float width, float height)
{
	if (!font.loadFromFile("font/arial.ttf"))
	{
		/*Hantera fel*/
	}

	GameOverMenuItems[0].setFont(font);
	GameOverMenuItems[0].setFillColor(sf::Color::Red);
	GameOverMenuItems[0].setString("GAMEOVER NOOB");
	GameOverMenuItems[0].setPosition(sf::Vector2f(width / 5, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	GameOverMenuItems[1].setFont(font);
	GameOverMenuItems[1].setFillColor(sf::Color::White);
	GameOverMenuItems[1].setString("Press Enter to Return to Main Menu");
	GameOverMenuItems[1].setPosition(sf::Vector2f(width / 5, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	selectedItemIndex = 1;
}

GameOver::~GameOver()
{

}

void GameOver::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(GameOverMenuItems[i]);
	}
}
	
