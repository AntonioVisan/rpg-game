#include "Character.h"

#include <algorithm>
#include <iostream>

void Character::setName(const std::string& name)
{
	this->name = name;
}

void Character::setAttackDamage(int value)
{
	if (value < baseAttackDamage)
		attackDamage = baseAttackDamage;
	else if (value > maxAttackDamage)
		attackDamage = maxAttackDamage;
	else
		attackDamage = value;
}

void Character::setDefence(int value)
{
	if (value < baseDefence)
		defence = baseDefence;
	else if (value > maxDefence)
		defence = maxDefence;
	else
		defence = value;
}


void Character::setHealthPoints(int value)
{
	if (value < baseHealthPoints)
		healthPoints = baseHealthPoints;
	else if (value > maxHealthPoints)
		healthPoints = maxHealthPoints;
	else
		healthPoints = value;
}

void Character::setRemainingHealthPoints(int value)
{
	if (value < 0)
		remainingHealthPoints = 0;
	else if (value > healthPoints)
		remainingHealthPoints = healthPoints;
	else
		remainingHealthPoints = value;
}

const std::string& Character::getName() const
{
	return name;
}

int Character::getAttackDamage() const
{
	return attackDamage;
}

int Character::getDefence() const
{
	return defence;
}

int Character::getHealthPoints() const
{
	return healthPoints;
}

int Character::getRemainingHealthPoints() const
{
	return remainingHealthPoints;
}

int Character::getLvl() const
{
	return lvl;
}

int Character::getHealthPotionsCount() const
{
	return healthPotionsCount;
}

Character::Character()
	: name(),
	lvl(startLvl),
	attackDamage(baseAttackDamage),
	defence(baseDefence),
	healthPoints(baseHealthPoints),
	remainingHealthPoints(baseHealthPoints),
	healthPotionsCount(startHealthPotionsCount)
{}

Character::Character(
	const std::string& name,
	int attackDamage,
	int healthPoints,
	int defence)
	: name(),
	lvl(startLvl),
	attackDamage(baseAttackDamage),
	defence(baseDefence),
	healthPoints(baseHealthPoints),
	remainingHealthPoints(baseHealthPoints),
	healthPotionsCount(startHealthPotionsCount)
{
	setName(name);
	setAttackDamage(attackDamage);
	setHealthPoints(healthPoints);
	setDefence(defence);
}

void Character::Heal()
{
	if (healthPotionsCount > 0)
	{
		setRemainingHealthPoints(
			getRemainingHealthPoints() + healPotionRestorationEffect
		);
		healthPotionsCount--;
	}
	else
	{
		std::cout << "No health potions remaining." << std::endl;
	}
}

void Character::Attack(Character& enemy)
{
	int damageDealt =
		attackDamage * std::min(
			static_cast<double>(enemy.healthPoints) / enemy.defence,
			1.0
		);

	enemy.setRemainingHealthPoints(
		enemy.remainingHealthPoints - damageDealt
	);
}

bool Character::isAlive() const
{
	return remainingHealthPoints > 0;
}

bool Character::isDead() const
{
	return remainingHealthPoints <= 0;
}

void Character::LvlUp()
{
	lvl++;
	setAttackDamage(attackDamage + baseAttackDamage);
	setDefence(defence + baseDefence);
	setHealthPoints(healthPoints + baseHealthPoints);
	setRemainingHealthPoints(healthPoints);
}

bool Character::operator<(const Character& other) const
{
	return (healthPoints * attackDamage * defence)
		< (other.healthPoints * other.attackDamage * other.defence);
}

bool Character::operator>(const Character& other) const
{
	return (healthPoints * attackDamage * defence)
> (other.healthPoints * other.attackDamage * other.defence);
}

bool Character::operator==(const Character& other) const
{
	return (healthPoints * attackDamage * defence)
		== (other.healthPoints * other.attackDamage * other.defence);
}

bool Character::operator!=(const Character& other) const
{
	return (healthPoints * attackDamage * defence)
		!= (other.healthPoints * other.attackDamage * other.defence);
}

Character& Character::operator++()
{
	LvlUp();
	return *this;
}

Character Character::operator++(int)
{
	Character temp = *this;
	++(*this);
	return temp;
}

std::istream& operator>>(std::istream& input, Character& character)
{
	std::string name;
	int attackDamage;
	int healthPoints;
	int defence;

	input >> name >> attackDamage >> healthPoints >> defence;

	character.setName(name);
	character.setAttackDamage(attackDamage);
	character.setDefence(defence);
	character.setHealthPoints(healthPoints);
	character.setRemainingHealthPoints(healthPoints);

	return input;
}

std::ostream& operator<<(std::ostream& output, const Character& character)
{
	output << "Character " << character.getName()
		<< " has the following statistics:" << std::endl;
	output << "Level: " << character.getLvl() << std::endl;
	output << "Attack Damage: " << character.getAttackDamage() << std::endl;
	output << "Defence: " << character.getDefence() << std::endl;
	output << "Health Points: " << character.getHealthPoints() << std::endl;
	output << "Remaining Health Points: "
		<< character.getRemainingHealthPoints() << std::endl;
	output << "Health Potions: "
		<< character.getHealthPotionsCount() << std::endl;
	output << std::endl;

	return output;
}


