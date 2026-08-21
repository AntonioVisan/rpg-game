#pragma once
#include <iostream>
class Character
{
public:
	void setName(std::string name);
	void setAttackDamage(int value);
	void setDefence(int value);
	void setHealthPoints(int value);
	void setRemainingHealthPoints(int value);
	inline int getAttackDamage() const;
	inline int getDefence() const;
	inline int getHealthPoints() const;
	inline int getRemainingHealthPoints() const;
	inline std::string getName() const
	{
		return name;
	};
	Character();
	Character(std::string name, int attackDamage, int healthPoints, int defence);
	void Heal();
	void Attack(Character& enemy);
	bool isAlive() const;
	bool isDead() const;
	void LvlUp();
	friend std::istream& operator>>(std::istream& input, Character& caracter);
	friend std::ostream& operator<<(std::ostream& output, const Character& caracter);
	bool operator<(const Character& aux) const;
	bool operator>(const Character& aux) const;
	bool operator==(const Character& aux) const;
	bool operator!=(const Character& aux) const;
	Character operator++();
	Character operator++(int);
private:
	std::string name;
	int lvl;
	int attackDamage;
	int defence;
	int healthPoints;
	int remainingHealthPoints;
	int healthPotionsCount;

	static const int baseAttackDamage;
	static const int baseDefence;
	static const int baseHealthPoints;
	static const int maxAttackDamage;
	static const int maxDefence;
	static const int maxHealthPoints;
	static const int startLvl;
	static const int startHealthPotionsCount;
	static const int healPotionRestorationEffect;
};

