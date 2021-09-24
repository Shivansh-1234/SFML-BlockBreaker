#include "DEFINITIONS.h"
#include "Game.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

int main()
{
	srand(time(0));

	Game::Game(SCREENWIDTH, SCREENHEIGHT, "ABC");
}