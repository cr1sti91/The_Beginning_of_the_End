#pragma once
#include "Player.h"
#include "Sword.h"


class Warrior : public Player
{
private: 
	std::unique_ptr<sf::Texture> textureAttacking; //Textura pentru atack


	//Private methods
	void initTexture() override;
	void initPlayerSpr() override;

public: 
	// Constructor / Destructor
	Warrior(const std::string& name);
	~Warrior() = default;


	void attack(std::vector<std::unique_ptr<Item>>& projectiles, const TypeItem& tipAttack, const float& angle,
			    const sf::Vector2f& pos) override;
	void getAttacked(const bool& isAttacked, const short& attackPower) override;


	std::unique_ptr<Item> generateItem() const override;
};

