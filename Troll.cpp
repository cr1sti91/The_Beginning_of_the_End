#include "Troll.h"

void Troll::initIntroTexAndSpr()
{
	initTexAndSpr(this->introTexture, this->introSprite, path_Troll_IntroTexture, "ERROR::TROLL::IntroTexture inaccesibil!");
}

void Troll::initBattleTexAndSpr()
{
	initTexAndSpr(this->MovingTexture, this->BattleSprite, path_Troll_MovingTexture, "ERROR::TROLL::MovingTexture inaccesibil!");
	initTex(this->AttackedTexture, path_Troll_BeingAttacked, "ERROR::TROLL::AttackedTexture inaccesibil!");

	this->BattleSprite->setOrigin(125.f, 115.f);
	this->BattleSprite->setPosition(900.f, 242.f);
}

Troll::Troll(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed)
	: Enemy(categorie, hp, attack, speed)
{
	this->initIntroTexAndSpr();
	this->initBattleTexAndSpr();
}

void Troll::attack(const bool& isAttacking)
{
}

void Troll::getAttacked(const bool& isAttacked, const short& attackPower, const TypeItem& tipAtac)
{
}

void Troll::move(const float& angle, const sf::Sprite& stopTexture)
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

const sf::Sprite& Troll::getIntroSprite()
{
	return *this->introSprite; 
}

const sf::Sprite& Troll::getBattleSprite()
{
	return *this->BattleSprite; 
}

void Troll::setScaleIntroSpr(const float& x_scale, const float& y_scale)
{
	this->introSprite->setScale(x_scale, y_scale); 
}

void Troll::setPosIntroSpr(const float& pos_x, const float& pos_y)
{
	this->introSprite->setPosition(pos_x, pos_y); 
}

void Troll::setRotation(const float& angle)
{
	this->BattleSprite->setRotation(angle); 
}
