#include "Ghoul.h"


void Ghoul::initIntroTexAndSpr()
{
	initTexAndSpr(this->introTexture, this->introSprite, path_Ghoul_IntroTexture, "ERROR::GHOUL::IntroTexture inaccesibil!"); 
}

void Ghoul::initBattleTexAndSpr()
{
	initTexAndSpr(this->MovingTexture, this->BattleSprite, path_Ghoul_MovingTexture, "ERROR::GHOUL::MovingTexture inaccesibil!");
	initTex(this->AttackingTexture, path_Ghoul_AttackingTexture, "ERROR::GHOUL::AttackingTexture inaccesibil!");
	initTex(this->AttackedTexture, path_Ghoul_BeingAttacked, "ERROR::GHOUL::AttackedTexture inaccesibil!");
	initTex(this->AttackingAttackedTexture, path_Ghoul_AttakingAttacked, "ERROR::GHOUL::AttackingAttackedTexture inaccesibil!");

	this->BattleSprite->setOrigin(273.f, 320.f); 
	this->BattleSprite->setScale(0.3f, 0.3f);
	this->BattleSprite->setPosition(900.f, 228.f);
}

Ghoul::Ghoul(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed)
	: Enemy(categorie, hp, attack, speed)
{
	this->initIntroTexAndSpr(); 
	this->initBattleTexAndSpr(); 

	this->attackBeginning = sf::Time::Zero; 
	this->attackDuration = sf::seconds(1.f); 
	this->lastAttack = sf::Time::Zero;
	this->woundedTime = sf::seconds(0.4f);

	this->isAttacked = false;
	this->setIsAttack(false);
}

void Ghoul::attack(const bool& isAttacking)
{
	if (this->getEnemyClock().getElapsedTime() - this->attackBeginning > this->attackDuration)
	{
		if (isAttacking)
		{
			this->BattleSprite->setTexture(*this->AttackingTexture);
			this->attackBeginning = this->getEnemyClock().getElapsedTime();

			this->set_speedMovement(6); //de trei ori mai mare
		}
		else
		{
			if (this->isAttacked)
				this->BattleSprite->setTexture(*this->AttackedTexture);
			else
				this->BattleSprite->setTexture(*this->MovingTexture);

			this->set_speedMovement(2);
		}

		this->setIsAttack(isAttacking);
	}
}

void Ghoul::getAttacked(const bool& isAttacked, const short& attackPower)
{
	if (isAttacked)
	{	
		if (this->getIsAttack())
		{
			this->BattleSprite->setTexture(*this->AttackingAttackedTexture);
		}
		else
		{
			this->BattleSprite->setTexture(*this->AttackedTexture);
		}

		this->healthDecreases(attackPower); //enemy este ranit
		this->lastAttack = this->getEnemyClock().getElapsedTime(); 
		this->isAttacked = true; 
	}
	else if (this->getEnemyClock().getElapsedTime() - this->lastAttack > this->woundedTime)
	{
		if (this->getIsAttack())
		{
			this->BattleSprite->setTexture(*this->AttackingTexture);
		}
		else
		{
			this->BattleSprite->setTexture(*this->MovingTexture);
		}
		this->isAttacked = false; 
	}
}

void Ghoul::move(const float& angle, const sf::Sprite& stopTexture)
{
	//Limita de coliziunea este pe baza dreptunghiurilor floatRect 
	//scade sansa ca enemy-ul sa blocheze complet sprite-ul player-ului
	/*sf::FloatRect futureBouds = this->BattleSprite->getGlobalBounds(); 
	futureBouds.left += - this->get_speedMovement() * std::cos((angle - 90) * M_PI / 180);
	futureBouds.top += -this->get_speedMovement() * std::sin((angle - 90) * M_PI / 180); 

	if (!(futureBouds.intersects(stopTexture.getGlobalBounds())))
		this->BattleSprite->move(-this->get_speedMovement() * std::cos((angle - 90) * M_PI / 180), 
								 -this->get_speedMovement() * std::sin((angle - 90) * M_PI / 180));*/

	this->BattleSprite->move(-this->get_speedMovement() * std::cos((angle - 90) * M_PI / 180),
							 -this->get_speedMovement() * std::sin((angle - 90) * M_PI / 180));

	if (pixelPerfectCollision(*this->BattleSprite, stopTexture))
		this->BattleSprite->move(this->get_speedMovement() * std::cos((angle - 90) * M_PI / 180),
								 this->get_speedMovement() * std::sin((angle - 90) * M_PI / 180));
}

const sf::Sprite& Ghoul::getIntroSprite() //Nu trebuie sa fie const, fiindca in dependenta de BattleLocation, poate necesita 
{										  //modificarea pozitiei
	return *this->introSprite; 
}

const sf::Sprite& Ghoul::getBattleSprite()
{
	return *this->BattleSprite; 
}

void Ghoul::setScaleIntroSpr(const float& x_scale, const float& y_scale)
{
	this->introSprite->setScale(x_scale, y_scale); 
}

void Ghoul::setPosIntroSpr(const float& pos_x, const float& pos_y)
{
	this->introSprite->setPosition(pos_x, pos_y); 
}

void Ghoul::setRotation(const float& angle)
{
	this->BattleSprite->setRotation(angle); 
}


