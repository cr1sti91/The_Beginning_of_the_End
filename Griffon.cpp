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
	this->BattleSprite->setScale(0.7f, 0.7f);
}

Griffon::Griffon(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed)
	: Enemy(categorie, hp, attack, speed)
{
	this->initIntroTexAndSpr();
	this->initBattleTexAndSpr();
}

void Griffon::closeAttack(const sf::Vector2f& playerPos, const sf::Vector2f& enemyPos)
{
}

void Griffon::projectileAttack(std::vector<std::unique_ptr<Item>>& projectiles, const float& angle, const sf::Vector2f& pos,
							   const float& distanceFromPlayer)
{
	//La moment griffon-ul nu ataca utilizand item-uri
}

void Griffon::getAttacked(const bool& isAttacked, const short& attackPower, const TypeItem& tipAtac)
{
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
