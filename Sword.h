#pragma once
#include "Item.h"



class Sword : public Item
{

public: 
	Sword(); 

	void move() override;
	const std::unique_ptr<sf::Sprite>& getSprite() const override;

};

