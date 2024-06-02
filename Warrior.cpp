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

	initTex(this->textureUp, path_Warrior_BattleUp, "ERROR::Warrior::Warrior Up inaccesibil!");
}

void Warrior::initPlayerSpr()
{
	this->playerSpr = std::make_unique<sf::Sprite>(*this->textureUp);
	this->playerSpr->setScale(0.3f, 0.3f);
	this->playerSpr->setOrigin(212.f, 315.f);
	this->playerSpr->setPosition(900.f, 800.f);

	this->setSpriteDirection(0, 1); //In mod implicit, player-ul o sa fie setat cu textura indreptata in sus
}

Warrior::Warrior(const std::string& name)
				 : Player(name, CategoriePlayer::Warrior, 200, 5)
{
	this->initTexture(); 
	this->initPlayerSpr(); 
}



void Warrior::attack(std::vector<std::unique_ptr<Item>>& attacks, const TypeItem& tipAttack, const float& angle,
				     const sf::Vector2f& pos)
{
	//NECESITA DEZVOLTARE
}

void Warrior::getAttacked(const bool& isAttacked, const short& attackPower)
{
}

std::unique_ptr<Item> Warrior::generateItem() const
{
	return nullptr;  //NECESITA DEZVOLTARE
}
