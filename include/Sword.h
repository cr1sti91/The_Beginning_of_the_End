#ifndef SWORD_H
#define SWORD_H

#include "Item.h"

class Sword : public Item
{
public: 
	Sword(const CategoriePlayer& player);

	const bool action() override;
	void move() override; 
	const std::unique_ptr<sf::Sprite>& getSprite() const override;
};

#endif //SWORD_H