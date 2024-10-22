#ifndef TROLL_H
#define TROLL_H

#include "Enemy.h"

class Troll : public Enemy
{
	bool projectileCooldown;

	sf::Vector2f movingOrigin, attackingOrigin; //Originile pentru texturi de din BattleScene

	//Private methods
	void initIntroTexAndSpr();
	void initBattleTexAndSpr();
	void initVariables(); 

public:
	// Constructor / Destructor
	Troll(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed);
	~Troll() = default;

	void move(const float& angle, const sf::Sprite& stopTexture) override; 

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

#endif //TROLL