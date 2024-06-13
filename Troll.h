#pragma once
#include "Enemy.h"



class Troll : public Enemy
{
	//Enemy is attacking
	sf::Time attackDuration;
	sf::Time attackBeginning;
	//Enemy is attacked
	sf::Time lastAttack;
	sf::Time woundedTime;

	sf::Vector2f movingOrigin, attackingOrigin; //Originile pentru texturi de din BattleScene

	//Private methods
	void initIntroTexAndSpr();
	void initBattleTexAndSpr();
	void initVariables(); 

public:
	// Constructor / Destructor
	Troll(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed);
	~Troll() = default;

	void attack(const bool& isAttacking) override;
	void getAttacked(const bool& isAttacked, const short& attackPower, const TypeItem& tipAtac) override;


	//Getters
	const sf::Sprite& getIntroSprite() override;
	const sf::Sprite& getBattleSprite() override;

	//Setters
	void setScaleIntroSpr(const float& x_scale, const float& y_scale) override;
	void setPosIntroSpr(const float& pos_x, const float& pos_y) override;
	void setRotation(const float& angle) override;
};

