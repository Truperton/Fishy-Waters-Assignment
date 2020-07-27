#pragma once

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TileMap : public Drawable, public Transformable
{
public:
	// Public variables

	// Public methods
	bool load(const string inputTileSetLoadLocation, Vector2u inputTileSize, array<array<unsigned char, 128>, 128> inputMap)
	{
		// Local Variables
		unsigned short int height, width;

		// Main load()
		if (!mapTileSet.loadFromFile(inputTileSetLoadLocation))
		{
			return false;
		}
		height = inputMap.size;
		width = inputMap[0].size;
	}

private:
	// Private variables
	VertexArray mapVertices;
	Texture mapTileSet;

	// Private methods
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

