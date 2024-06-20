#include "Sword.h"

Sword::Sword(const CategoriePlayer& player) : Item(TypeItem::Sword)
{
	switch (player)
	{
	case CategoriePlayer::Warrior: 
	{
		this->itemLimits = sf::IntRect
		(
			225, 0, 70, 225
		);
	}break; 

	default:
		std::cerr << "ERROR::Sword::Sword::Categorie player incorecta!" << std::endl;
		break;
	}
}

const bool Sword::action()
{
	return false; 
}

void Sword::move()
{
}

const std::unique_ptr<sf::Sprite>& Sword::getSprite() const
{
	return nullptr;
}
