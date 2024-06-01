#pragma once
#include "Player.h"
#include "ItemsForWizard.h"


class Wizard : public Player
{
private:
	float projectileDirection; //pentru momentul in care arunca fireball-uri

	//Player is attacked
	sf::Time lastAttacked;
	sf::Time woundedTime;


	//Random device for generateItem
	std::random_device rd;

	//Private methods
	void initTexture();	
	void initPlayerSpr(); 

public:
	// Constructor / Destructor
	Wizard(const std::string& name, const CategoriePlayer& categorie);
	~Wizard() = default;

	/// 
	/// AM NEVOIE DE O METODA CHECK INVENTAR PENTRU A STI CE ATACURI POT FACE
	///


	void attack(std::vector<std::unique_ptr<Item>>& attacks, const TypeItem& tipAttack, const float& angle,
				const sf::Vector2f&) override;
	void getAttacked(const bool& isAttacked, const short& attackPower);

	void move(const float& dir_x, const float& dir_y) override;

	std::unique_ptr<Item> generateItem() const override;

	//Setters
	void setRotation(const float& angle) override;
	void setSpriteDirection(const short& dir_x, const short& dir_y) override; //Info pentru a initializa fireballs

	//Getters
	//Scena CrossRoads
	const sf::Texture& getToCaveTexture() const override;
	const sf::Texture& getToForestTexture() const override;
	const sf::Texture& getToVillageTexture() const override;
};

