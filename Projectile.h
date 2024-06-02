#pragma once
#include "Item.h"


class Projectile : public Item
{
private:
	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<sf::Sprite> shape;

	float unghi;
	float movementSpeed;
	

	//Private methods
	void initShape(float pos_x, float pos_y);


public:
	Projectile(const TypeItem& tip, float pos_x, float pos_y, const float& angle, float movement_speed = 12);
	~Projectile() = default;

	void move() override; 

	//Accessors 
	const std::unique_ptr<sf::Sprite>& getSprite() const override;
};
