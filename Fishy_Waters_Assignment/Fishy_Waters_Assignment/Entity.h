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
class Entity : public Sprite
{
public:
	// Public variables
	/// <summary>
	/// Set to true if you want the entity to output
	/// debugging related messages in the console 
	/// </summary>
	bool debugging = false;
	string entityName;
	float travelSpeed;
	vector<char> traversableTerrain;
	Vector2u mapPosition;
	// Default states:
	// 0 - Idle
	// 1 - Walk
	unsigned char animationState;
	unsigned char animationFrame;

	// Constructors

	Entity();
	/// <summary>
	/// Constructs a new entity with a name.
	/// </summary>
	/// <param name="inputName"> The individual name of the entity. </param>
	Entity(string inputName);

	/// <summary>
	/// Constructs a new entity with a name and given location.
	/// </summary>
	/// <param name="inputName"> The individual name of the entity. </param>
	/// <param name="inputPosition"> The position on the map that the entity is to spawn at. </param>
	Entity(string inputName, Vector2u inputPosition);

	/// <summary>
	/// Constructs a new entity with a name and given location.
	/// </summary>
	/// <param name="inputName"> The individual name of the entity. </param>
	/// <param name="inputPosition"> The position on the map that the entity is to spawn at. </param>
	Entity(string inputName, Vector2u inputPosition, array<array<unsigned char, 128>, 128> *inputMapPointer);

	// Destructor

	~Entity();

	// Public methods

	virtual void update(float inputProcessSpeed);

	bool load(const string inputSpriteSheetLoadLocation, Vector2i inputSpriteSize);

	/// <summary>
	/// This method moves the entity in the 2 dimensional
	/// array depending on the input.
	/// </summary>
	void move(Vector2u inputMovement);
protected:
	// Protected variables
	/// <summary> Stores the pointer to the game map in the main program. </summary>
	array<array<unsigned char, 128>, 128> *localMapPointer;
	// Protected methods

private:
	// Private variables
	/// <summary> The variable that stores the texture of the entity internally. </summary>
	Texture spriteTexture;
	// Private methods

};