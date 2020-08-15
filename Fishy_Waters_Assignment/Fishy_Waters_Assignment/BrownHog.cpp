#include "BrownHog.h"

BrownHog::BrownHog(string inputID, Vector2u inputPosition, array<array<unsigned char, 128>, 128> *inputMapPointer, unsigned char inputDifficulty)
{
	// Local variables

	// Main "CapturableCritter()"
	entityName = "Brown Hog " + inputID;
	mapPosition = inputPosition;
	Sprite::setPosition(64 * mapPosition.x, 64 * mapPosition.y);
	localMapPointer = inputMapPointer;
	travelSpeed = 60;
	intervalMinimum = 1;
	intervalMaximum = 5;
	traversableTerrain.push_back(13);
	difficulty = inputDifficulty;
}