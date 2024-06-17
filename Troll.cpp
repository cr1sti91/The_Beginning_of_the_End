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

	this->projectileCooldown = false; 

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


void Troll::closeAttack(const sf::Vector2f& playerPos, const sf::Vector2f& enemyPos)
{
	static std::random_device rd; 
	std::uniform_int_distribution<int> attackChance(1, 150); //atacurile sa fie random


	if (this->getEnemyClock().getElapsedTime() - this->attackBeginning > this->attackDuration)
	{
		const float distance = distanceBetweenPoints(playerPos, enemyPos);
		if (distance > 200 && attackChance(rd) == 1)
		{
			this->isAttacking = true;
			this->projectileCooldown = false; 
		}
		else
		{
			this->isAttacking = false;
			this->projectileCooldown = true; 
		}



		if (this->isAttacking)
		{
			if (this->isAttacked)
			{
				if (this->ThermalAttack.has_value())
				{
					if (this->ThermalAttack.value())
					{
						resetBattleSprite(this->BattleSprite, this->AttackingAttackedTexture, this->attackingOrigin);
						this->set_speedMovement(4.f);
					}
					else
					{
						resetBattleSprite(this->BattleSprite, this->AttackingColdAttackedTexture, this->attackingOrigin);
						this->set_speedMovement(2.f);
					}
				}
				else
				{
					resetBattleSprite(this->BattleSprite, this->AttackingAttackedTexture, this->attackingOrigin);
					this->set_speedMovement(2.5f);
				}
			}
			else
			{
				resetBattleSprite(this->BattleSprite, this->AttackingTexture, this->attackingOrigin);
				this->set_speedMovement(3.f);
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
						this->set_speedMovement(2.f);
					}
					else
					{
						resetBattleSprite(this->BattleSprite, this->ColdAttackedTexture, this->movingOrigin);
						this->set_speedMovement(0.5f);
					}
				}
				else
				{
					resetBattleSprite(this->BattleSprite, this->AttackedTexture, this->movingOrigin);
					this->set_speedMovement(1.f);
				}
			}
			else
			{
				resetBattleSprite(this->BattleSprite, this->MovingTexture, this->movingOrigin);
				this->set_speedMovement(1.f);
			}
		}
	}
}



void Troll::projectileAttack(std::vector<std::unique_ptr<Item>>& projectiles, const float& angle, const sf::Vector2f& pos,
							 const float& distanceFromPlayer)
{
	if (!this->projectileCooldown)
	{
		if (this->isAttacking && distanceFromPlayer > 500)
		{
			//Avem 'angle + 180' pentru ca initial sprite-ul troll-ului este rotit cu 180 grade fata de sprite-ul player-ului
			projectiles.push_back(std::make_unique<Projectile>(TypeItem::Rock, pos.x, pos.y, angle + 180));
			this->projectileCooldown = true; 
		}
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
