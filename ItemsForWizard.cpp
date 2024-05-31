#include "ItemsForWizard.h"


void ThrownBall::initShape(float pos_x, float pos_y)
{
	switch (this->getTipItem())
	{
	case TypeItem::FireBall:
	{
		initTexAndSpr(this->texture, this->shape, path_Wizard_fireBall, "ERROR::initShape::Fireball inaccesibil!");
		this->shape->setPosition(pos_x, pos_y);
		this->shape->scale(0.25f, 0.25f);
		this->shape->setOrigin(87.f, 380.f);  //Cand vor fi create fireball-uri in scena de lupta, punctul de spawn va fi acesta

	}break;

	case TypeItem::IceBall:
	{
		initTexAndSpr(this->texture, this->shape, path_Wizard_iceBall, "ERROR::initShape::Iceball inaccesibil!");
		this->shape->setPosition(pos_x, pos_y);
		this->shape->scale(0.35f, 0.2f);
		this->shape->setOrigin(92.f, 674);  //Cand vor fi create fireball-uri in scena de lupta, punctul de spawn va fi acesta

	}break;

	default:
		std::cout << "TypeItem incorect!" << std::endl;
		break;
	}
	
}



ThrownBall::ThrownBall(const TypeItem& tip, float pos_x, float pos_y, const float& angle, float movement_speed)
	: Item(tip), unghi(angle), movementSpeed(movement_speed)
{
	this->initShape(pos_x, pos_y); 
	this->shape->setRotation(angle); 
}


void ThrownBall::move()
{
	this->shape->move(this->movementSpeed * std::cos((unghi - 90) * M_PI / 180), this->movementSpeed * std::sin((unghi - 90) * M_PI / 180));
	std::cout << "unghiul este : " << unghi << std::endl;
}

const std::unique_ptr<sf::Sprite>& ThrownBall::getSprite() const
{
	return this->shape; 
}


