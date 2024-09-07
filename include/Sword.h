#ifndef SWORD_H
#define SWORD_H

#include "Item.h"

class Sword : public Item
{
private:
	std::unique_ptr<sf::Sprite> sword_spr; 
	
public: 
	Sword(const CategoriePlayer& player);

	const bool action() override;
	void move() override; 
	const std::unique_ptr<sf::Sprite>& getSprite() const override;
};

#endif //SWORD_H