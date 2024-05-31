#pragma once
#include "GameInfo.h"




class GameCrossRoads : public GameInfo
{
private: 
	std::unique_ptr<sf::Texture> backgroundTex           { nullptr };
	std::unique_ptr<sf::Texture> backgroundTex_chestScene{ nullptr };
	std::unique_ptr<sf::Sprite>  backgroundSpr           { nullptr };

	std::unique_ptr<sf::Texture> chestTex_1{ nullptr };
	std::unique_ptr<sf::Texture> chestTex_2{ nullptr };
	std::unique_ptr<sf::Sprite>  chestSpr  { nullptr };

	std::unique_ptr<sf::Texture> chestInfoTex_1         { nullptr }; //am gasit un chest
	std::unique_ptr<sf::Texture> chestInfoTex_2_fireball{ nullptr }; //descriere ceea ce se afla in chest
	std::unique_ptr<sf::Texture> chestInfoTex_2_iceball	{ nullptr }; 
	std::unique_ptr<sf::Sprite>  chestInfoSpr           { nullptr };

	std::unique_ptr<sf::Texture> OpenTex_1{ nullptr };
	std::unique_ptr<sf::Texture> OpenTex_2{ nullptr };
	std::unique_ptr<sf::Sprite>  OpenSpr  { nullptr };

	std::unique_ptr<sf::Sprite>  addedItem{ nullptr };

	std::unique_ptr<sf::Texture> SkipTex_1{ nullptr }; 
	std::unique_ptr<sf::Texture> SkipTex_2{ nullptr };
	std::unique_ptr<sf::Sprite>  SkipSpr  { nullptr };   

	std::unique_ptr<sf::Texture> continueTex_1{ nullptr };
	std::unique_ptr<sf::Texture> continueTex_2{ nullptr };
	std::unique_ptr<sf::Sprite>  continueSpr  { nullptr };

	std::unique_ptr<sf::Texture> caveInscriptionTex_1{ nullptr };
	std::unique_ptr<sf::Texture> caveInscriptionTex_2{ nullptr };
	std::unique_ptr<sf::Texture> caveInscriptionTex_3{ nullptr };
	std::unique_ptr<sf::Sprite>  caveInscriptionSpr  { nullptr };

	std::unique_ptr<sf::Texture> forestInscriptionTex_1{ nullptr };
	std::unique_ptr<sf::Texture> forestInscriptionTex_2{ nullptr };
	std::unique_ptr<sf::Texture> forestInscriptionTex_3{ nullptr };
	std::unique_ptr<sf::Sprite>  forestInscriptionSpr  { nullptr };

	std::unique_ptr<sf::Texture> villageInscriptionTex_1{ nullptr };
	std::unique_ptr<sf::Texture> villageInscriptionTex_2{ nullptr };
	std::unique_ptr<sf::Texture> villageInscriptionTex_3{ nullptr };
	std::unique_ptr<sf::Sprite>  villageInscriptionSpr  { nullptr };

	std::unique_ptr<sf::Sprite>  playerSpr{ nullptr }; 

	//Coordinates
	unsigned short center_x;
	unsigned short center_y;

	unsigned short forest_x;
	unsigned short forest_y;

	unsigned short cave_x;
	unsigned short cave_y;

	unsigned short village_x;
	unsigned short village_y;



	//Logic
	bool mouseHeld;
	bool isExecuted;

	bool isPlayerSprSeted;

	bool goToCave; 
	bool goToForest; 
	bool goToVillage; 

	bool isInTheCenter; 
	bool isChestScene; 
	bool afterChestScene;
	bool isChestReseted;

	bool isAtTheDestination;

	std::optional<bool> isChestOpen; 


	//Private methods
	void initVariables(); 
	void initBackground(); 
	void initPlayerSpr(); 
	void initCaveInscription();
	void initForestInscription();
	void initVillageInscription();
	void initChest(); 
	void initChestInfo(); 
	void initOpen(); 
	void initAddedItem(); 
	void initSkip(); 
	void initContinue(const sf::Vector2u& size);

	void setPlayerSprite(ActionResults& interact); 
	void deplasareSpreCufar(); 
	void deplasareSpreDestinatie(); 


public: 
	//Metodele de initializare sunt chemate in constructor (init all sprites)
	GameCrossRoads(const sf::Vector2u& size, const ActionResults& interact);
	~GameCrossRoads() = default; 

	//Draw all sprites
	void drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const override;

	//Check mouse held
	void updatePollEvents(sf::RenderWindow& target, ActionResults& interact) override;
};

