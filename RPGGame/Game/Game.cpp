#include "Game.h"
#include <fstream>
#include <algorithm>
const int Game::enemiesCount = 15;
Game* Game::game = nullptr;

Game* Game::getGame()
{
    if (game == nullptr)
        game = new Game();
    return game;
}

void Game::Initialize()
{
    std::ifstream file("Data/input.txt");
    if (!file)
    {
        throw "Eroare citire fisier";
    }
    file >> mainCharacter;
    enemies = new Character[enemiesCount];
    if (!enemies)
    {
        file.close();
        throw "Eroare alocare vectori de inamici";
    }
    for (int i = 0; i < enemiesCount; i++)
        file >> enemies[i];
    file.close();
}

void Game::CheckIfEnemyDead(int &i, int &defeatedEnemies)
{
    if (enemies[i].isDead())
    {
        std::cout <<"Inamicul "<<enemies[i].getName() << " a murit." << std::endl;
        i++;
        std::cout << "Ai batut " << i << " din " << enemiesCount << " inamici." << std::endl;
        defeatedEnemies++;
    }
}

void Game::Run()
{
    int i = 0,defeatedEnemies=0;
    std::string option;
    std::sort(enemies, enemies + enemiesCount);
    std::cout << mainCharacter;
    while (mainCharacter.isAlive() && i < enemiesCount)
    {
        //std::cout << enemies[i];
        std::cout << "Alege o optiune: " << std::endl;
        std::cout << "Optiunea 1 - Ataca inamicul curent."<<std::endl;
        std::cout << "Optiunea 2 - Consuma o potiune pentru a te vindeca." << std::endl;
        std::cin >> option;
        if (option == "1")
        {
            mainCharacter.Attack(enemies[i]);
            std::cout << "Dupa atac viata inamicului " << enemies[i].getName() << " este de : " << enemies[i].getRemainingHealthPoints() << std::endl;
            CheckIfEnemyDead(i, defeatedEnemies);
            if (defeatedEnemies == 2)
            {
                defeatedEnemies = 0;
                std::cout << "Level up: " << std::endl;
                mainCharacter.LvlUp();
                std::cout << mainCharacter;
                if (i < enemiesCount)
                {
                    mainCharacter.Attack(enemies[i]);
                    std::cout << "Dupa atac viata ramasa inamicului " << enemies[i].getName() << " este  : " << enemies[i].getRemainingHealthPoints() << std::endl;
                    CheckIfEnemyDead(i, defeatedEnemies);
                }
            }
            if (i < enemiesCount)
            {
                enemies[i].Attack(mainCharacter);
                std::cout << "Dupa atacul inamicului " << enemies[i].getName() << ",viata ramasa caracterului principal este : " << mainCharacter.getRemainingHealthPoints() << std::endl;
            }
        }
        else if (option == "2")
        {
            mainCharacter.Heal();
            std::cout << "Dupa heal: " << std::endl;
            std::cout << mainCharacter;
            enemies[i].Attack(mainCharacter);
            std::cout << "Dupa atacul inamicului " << enemies[i].getName() << ",viata ramasa caracterului principal este : " << mainCharacter.getRemainingHealthPoints() << std::endl;
        }
        else std::cout << "Optiune gresita. Mai introdu o data." << std::endl;
        std::cout << std::endl;
    }
    if (mainCharacter.isDead())
        std::cout << "Ai pierdut. Jocul s-a terminat." << std::endl;
    else std::cout << "Ai castigat, ai batut toti inamicii. GG!" << std::endl;
}

Game::~Game()
{
    delete[] enemies;
    enemies = nullptr;
    game = nullptr;
}
