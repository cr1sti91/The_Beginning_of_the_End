#pragma once
#include "Enemy.h"



class Griffon : public Enemy
{
	//Private methods
	void initIntroTexAndSpr();
	void initBattleTexAndSpr();

public:
	// Constructor / Destructor
	Griffon(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed);
	~Griffon() = default;


	void closeAttack(const sf::Vector2f& playerPos, const sf::Vector2f& enemyPos) override;
	void projectileAttack(std::vector<std::unique_ptr<Item>>& projectiles, const float& angle, const sf::Vector2f& pos,
				          const float& distanceFromPlayer) override;

	void getAttacked(const bool& isAttacked, const short& attackPower, const TypeItem& tipAtac) override;


	//Getters
	const sf::Sprite& getIntroSprite() override;
	const sf::Sprite& getBattleSprite() override;

	//Setters
	void setScaleIntroSpr(const float& x_scale, const float& y_scale) override;
	void setPosIntroSpr(const float& pos_x, const float& pos_y) override;
	void setRotation(const float& angle) override;
};

