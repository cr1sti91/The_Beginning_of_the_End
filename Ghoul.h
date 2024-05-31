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
	

	//IntroBattle
	std::unique_ptr<sf::Texture> introTexture;
	std::unique_ptr<sf::Sprite> introSprite;

	//BattleScene
	const sf::Texture* temp; //Cand enemy-ul ataca, textura precedenta este pastrata in el.
	std::unique_ptr<sf::Texture> MovingTexture;
	std::unique_ptr<sf::Texture> AttackingTexture;
	std::unique_ptr<sf::Texture> AttackingAttackedTexture; 
	std::unique_ptr<sf::Texture> AttackedTexture;
	std::unique_ptr<sf::Sprite> BattleSprite;


	//Private methods
	void initIntroTexAndSpr(); 
	void initBattleTexAndSpr(); 

public: 
	// Constructor / Destructor
	Ghoul(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed);
	~Ghoul() = default;



	void attack(const bool& isAttacking) override;
	void getAttacked(const bool& isAttacked, const short& attackPower) override;
	void move(const float& angle, const sf::Sprite& stopTexture) override;

	//Getters
    const sf::Sprite& getIntroSprite() override; 
	const sf::Sprite& getBattleSprite() override; 

	//Setters
	void setScaleIntroSpr(const float& x_scale, const float& y_scale) override;
	void setPosIntroSpr(const float& pos_x, const float& pos_y) override;
	void setRotation(const float& angle) override; 
};

