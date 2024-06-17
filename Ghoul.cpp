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
	initTex(this->AttackingAttackedTexture, path_Ghoul_AttackingAttacked, "ERROR::GHOUL::AttackingAttackedTexture inaccesibil!");

	initTex(this->ColdAttackedTexture, path_Ghoul_BeingColdAttacked, "ERROR::GHOUL::ColdAttackedTexture inaccesibil!");
	initTex(this->AttackingColdAttackedTexture, path_Ghoul_AttackingColdAttacked, "ERROR::GHOUL::AttackingColdAttackedTexture inaccesibil!");

	this->BattleSprite->setOrigin(273.f, 320.f); 
	this->BattleSprite->setScale(0.3f, 0.3f);
	this->BattleSprite->setPosition(900.f, 228.f);
}

void Ghoul::initVariables()
{
	this->attackBeginning = sf::Time::Zero;
	this->attackDuration = sf::seconds(1.f);
	this->lastAttack = sf::Time::Zero;
	this->woundedTime = sf::seconds(0.4f);

	this->isAttacked = false;
	this->isAttacking = false;
	this->ThermalAttack = std::nullopt;
}



Ghoul::Ghoul(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed)
	: Enemy(categorie, hp, attack, speed)
{
	this->initIntroTexAndSpr(); 
	this->initBattleTexAndSpr(); 
	this->initVariables(); 
}

void Ghoul::closeAttack(const sf::Vector2f& playerPos, const sf::Vector2f& enemyPos)
{
	static std::random_device rd; 
	std::uniform_int_distribution<int> attackChance(1, 150); //atacurile sa fie random


	if (this->getEnemyClock().getElapsedTime() - this->attackBeginning > this->attackDuration)
	{
		const float distance = distanceBetweenPoints(playerPos, enemyPos);
		if (distance > 200 && distance < 400 && attackChance(rd) == 1)
		{
			this->isAttacking = true;
		}
		else
		{
			this->isAttacking = false;
		}


		if (isAttacking)
		{
			if (this->isAttacked)
			{
				if (this->ThermalAttack.has_value())
				{
					if (this->ThermalAttack.value())
					{
						this->BattleSprite->setTexture(*this->AttackingAttackedTexture);
						this->set_speedMovement(8);
					}
					else 
					{
						this->BattleSprite->setTexture(*this->AttackingColdAttackedTexture);
						this->set_speedMovement(4);
					}
				}
				else
				{
					this->BattleSprite->setTexture(*this->AttackingAttackedTexture);
					this->set_speedMovement(5);
				}
			}
			else
			{
				this->BattleSprite->setTexture(*this->AttackingTexture); 
				this->set_speedMovement(6);
			}
			

			this->attackBeginning = this->getEnemyClock().getElapsedTime();
		}
		else
		{
			if (this->isAttacked)
			{
				if (this->ThermalAttack.has_value())
				{
					if (this->ThermalAttack.value())
					{
						this->BattleSprite->setTexture(*this->AttackedTexture);
						this->set_speedMovement(4);
					}
					else
					{
						this->BattleSprite->setTexture(*this->ColdAttackedTexture);
						this->set_speedMovement(1);
					}
				}
				else
				{
					this->BattleSprite->setTexture(*this->AttackedTexture);
					this->set_speedMovement(2);
				}
			}
			else
			{
				this->BattleSprite->setTexture(*this->MovingTexture);
				this->set_speedMovement(2);
			}
		}
		this->isAttacking = isAttacking; 
	}
}

void Ghoul::projectileAttack(std::vector<std::unique_ptr<Item>>& projectiles, const float& angle, const sf::Vector2f& pos,
							 const float& distanceFromPlayer)
{
	//La moment ghoul-ul nu ataca utilizand item-uri
}

void Ghoul::getAttacked(const bool& isAttacked, const short& attackPower, const TypeItem& tipAtac)
{
	if (isAttacked)
	{	
		if (tipAtac == TypeItem::IceBall) //Atacurile cu apa sau gheata sunt considerate cold attacks
		{
			this->ThermalAttack = false;

			if (this->isAttacking)
			{
				this->BattleSprite->setTexture(*this->AttackingColdAttackedTexture);
			}
			else
			{
				this->BattleSprite->setTexture(*this->ColdAttackedTexture);
			}
		}
		else if (tipAtac == TypeItem::FireBall)
		{
			this->ThermalAttack = true; 

			if (this->isAttacking)
			{
				this->BattleSprite->setTexture(*this->AttackingAttackedTexture);
			}
			else
			{
				this->BattleSprite->setTexture(*this->AttackedTexture);
			}
		}
		else
		{
			this->ThermalAttack = std::nullopt; 

			if (this->isAttacking)
			{
				this->BattleSprite->setTexture(*this->AttackingAttackedTexture);
			}
			else
			{
				this->BattleSprite->setTexture(*this->AttackedTexture);
			}
		}

		this->healthDecreases(attackPower); //enemy este ranit
		this->lastAttack = this->getEnemyClock().getElapsedTime(); 
		this->isAttacked = true; 
	}
	else if (this->getEnemyClock().getElapsedTime() - this->lastAttack > this->woundedTime)
	{
		if (this->isAttacking)
		{
			this->BattleSprite->setTexture(*this->AttackingTexture);
		}
		else
		{
			this->BattleSprite->setTexture(*this->MovingTexture);
		}
		this->isAttacked = false; 
		this->ThermalAttack = std::nullopt; 
	}
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


