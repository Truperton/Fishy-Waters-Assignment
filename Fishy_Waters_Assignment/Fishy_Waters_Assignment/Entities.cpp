#include "Entities.h"

/// <summary>
/// This method moves the entity in the 2 dimensional
/// array depending on the input.
/// </summary>
void Entities::Move(array<array<bool, 128>, 128> inputPosition, array<array<unsigned char, 128>, 128> inputMap, short int inputX, short int inputY)
{
	short i, j, x = 0, y = 0;
	for (i = 127; i > 1; i--)
	{
		for (j = 127; j > 1; j--)
		{
			if (position[i][j])
			{
				x = i;
				y = j;
				i = 0;
				j = 0;
			}
		}
	}
	if (inputMap[x + inputX][y + inputY] != 2)
	{
		position[x + inputX][y + inputY] = true;
		position[x][y] = false;
	}
	else
	{
		cout << "Collision\n";
	}
	return;
}
