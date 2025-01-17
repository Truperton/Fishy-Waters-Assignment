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
			// obtains the tile number
			int tileNumber = (*inputMap)[x][y];

			// find its position in the tileset texture
			int tu = tileNumber % (mapTileSet.getSize().x / inputTileSize.x);
			int tv = tileNumber / (mapTileSet.getSize().x / inputTileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &mapVertices[(y + x * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(y * inputTileSize.x, x * inputTileSize.y);
			quad[1].position = sf::Vector2f((y + 1) * inputTileSize.x, x * inputTileSize.y);
			quad[2].position = sf::Vector2f((y + 1) * inputTileSize.x, (x + 1) * inputTileSize.y);
			quad[3].position = sf::Vector2f(y * inputTileSize.x, (x + 1) * inputTileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * inputTileSize.x, tv * inputTileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * inputTileSize.x, tv * inputTileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * inputTileSize.x, (tv + 1) * inputTileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * inputTileSize.x, (tv + 1) * inputTileSize.y);
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

		//for (auto item : *localMapPointer)
		//{
		//	for (auto item2 : item)
		//	{
		//		cout << +item2 << " ";
		//	}
		//	cout << endl;
		//}
		//(*localMapPointer)[0] = integerArray[0];
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