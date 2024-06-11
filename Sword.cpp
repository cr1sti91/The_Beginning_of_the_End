#include "Sword.h"

Sword::Sword(const CategoriePlayer& player) : Item(TypeItem::Sword)
{
	switch (player)
	{
	case CategoriePlayer::Warrior: 
	{
		this->itemLimits = sf::IntRect
		(
			225.f, 0.f, 70.f, 225.f
		);
	}break; 

	default:
		std::cerr << "ERROR::Sword::Sword::Categorie player incorecta!" << std::endl;
		break;
	}
}

void Sword::move()
{
}

const std::unique_ptr<sf::Sprite>& Sword::getSprite() const
{
	return nullptr;
}
