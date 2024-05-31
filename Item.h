#pragma once
#include "AllAdditionalAndLibraries.h"



class Item
{
	TypeItem tipItem; 
	
	std::optional<short> countDown; 

public: 
	Item(const TypeItem& tip);
	virtual ~Item() = default; 

	virtual void move() = 0; 

	//Setters
	void setCountDown(const short& value); 
	void decrCountDown(); 

	//Getters
	const TypeItem& getTipItem() const; 
	const std::optional<short>& getCountDown() const; 

	virtual const std::unique_ptr<sf::Sprite>& getSprite() const = 0;
};

