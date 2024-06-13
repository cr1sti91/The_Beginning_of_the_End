#include "Troll.h"

void Troll::initIntroTexAndSpr()
{
	initTexAndSpr(this->introTexture, this->introSprite, path_Troll_IntroTexture, "ERROR::TROLL::IntroTexture inaccesibil!");
}

void Troll::initBattleTexAndSpr()
{
	initTexAndSpr(this->MovingTexture, this->BattleSprite, path_Troll_MovingTexture, "ERROR::TROLL::MovingTexture inaccesibil!");
	initTex(this->AttackingTexture, path_Troll_AttackingTexture, "ERROR::TROLL::AttackingTexture inaccesibil!");

	initTex(this->AttackedTexture, path_Troll_BeingAttacked, "ERROR::TROLL::AttackedTexture inaccesibil!");
	initTex(this->ColdAttackedTexture, path_Troll_BeingColdAttacked, "ERROR::TROLL::AttackingTexture inaccesibil!");

	initTex(this->AttackingAttackedTexture, path_Troll_AttackingAttacked, "ERROR::TROLL::AttackingTexture inaccesibil!");
	initTex(this->AttackingColdAttackedTexture, path_Troll_AttackingColdAttacked, "ERROR::TROLL::AttackingTexture inaccesibil!");


	this->BattleSprite->setOrigin(125.f, 115.f);
	this->BattleSprite->setPosition(900.f, 242.f);
}

void Troll::initVariables()
{
	this->isAttacked = false;
	this->isAttacking = false;
	this->ThermalAttack = std::nullopt;

	this->attackBeginning = sf::Time::Zero;
	this->attackDuration = sf::seconds(1.f);
	this->lastAttack = sf::Time::Zero;
	this->woundedTime = sf::seconds(0.4f);

	this->movingOrigin = sf::Vector2f(125.f, 115.f);
	this->attackingOrigin = sf::Vector2f(206.f, 133.f);
}

Troll::Troll(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed)
	: Enemy(categorie, hp, attack, speed)
{
	this->initIntroTexAndSpr();
	this->initBattleTexAndSpr();
	this->initVariables();
}

void Troll::attack(const bool& isAttacking)
{

	/*if (this->getEnemyClock().getElapsedTime() - this->attackBeginning > this->attackDuration)
	{
		if (isAttacking)
		{
			if (this->isAttacked)
			{
				if (this->ThermalAttack.has_value())
				{
					if (this->ThermalAttack.value())
					{
						resetBattleSprite(this->BattleSprite, this->AttackingAttackedTexture, this->attackingOrigin); 

						this->set_speedMovement(8);
					}
					else
					{
						resetBattleSprite(this->BattleSprite, this->AttackingColdAttackedTexture, this->attackingOrigin); 

						this->set_speedMovement(4);
					}
				}
				else
				{
					resetBattleSprite(this->BattleSprite, this->AttackingAttackedTexture, this->attackingOrigin); 

					this->set_speedMovement(5);
				}
			}
			else
			{
				resetBattleSprite(this->BattleSprite, this->AttackingTexture, this->attackingOrigin); 

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
						resetBattleSprite(this->BattleSprite, this->AttackedTexture, this->movingOrigin);

						this->set_speedMovement(4);
					}
					else
					{
						resetBattleSprite(this->BattleSprite, this->ColdAttackedTexture, this->movingOrigin); 

						this->set_speedMovement(1);
					}
				}
				else
				{
					resetBattleSprite(this->BattleSprite, this->AttackedTexture, this->movingOrigin); 

					this->set_speedMovement(2);
				}
			}
			else
			{
				resetBattleSprite(this->BattleSprite, this->MovingTexture, this->movingOrigin);

				this->set_speedMovement(2);
			}
		}
	}
	this->isAttacking = isAttacking;*/

	if (this->getEnemyClock().getElapsedTime() - this->attackBeginning > this->attackDuration)
	{
		if (isAttacking)
		{
			if (this->isAttacked)
			{
				if (this->ThermalAttack.has_value())
				{
					if (this->ThermalAttack.value())
					{
						resetBattleSprite(this->BattleSprite, this->AttackingAttackedTexture, this->attackingOrigin);
						this->set_speedMovement(8);
					}
					else
					{
						resetBattleSprite(this->BattleSprite, this->AttackingColdAttackedTexture, this->attackingOrigin);
						this->set_speedMovement(4);
					}
				}
				else
				{
					resetBattleSprite(this->BattleSprite, this->AttackingAttackedTexture, this->attackingOrigin);
					this->set_speedMovement(5);
				}
			}
			else
			{
				resetBattleSprite(this->BattleSprite, this->AttackingTexture, this->attackingOrigin);
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
						resetBattleSprite(this->BattleSprite, this->AttackedTexture, this->movingOrigin);
						this->set_speedMovement(4);
					}
					else
					{
						resetBattleSprite(this->BattleSprite, this->ColdAttackedTexture, this->movingOrigin);
						this->set_speedMovement(1);
					}
				}
				else
				{
					resetBattleSprite(this->BattleSprite, this->AttackedTexture, this->movingOrigin);
					this->set_speedMovement(2);
				}
			}
			else
			{
				resetBattleSprite(this->BattleSprite, this->MovingTexture, this->movingOrigin);
				this->set_speedMovement(2);
			}
		}
		this->isAttacking = isAttacking;
	}
}

void Troll::getAttacked(const bool& isAttacked, const short& attackPower, const TypeItem& tipAtac)
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
