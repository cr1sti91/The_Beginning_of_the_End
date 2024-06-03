#include "Projectile.h"


void Projectile::initShape(float pos_x, float pos_y)
{
	switch (this->getTipItem())
	{
	case TypeItem::FireBall:
	{
		initTexAndSpr(this->texture, this->shape, path_Wizard_fireBall, "ERROR::Projectile::initShape::Fireball inaccesibil!");
		this->shape->setPosition(pos_x, pos_y);
		this->shape->scale(0.25f, 0.25f);
		this->shape->setOrigin(87.f, 380.f);  //Cand vor fi create fireball-uri in scena de lupta, punctul de spawn va fi acesta

	}break;

	case TypeItem::IceBall:
	{
		initTexAndSpr(this->texture, this->shape, path_Wizard_iceBall, "ERROR::Projectile::initShape::Iceball inaccesibil!");
		this->shape->setPosition(pos_x, pos_y);
		this->shape->scale(0.35f, 0.2f);
		this->shape->setOrigin(92.f, 674);  //Cand vor fi create fireball-uri in scena de lupta, punctul de spawn va fi acesta

	}break;

	case TypeItem::Arrow:
	{
		initTexAndSpr(this->texture, this->shape, path_Rogue_arrow, "ERROR::Projectile::initShape::Arrow inaccesibil!");
		this->shape->setPosition(pos_x, pos_y);
		this->shape->scale(0.35f, 0.1f);
		this->shape->setOrigin(78.f, 1140);  //Cand vor fi create fireball-uri in scena de lupta, punctul de spawn va fi acesta

	}break;

	default:
		std::cout << "TypeItem incorect!" << std::endl;
		break;
	}
	
}



Projectile::Projectile(const TypeItem& tip, float pos_x, float pos_y, const float& angle, float movement_speed)
	: Item(tip), unghi(angle), movementSpeed(movement_speed)
{
	this->initShape(pos_x, pos_y); 
	this->shape->setRotation(angle); 
}


void Projectile::move()
{
	this->shape->move(this->movementSpeed * std::cos((unghi - 90) * M_PI / 180), this->movementSpeed * std::sin((unghi - 90) * M_PI / 180));
	std::cout << "unghiul este : " << unghi << std::endl;
}

const std::unique_ptr<sf::Sprite>& Projectile::getSprite() const
{
	return this->shape; 
}


