#pragma once
#include "AllAdditionalAndLibraries.h"


class Enemy
{
private: 
	//Enemy features
	CategorieEnemy categorie; 

	sf::Clock enemyClock; 

	short health;
	short attackPower;
	float speedMovement;

	bool isAttacking; //enemy-ul ataca


protected: 
	//IntroBattle
	std::unique_ptr<sf::Texture> introTexture;
	std::unique_ptr<sf::Sprite> introSprite;

	//BattleScene
	std::unique_ptr<sf::Texture> MovingTexture;
	std::unique_ptr<sf::Texture> AttackingTexture;

	std::unique_ptr<sf::Texture> AttackingAttackedTexture;
	std::unique_ptr<sf::Texture> AttackingColdAttackedTexture; 

	std::unique_ptr<sf::Texture> AttackedTexture;
	std::unique_ptr<sf::Texture> ColdAttackedTexture;

	std::unique_ptr<sf::Sprite> BattleSprite;
	

public: 
	Enemy(const CategorieEnemy& categorie, const short& hp, const short& attack, const float& speed);
	virtual ~Enemy();

	//Metode pur virtuale
	virtual void attack(const bool& isAttacking) = 0;
	virtual void getAttacked(const bool& isAttacked, const short& attackPower, const TypeItem& tipAtac) = 0;
	virtual void move(const float& angle, const sf::Sprite& stopTexture) = 0;
	


	//Getters
	const short& get_health() const;
	const short& get_attackPower() const;
	const short& get_speedMovement() const;
	const CategorieEnemy& getCategorie() const;
	const bool& getIsAttacking() const; 

	const sf::Clock& getEnemyClock() const; 

	virtual const sf::Sprite& getIntroSprite() = 0;   
	virtual const sf::Sprite& getBattleSprite() = 0;

	//Setters
	void setIsAttack(const bool& status);
	void set_speedMovement(const float& newValue); 
	void healthDecreases(const short& damage); 
	//For IntroBattle
	virtual void setScaleIntroSpr(const float& x_scale, const float& y_scale) = 0;
	virtual void setPosIntroSpr(const float& pos_x, const float& pos_y) = 0;
	virtual void setRotation(const float& angle) = 0;
};

