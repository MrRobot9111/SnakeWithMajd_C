#include <SFML/Graphics.hpp>

//Memory leaks detetection
#include "windows.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>  
#include <crtdbg.h>
#include "Snake.h"
#include "SnakeBody.h"
#include "Food.h"
#include "FoodHandler.h"
#include "SnakeHandler.h"
#include "StartMenu.h"
#include "GameOver.h"
#include "Constants.h"
#include "GameStatesEnum.h"
#include "GameStatesManager.h"
#include "GridMap.h"
#include "LoadData.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    //Läs mer här: https://learn.microsoft.com/en-us/cpp/c-runtime-library/find-memory-leaks-using-the-crt-library?view=msvc-170
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GridMap::InitializeGridMap();

    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "TB Snake!");
    window.setFramerateLimit(10);
    
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile("img/snake_head.png");

    sf::Texture* textureBody = new sf::Texture();
    texture->loadFromFile("img/circleTexture2.png");

    FoodHandler foodHandler;

    SnakeHandler snakeHandler(texture, textureBody);

    foodHandler.SpawnFood(5);

    StartMenu menu(window.getSize().x, window.getSize().y, sf::Color::Black);

    GameOver GameOverMenuItems(window.getSize().x, window.getSize().y);
    
	GridMap::DrawGridMap(window);

    // Set the state of the game
    GameStatesManager* gameStatesManager = new GameStatesManager();
    gameStatesManager->SetState(GameStatesEnum::MainMenu);

    // Loading Screen

    bool loading = true;

    sf::Texture* textureLoadinScreen = new sf::Texture();
    textureLoadinScreen->loadFromFile("img/snake_head.png");
    LoadData loader(textureLoadinScreen);

    loader.StartLoading(&loading);

    while (window.isOpen())
    {

        // Calculate deltaTime for smooth rotation
        float deltaTime = loader.clock.restart().asSeconds();

        if (loading)
        {
            menu.SetColor(sf::Color::White); // Show loading color
            window.clear(sf::Color::Black);
			window.draw(loader.snakeSprite);
            loader.RotateSnake(deltaTime);
            //menu.draw(window); // Display loading screen
            window.display();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Handle events based on the current game state
            if (gameStatesManager->currentGameState == GameStatesEnum::MainMenu && !loading)
            {
                switch (event.type)
                {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                        case 0: // Start game
                            gameStatesManager->SetState(GameStatesEnum::Playing);
                            break;
                        case 2: // Exit game
                            window.close();
                            break;
                        }
                        break;
                    }
                    break;
                }
            }
            else if (gameStatesManager->currentGameState == GameStatesEnum::GameOver)
            {
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)
                {
                    switch (GameOverMenuItems.GetPressedItem())
                    {
                    case 1: // Return to Main Menu
                        gameStatesManager->SetState(GameStatesEnum::MainMenu);
                        snakeHandler.ResetSnake();
                        break;
                    }
                }
            }
        }

        // Render based on the current game state
        if (gameStatesManager->currentGameState == GameStatesEnum::MainMenu && !loading)
        {
            window.clear(sf::Color::Black);
            menu.draw(window);
            window.display();
        }
        else if (gameStatesManager->currentGameState == GameStatesEnum::Playing)
        {
			sf::Color gray(75, 75, 75);
            window.clear(gray);
            GridMap::DrawGridMap(window);  
            snakeHandler.IsCollidedWithApple(foodHandler);
            foodHandler.EnsureAmountOfFoodOnScreen(5);
            snakeHandler.Update(window, SCREEN_SIZE.x, SCREEN_SIZE.y, gameStatesManager);
            foodHandler.DrawFood(window);
            window.display();
        }
        else if (gameStatesManager->currentGameState == GameStatesEnum::GameOver)
        {
            window.clear(sf::Color::Black);
            GameOverMenuItems.draw(window);
            window.display();
        }
    }

    delete gameStatesManager;
    
    return 0;
}