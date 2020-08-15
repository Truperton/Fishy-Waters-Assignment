#include "CapturableCritter.h"

CapturableCritter::CapturableCritter()
{

}

CapturableCritter::CapturableCritter(Vector2u inputPosition, array<array<unsigned char, 128>, 128> *inputMapPointer)
{
	// Local variables

	// Main "CapturableCritter()"
	entityName = "Default Creature";
	mapPosition = inputPosition;
	Sprite::setPosition(64 * mapPosition.x, 64 * mapPosition.y);
	localMapPointer = inputMapPointer;
	travelSpeed = 100;
}

CapturableCritter::~CapturableCritter()
{
	// Local variables

	// Main "~CapturableCritter()"
	cout << "[CapturableCritter destructor] The \"" << entityName << "\" has been destroyed" << endl;
}

void CapturableCritter::update(Time inputProcessSpeed, unsigned char direction, float inputInterval)
{
	// Local variables
	Time elapsedTime = timer.getElapsedTime();

	// Main "update()"
	lifespanCurrent += inputProcessSpeed.asSeconds();
	//cout << "update() method started\n";
	animationInterval += inputProcessSpeed.asSeconds();
	if (elapsedTime.asSeconds() > currentInterval && !moving)
	{
		//direction = directionDistribution(numberGenerator);
		cout << +direction << endl;
		//currentInterval = intervalDistribution(numberGenerator);
		currentInterval = inputInterval;
		cout << currentInterval << endl;
		switch (direction)
		{
		case 0:
			cout << entityName << " Moving North" << endl;
			Entity::move(Vector2u(0, -1));
			break;
		case 1:
			cout << entityName << " Moving West" << endl;
			Entity::move(Vector2u(1, 0));
			break;
		case 2:
			cout << entityName << " Moving South" << endl;
			Entity::move(Vector2u(0, 1));
			break;
		case 3:
			cout << entityName << " Moving East" << endl;
			Entity::move(Vector2u(-1, 0));
			break;
		case 5 | 6:
			cout << entityName << " Staying in place" << endl;
			break;
		default:
			cout << "Invaling number." << endl;
			break;
		}
		timer.restart();
	}
	animator();
	travel(inputProcessSpeed);
	//Sprite::setPosition(64 * mapPosition.x, 64 * mapPosition.y);
	//cout << "update() method ended\n";
}