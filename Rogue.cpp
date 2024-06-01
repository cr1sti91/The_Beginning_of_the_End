#include "Rogue.h"




void Rogue::initTexture()
{
	//For CrossRoads scene
	initTex(this->textureToCave, path_Rogue_toCave, "ERROR::Rogue::Rogue to cave inaccesibil!");
	initTex(this->textureToForest, path_Rogue_toForest, "ERROR::Rogue::Rogue to forest inaccesibil!");
	initTex(this->textureToVillage, path_Rogue_toVillage, "ERROR::Rogue::Rogue to village inaccesibil!");
}

Rogue::Rogue(const std::string& name, const CategoriePlayer& categorie)
	: Player(name, categorie, 100, 100, 100)
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

void Rogue::move(const float& dir_x, const float& dir_y)
{
	//NECESITA DEZVOLTARE
}

void Rogue::setRotation(const float& angle)
{
	//NECESITA DEZVOLTARE
}

std::unique_ptr<Item> Rogue::generateItem() const
{
	return nullptr;  //NECESITA DEZVOLTARE
}

const sf::Texture& Rogue::getToCaveTexture() const
{
	return *this->textureToCave; 
}

const sf::Texture& Rogue::getToForestTexture() const
{
	return *this->textureToForest;
}

const sf::Texture& Rogue::getToVillageTexture() const
{
	return *this->textureToVillage;
}

void Rogue::setSpriteDirection(const short& dir_x, const short& dir_y)
{
	///////////////////////////////////////////////////////////
}

