#pragma once
#include <vector>
#include "SnakeBody.h"
#include <deque>

class SnakeHandler
{
// https://www.w3schools.com/cpp/cpp_data_structures.asp
// https://www.w3schools.com/cpp/cpp_deque.asp
// https://www.w3schools.com/cpp/cpp_vectors.asp

public:
	std::deque<SnakeBody> snakeBody; // Alternatively a double linked list, since it has a tail
};

