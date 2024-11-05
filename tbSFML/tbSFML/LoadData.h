#pragma once
#pragma once
#include <iostream>
#include <thread>
#include <chrono> // For std::chrono::seconds
#include <SFML/Graphics.hpp>
#include "StartMenu.h"
#include "Constants.h"


class LoadData {
public:

    LoadData(std::string filePath, float rotationSpeed = 72.0f);

    void RotateSnake(float deltaTime);
    void LoadMethod(bool* loading);
    void StartLoading(bool* loading);

    ~LoadData();

public:
    float rotationSpeed;
    sf::Sprite snakeSprite;
    sf::Clock clock;

private:

    sf::Texture texture;    // Keep texture as a member variable to ensure it's valid
    std::thread t;          // Thread to manage loading
};
