#include "Game/Game.h"

#include <iostream>
#include <stdexcept>

int main()
{
	try
	{
		Game* game = Game::getGame();
		game->Initialize();
		game->Run();
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Error: " << exception.what() << std::endl;
		return 1;
	}

	return 0;
}