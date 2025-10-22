#include "Button.h"

Button::Button(std::string text, int x, int y, int windowX, int windowY, int fontSize) : x{ x }, y{ y }, text{ text }, fontSize{fontSize}, padding{defPadding}, color{defColor}, windowX{windowX}, windowY{windowY}
{
	if (x == -1) {
		this->x = (windowX - MeasureText(text.c_str(), fontSize)) / 2;
	}
	if (y == -1) {
		this->y = (windowY - fontSize) / 2;
	}
	xSize = MeasureText(text.c_str(), fontSize) + padding;
	ySize = fontSize + padding;
}

bool Button::CheckIfClicked(int x, int y) const
{
	return this->x - padding <= x && this->x + xSize >= x && this->y - padding <= y && this->y + ySize >= y;
}

void Button::Draw() const {
	DrawText(text.c_str(), x, y, fontSize, BLACK);
}
