#pragma once
#include "Entity.h"
#include <random>

class CapturableCritter : public Entity
{
public:
	// Public variables
	// Boolean that determines if the critter is contested by the player.
	bool contested;
	// The minimum time interval in seconds before the critter moves.
	float intervalMinimum;
	// The maximum time interval in seconds before the critter moves.
	float intervalMaximum;
	// Keeps track how long the creature has been on the map, once it
	// lived long enough it gets deleted to avoid too many appearing
	// in the game.
	float lifespanCurrent;
	// The difficulty of the creature when contested, determines how
	// difficulty the capture is and works as a multiplier for the
	// reward.
	unsigned char difficulty;
	// The price of the critter that gets modified by the difficulty
	// when the player captures it.
	int critterPrice;

	// Constructors
	CapturableCritter();
	CapturableCritter(Vector2u inputPosition, array<array<unsigned char, 128>, 128> *inputMapPointer);

	// Destructor
	~CapturableCritter();

	// Public methods
	virtual void update(Time inputProcessSpeed, unsigned char direction, float inputInterval);

protected:
	// Protected variables
	/// <summary>
	/// Used to time when the critter decides to move again
	/// and in case of capture attempt the intervals between key
	/// presses to make sure the player stays within the time limit.
	/// </summary>
	Clock timer;
	// The current interval
	float currentInterval;

	// Protected methods

private:
	// Private variables

	// Private methods

};

