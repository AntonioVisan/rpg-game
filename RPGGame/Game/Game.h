#pragma once

#include "../Character/Character.h"

#include <memory>

class Game
{
public:
	static Game* getGame();

	~Game() = default;

	void Initialize();
	void Run();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

private:
	Game() = default;

	Character mainCharacter;
	std::unique_ptr<Character[]> enemies;

	static constexpr int enemiesCount = 15;
	static Game* game;
};