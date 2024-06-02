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
}

void Rogue::initPlayerSpr()
{
}

Rogue::Rogue(const std::string& name)
	: Player(name, CategoriePlayer::Rogue, 100, 100)
{
	this->initTexture(); 
}



void Rogue::attack(std::vector<std::unique_ptr<Item>>& attacks, const TypeItem& tipAttack, const float& angle,
				   const sf::Vector2f& pos)
{
	//NECESITA DEZVOLTARE
}

void Rogue::getAttacked(const bool& isAttacked, const short& attackPower)
{
}


std::unique_ptr<Item> Rogue::generateItem() const
{
	return nullptr;  //NECESITA DEZVOLTARE
}


