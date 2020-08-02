#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(Vector2u inputPosition)
{
	cout << "[PlayerCharacter constructor] Constructing \"Player\" entity." << endl;
	entityName = "Player";
	mapPosition = inputPosition;
	cout << "[PlayerCharacter constructor] The entity named \"Player\" has been constructed." << endl;
}

PlayerCharacter::PlayerCharacter(Vector2u inputPosition, array<array<unsigned char, 128>, 128> &inputMapPointer)
{
	cout << "[PlayerCharacter constructor] Constructing \"Player\" entity from \"" << entityName<< "\"." << endl;
	entityName = "Player";
	mapPosition = inputPosition;
	localMap = &inputMapPointer;
	cout << "[PlayerCharacter constructor] The entity named \"" << entityName << "\" has been constructed." << endl;
}

PlayerCharacter::~PlayerCharacter()
{
	//cout << "The \"" << entityName << "\" is being destroyed" << endl;
	cout << "[PlayerCharacter destructor] The \"" << entityName << "\" has been destroyed" << endl;
}

void PlayerCharacter::update(float inputProcessSpeed)
{
	// Local variables

	// Main "update()"
	Sprite::setPosition(64 * mapPosition.x, 64 * mapPosition.y);
	playerView.setSize(960, 640);
	playerView.setCenter(Sprite::getPosition().x + 32, Sprite::getPosition().y + 32);
	cout << playerView.getSize().x << " " << playerView.getSize().y << endl;

}