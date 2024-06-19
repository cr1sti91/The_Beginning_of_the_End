#pragma once
#include "Warrior.h"
#include "Wizard.h"
#include "Rogue.h"
#include "GameIntroInfo.h"
#include "GameInfoChoose.h"
#include "GameCrossRoads.h"
#include "GameInfoIntroBattle.h"
#include "GameInfoBattleScene.h"
#include "GameInfoEndOfTheFight.h"


class Game
{
private:
	//Window features
	sf::VideoMode videoMode;
	std::string windowName;
	unsigned short frameLimit = 60;

	//Music
	std::unique_ptr<sf::Music> music;


	//Player
	std::shared_ptr<Player> player; 


	//Eveniment
	sf::Event event;

	//Game logic
	unsigned short currentScene; 
	bool stopMusic;

	//std::atomic asigura ca variabilele date sa fie modificate in siguranta intre thread-uri
	std::atomic<bool> musicIsStopped; 
	std::atomic<bool> musicIsInitialized;

	ActionResults interact; //De la 'interactionarea' clasei Game cu clasele derivate din GameInfo

	//Window
	std::unique_ptr<sf::RenderWindow> window = nullptr;

	//Game Info
	std::unique_ptr<GameInfo> gameInfoPtr = nullptr;
	std::unique_ptr<GameInfo> temp = nullptr;


	//--------------Private methods--------------

	//
	void initMusic(); 
	void initWindowFeatures(const short& width, const short& height, const std::string& name, unsigned short fLimit); 
	void initWindow();
	void initInfoPtr();
	void initVariables(); 

	void initPlayer(const CategoriePlayer& categorie, const std::string& nume); 


	//---------------Reset methods---------------
	//Pentru scena_1
	void resetMusic(unsigned short); 
	void resetInfoPtr(unsigned short); 
	void resetVariables(); 

	void UpdateAll(unsigned short);

	

public:
	Game(const short& width, const short& height, const std::string& name,
			  unsigned short fLimit);
	~Game();

	//Functions
	void run();
	void playMusic(); 


	void renderGameInfo(); 

	void updatePollEvents();
	void update(); //Update all the possitions
	void render(); //Draw all changes

	//Getters
	const sf::Vector2u getWindowSize() const;
	const bool getWindowStatus() const; 


	//Check music
	const bool isMusicPlaying() const;
};

