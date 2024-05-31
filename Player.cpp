#include "Player.h"

//Constructori
Player::Player(const std::string& name, const CategoriePlayer& categorie, const short& hp, const short& attack, const float& speed)
		       : playerName(name), categorie(categorie), health(hp), attackPower(attack), speedMovement(speed)
{
}

//Destructor
Player::~Player()
{
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

const short Player::get_attackPower() const
{
	return this->attackPower; 
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

const sf::Clock& Player::getPlayerClock() const
{
	return this->playerClock; 
}



const sf::Sprite& Player::getPlayerSpr() const
{
	return *this->playerSpr;
}



//Setters
bool Player::addItems(std::shared_ptr<Item> item)
{
	bool exist = false; 

	for (unsigned short i{}; i < this->inventar.size(); i++)
	{
		if (item->getTipItem() == this->inventar.at(i)->getTipItem())
		{
			exist = true; 
		}
	}
	if (!exist)
		this->inventar.push_back(item);

	return (!exist);
}

void Player::healthDecreases(const short& damage)
{
	this->health -= damage; 
}



