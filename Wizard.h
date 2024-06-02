#pragma once
#include "Player.h"
#include "Projectile.h"


class Wizard : public Player
{
private:
	//Player is attacked
	sf::Time lastAttacked;
	sf::Time woundedTime;

	//Private methods
	void initTexture() override;	
	void initPlayerSpr() override;

public:
	// Constructor / Destructor
	Wizard(const std::string& name);
	~Wizard() = default;

	void attack(std::vector<std::unique_ptr<Item>>& attacks, const TypeItem& tipAttack, 
				const float& angle, const sf::Vector2f&) override;
	void getAttacked(const bool& isAttacked, const short& attackPower) override;

	std::unique_ptr<Item> generateItem() const override;
};

