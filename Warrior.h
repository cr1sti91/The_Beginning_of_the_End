#pragma once
#include "Player.h"


class Warrior : public Player
{
private: 
	//Private methods
	void initTexture() override;
	void initPlayerSpr() override;

public: 
	// Constructor / Destructor
	Warrior(const std::string& name);
	~Warrior() = default;


	void attack(std::vector<std::unique_ptr<Item>>& attacks, const TypeItem& tipAttack, const float& angle,
			    const sf::Vector2f& pos) override;
	void getAttacked(const bool& isAttacked, const short& attackPower) override;


	std::unique_ptr<Item> generateItem() const override;
};

