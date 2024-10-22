#include "Enemy.h"

Enemy::Enemy(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed)
	: categorie(categorie), health(hp), attackPower(attack), speedMovement(speed)
{
	this->isAttacking = false; 
	this->isAttacked = false; 
	this->enemyIsWaiting = false;

	this->fellTrap = false; 
	this->trapDuration = sf::seconds(3.f); 
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

const float& Enemy::get_speedMovement() const
{
	return this->speedMovement;
}

const CategorieEnemy& Enemy::getCategorie() const
{
	return this->categorie; 
}

const bool& Enemy::getIsAttacking() const
{
	return this->isAttacking; 
}

const sf::Clock& Enemy::getEnemyClock() const
{
	return this->enemyClock; 
}

void Enemy::set_speedMovement(const float& newValue)
{
	this->speedMovement = newValue; 
}

void Enemy::healthDecreases(const short& damage)
{
	if (damage < this->health)
		this->health -= damage;
	else
		this->health = 0; 
}


