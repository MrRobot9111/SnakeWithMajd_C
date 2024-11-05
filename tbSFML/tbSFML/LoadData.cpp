#include "LoadData.h"


    LoadData::LoadData(std::string filePath, float _rotationSpeed) 
    {
        // Load texture and create sprite
        texture.loadFromFile(filePath);
        snakeSprite.setTexture(texture);

        // Set origin to center of sprite for smooth rotation
        sf::Vector2u textureSize = texture.getSize();
        snakeSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
        snakeSprite.setPosition(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2);

        rotationSpeed = _rotationSpeed;

    }

    void LoadData::RotateSnake(float deltaTime)
    {
        float rotation = rotationSpeed * deltaTime; // Degrees to rotate this frame
        snakeSprite.rotate(rotation);
    }

    void LoadData::LoadMethod(bool* loading) {

        std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate loading for 5 seconds
        *loading = false;
    }

    void LoadData::StartLoading(bool* loading) {

        t = std::thread(&LoadData::LoadMethod, this, loading);
    }

    LoadData::~LoadData() {
        if (t.joinable()) {
            t.join(); // Ensure the thread is finished before destruction
        }
    }
