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

bool debuggingMap = false;
// Game window related variables

sf::Vector2f theGameWindow_CurrentDimensions(960, 640);
sf::Vector2f theGameWindow_PerspectiveDimensions(960, 640);
sf::RenderWindow theGameWindow(sf::VideoMode(theGameWindow_CurrentDimensions.x, theGameWindow_CurrentDimensions.y), "Fishy Waters");

// Tile Map variables

TileMap *mainTileMap;

// This variable stores a 128x128 tiles map
array<array<unsigned char, 128>, 128> gameMap;
PlayerCharacter *MainPlayer;

void InputListener();
void ConsoleMapOutput();

int main()
{
	// Local Variables
	Clock delta;
	Clock sessionTime;
	Time elapsedTime;

	// Main main()
	theGameWindow.setFramerateLimit(60);
	mainTileMap = new TileMap;
	if (!mainTileMap->load("Assets/Tile Sets/Main Tile Set.png", "Map 1.csv", Vector2u(64, 64), &gameMap))
	{
		cout << "[Error] Failed to load TileMap.";
	}
	MainPlayer = new PlayerCharacter(Vector2u(4, 5), &gameMap, 150.0f);
	MainPlayer->load("Assets/Sprite Sheets/Player Character Sprite Sheet.png", Vector2i(64, 64));
	MainPlayer->traversableTerrain.push_back(13);
	elapsedTime = delta.getElapsedTime();
	cout << "[Game Status] Game loaded in " << elapsedTime.asSeconds() << " seconds.";
	sessionTime.restart();
	while (theGameWindow.isOpen())
	{
		InputListener();
		elapsedTime = delta.restart();
		//cout << elapsedTime.asSeconds() << " " << elapsedTime.asMilliseconds() << " " << elapsedTime.asMicroseconds() << endl;
		MainPlayer->update(elapsedTime);

		// Following section handles drawing on the game window.
		theGameWindow.clear();
		theGameWindow.setView(MainPlayer->playerView);
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
	bool w = false, a = false, s = false, d = false;
	Vector2u direction;

	// Main "InputListener()"
	while (theGameWindow.pollEvent(event))
	{
		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
		{
			theGameWindow.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::W)
			{
				//MainPlayer->move(Vector2u(0, -1));
				w = true;
				if (MainPlayer->debugging)
				{
					cout << "W Key Down" << endl;
				}
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
			if (event.key.code == sf::Keyboard::S)
			{
				s = true;
				//MainPlayer->move(Vector2u(0, 1));
				if (MainPlayer->debugging)
				{
					cout << "S Key Down" << endl;
				}
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
			if (event.key.code == sf::Keyboard::A)
			{
				a = true;
				//MainPlayer->move(Vector2u(-1, 0));
				if (MainPlayer->debugging)
				{
					cout << "A Key Down" << endl;
				}
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
			if (event.key.code == sf::Keyboard::D)
			{
				d = true;
				//MainPlayer->move(Vector2u(1, 0));
				if (MainPlayer->debugging)
				{
					cout << "D Key Down" << endl;
				}
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::W)
			{
				w = false;
				if (MainPlayer->debugging)
				{
					cout << "[Key event] W key released" << endl;
				}
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
			if (event.key.code == sf::Keyboard::S)
			{
				s = false;
				if (MainPlayer->debugging)
				{
					cout << "[Key event] S key released" << endl;
				}
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
			if (event.key.code == sf::Keyboard::A)
			{
				a = false;
				if (MainPlayer->debugging)
				{
					cout << "[Key event] A key released" << endl;
				}
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
			if (event.key.code == sf::Keyboard::D)
			{
				d = false;
				if (MainPlayer->debugging)
				{
					cout << "[Key event] D key released" << endl;
				}
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
		}

	}
	if (w)
	{
		direction += Vector2u(0, -1);
	}
	if (s)
	{
		direction += Vector2u(0, 1);
	}
	if (a)
	{
		direction += Vector2u(-1, 0);
	}
	if (d)
	{
		direction += Vector2u(1, 0);
	}
	MainPlayer->move(direction);
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
