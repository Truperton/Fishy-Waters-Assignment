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
	Entities()
	{

	}
	~Entities()
	{

	}
	Texture characterTextures[1];
	Sprite characterSprite;
	float travelSpeed;
	vector<char> traversableTerrain;
	array<array<bool, 128>, 128> position;
	void Move(array<array<bool, 128>, 128> inputPosition, array<array<unsigned char, 128>, 128> inputMap, short int inputX, short int inputY);

private:

};