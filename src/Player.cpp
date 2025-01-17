#include "Player.h"

//Constructori
Player::Player(const std::string& name, const CategoriePlayer& categorie, const short& hp, const float& speed)
		       : playerName(name), categorie(categorie), health(hp), speedMovement(speed)
{
}


void Player::move(const float& dir_x, const float& dir_y)
{
	this->playerSpr->move(this->get_speedMovement() * dir_x, this->get_speedMovement() * dir_y);
}

void Player::setSpriteDirection(const short& dir_x, const short& dir_y)
{
	this->playerSpr->setRotation(dirToDegree(dir_x, dir_y));
}

void Player::setRotation(const float& angle)
{
	this->playerSpr->setRotation(angle);
}

//Getters
const std::string& Player::get_playerName() const
{
	return this->playerName; 
}

const short Player::get_health() const
{
	return this->health; 
}


const short Player::get_speedMovement() const
{
	return this->speedMovement; 
}



const CategoriePlayer& Player::getCategorie() const
{
	return this->categorie; 
}

const std::vector<std::shared_ptr<Item>>& Player::getInvetar() const
{
	return this->inventar; 
}

const sf::Vector2f& Player::getPosition() const
{
	return this->playerSpr->getPosition(); 
}

const sf::Sprite& Player::getPlayerSpr() const
{
	return *this->playerSpr;
}

const sf::Texture& Player::getToCaveTexture() const
{
	return *this->textureToCave;
}

const sf::Texture& Player::getToForestTexture() const
{
	return *this->textureToForest;
}

const sf::Texture& Player::getToVillageTexture() const
{
	return *this->textureToVillage;
}



//Setters
bool Player::addItems(std::unique_ptr<Item> item)
{
	bool exist = false; 

	for (unsigned short i{}; i < this->inventar.size(); i++)
	{
		if (item->getTipItem() == this->inventar.at(i)->getTipItem())
		{
			exist = true; 
		}
	}
	if (!exist && item) //Item trebuie sa fie diferit de 'nullptr'
		this->inventar.push_back(std::move(item));

	return (!exist);
}

void Player::healthDecreases(const short& damage)
{
	if (damage < this->health)
		this->health -= damage;
	else
		this->health = 0; 
}





