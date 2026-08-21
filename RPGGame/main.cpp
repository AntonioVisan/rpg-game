#include "Game/Game.h"
int main()
{
	try
	{
		
		Game* game = Game::getGame();
		game->Initialize();
		game->Run();
		delete game;
		return 0;
	}
	catch (const char* mesaj)
	{
		std::cerr << mesaj;
		return 1;
	}
}