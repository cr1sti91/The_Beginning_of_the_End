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

	case TypeItem::Arrow:
	{
		initTexAndSpr(this->texture, this->sprite, path_Rogue_arrow, "ERROR::Projectile::initShape::Arrow inaccesibil!");
		this->sprite->setPosition(pos_x, pos_y);
		this->sprite->scale(0.35f, 0.1f);
		this->sprite->setOrigin(78.f, 1140.f);  

	}break;

	case TypeItem::Spear:
	{
		initTexAndSpr(this->texture, this->sprite, path_Warrior_spear, "ERROR::Projectile::initShape::Spear inaccesibil!");
		this->sprite->setPosition(pos_x, pos_y);
		this->sprite->scale(0.5f, 0.3f);
		this->sprite->setOrigin(30.f, 870.f);  

	}break;

	default:
		std::cout << "ERROR::Projectile::initShape::TypeItem incorect!" << std::endl;
		break;
	}
}



Projectile::Projectile(const TypeItem& tip, float pos_x, float pos_y, const float& angle, float movement_speed)
	: Item(tip), unghi(angle), movementSpeed(movement_speed)
{
	this->initShape(pos_x, pos_y); 
	this->sprite->setRotation(angle);
}


void Projectile::move()
{
	this->sprite->move(this->movementSpeed * std::cos((unghi - 90) * M_PI / 180), this->movementSpeed * std::sin((unghi - 90) * M_PI / 180));
	std::cout << "unghiul este : " << unghi << std::endl;
}

const std::unique_ptr<sf::Sprite>& Projectile::getSprite() const
{
	return this->sprite;
}


