#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

/// <summary>
/// This is the base class for entities
/// that contains the basic operations for
/// moving objects within the game.
/// </summary>
class Entities
{
public:
	// Public variables
	string entityName;
	Texture characterTextures[1];
	Sprite characterSprite;
	float travelSpeed;
	vector<char> traversableTerrain;
	Vector2u mapPosition;

	// Constructors
	Entities()
	{

	}

	/// <summary>
	/// Constructs a new entity with a name.
	/// </summary>
	/// <param name="inputName"> The individual name of the entity. </param>
	Entities(string inputName)
	{
		cout << "Constructing \"" << inputName << "\" entity." << endl;
		entityName = inputName;
		cout << "The entity named \"" << entityName << "\" has been constructed." << endl;
	}

	/// <summary>
	/// Constructs a new entity with a name and given location.
	/// </summary>
	/// <param name="inputName"> The individual name of the entity. </param>
	/// <param name="inputPosition"> The position on the map that the entity is to spawn at. </param>
	Entities(string inputName, Vector2u inputPosition)
	{
		cout << "Constructing \"" << inputName << "\" entity." << endl;
		entityName = inputName;
		cout << "The entity named \"" << entityName << "\" has been constructed." << endl;
	}

	// Destructor
	~Entities()
	{
		cout << "The \"" << entityName << "\" is being destructed" << endl;
		cout << "The \"" << entityName << "\" has been destructed" << endl;
	}

	/// <summary>
	/// This method moves the entity in the 2 dimensional
	/// array depending on the input.
	/// </summary>
	void Move(array<array<unsigned char, 256>, 256> inputMap, Vector2u inputMovement)
	{
		if (inputMap[mapPosition.x + inputMovement.x][mapPosition.y + inputMovement.y] != 2)
		{
			mapPosition += inputMovement;
		}
		else
		{
			cout << "Entity \"" << entityName << "\": Collision\n";
		}
		return;
	}

private:

};