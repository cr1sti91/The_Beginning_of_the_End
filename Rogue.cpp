#include "Rogue.h"


void Rogue::initTexture()
{
	//For CrossRoads scene
	initTex(this->textureToCave, path_Rogue_toCave, "ERROR::Rogue::Rogue to cave inaccesibil!");
	initTex(this->textureToForest, path_Rogue_toForest, "ERROR::Rogue::Rogue to forest inaccesibil!");
	initTex(this->textureToVillage, path_Rogue_toVillage, "ERROR::Rogue::Rogue to village inaccesibil!");

	this->textureToCave->setSmooth(true);
	this->textureToForest->setSmooth(true);
	this->textureToVillage->setSmooth(true);

	//For BattleScene
	initTex(this->textureUp, path_Rogue_BattleUp, "ERROR::Rogue::Rogue Up inaccesibil!");
}

void Rogue::initPlayerSpr()
{
	this->playerSpr = std::make_unique<sf::Sprite>(*this->textureUp);
	this->playerSpr->setScale(0.5f, 0.5f);
	this->playerSpr->setOrigin(210.f, 115.f);
	this->playerSpr->setPosition(900.f, 800.f);

	this->setSpriteDirection(0, 1); //In mod implicit, player-ul o sa fie setat cu textura indreptata in sus
}

Rogue::Rogue(const std::string& name)
	: Player(name, CategoriePlayer::Rogue, 150, 8)
{
	this->initTexture(); 
	this->initPlayerSpr(); 

	//Init variables
	this->woundedTime = sf::seconds(0.4f);
	this->lastAttacked = sf::Time::Zero;

	//In mod implicit un rogue detine sageti in inventar
	this->inventar.push_back(std::make_shared<Projectile>(TypeItem::Arrow, this->getPosition().x,
													      this->getPosition().y, this->playerSpr->getRotation())); 
}



void Rogue::attack(std::vector<std::unique_ptr<Item>>& projectiles, const TypeItem& tipAttack, const float& angle,
				   const sf::Vector2f& pos)
{
	switch (tipAttack)
	{
	case TypeItem::Arrow:
	{
		projectiles.push_back(std::make_unique<Projectile>(TypeItem::Arrow, pos.x, pos.y, angle));
	}break;

	default:
		break;
	}
}


void Rogue::getAttacked(const bool& isAttacked, const short& attackPower)
{
	if (isAttacked)
	{
		this->lastAttacked = this->playerClock.getElapsedTime();
		this->playerSpr->setTexture(*this->textureUpAttacked);

		this->healthDecreases(attackPower);
	}
	else if (this->playerClock.getElapsedTime() - this->lastAttacked > this->woundedTime)
	{
		this->playerSpr->setTexture(*this->textureUp);
	}
}


std::unique_ptr<Item> Rogue::generateItem() const
{
	return nullptr;  //NECESITA DEZVOLTARE
}


