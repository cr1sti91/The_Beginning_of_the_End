#ifndef ITEM_H
#define ITEM_H

#include "AllAdditionalAndLibraries.h"

class Item
{
private: 
	TypeItem tipItem; 
	short attackPower;

	std::optional<short> countDown; 

protected: 
	//Pentru item-uri de close attack - atunci cand item-ul este parte din textura player-ului
	sf::IntRect itemLimits;
	std::optional<sf::Time> lifeTime; 


public: 
	Item(const TypeItem& tip, const std::optional<sf::Time> time = std::nullopt);
	virtual ~Item() = default; 

	virtual void move() = 0; 
	virtual const bool action() = 0; 

	//Setters
	void setCountDown(const short& value); 
	void decrCountDown(); 

	//Getters
	const TypeItem& getTipItem() const; 
	const short& getAttackPower() const; 
	const std::optional<short>& getCountDown() const; 
	const sf::IntRect& getItemLimits() const; 
	const std::optional<sf::Time>& getLifeTime() const; 

	virtual const std::unique_ptr<sf::Sprite>& getSprite() const = 0;

	//Static methods
	static const std::string typeItemToStr(const TypeItem& typeItem);
};

#endif //ITEM_H