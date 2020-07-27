// Fishy_Waters_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include "Entities.h"

using namespace std;
using namespace sf;
// Global Variables
// Debugging variables
bool debuggingMap = true;
// Game window related variables
sf::Vector2f theGameWindow_CurrentDimensions(960, 640);
sf::Vector2f theGameWindow_PerspectiveDimensions(960, 640);
sf::RenderWindow theGameWindow(sf::VideoMode(theGameWindow_CurrentDimensions.x, theGameWindow_CurrentDimensions.y), "Fishy Waters", sf::Style::Titlebar);
// Tile Map variables
Texture currentTileSet;

// This variable stores a 128x128 tiles map
array<array<unsigned char, 128>, 128> gameMap;
Entities MainPlayer;

void InputListener();
void DrawMap(array<array<char, 128>, 128> inputMap);
void ConsoleMapOutput();

int main()
{
	// Local Variables

	// Main main()
	//              0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
	gameMap[0]  = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	gameMap[1]  = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	gameMap[2]  = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	gameMap[3]  = { 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
	gameMap[4]  = { 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
	gameMap[5]  = { 2, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
	gameMap[6]  = { 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
	gameMap[7]  = { 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
	gameMap[8]  = { 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
	gameMap[9]  = { 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
	gameMap[10] = { 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
	gameMap[11] = { 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
	gameMap[12] = { 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
	gameMap[13] = { 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2 };
	gameMap[14] = { 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2 };
	gameMap[15] = { 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 };
	gameMap[16] = { 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 };
	//if (!currentTileSet.loadFromFile("Assets/Tilemaps/Temperate TileMap.png")) //The "Temperate TileMap" Sprite
	//{
	//	cout << "Error 1: Loading The Game Image(s) Failed. Make Sure ALL Images Are 8-bit-RGBA Images..." << "\n";
	//	system("pause");
	//}
	MainPlayer.position[4][5] = true;
    cout << "Game loaded\n";
	while (theGameWindow.isOpen())
	{
		InputListener();
		theGameWindow.clear();
		theGameWindow.display();
	}
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
				MainPlayer.Move(MainPlayer.position, gameMap, -1, 0);
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
			else if (event.key.code == sf::Keyboard::S)
			{
				MainPlayer.Move(MainPlayer.position, gameMap, 1, 0);
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
			else if (event.key.code == sf::Keyboard::A)
			{
				MainPlayer.Move(MainPlayer.position, gameMap, 0, -1);
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				MainPlayer.Move(MainPlayer.position, gameMap, 0, 1);
				if (debuggingMap)
				{
					ConsoleMapOutput();
				}
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{

		}
	}
}

void ConsoleMapOutput()
{
	// Local Variables
	char i = -1, j = -1;

	// Main ConsoleMapOutput()
	for (auto item : gameMap)
	{
		++i;
		for (auto item2 : item)
		{
			++j;
			if (MainPlayer.position[i][j])
			{
				cout << "C";
			}
			else
			{
				cout << +item2;
			}
		}
		j = -1;
		cout << endl;
	}
	cout << endl;
	//for (i = 0; i < 127; i++)
	//{
	//	for (j = 0; j < 127; j++)
	//	{
	//		if (MainPlayer.position[i][j])
	//		{
	//			cout << "C";
	//		}
	//		else
	//		{
	//			cout << +gameMap[i][j];
	//		}
	//	}
	//	cout << endl;
	//}
	//cout << endl;
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
