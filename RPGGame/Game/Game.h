#pragma once
#include "../Character/Character.h"
class Game
{
public:
	static Game* getGame();
	~Game();
	void Initialize();
	void Run();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
private:
	Game() = default;
	Character mainCharacter;
	Character* enemies=nullptr;
	static const int enemiesCount;
	static Game* game;
	void CheckIfEnemyDead(int&, int&);
};