#include "TileMap.h"

TileMap::TileMap()
{
	cout << "[TileMap constructor] TileMap constructed" << endl;
}

TileMap::~TileMap()
{
	cout << "[TileMap destructor] TileMap destroyed" << endl;
}

bool TileMap::load(const string inputTileSetLoadLocation, const string inputGameMapLocation, Vector2u inputTileSize, array<array<unsigned char, 128>, 128> *inputMap)
{
	// Local Variables
	unsigned short int height, width;

	// Main load()
	localMapPointer = inputMap;
	loadGameMap(inputGameMapLocation);
	cout << "[TileMap loading] ";
	if (!mapTileSet.loadFromFile(inputTileSetLoadLocation))
	{
		cout << "[Error] Failed to load TileMap: Couldn't find tile set under \"" << inputTileSetLoadLocation << "\"" << endl;
		return false;
	}
	height = inputMap->size();
	width = inputMap[0].size();
	mapVertices.setPrimitiveType(sf::Quads);
	mapVertices.resize(width * height * 4);
	for (unsigned short int y = 0; y < height; y++)
	{
		for (unsigned short int x = 0; x < width; x++)
		{
			// Retrieve the tile number
			int tileNumber = (*inputMap)[y][x];

			// Get the coordinates in the tileset texture
			int tileX = tileNumber % (mapTileSet.getSize().x / inputTileSize.x);
			int tileY = tileNumber / (mapTileSet.getSize().x / inputTileSize.x);

			// Retrieve the pointer for the current tile's quad
			sf::Vertex* quad = &mapVertices[(y + x * width) * 4];

			// Define the quad's 4 corners
			quad[0].position = sf::Vector2f(x * inputTileSize.x, y * inputTileSize.y);
			quad[1].position = sf::Vector2f((x + 1) * inputTileSize.x, y * inputTileSize.y);
			quad[2].position = sf::Vector2f((x + 1) * inputTileSize.x, (y + 1) * inputTileSize.y);
			quad[3].position = sf::Vector2f(x * inputTileSize.x, (y + 1) * inputTileSize.y);

			// Define the quad's coordinates in the texture
			quad[0].texCoords = sf::Vector2f(tileX * inputTileSize.x, tileY * inputTileSize.y);
			quad[1].texCoords = sf::Vector2f((tileX + 1) * inputTileSize.x, tileY * inputTileSize.y);
			quad[2].texCoords = sf::Vector2f((tileX + 1) * inputTileSize.x, (tileY + 1) * inputTileSize.y);
			quad[3].texCoords = sf::Vector2f(tileX * inputTileSize.x, (tileY + 1) * inputTileSize.y);
		}
	}
	cout << "TileMap loaded from \"" << inputTileSetLoadLocation << "\"" << endl;
	return true;
}

bool TileMap::loadGameMap(const string inputGameMapLocation)
{
	// Local variables
	ifstream openedFile;
	array<string, 128> stringArray;
	string *stringToArray = new string;
	string::size_type stringSizeType;
	int counter, counterTwo, counterThree, maxSizeOne, maxSizeTwo, tempInt;

	// Main "loadGameMap()"
	cout << "[Loading Game Map]";
	openedFile.open(inputGameMapLocation, ios::in);
	if (openedFile.is_open())
	{
		cout << " Game map \"" << inputGameMapLocation << "\"\n";
		counter = 0;
		while (getline(openedFile, *stringToArray))
		{
			stringArray[counter] = *stringToArray;
			counter++;
		}
		stringToArray = NULL;
		openedFile.close();

		stringToArray = new string;
		counterThree = 0;
		maxSizeOne = stringArray.size();
		for (counter = 0; counter < maxSizeOne; counter++)
		{
			maxSizeTwo = stringArray[counter].size();
			for (counterTwo = 0; counterTwo < maxSizeTwo + 1; counterTwo++)
			{
				if (stringArray[counter][counterTwo] != ',')
				{
					if (counterTwo >= maxSizeTwo)
					{
						tempInt = stoi(*stringToArray, &stringSizeType);
						(*localMapPointer)[counter][counterThree] = tempInt;
						stringToArray = NULL;
						stringToArray = new string;
					}
					else
					{
						*stringToArray += stringArray[counter][counterTwo];
					}
				}
				else
				{
					if (stringToArray->length() > 0)
					{
						tempInt = stoi(*stringToArray, &stringSizeType);
						(*localMapPointer)[counter][counterThree] = tempInt;
					}
					else
					{
						(*localMapPointer)[counter][counterThree] = 255;
					}
					stringToArray = NULL;
					stringToArray = new string;
					counterThree++;
				}
			}
			counterThree = 0;
		}

		return true;
	}
	else
	{
		cout << " Failed to find game map \"" << inputGameMapLocation << "\"\n";
		return false;
	}
	delete stringToArray;
	stringToArray = nullptr;
	delete &stringArray;
	counter, counterTwo, counterThree, maxSizeOne, maxSizeTwo, tempInt = NULL;

}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &mapTileSet;

	// draw the vertex array
	target.draw(mapVertices, states);
}