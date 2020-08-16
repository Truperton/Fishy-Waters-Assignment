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

Entity::Entity(string inputName, Vector2u inputPosition, array<array<unsigned char, 128>, 128> *inputMapPointer)
{
	cout << "[Entity constructor] Constructing \"" << inputName << "\" entity." << endl;
	entityName = inputName;
	mapPosition = inputPosition;
	localMapPointer = inputMapPointer;
	cout << "[Entity constructor] The entity named \"" << entityName << "\" has been constructed." << endl;
}

Entity::~Entity()
{
	// Local variables

	// Main "~Entity()"
	cout << "The \"" << entityName << "\" is being destroyed" << endl;
	localMapPointer = nullptr;
	cout << "[Entity destructor] The \"" << entityName << "\" has been destroyed" << endl;
}

void Entity::update(Time inputProcessSpeed)
{
	// Local variables

	// Main "update()"
	Sprite::setPosition(64 * mapPosition.x, 64 * mapPosition.y);
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
	Sprite::setTexture(spriteTexture);
	Sprite::setTextureRect(sf::IntRect(Vector2i(0,0) ,inputSpriteSize));
	cout << "Sprite sheet loaded from \"" << inputSpriteSheetLoadLocation << "\"" << endl;
	return true;
}

void Entity::move(Vector2u inputMovement)
{
	// Local variables
	/// <summary> If the variable still ends as true it outputs that the object collided. </summary>
	bool moveCollision = true;
	// Main "move()"
	if (!moving)
	{
		for (auto item : traversableTerrain)
		{
			if ((*localMapPointer)[mapPosition.y + inputMovement.y][mapPosition.x + inputMovement.x] == item)
			{
				mapPosition += inputMovement;
				moveCollision = false;
			}
		}
		if (moveCollision)
		{
			if (debugging)
			{
				cout << "[Entity event] Entity \"" << entityName << "\": Collision\n";
			}
		}
	}
	else
	{
		if (debugging)
		{
			cout << "[Entity event] Entity \"" << entityName << "\" still moving\n";
		}
	}
	return;
}

void Entity::animator()
{
	// Local variables

	// Main "travel()"
	if (moving)
	{
		if (animationState != 1)
		{
			animationFrame = 0;
		}
		animationState = 1;
	}
	else if (!moving)
	{
		if (animationState != 0)
		{
			animationFrame = 0;
		}
		animationState = 0;
	}
	if (animationInterval > 0.4f)
	{
		if (animationFrame < 3)
		{
			animationFrame++;
		}
		else
		{
			animationFrame = 0;
		}
		animationInterval = 0.0f;
		//cout << +animationState << " " << +animationFrame << endl;
	}
	Sprite::setTextureRect(sf::IntRect(Vector2i(animationFrame * 64, animationState* 64), Vector2i(64,64)));
}

void Entity::travel(Time inputProcessSpeed)
{
	// Local variables
	Vector2f destination;
	Vector2f step;
	// Main "travel()"
	destination = Vector2f(mapPosition.x * 64, mapPosition.y * 64);
	if (destination != Sprite::getPosition())
	{
		moving = true;
		if (debugging)
		{
			cout << entityName << " moving set to true\n";
		}
		if (destination.x - Sprite::getPosition().x > travelSpeed / 15)
		{
			step.x = travelSpeed * inputProcessSpeed.asSeconds();
			step.y = 0;
		}
		else if (destination.x - Sprite::getPosition().x < -travelSpeed / 15)
		{
			step.x = travelSpeed * -inputProcessSpeed.asSeconds();
			step.y = 0;
		}
		else
		{
			step.x = 0;
		}

		if (destination.y - Sprite::getPosition().y > travelSpeed / 15)
		{
			step.y = travelSpeed * inputProcessSpeed.asSeconds();
		}
		else if (destination.y - Sprite::getPosition().y < -travelSpeed / 15)
		{
			step.y = travelSpeed * -inputProcessSpeed.asSeconds();
		}
		else
		{
			step.y = 0;
		}

		if (step == Vector2f(0, 0))
		{
			Sprite::setPosition(destination);
			//moving = false;
			//if (debugging)
			//{
			//	cout << entityName << " moving set to false after being set to true\n";
			//}
		}
		Sprite::move(step);
	}
	else
	{
		moving = false;
		if (debugging)
		{
			cout << entityName << " moving set to false\n";
		}
	}

}