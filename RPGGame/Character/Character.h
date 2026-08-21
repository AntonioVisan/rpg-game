#pragma once

#include <iosfwd>
#include <string>

class Character
{
public:
	Character();
	Character(const std::string& name, int attackDamage, int healthPoints, int defence);

	void setName(const std::string& name);
	void setAttackDamage(int value);
	void setDefence(int value);
	void setHealthPoints(int value);
	void setRemainingHealthPoints(int value);

	const std::string& getName() const;
	int getAttackDamage() const;
	int getDefence() const;
	int getHealthPoints() const;
	int getRemainingHealthPoints() const;
	int getLvl() const;
	int getHealthPotionsCount() const;

	void Heal();
	void Attack(Character& enemy);

	bool isAlive() const;
	bool isDead() const;

	void LvlUp();

	bool operator<(const Character& other) const;
	bool operator>(const Character& other) const;
	bool operator==(const Character& other) const;
	bool operator!=(const Character& other) const;

	Character& operator++();
	Character operator++(int);

private:
	std::string name;
	int lvl;
	int attackDamage;
	int defence;
	int healthPoints;
	int remainingHealthPoints;
	int healthPotionsCount;

	static constexpr int baseAttackDamage = 2;
	static constexpr int baseDefence = 40;
	static constexpr int baseHealthPoints = 35;

	static constexpr int maxAttackDamage = 44;
	static constexpr int maxDefence = 450;
	static constexpr int maxHealthPoints = 300;

	static constexpr int startLvl = 1;
	static constexpr int startHealthPotionsCount = 4;
	static constexpr int healPotionRestorationEffect = 30;
};

std::istream& operator>>(std::istream& input, Character& character);
std::ostream& operator<<(std::ostream& output, const Character& character);