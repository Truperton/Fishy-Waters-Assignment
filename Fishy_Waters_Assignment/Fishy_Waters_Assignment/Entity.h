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
	Entity(string inputName, Vector2u inputPosition, array<array<unsigned char, 128>, 128> &inputMapPointer);

	// Destructor

	~Entity();

	// Public methods

	virtual void update(float inputProcessSpeed);

	bool load(const string inputSpriteSheetLoadLocation, Vector2i inputSpriteSize);

	/// <summary>
	/// This method moves the entity in the 2 dimensional
	/// array depending on the input.
	/// </summary>
	void move(array<array<unsigned char, 128>, 128> inputMap, Vector2u inputMovement);
protected:
	// Protected variables

	array<array<unsigned char, 128>, 128> *localMap;
	// Protected methods

private:
	// Private variables

	Texture spriteTexture;
	// Private methods

};