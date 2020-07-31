#pragma once
#include "Entity.h"

class PlayerCharacter : public Entity
{
public:
	// Public variables
	
	// Constructors

	PlayerCharacter(Vector2u inputPosition);
	PlayerCharacter(Vector2u inputPosition, array<array<unsigned char, 128>, 128> &inputMapPointer);
	// Destructor

	~PlayerCharacter();

	// public methods

private:
	// Private variables

	// Private methods

};

