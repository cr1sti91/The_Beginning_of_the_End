#pragma once
#include "Player.h"
#include "Projectile.h"


class Wizard : public Player
{
private:
	//Private methods
	void initTexture() override;	
	void initPlayerSpr() override;

public:
	// Constructor / Destructor
	Wizard(const std::string& name);
	~Wizard() = default;

	void attack(std::vector<std::unique_ptr<Item>>& projectiles, const TypeItem& tipAttack,
						  const float& angle, const sf::Vector2f&) override;

	void stopAttack() override;

	void getAttacked(const bool& isAttacked, const short& attackPower) override;

	std::unique_ptr<Item> generateItem() const override;
};

