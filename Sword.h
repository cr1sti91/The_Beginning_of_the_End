#pragma once
#include "Item.h"


class Sword : public Item
{
public: 
	Sword(const CategoriePlayer& player);

	const bool action() override;
	void move() override; 
	const std::unique_ptr<sf::Sprite>& getSprite() const override;
};

