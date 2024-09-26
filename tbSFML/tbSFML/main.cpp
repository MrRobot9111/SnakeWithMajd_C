#include <SFML/Graphics.hpp>

//Memory leaks detetection
#include "windows.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>  
#include <crtdbg.h>

class SimpleRectangle
{
private:
    sf::RectangleShape _shape;
    sf::Vector2f _position;

public:

    SimpleRectangle(float width, float height, float startX = 0.0f, float startY = 0.0f)
    {
        _shape.setSize(sf::Vector2f(width, height));
        _position.x = startX;
        _position.y = startY;
    }

    SimpleRectangle(float width, float height, sf::Texture texturePath, float startX = 0.0f, float startY = 0.0f)
    {
        _shape.setSize(sf::Vector2f(width, height));
        _shape.setTexture(&texturePath);
        _position.x = startX;
        _position.y = startY;
    }



    ~SimpleRectangle()
    {

    }

    void Draw(sf::RenderWindow &win) const
    {
        win.draw(_shape);
    }

    void Update(int winWidth, int winHeight)
    {
        // Controlling the player

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _position.x -= 10.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _position.x += 10.0f;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _position.y -= 10.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _position.y += 10.0f;
        }

        // Check of outside window

        if (_position.x > winWidth - _shape.getSize().x)
        {

            _position.x = float(winWidth - _shape.getSize().x);
        }
        else if (_position.x < 0)
        {

            _position.x = 0;
        }

        if (_position.y > winHeight - _shape.getSize().y)
        {

            _position.y = float(winHeight - _shape.getSize().x);
        }
        else if (_position.y < 0)
        {

            _position.y = 0;
        }

        _shape.setPosition(_position);
    }
};

// Arrows should be created with this
class MovingObjects
{
private:
    sf::Sprite _sprite;
    sf::Vector2f _position;
    sf::Vector2f _direction;
    sf::Vector2f _speed;

public:
    MovingObjects(sf::Texture &texture, float startX = 0.0f, float startY = 0.0f)
    {
        _sprite.setTexture(texture);
        _position.x = startX;
        _position.y = startY;

        _direction.x = 1;
        _direction.y = 1;

        _speed.x = 2;
        _speed.y = 3;
    }

    ~MovingObjects()
    {
        
    }

    void Draw(sf::RenderWindow& win) const
    {
        win.draw(_sprite);
    }

    void Update(int winWidth, int winHeight)
    {
        _position.x += _speed.x * _direction.x;
        _position.y += _speed.y * _direction.y;

        if (_position.x > winWidth - _sprite.getTextureRect().width)
        {
            _direction.x *= -1;
            _position.x = float(winWidth - _sprite.getTextureRect().width);
        }
        else if (_position.x < 0)
        {
            _direction.x *= -1;
            _position.x = 0;
        }

        if (_position.y > winHeight - _sprite.getTextureRect().height)
        {
            _direction.y *= -1;
            _position.y = float(winHeight - _sprite.getTextureRect().height);
        }
        else if (_position.y < 0)
        {
            _direction.y *= -1;
            _position.y = 0;
        }

        _sprite.setPosition(_position);
    }
};

// Create Apples by creating a class that the arrow class will inherit from


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    //Läs mer här: https://learn.microsoft.com/en-us/cpp/c-runtime-library/find-memory-leaks-using-the-crt-library?view=msvc-170
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    int windowWidth = 1200, windowHeight = 800;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "TB Snake!");
    window.setFramerateLimit(60);
    
    // Drawing square
    SimpleRectangle snake(50, 50, 400, 500);





    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Background color - change to texture
        window.clear(sf::Color::Cyan);
        snake.Update(windowWidth, windowHeight);
        snake.Draw(window);

        window.display();

    }
    
    return 0;
}