#pragma once
#include "Enemy.h"



class Troll : public Enemy
{


	//Private methods
	void initIntroTexAndSpr();
	void initBattleTexAndSpr();

public:
	// Constructor / Destructor
	Troll(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed);
	~Troll() = default;



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

