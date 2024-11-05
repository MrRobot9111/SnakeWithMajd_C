#pragma once
#include <iostream>
#include <thread>
#include <chrono> // For std::chrono::seconds
#include "StartMenu.h"

class LoadData {
public:
    void LoadMethod(bool* loading) {
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate loading for 5 seconds
        *loading = false;
    }

    void StartLoading(bool* loading) {
        
        t = std::thread(&LoadData::LoadMethod, this, loading);
    }

    ~LoadData() {
        if (t.joinable()) {
            t.join(); // Ensure the thread is finished before destruction
        }
    }

private:
    std::thread t; // Thread member to manage the thread's lifetime
};
