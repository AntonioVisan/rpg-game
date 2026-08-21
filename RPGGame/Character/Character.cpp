#include "Character.h"
const int Character::baseAttackDamage = 2;
const int Character::baseDefence = 40;
const int Character::baseHealthPoints = 35;
const int Character::maxAttackDamage = 44;
const int Character::maxDefence = 450;
const int Character::maxHealthPoints = 300;
const int Character::startLvl = 1;
const int Character::startHealthPotionsCount = 4;
const int Character::healPotionRestorationEffect = 30;

void Character::setName(std::string name)
{
	this->name = name;
}
void Character::setAttackDamage(int value)
{
	if (value < baseAttackDamage)
		attackDamage = baseAttackDamage;
	else if (value > maxAttackDamage)
		attackDamage = maxAttackDamage;
	else attackDamage = value;
}

void Character::setDefence(int value)
{
	if (value < baseDefence)
		defence = baseDefence;
	else if (value > maxDefence)
		defence = maxDefence;
	else defence = value;
}


void Character::setHealthPoints(int value)
{
	if (value < baseHealthPoints)
		healthPoints = baseHealthPoints;
	else if (value > maxHealthPoints)
		healthPoints = maxHealthPoints;
	else healthPoints = value;
}

void Character::setRemainingHealthPoints(int value)
{
	if (value > healthPoints)
		remainingHealthPoints = healthPoints;
	else remainingHealthPoints = value;
}

inline int Character::getAttackDamage() const
{
	return attackDamage;
}

inline int Character::getDefence() const
{
	return defence;
}

inline int Character::getHealthPoints() const
{
	return healthPoints;
}

inline int Character::getRemainingHealthPoints() const
{
	return remainingHealthPoints;
}


Character::Character()
{
	attackDamage = baseAttackDamage;
	defence = baseDefence;
	healthPoints = baseHealthPoints;
	lvl = startLvl;
	healthPotionsCount = startHealthPotionsCount;
	remainingHealthPoints = healthPoints;
}

Character::Character(std::string name, int attackDamage, int healthPoints, int defence)
{
	setName(name);
	setAttackDamage(attackDamage);
	setHealthPoints(healthPoints);
	setDefence(defence);
	lvl = startLvl;
	healthPotionsCount = startHealthPotionsCount;
	remainingHealthPoints = this->healthPoints;
}

void Character::Heal()
{
	if (healthPotionsCount > 0)
	{
		setRemainingHealthPoints(getRemainingHealthPoints() + healPotionRestorationEffect);
		healthPotionsCount--;
	}
	else std::cout << "Nu mai ai potiuni. " << std::endl;
}

void Character::Attack(Character& enemy)
{
	int damageDealt = attackDamage * std::min((double)enemy.healthPoints / enemy.defence, 1.0);
	enemy.setRemainingHealthPoints(enemy.remainingHealthPoints - damageDealt);
}

bool Character::isAlive() const
{
	return remainingHealthPoints > 0;
}

bool Character::isDead() const
{
	return remainingHealthPoints<=0;
}

void Character::LvlUp()
{
	lvl++;
	setAttackDamage(attackDamage + baseAttackDamage);
	setDefence(defence + baseDefence);
	setHealthPoints(healthPoints + baseHealthPoints);
	setRemainingHealthPoints(healthPoints);
}

bool Character::operator<(const Character& aux) const
{
	return (healthPoints * attackDamage * defence) < (aux.healthPoints * aux.attackDamage * aux.defence);
}

bool Character::operator>(const Character& aux) const
{
	return (healthPoints * attackDamage * defence) > (aux.healthPoints * aux.attackDamage * aux.defence);
}

bool Character::operator==(const Character& aux) const
{
	return (healthPoints * attackDamage * defence) == (aux.healthPoints * aux.attackDamage * aux.defence);
}

bool Character::operator!=(const Character& aux) const
{
	return (healthPoints * attackDamage * defence) != (aux.healthPoints * aux.attackDamage * aux.defence);
}

Character Character::operator++()
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

std::istream& operator>>(std::istream& input, Character& caracter)
{
	std::string name;
	int attackDamage, healthPoints, defence;
	input >> name >> attackDamage >> healthPoints >> defence;
	caracter.setName(name);
	caracter.setAttackDamage(attackDamage);
	caracter.setDefence(defence);
	caracter.setHealthPoints(healthPoints);
	caracter.setRemainingHealthPoints(healthPoints);
	return input;
}

std::ostream& operator<<(std::ostream& output, const Character& caracter)
{
	output << "Caracterul " << caracter.name << " are urmatoarele statistici: " << std::endl;
	output << "Level: " << caracter.lvl << std::endl;
	output << "Attack Damage: " << caracter.attackDamage << std::endl;
	output << "Defence: " << caracter.defence << std::endl;
	output << "Health Points: " << caracter.healthPoints << std::endl;
	output << "Remaining Health Points: " << caracter.remainingHealthPoints << std::endl;
	output << "Health Potions: " << caracter.healthPotionsCount << std::endl;
	output << std::endl;
	return output;
}


