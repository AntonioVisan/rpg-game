#include "Game.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

Game* Game::game = nullptr;

Game* Game::getGame()
{
	if (game == nullptr)
	{
		game = new Game();
	}

	return game;
}

void Game::Initialize()
{
	std::ifstream file("Data/input.txt");

	if (!file)
	{
		throw std::runtime_error("Failed to open input file.");
	}

	file >> mainCharacter;

	enemies = std::make_unique<Character[]>(enemiesCount);

	for (int i = 0; i < enemiesCount; ++i)
	{
		file >> enemies[i];
	}
}

void Game::Run()
{
	int currentEnemy = 0;
	int enemiesSinceLastLevelUp = 0;
	std::string option;

	std::sort(
		enemies.get(),
		enemies.get() + enemiesCount
	);

	std::cout << mainCharacter;

	while (mainCharacter.isAlive() && currentEnemy < enemiesCount)
	{
		std::cout << "Choose an option:" << std::endl;
		std::cout << "1 - Attack the current enemy." << std::endl;
		std::cout << "2 - Use a health potion." << std::endl;
		std::cout << "Option: ";

		std::cin >> option;

		if (option == "1")
		{
			mainCharacter.Attack(enemies[currentEnemy]);

			std::cout
				<< "After your attack, "
				<< enemies[currentEnemy].getName()
				<< " has "
				<< enemies[currentEnemy].getRemainingHealthPoints()
				<< " health points remaining."
				<< std::endl;

			if (enemies[currentEnemy].isDead())
			{
				std::cout
					<< "Enemy "
					<< enemies[currentEnemy].getName()
					<< " has been defeated."
					<< std::endl;

				++currentEnemy;
				++enemiesSinceLastLevelUp;

				std::cout
					<< "You have defeated "
					<< currentEnemy
					<< " out of "
					<< enemiesCount
					<< " enemies."
					<< std::endl;

				if (enemiesSinceLastLevelUp == 2)
				{
					enemiesSinceLastLevelUp = 0;

					std::cout << "Level up!" << std::endl;

					++mainCharacter;

					std::cout << mainCharacter;

					continue;
				}
			}

			if (currentEnemy < enemiesCount)
			{
				enemies[currentEnemy].Attack(mainCharacter);

				std::cout
					<< "After "
					<< enemies[currentEnemy].getName()
					<< "'s attack, you have "
					<< mainCharacter.getRemainingHealthPoints()
					<< " health points remaining."
					<< std::endl;
			}
		}
		else if (option == "2")
		{
			mainCharacter.Heal();

			std::cout << "After healing:" << std::endl;
			std::cout << mainCharacter;

			if (currentEnemy < enemiesCount)
			{
				enemies[currentEnemy].Attack(mainCharacter);

				std::cout
					<< "After "
					<< enemies[currentEnemy].getName()
					<< "'s attack, you have "
					<< mainCharacter.getRemainingHealthPoints()
					<< " health points remaining."
					<< std::endl;
			}
		}
		else
		{
			std::cout << "Invalid option. Please try again." << std::endl;
		}

		std::cout << std::endl;
	}

	if (mainCharacter.isDead())
	{
		std::cout << "You lost. Game over." << std::endl;
	}
	else
	{
		std::cout << "You won! You defeated all enemies. GG!" << std::endl;
	}
}
