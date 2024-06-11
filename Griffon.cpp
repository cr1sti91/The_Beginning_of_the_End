#include "Griffon.h"

void Griffon::initIntroTexAndSpr()
{
	initTexAndSpr(this->introTexture, this->introSprite, path_Griffon_IntroTexture, "ERROR::GRIFFON::IntroTexture inaccesibil!");
}

void Griffon::initBattleTexAndSpr()
{
	initTexAndSpr(this->MovingTexture, this->BattleSprite, path_Griffon_MovingTexture, "ERROR::GRIFFON::MovingTexture inaccesibil!");
	initTex(this->AttackedTexture, path_Griffon_AttackingTexture, "ERROR::GRIFFON::AttackingTexture inaccesibil!");

	this->BattleSprite->setOrigin(199.f, 221.f);
	this->BattleSprite->setPosition(900.f, 242.f);
}

Griffon::Griffon(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed)
	: Enemy(categorie, hp, attack, speed)
{
	this->initIntroTexAndSpr();
	this->initBattleTexAndSpr();
}

void Griffon::attack(const bool& isAttacking)
{
}

void Griffon::getAttacked(const bool& isAttacked, const short& attackPower, const TypeItem& tipAtac)
{
}

void Griffon::move(const float& angle, const sf::Sprite& stopTexture)
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

const sf::Sprite& Griffon::getIntroSprite()
{
	return *this->introSprite;
}

const sf::Sprite& Griffon::getBattleSprite()
{
	return *this->BattleSprite;
}

void Griffon::setScaleIntroSpr(const float& x_scale, const float& y_scale)
{
	this->introSprite->setScale(x_scale, y_scale);
}

void Griffon::setPosIntroSpr(const float& pos_x, const float& pos_y)
{
	this->introSprite->setPosition(pos_x, pos_y);
}

void Griffon::setRotation(const float& angle)
{
	this->BattleSprite->setRotation(angle);
}
