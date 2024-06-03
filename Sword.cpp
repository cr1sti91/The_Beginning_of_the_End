#include "Sword.h"

Sword::Sword() : Item(TypeItem::Sword)
{
}

void Sword::move()
{
}

const std::unique_ptr<sf::Sprite>& Sword::getSprite() const
{
	return nullptr;
}
