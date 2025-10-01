#pragma once

#include <iostream>

class Position
{
public:
	std::string id;
	int x;
	int y;
	Position(std::string id = "", int x = -1, int y = -1) : id{id}, x{x}, y{y} {}
};

