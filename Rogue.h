#pragma once
#include "Player.h"



class Rogue : public Player
{
private:
	//Private methods
	void initTexture() override;
	void initPlayerSpr() override;

public:
	// Constructor / Destructor
	Rogue(const std::string& name);
	~Rogue() = default;


	void attack(std::vector<std::unique_ptr<Item>>& attacks, const TypeItem& tipAttack, const float& angle,
				const sf::Vector2f& pos) override;
	void getAttacked(const bool& isAttacked, const short& attackPower);


	std::unique_ptr<Item> generateItem() const;
};

