#pragma once
#include "Item.h"
#include "AllAdditionalAndLibraries.h"



class Player
{
private:
	//Player features
	std::string playerName;
	CategoriePlayer categorie; 

	short health;
	short attackPower;
	float speedMovement;

protected: 
	sf::Clock playerClock;

	//Player is attacked
	sf::Time lastAttacked;
	sf::Time woundedTime;

	//Inventarul este accesat direct in constructorul claselor derivate
	std::vector<std::shared_ptr<Item>> inventar; 

	//----------------------------------------------Player textures----------------------------------------------
	//For CrossRoads scene
	std::unique_ptr<sf::Texture> textureToVillage;
	std::unique_ptr<sf::Texture> textureToForest;
	std::unique_ptr<sf::Texture> textureToCave;
	//For Battle scene
	std::unique_ptr<sf::Texture> textureUp;
	std::unique_ptr<sf::Texture> textureUpAttacked;

	std::unique_ptr<sf::Sprite> playerSpr; //in timpul luptei isi va modifica pozitia, astfel
										   //attack-ul sa fie facut in dependenta de pozitia sprite-ului

	//Initializarea texturilor si sprite-urilor sa fie facuta in clasele derivate
	virtual void initTexture() = 0;
	virtual void initPlayerSpr() = 0;

public:
	// Constructor / Destructor
	Player(const std::string& name, const CategoriePlayer& categorie, const short& hp, const float& speed);
	virtual ~Player() = default;


	//---------------------------------------Metode pur virtuale--------------------------------------
	virtual void attack(std::vector<std::unique_ptr<Item>>& projectiles, const TypeItem& tipAttack,
						const float& angle, const sf::Vector2f& pos) = 0;

	virtual void stopAttack() = 0; 

	virtual void getAttacked(const bool& isAttacked, const short& attackPower) = 0;

	//Generarea random a item-urilor
	virtual std::unique_ptr<Item> generateItem() const = 0;


	//-------------------------------------Setters for player moving----------------------------------
	void move(const float& dir_x, const float& dir_y);
	//Ambele rotesc sprite-ul
	void setSpriteDirection(const short& dir_x, const short& dir_y); //Roteste sprite-ul in dependenta de butoane
	void setRotation(const float& angle);  //Roteste sprite-ul in dependenta de pozitia mouse-ului


	//---------------------------------------------Getters---------------------------------------------
	const std::string& get_playerName() const;
	const short get_health() const;
	const short get_speedMovement() const;
	const CategoriePlayer& getCategorie() const; 
	const std::vector<std::shared_ptr<Item>>& getInvetar() const; //Doar pentru accesare
	const sf::Vector2f& getPosition() const; 
	const sf::Sprite& getPlayerSpr() const;

	//For CrossRoads scene
	const sf::Texture& getToCaveTexture() const;
	const sf::Texture& getToForestTexture() const;
	const sf::Texture& getToVillageTexture() const;

	//---------------------------------------------Setters---------------------------------------------
	bool addItems(std::unique_ptr<Item> item); //Returneaza 'true' daca item-ul a fost adaugat, in caz constrar - 'false'
	void healthDecreases(const short& damage);
};