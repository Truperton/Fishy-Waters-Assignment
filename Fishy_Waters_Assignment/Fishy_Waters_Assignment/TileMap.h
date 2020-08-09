#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <array>

using namespace std;
using namespace sf;

class TileMap : public Drawable, public Transformable
{
public:
	// Public variables

	// Constructor

	TileMap();

	// Destructor

	~TileMap();

	// Public methods

	/// <summary>
	/// Loads the tile map from the level map that was inputted with tiles of
	/// the given size from the tile set that was put in.
	/// </summary>
	/// <param name="inputTileSetLoadLocation"> The path to the tile set file. </param>
	/// <param name="inputGameMApLoaction"> The name of the game map CSV. </param>
	/// <param name="inputTileSize"> The size in height and width of tiles in pixels. </param>
	/// <param name="inputMap"> The two dimensional array on which the game map is to be based off of. </param>
	bool load(const string inputTileSetLoadLocation, const string inputGameMapLocation, Vector2u inputTileSize, array<array<unsigned char, 128>, 128> *inputMap);

private:
	// Private variables

	VertexArray mapVertices;
	Texture mapTileSet;
	array<array<unsigned char, 128>, 128> *localMapPointer;

	// Private methods

	bool loadGameMap(const string inputGameMapLocation);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};