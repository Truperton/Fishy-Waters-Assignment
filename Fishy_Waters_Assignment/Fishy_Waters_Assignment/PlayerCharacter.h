#pragma once
#include "Entity.h"

class PlayerCharacter : public Entity
{
public:
	// Public variables
		// Score variables
	/// <summary> Stores the high score based on the total coins earned through the session. </summary>
	int score;
	/// <summary> Stores the current coin balance of the player. </summary>
	int coins;

	sf::View playerView;
	// Constructors

	PlayerCharacter(Vector2u inputPosition);
	PlayerCharacter(Vector2u inputPosition, array<array<unsigned char, 128>, 128> &inputMapPointer);

	// Destructor

	~PlayerCharacter();

	// public methods
	void update(float inputProcessSpeed);

private:
	// Private variables

	// Private methods

};

