#pragma once
#include "Item.h"
#include "AllAdditionalAndLibraries.h"



class Player
{
private:
	sf::Clock playerClock;

	//Player features
	std::string playerName;
	CategoriePlayer categorie; 

	short health;
	short attackPower;
	float speedMovement;

protected: 
	//Inventarul este accesat direct in constructorul claselor derivate
	std::vector<std::unique_ptr<Item>> inventar; 

	//Initializarea texturilor si sprite-urilor sa fie facuta in clasele derivate

	//Player textures
	//For CrossRoads scene
	std::unique_ptr<sf::Texture> textureToVillage;
	std::unique_ptr<sf::Texture> textureToForest;
	std::unique_ptr<sf::Texture> textureToCave;

	//For Battle scene
	std::unique_ptr<sf::Texture> textureUp;
	std::unique_ptr<sf::Texture> textureUpAttacked;

	std::unique_ptr<sf::Sprite> playerSpr; //in timpul luptei isi va modifica pozitia, astfel
										   //attack-ul sa fie facut in dependenta de pozitia sprite-ului

	//Protected methods
	const sf::Clock& getPlayerClock() const;

public:
	Player(const std::string& name, const CategoriePlayer& categorie, const short& hp,
		   const short& attack, const float& speed);
	virtual ~Player();


	//Metode pur virtuale
	virtual void attack(std::vector<std::unique_ptr<Item>>& attacks, const TypeItem& tipAttack, const float& angle,
						const sf::Vector2f&) = 0;
	virtual void getAttacked(const bool& isAttacked, const short& attackPower) = 0;

	virtual void move(const float& dir_x, const float& dir_y) = 0;

	//Ambele rotesc sprite-ul
	virtual void setRotation(const float& angle) = 0;                            //Roteste sprite-ul in dependenta de pozitia mouse-ului
	virtual void setSpriteDirection(const short& dir_x, const short& dir_y) = 0; //Roteste sprite-ul in dependenta de butoane


	//Getters
	const std::string& get_playerName() const;
	const short get_health() const;
	const short get_attackPower() const;
	const short get_speedMovement() const;
	const CategoriePlayer& getCategorie() const; 
	const std::vector<std::unique_ptr<Item>>& getInvetar() const; //Doar pentru accesare
	const sf::Vector2f& getPosition() const; 

	const sf::Sprite& getPlayerSpr() const;


	//Getters pure virtual
	//For CrossRoads scene
	virtual const sf::Texture& getToCaveTexture() const = 0;
	virtual const sf::Texture& getToForestTexture() const = 0;
	virtual const sf::Texture& getToVillageTexture() const = 0;



	//Generarea random a item-urilor
	virtual std::unique_ptr<Item> generateItem() const = 0;

	//Setters
	bool addItems(std::unique_ptr<Item> item); //Returneaza 'true' daca item-ul a fost adaugat, in caz constrar - 'false'
	void healthDecreases(const short& damage);
};