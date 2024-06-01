#include "Warrior.h"



void Warrior::initTexture()
{
	//NECESITA DEZVOLTARE
}

Warrior::Warrior(const std::string& name, const CategoriePlayer& categorie)
				 : Player(name, categorie, 100, 100)
{
	this->initTexture(); 
}



void Warrior::attack(std::vector<std::unique_ptr<Item>>& attacks, const TypeItem& tipAttack, const float& angle,
				     const sf::Vector2f& pos)
{
	//NECESITA DEZVOLTARE
}

void Warrior::getAttacked(const bool& isAttacked, const short& attackPower)
{
}

void Warrior::move(const float& dir_x, const float& dir_y)
{
	//NECESITA DEZVOLTARE
}

void Warrior::setRotation(const float& angle)
{
	//NECESITA DEZVOLATER
}

std::unique_ptr<Item> Warrior::generateItem() const
{
	return nullptr;  //NECESITA DEZVOLTARE
}

const sf::Texture& Warrior::getToCaveTexture() const
{
	return *this->textureToCave;
}

const sf::Texture& Warrior::getToForestTexture() const
{
	return *this->textureToForest;
}

const sf::Texture& Warrior::getToVillageTexture() const
{
	return *this->textureToVillage;
}

void Warrior::setSpriteDirection(const short& dir_x, const short& dir_y)
{
	///////////////////////////////////////////////////////////////
}

