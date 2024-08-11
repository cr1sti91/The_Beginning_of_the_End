#include "Warrior.h"



void Warrior::initTexture()
{
	//For CrossRoads scene
	initTex(this->textureToCave, path_Warrior_toCave, "ERROR::Rogue::Rogue to cave inaccesibil!");
	initTex(this->textureToForest, path_Warrior_toForest, "ERROR::Rogue::Rogue to forest inaccesibil!");
	initTex(this->textureToVillage, path_Warrior_toVillage, "ERROR::Rogue::Rogue to village inaccesibil!");

	this->textureToCave->setSmooth(true);
	this->textureToForest->setSmooth(true);
	this->textureToVillage->setSmooth(true);

	//For BattleScene
	initTex(this->textureUp, path_Warrior_BattleUp, "ERROR::Warrior::Warrior Up inaccesibil!");
	initTex(this->textureAttacking, path_Warrior_BattleAttacking, "ERROR::Warrior::Warrior Up Attacking inaccesibil!");
	initTex(this->textureUpAttacked, path_Warrior_BattleUpAttacked, "ERROR::Warrior::Warrior Up Attacked inaccesibil!");
	initTex(this->textureAttackingAttacked, path_Warrior_BattleAttackingAttacked, "ERROR::Warrior::Warrior Up Attacking Attacked inaccesibil!");
}

void Warrior::initPlayerSpr()
{
	this->playerSpr = std::make_unique<sf::Sprite>(*this->textureUp);
	this->playerSpr->setScale(0.65f, 0.65f);
	this->playerSpr->setOrigin(117.f, 91.f);
	this->playerSpr->setPosition(900.f, 800.f);

	this->setSpriteDirection(0, 1); //In mod implicit, player-ul o sa fie setat cu textura indreptata in sus
}

Warrior::Warrior(const std::string& name)
				 : Player(name, CategoriePlayer::Warrior, 200, 5)
{
	this->initTexture(); 
	this->initPlayerSpr(); 

	//For attack
	this->attackDuration = sf::seconds(0.5); 
	this->lastAttack = sf::Time::Zero; 

	this->isAttacking = false; 

	//Init variables
	this->woundedTime = sf::seconds(0.8f);
	this->lastAttacked = sf::Time::Zero;

	//In mod implicit, warrior-ul va avea in inventar un sword
	this->inventar.push_back(std::move(std::make_unique<Sword>(CategoriePlayer::Warrior))); 
}



void Warrior::attack(std::vector<std::unique_ptr<Item>>& projectiles, const TypeItem& tipAttack, const float& angle,
				     const sf::Vector2f& pos)
{
	switch (tipAttack)
	{
	case TypeItem::Sword: 
	{
		this->lastAttack = this->playerClock.getElapsedTime(); 

		sf::Vector2f pos = this->playerSpr->getPosition(); 
		float rot = this->playerSpr->getRotation(); 

		this->playerSpr = std::make_unique<sf::Sprite>();
		this->playerSpr->setTexture(*this->textureAttacking);
		this->playerSpr->setScale(0.5f, 0.5f);
		this->playerSpr->setOrigin(157.f, 387.f);
		this->playerSpr->setPosition(pos); 
		this->playerSpr->setRotation(rot); 

		this->isAttacking = true; 
	}break;

	case TypeItem::Spear:
	{
		projectiles.push_back(std::make_unique<Projectile>(TypeItem::Spear, pos.x, pos.y, angle));
	}break;

	default:
		std::cout << "ERROR::Warrior::attack::Tip atac incorect!" << std::endl;
	}
}


void Warrior::stopAttack()
{
	if (this->playerClock.getElapsedTime() - this->lastAttack > this->attackDuration && this->isAttacking)
	{
		sf::Vector2f pos = this->playerSpr->getPosition();
		float rot = this->playerSpr->getRotation(); 

		this->playerSpr = std::make_unique<sf::Sprite>();
		this->playerSpr->setTexture(*this->textureUp);
		this->playerSpr->setScale(0.65f, 0.65f);
		this->playerSpr->setOrigin(117.f, 91.f);
		this->playerSpr->setPosition(pos);
		this->playerSpr->setRotation(rot); 

		this->isAttacking = false; 
	}
}

void Warrior::getAttacked(const bool& isAttacked, const short& attackPower)
{
	if (isAttacked)
	{
		if (this->isAttacking)
		{
			this->lastAttacked = this->playerClock.getElapsedTime();
			this->playerSpr->setTexture(*this->textureAttackingAttacked);

			this->healthDecreases(attackPower);
		}
		else
		{
			this->lastAttacked = this->playerClock.getElapsedTime();
			this->playerSpr->setTexture(*this->textureUpAttacked);

			this->healthDecreases(attackPower);
		}
	}
	else if (this->playerClock.getElapsedTime() - this->lastAttacked > this->woundedTime)
	{
		if (this->isAttacking)
		{
			this->playerSpr->setTexture(*this->textureAttacking);
		}
		else
		{
			this->playerSpr->setTexture(*this->textureUp);
		}
	}
}

std::unique_ptr<Item> Warrior::generateItem() const
{
	static std::random_device rd; 
	std::vector<int> unownedItems; //Vector de itemi (pentru wizard) care nu sunt prezenti in inventar

	for (int i{}; i < possItemsWizard; i++)
	{
		bool exist = false;
		for (int j{}; j < this->inventar.size(); j++)
		{
			if (this->inventar.at(j)->getTipItem() == static_cast<TypeItem>(i + 2))
			{
				exist = true;
				break;
			}
		}

		if (!exist)
			unownedItems.push_back(i + 2);
	}

	if (unownedItems.size() == 0)
	{
		std::cerr << "ERROR::Warrior::generateItem::A avut loc incercarea de generare cand unownedItems.size = 0" << std::endl;
		return nullptr;
	}

	std::uniform_int_distribution<int> dist(0, unownedItems.size() - 1); 

	return std::make_unique<Projectile>(static_cast<TypeItem>(unownedItems.at(dist(rd))), this->getPosition().x, 
									    this->getPosition().y, this->playerSpr->getRotation());
}
