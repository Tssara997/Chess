#include "Position.h"

Position& Position::operator=(const Position& rhs) {
	if (this == &rhs)
		return *this;
	if (this == nullptr) {
		
	}
	this->id = rhs.id;
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}