#include "Trap.h"

void Trap::initShape(const float pos_x, const float pos_y, const float angle)
{
	switch (this->getTipItem())
	{
	case TypeItem::SpikedTrap: 
	{
		initTexAndSpr(this->texture, this->sprite, path_Rogue_trap, "ERROR::ERROR::Trap::initShape::SpikedTrap inaccesibil!");
		this->sprite->setPosition(pos_x, pos_y);
		this->sprite->scale(0.2f, 0.2f);
		this->sprite->setOrigin(256.f, 237.f);
		this->sprite->setRotation(angle); 
	}
		break; 

	default: std::cerr << "ERROR::Trap::initShape::Tip item incorect!" << std::endl;
		break;
	}
}

void Trap::initVariables()
{
	this->actionCall = false; 
	this->lifeBegin = sf::Time::Zero; 
}

Trap::Trap(const TypeItem& tip, float pos_x, float pos_y, const float& angle)
	: Item(tip, sf::Time(sf::seconds(5.f)))
{
	this->initShape(pos_x, pos_y, angle);
	this->initVariables(); 
}



const bool Trap::action()  //Daca metoda data returneaza 'true', obiectul dat trebuie eliminat din scena de lupta
{
	if (this->actionCall)
	{
		if (this->lifeClock.getElapsedTime() - this->lifeBegin > this->lifeTime)
			return true;
	}
	else
	{
		this->actionCall = true;
		this->lifeBegin = this->lifeClock.getElapsedTime(); 
	}

	return false; 
}


void Trap::move()
{
}


const std::unique_ptr<sf::Sprite>& Trap::getSprite() const
{
	return this->sprite;
}
