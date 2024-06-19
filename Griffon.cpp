#include "Griffon.h"

void Griffon::initIntroTexAndSpr()
{
	initTexAndSpr(this->introTexture, this->introSprite, path_Griffon_IntroTexture, "ERROR::GRIFFON::IntroTexture inaccesibil!");
}

void Griffon::initBattleTexAndSpr()
{
	initTexAndSpr(this->MovingTexture, this->BattleSprite, path_Griffon_MovingTexture, "ERROR::GRIFFON::MovingTexture inaccesibil!");
	initTex(this->AttackingTexture, path_Griffon_AttackingTexture, "ERROR::GRIFFON::AttackingTexture inaccesibil!");

	initTex(this->AttackedTexture, path_Griffon_BeingAttacked, "ERROR::GRIFFON::AttackedTexture inaccesibil!");
	initTex(this->ColdAttackedTexture, path_Griffon_BeingColdAttacked, "ERROR::GRIFFON::AttackingTexture inaccesibil!");

	initTex(this->AttackingAttackedTexture, path_Griffon_AttackingAttacked, "ERROR::GRIFFON::AttackingTexture inaccesibil!");
	initTex(this->AttackingColdAttackedTexture, path_Griffon_AttackingColdAttacked, "ERROR::GRIFFON::AttackingTexture inaccesibil!");

	this->BattleSprite->setOrigin(this->movingOrigin);
	this->BattleSprite->setPosition(900.f, 242.f);
	this->BattleSprite->setScale(0.7f, 0.7f);
}

void Griffon::initVariables()
{
	this->attackBeginning = sf::Time::Zero;
	this->attackDuration = sf::seconds(1.f);
	this->lastAttack = sf::Time::Zero;
	this->woundedTime = sf::seconds(0.4f);

	this->isAttacked = false;
	this->isAttacking = false;
	this->ThermalAttack = std::nullopt;

	this->movingOrigin = sf::Vector2f(199.f, 221.f);
	this->attackingOrigin = sf::Vector2f(304.f, 250.f);

	this->enemyIsWaiting = false;
	this->waitingBegin = sf::seconds(-3);  //cand incepe scena, enemy-ul nu va fi stopat
	this->waitingTime = sf::seconds(3.f);
}



Griffon::Griffon(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed)
	: Enemy(categorie, hp, attack, speed)
{
	this->initVariables();
	this->initIntroTexAndSpr();
	this->initBattleTexAndSpr();
}



void Griffon::move(const float& angle, const sf::Sprite& stopTexture)
{
	//The enemy is directed towards the player
	if (!this->isAttacking)
		this->BattleSprite->setRotation(calculateAngle(this->BattleSprite->getPosition(), stopTexture.getPosition())); 

	static std::random_device rd; 
	static std::uniform_int_distribution<int> waitingChance(1, 500);

	//The enemy moves towards the player or enemy is waiting
	if (!this->enemyIsWaiting && this->getEnemyClock().getElapsedTime() - this->waitingBegin > this->waitingTime)
	{
		this->enemyIsWaiting = (waitingChance(rd) == 1);
		if (this->enemyIsWaiting)
		{
			this->waitingBegin = this->getEnemyClock().getElapsedTime();
			this->enemyIsWaiting = false;
		}
	}

	if (this->getEnemyClock().getElapsedTime() - this->waitingBegin > this->waitingTime)
	{
		const float newAngle = (this->isAttacking) ? this->BattleSprite->getRotation() : angle; 

		this->BattleSprite->move(-this->get_speedMovement() * std::cos((newAngle - 90) * M_PI / 180),
			-this->get_speedMovement() * std::sin((newAngle - 90) * M_PI / 180));

		for (int i{}; i < 2; i++) //A doua iterare impune miscarea inapoi cand sprite-ul player-ului are coliziune cu enemy
		{
			if (pixelPerfectCollision(*this->BattleSprite, stopTexture))
				this->BattleSprite->move(this->get_speedMovement() * std::cos((newAngle - 90) * M_PI / 180),
					this->get_speedMovement() * std::sin((newAngle - 90) * M_PI / 180));
		}
	}
}


void Griffon::closeAttack(const sf::Vector2f& playerPos, const sf::Vector2f& enemyPos)
{
	static std::random_device rd;
	std::uniform_int_distribution<int> attackChance(1, 150); //atacurile sa fie random


	if (this->getEnemyClock().getElapsedTime() - this->attackBeginning > this->attackDuration)
	{
		const float distance = distanceBetweenPoints(playerPos, enemyPos);
		if (distance > 200 && attackChance(rd) == 1)
		{
			this->isAttacking = true;
		}
		else
		{
			this->isAttacking = false;
		}



		if (this->isAttacking && !this->enemyIsWaiting)
		{
			if (this->isAttacked)
			{
				if (this->ThermalAttack.has_value())
				{
					if (this->ThermalAttack.value())
					{
						resetBattleSprite(this->BattleSprite, this->AttackingAttackedTexture, this->attackingOrigin);
						this->BattleSprite->setScale(0.9f, 0.9f); 
						this->set_speedMovement(11.f);
					}
					else
					{
						resetBattleSprite(this->BattleSprite, this->AttackingColdAttackedTexture, this->attackingOrigin);
						this->BattleSprite->setScale(0.9f, 0.9f);
						this->set_speedMovement(7.f);
					}
				}
				else
				{
					resetBattleSprite(this->BattleSprite, this->AttackingAttackedTexture, this->attackingOrigin);
					this->BattleSprite->setScale(0.9f, 0.9f);
					this->set_speedMovement(11.f);
				}
			}
			else
			{
				resetBattleSprite(this->BattleSprite, this->AttackingTexture, this->attackingOrigin);
				this->BattleSprite->setScale(0.9f, 0.9f);
				this->set_speedMovement(11.f);
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
						this->BattleSprite->setScale(0.7f, 0.7f);
						this->set_speedMovement(1.f);
					}
					else
					{
						resetBattleSprite(this->BattleSprite, this->ColdAttackedTexture, this->movingOrigin);
						this->BattleSprite->setScale(0.7f, 0.7f);
						this->set_speedMovement(0.25f);
					}
				}
				else
				{
					resetBattleSprite(this->BattleSprite, this->AttackedTexture, this->movingOrigin);
					this->BattleSprite->setScale(0.7f, 0.7f);
					this->set_speedMovement(1.f);
				}
			}
			else
			{
				resetBattleSprite(this->BattleSprite, this->MovingTexture, this->movingOrigin);
				this->BattleSprite->setScale(0.7f, 0.7f);
				this->set_speedMovement(0.5f);
			}
		}
	}
}


void Griffon::projectileAttack(std::vector<std::unique_ptr<Item>>& projectiles, const float& angle, const sf::Vector2f& pos,
							   const float& distanceFromPlayer)
{
	//La moment griffon-ul nu ataca utilizand item-uri
}

void Griffon::getAttacked(const bool& isAttacked, const short& attackPower, const TypeItem& tipAtac)
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
