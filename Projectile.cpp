#include "Projectile.h"


void Projectile::initShape(float pos_x, float pos_y)
{
	switch (this->getTipItem())
	{
	case TypeItem::FireBall:
	{
		initTexAndSpr(this->texture, this->sprite, path_Wizard_fireBall, "ERROR::Projectile::initShape::Fireball inaccesibil!");
		this->sprite->setPosition(pos_x, pos_y);
		this->sprite->scale(0.25f, 0.25f);
		this->sprite->setOrigin(87.f, 380.f);  

	}break;

	case TypeItem::IceBall:
	{
		initTexAndSpr(this->texture, this->sprite, path_Wizard_iceBall, "ERROR::Projectile::initShape::Iceball inaccesibil!");
		this->sprite->setPosition(pos_x, pos_y);
		this->sprite->scale(0.35f, 0.2f);
		this->sprite->setOrigin(92.f, 674.f); 

	}break;

	case TypeItem::Knive:
	{
		initTexAndSpr(this->texture, this->sprite, path_Rogue_knive, "ERROR::Projectile::initShape::Arrow inaccesibil!");
		this->sprite->setPosition(pos_x, pos_y);
		this->sprite->scale(0.25f, 0.25f);
		this->sprite->setOrigin(65.f, 485.f);  

	}break;

	case TypeItem::Spear:
	{
		initTexAndSpr(this->texture, this->sprite, path_Warrior_spear, "ERROR::Projectile::initShape::Spear inaccesibil!");
		this->sprite->setPosition(pos_x, pos_y);
		this->sprite->scale(0.5f, 0.3f);
		this->sprite->setOrigin(30.f, 870.f);  

	}break;

	case TypeItem::Rock:
	{
		initTexAndSpr(this->texture, this->sprite, path_Troll_Rock, "ERROR::Projectile::initShape::Rock inaccesibil!");
		this->sprite->setPosition(pos_x, pos_y);
		this->sprite->scale(0.5f, 0.3f);
		this->sprite->setOrigin(130.f, 232.f);

	}break;

	default:
		std::cout << "ERROR::Projectile::initShape::TypeItem incorect!" << std::endl;
		break;
	}
}



Projectile::Projectile(const TypeItem& tip, float pos_x, float pos_y, const float& angle)
	: Item(tip), unghi(angle), movementSpeed(projSpeed.at(tip))
{
	this->initShape(pos_x, pos_y); 
	this->sprite->setRotation(angle);
}


void Projectile::move()
{
	this->sprite->move(this->movementSpeed * std::cos((unghi - 90) * M_PI / 180), this->movementSpeed * std::sin((unghi - 90) * M_PI / 180));
}

const std::unique_ptr<sf::Sprite>& Projectile::getSprite() const
{
	return this->sprite;
}


