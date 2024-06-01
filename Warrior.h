#pragma once
#include "Player.h"


class Warrior : public Player
{
private: 
	//Private methods
	void initTexture();

public: 
	// Constructor / Destructor
	Warrior(const std::string& name, const CategoriePlayer& categorie);
	~Warrior() = default;


	void attack(std::vector<std::unique_ptr<Item>>& attacks, const TypeItem& tipAttack, const float& angle,
			    const sf::Vector2f& pos) override;
	void getAttacked(const bool& isAttacked, const short& attackPower);

	void move(const float& dir_x, const float& dir_y) override;
	void setRotation(const float& angle) override;


	std::unique_ptr<Item> generateItem() const override;

	//Getters
	const sf::Texture& getToCaveTexture() const override;
	const sf::Texture& getToForestTexture() const override;
	const sf::Texture& getToVillageTexture() const override;

	//Setters
	void setSpriteDirection(const short& dir_x, const short& dir_y) override;
};
