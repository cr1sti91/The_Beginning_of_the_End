#pragma once
#include "Player.h"
#include "Sword.h"


class Warrior : public Player
{
private: 
	sf::Time attackDuration; 
	sf::Time lastAttack; 

	std::unique_ptr<sf::Texture> textureAttacking; //Textura pentru atack
	std::unique_ptr<sf::Texture> textureAttackingAttacked; //Textura pentru atack

	bool isAttacking; 



	//Private methods
	void initTexture() override;
	void initPlayerSpr() override;

public: 
	// Constructor / Destructor
	Warrior(const std::string& name);
	~Warrior() = default;


	void attack(std::vector<std::unique_ptr<Item>>& projectiles, const TypeItem& tipAttack, const float& angle,
			    const sf::Vector2f& pos) override;
	void stopAttack() override;

	void getAttacked(const bool& isAttacked, const short& attackPower) override;


	std::unique_ptr<Item> generateItem() const override;
};

