#pragma once
#include "Enemy.h"


class Ghoul : public Enemy
{
private: 
	//Enemy is attacking
	sf::Time attackDuration; 
	sf::Time attackBeginning; 
	//Enemy is attacked
	sf::Time lastAttack; 
	sf::Time woundedTime; 

	bool isAttacked; //este atacat
	std::optional<bool> ThermalAttack; //iceball-ul va fi pentru 'false', iar fireball-ul va fi pentru 'true'

	//Private methods
	void initIntroTexAndSpr(); 
	void initBattleTexAndSpr(); 

public: 
	// Constructor / Destructor
	Ghoul(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed);
	~Ghoul() = default;



	void attack(const bool& isAttacking) override;
	void getAttacked(const bool& isAttacked, const short& attackPower, const TypeItem& tipAtac) override;
	void move(const float& angle, const sf::Sprite& stopTexture) override;

	//Getters
    const sf::Sprite& getIntroSprite() override; 
	const sf::Sprite& getBattleSprite() override; 

	//Setters
	void setScaleIntroSpr(const float& x_scale, const float& y_scale) override;
	void setPosIntroSpr(const float& pos_x, const float& pos_y) override;
	void setRotation(const float& angle) override; 
};

