// Fishy_Waters_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "PlayerCharacter.h"
#include "TileMap.h"

using namespace std;
using namespace sf;
// Global Variables
// Debugging variables

bool debuggingMap = true;
// Game window related variables

sf::Vector2f theGameWindow_CurrentDimensions(960, 640);
sf::Vector2f theGameWindow_PerspectiveDimensions(960, 640);
sf::RenderWindow theGameWindow(sf::VideoMode(theGameWindow_CurrentDimensions.x, theGameWindow_CurrentDimensions.y), "Fishy Waters");
// Tile Map variables

TileMap *mainTileMap;

// This variable stores a 128x128 tiles map
array<array<unsigned char, 128>, 128> gameMap;
Entity *MainPlayer;

void InputListener();
void ConsoleMapOutput();

int main()
{
	// Local Variables

	// Main main()
	//              0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
	gameMap[0]  = { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 };
	gameMap[1]  = { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 };
	gameMap[2]  = { 14, 14,  4,  8,  8,  8,  5,  4,  8,  8,  8,  8,  8,  5, 14, 14 };
	gameMap[3]  = { 14, 14, 11, 13, 13, 13,  9, 11, 13, 13, 13, 13, 13,  9, 14, 14 };
	gameMap[4]  = { 14, 14, 11, 13, 13, 13,  9, 11, 13, 13, 13, 13, 13,  9, 14, 14 };
	gameMap[5]  = { 14, 14, 11, 13, 13,  0,  7, 11, 13, 13, 13, 13, 13,  9, 14, 14 };
	gameMap[6]  = { 14, 14, 11, 13, 13,  2,  8,  3, 13, 13, 13, 13, 13,  9, 14, 14 };
	gameMap[7]  = { 14, 14, 11, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9, 14, 14 };
	gameMap[8]  = { 14, 14, 11, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9, 14, 14 };
	gameMap[9]  = { 14, 14, 11, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9, 14, 14 };
	gameMap[10] = { 14, 14, 11, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9, 14, 14 };
	gameMap[11] = { 14, 14, 11, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9, 14, 14 };
	gameMap[12] = { 14, 14, 11, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9, 14, 14 };
	gameMap[13] = { 14, 14,  6, 14, 14, 14, 14, 13, 14, 14, 14, 14, 14, 14, 14, 14 };
	gameMap[14] = { 14, 14, 14, 14, 14, 14, 14, 13, 14, 14, 14, 14, 14, 14, 14, 14 };
	gameMap[15] = { 14, 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14 };
	gameMap[16] = { 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14 };
	mainTileMap = new TileMap;
	if (!mainTileMap->load("Assets/Tile Sets/Main Tile Set.png", Vector2u(64, 64), gameMap))
	{
		cout << "[Error] Failed to load TileMap.";
	}
	//if (!currentTileSet.loadFromFile("Assets/Tilemaps/Temperate TileMap.png")) //The "Temperate TileMap" Sprite
	//{
	//	cout << "Error 1: Loading The Game Image(s) Failed. Make Sure ALL Images Are 8-bit-RGBA Images..." << "\n";
	//	system("pause");
	//}
	//MainPlayer->mapPosition = Vector2u(4, 5);
	//MainPlayer.position[4][5] = true;
	MainPlayer = new PlayerCharacter(Vector2u(4, 5), gameMap);
	MainPlayer->load("Assets/Sprite Sheets/Player Character Sprite Sheet.png", Vector2i(64, 64));
	MainPlayer->traversableTerrain.push_back(13);
	cout << "[Game Status] Game loaded\n";

	while (theGameWindow.isOpen())
	{
		InputListener();
		MainPlayer->update(1);
		theGameWindow.clear();
		theGameWindow.draw(*mainTileMap);
		theGameWindow.draw(*MainPlayer);
		theGameWindow.display();
	}
	cout << "[Game Status] Game closing down..." << endl;
	delete mainTileMap;
	mainTileMap = nullptr;
	delete MainPlayer;
	MainPlayer = nullptr;
}

/// <summary>
/// This method takes in player input
/// </summary>
void InputListener()
{
	// Local Variables
	sf::Event event;

	// Main "InputListener()"
	while (theGameWindow.pollEvent(event))
	{
		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
		{
			theGameWindow.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::W)
			{
				MainPlayer->move(gameMap, Vector2u(0, -1));
				if (debuggingMap)
				{
					cout << "W Key Down" << endl;
					ConsoleMapOutput();
				}
			}
			else if (event.key.code == sf::Keyboard::S)
			{
				MainPlayer->move(gameMap, Vector2u(0, 1));
				if (debuggingMap)
				{
					cout << "S Key Down" << endl;
					ConsoleMapOutput();
				}
			}
			else if (event.key.code == sf::Keyboard::A)
			{
				MainPlayer->move(gameMap, Vector2u(-1, 0));
				if (debuggingMap)
				{
					cout << "A Key Down" << endl;
					ConsoleMapOutput();
				}
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				MainPlayer->move(gameMap, Vector2u(1, 0));
				if (debuggingMap)
				{
					cout << "D Key Down" << endl;
					ConsoleMapOutput();
				}
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{

		}
	}
}

/// <summary>
/// Outputs a small portion of the map in text form in the console.
/// </summary>
void ConsoleMapOutput()
{
	// Local Variables
	unsigned char i = -1, j = -1;

	// Main ConsoleMapOutput()
	cout << +gameMap[MainPlayer->mapPosition.y - 2][MainPlayer->mapPosition.x - 2] << " | " << +gameMap[MainPlayer->mapPosition.y - 2][MainPlayer->mapPosition.x - 1] << " | " << +gameMap[MainPlayer->mapPosition.y - 2][MainPlayer->mapPosition.x] << " | " << +gameMap[MainPlayer->mapPosition.y - 2][MainPlayer->mapPosition.x + 1] << " | " << +gameMap[MainPlayer->mapPosition.y - 2][MainPlayer->mapPosition.x + 2] << endl;
	cout << +gameMap[MainPlayer->mapPosition.y - 1][MainPlayer->mapPosition.x - 2] << " | " << +gameMap[MainPlayer->mapPosition.y - 1][MainPlayer->mapPosition.x - 1] << " | " << +gameMap[MainPlayer->mapPosition.y - 1][MainPlayer->mapPosition.x] << " | " << +gameMap[MainPlayer->mapPosition.y - 1][MainPlayer->mapPosition.x + 1] << " | " << +gameMap[MainPlayer->mapPosition.y - 1][MainPlayer->mapPosition.x + 2] << endl;
	cout << +gameMap[MainPlayer->mapPosition.y][MainPlayer->mapPosition.x - 2] << " | " << +gameMap[MainPlayer->mapPosition.y][MainPlayer->mapPosition.x - 1] << " | " << "C" << " | " << +gameMap[MainPlayer->mapPosition.y][MainPlayer->mapPosition.x + 1] << " | " << +gameMap[MainPlayer->mapPosition.y][MainPlayer->mapPosition.x + 2] << " | " << endl;
	cout << +gameMap[MainPlayer->mapPosition.y + 1][MainPlayer->mapPosition.x - 2] << " | " << +gameMap[MainPlayer->mapPosition.y + 1][MainPlayer->mapPosition.x - 1] << " | " << +gameMap[MainPlayer->mapPosition.y + 1][MainPlayer->mapPosition.x] << " | " << +gameMap[MainPlayer->mapPosition.y + 1][MainPlayer->mapPosition.x + 1] << " | " << +gameMap[MainPlayer->mapPosition.y + 1][MainPlayer->mapPosition.x + 2] << endl;
	cout << +gameMap[MainPlayer->mapPosition.y + 2][MainPlayer->mapPosition.x - 2] << " | " << +gameMap[MainPlayer->mapPosition.y + 2][MainPlayer->mapPosition.x - 1] << " | " << +gameMap[MainPlayer->mapPosition.y + 2][MainPlayer->mapPosition.x] << " | " << +gameMap[MainPlayer->mapPosition.y + 2][MainPlayer->mapPosition.x + 1] << " | " << +gameMap[MainPlayer->mapPosition.y + 2][MainPlayer->mapPosition.x + 2] << endl;
	cout << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
