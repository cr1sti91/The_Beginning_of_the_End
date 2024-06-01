#include "Enemy.h"

Enemy::Enemy(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed)
	: categorie(categorie), health(hp), attackPower(attack), speedMovement(speed)
{
	this->isAttack = false; 
}

Enemy::~Enemy()
{
}


//Getters
const short& Enemy::get_health() const
{
	return this->health;
}

const short& Enemy::get_attackPower() const
{
	return this->attackPower;
}

const short& Enemy::get_speedMovement() const
{
	return this->speedMovement;
}

const CategorieEnemy& Enemy::getCategorie() const
{
	return this->categorie; 
}

const bool& Enemy::getIsAttack() const
{
	return this->isAttack; 
}

const sf::Clock& Enemy::getEnemyClock() const
{
	return this->enemyClock; 
}

void Enemy::setIsAttack(const bool& status)
{
	this->isAttack = status; 
}

void Enemy::set_speedMovement(const float& newValue)
{
	this->speedMovement = newValue; 
}

void Enemy::healthDecreases(const short& damage)
{
	this->health -= damage; 
}

