#include "Entity.h"

Entity::Entity()
{
	cout << "[Entity constructor] Constructing \"Base Entity\" entity." << endl;
	entityName = "Base Entity";
	cout << "[Entity constructor] The entity named \"" << entityName << "\" has been constructed." << endl;
}

Entity::Entity(string inputName)
{
	cout << "[Entity constructor] Constructing \"" << inputName << "\" entity." << endl;
	entityName = inputName;
	cout << "[Entity constructor] The entity named \"" << entityName << "\" has been constructed." << endl;
}

Entity::Entity(string inputName, Vector2u inputPosition)
{
	cout << "[Entity constructor] Constructing \"" << inputName << "\" entity." << endl;
	entityName = inputName;
	mapPosition = inputPosition;
	cout << "[Entity constructor] The entity named \"" << entityName << "\" has been constructed." << endl;
}

Entity::Entity(string inputName, Vector2u inputPosition, array<array<unsigned char, 128>, 128> &inputMapPointer)
{
	cout << "[Entity constructor] Constructing \"" << inputName << "\" entity." << endl;
	entityName = inputName;
	mapPosition = inputPosition;
	localMap = &inputMapPointer;
	cout << "[Entity constructor] The entity named \"" << entityName << "\" has been constructed." << endl;
}

Entity::~Entity()
{
	//cout << "The \"" << entityName << "\" is being destroyed" << endl;
	cout << "[Entity destructor] The \"" << entityName << "\" has been destroyed" << endl;
}

void Entity::update(float inputProcessSpeed)
{
	Sprite::setPosition(Sprite::getTextureRect().width * mapPosition.x, Sprite::getTextureRect().height * mapPosition.y);
}

bool Entity::load(const std::string inputSpriteSheetLoadLocation, sf::Vector2i inputSpriteSize)
{
	// Local variables

	// Main "load()"
	cout << "[Entity sprite sheet loading] ";
	if (!spriteTexture.loadFromFile(inputSpriteSheetLoadLocation))
	{
		cout << "[Error] Failed to load sprite sheet: Couldn't find tile set under \"" << inputSpriteSheetLoadLocation << "\"" << endl;
		return false;
	}
	//testSprite.setTexture(spriteTexture);
	//testSprite.setTextureRect(sf::IntRect(Vector2i(0, 0), inputSpriteSize));
	Sprite::setTexture(spriteTexture);
	Sprite::setTextureRect(sf::IntRect(Vector2i(0,0) ,inputSpriteSize));
	cout << "Sprite sheet loaded from \"" << inputSpriteSheetLoadLocation << "\"" << endl;
	return true;
}

void Entity::move(array<array<unsigned char, 128>, 128> inputMap, Vector2u inputMovement)
{
	// Local variables
	
	bool moveCollision = true;
	// Main "move()"
	for (auto item : traversableTerrain)
	{
		if (inputMap[mapPosition.y + inputMovement.y][mapPosition.x + inputMovement.x] == item)
		{
			mapPosition += inputMovement;
			moveCollision = false;
		}
	}
	if (moveCollision)
	{
		cout << "[Entity event] Entity \"" << entityName << "\": Collision\n";
	}
	return;
}