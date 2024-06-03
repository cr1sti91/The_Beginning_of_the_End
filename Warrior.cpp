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
	initTex(this->textureAttacking, path_Warrior_BattleAttacking, "ERROR::Warrior::Warrior Up inaccesibil!");
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

	////////////test
	this->inventar.push_back(std::move(std::make_unique<Sword>())); 
}



void Warrior::attack(std::vector<std::unique_ptr<Item>>& projectiles, const TypeItem& tipAttack, const float& angle,
				     const sf::Vector2f& pos)
{
	switch (tipAttack)
	{
	case TypeItem::Sword: 
	{
		sf::Vector2f pos = this->playerSpr->getPosition(); 
		this->playerSpr = std::make_unique<sf::Sprite>();
		this->playerSpr->setTexture(*this->textureAttacking);
		this->playerSpr->setScale(0.5f, 0.5f);
		this->playerSpr->setOrigin(157.f, 387.f);
		this->playerSpr->setPosition(pos); 
	}break;

	case TypeItem::None:
	{
		sf::Vector2f pos = this->playerSpr->getPosition();
		this->playerSpr = std::make_unique<sf::Sprite>();
		this->playerSpr->setTexture(*this->textureUp);
		this->playerSpr->setScale(0.65f, 0.65f);
		this->playerSpr->setOrigin(117.f, 91.f);
		this->playerSpr->setPosition(pos);
	}

	default:
		break;
	}
}

void Warrior::getAttacked(const bool& isAttacked, const short& attackPower)
{
}

std::unique_ptr<Item> Warrior::generateItem() const
{
	return nullptr;  //NECESITA DEZVOLTARE
}
