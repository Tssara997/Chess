#pragma once

#include <string>

class Position
{
public:
	std::string id;
	int x;
	int y;

	Position() : id{ "000" }, x{ -1 }, y{ -1 } {}
	Position(std::string id, int x, int y) : id{id}, x{x}, y{y} {}
	Position& operator=(const Position& rhs);
	Position& operator=(const Position* rhs);
};

