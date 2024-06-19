#include "Enemy.h"

Enemy::Enemy(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed)
	: categorie(categorie), health(hp), attackPower(attack), speedMovement(speed)
{
	this->isAttacking = false; 
	this->isAttacked = false; 
}


void Enemy::move(const float& angle, const sf::Sprite& stopTexture)
{
	this->BattleSprite->move(-this->get_speedMovement() * std::cos((angle - 90) * M_PI / 180),
		-this->get_speedMovement() * std::sin((angle - 90) * M_PI / 180));

	for (int i{}; i < 2; i++) //A doua iterare impune miscarea inapoi cand sprite-ul player-ului are coliziune cu enemy
	{
		if (pixelPerfectCollision(*this->BattleSprite, stopTexture))
			this->BattleSprite->move(this->get_speedMovement() * std::cos((angle - 90) * M_PI / 180),
				this->get_speedMovement() * std::sin((angle - 90) * M_PI / 180));
	}
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
	this->health -= damage; 
}


