#pragma once
#include "Item.h"


class Trap : public Item
{
private:
	sf::Clock lifeClock; 
	sf::Time  lifeBegin; 
	bool actionCall; 

	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<sf::Sprite> sprite;

	//Private methods
	void initShape(const float pos_x, const float pos_y, const float angle);
	void initVariables(); 


public:
	Trap(const TypeItem& tip, float pos_x, float pos_y, const float& angle);
	~Trap() = default;

	const bool action() override;
	void move() override;

	//Accessors 
	const std::unique_ptr<sf::Sprite>& getSprite() const override;
};

