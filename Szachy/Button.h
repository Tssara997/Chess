#pragma once

#include <raylib.h>
#include <string>

class Button
{
private:

	static constexpr int defFontSize = 48;
	static constexpr Color defColor = BLACK;
	static constexpr int defPadding = 5;

	int x;
	int y;
	int xSize;
	int ySize;
	int padding;
	int windowX;
	int windowY;
	std::string text;
	int fontSize;
	Color color;


public:
	Button(std::string text = "", int x = -1, int y = -1, int windowX = 0, int windowY = 0, int fontSize = defFontSize);
	~Button() = default;
	bool CheckIfClicked(int x, int y) const;
	void Draw() const;
};
