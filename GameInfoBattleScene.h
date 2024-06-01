#pragma once
#include "GameInfo.h"
#include "Ghoul.h" //Enemy sunt necesar doar in scenele Battle


class GameInfoBattleScene : public GameInfo
{
private: 
	//Pentru a crea pauze
	sf::Clock clock; 
	sf::Time cooldownTime;
	sf::Time waitingTime; 
	sf::Time waitingBegin; 
	sf::Time timePoint;
	sf::Time lastAttack;

	std::random_device rd; 

	//Font
	std::unique_ptr<sf::Font> font;

	//Text 
	std::unique_ptr<sf::Text> uiText_PlayerName;
	std::unique_ptr<sf::Text> uiText_PlayerHealth;
	
	std::vector<std::unique_ptr<sf::Text>> itemsFromInventar; 

	std::unique_ptr<sf::Text> uiText_EnemyName;
	std::unique_ptr<sf::Text> uiText_EnemyHealth;

	//Background
	std::unique_ptr<sf::Texture> backgroundTex{ nullptr };
	std::unique_ptr<sf::Sprite>  backgroundSpr{ nullptr };

	std::unique_ptr<sf::Sprite> playerSpr	  { nullptr }; 

	bool keyWasPressed; 
	bool x_modified; 
	bool y_modified; 
	bool mouseHeld;	
	bool keyHeld; 


	//Sunt float, fiindca getPostion returneaza valori float
	//si conversia implicita este evitata
	float min_x; 
	float min_y; 
	float max_x; 
	float max_y; 

	std::shared_ptr<Item> currentItem; //este indexul in inventar al item-ului folosit 
	bool itemChanged; 

	bool enemyIsWainting; 
	bool enemyWasAttacked; //enemy a fost atacat
	bool enemyAttacked; //enemy a atacat
	bool newEnemyAttack; 


	//For attacking
	std::vector<std::unique_ptr<Item>> projectiles; //Item-uri ce sunt generate intr-un numar mai mare - fireballs, arrows, spears

	//Private methods
	void initFont(); 
	void initText(const ActionResults& interact); 
	void initTime(); 
	void initLimits(); 
	void initVariables(const ActionResults& interact);
	void initBackground(const ActionResults& interact);

	const double calculateAngle(const sf::Vector2f mousePosition, const ActionResults& interact);  //Unghiul returnat va fi fata de 
																								 //directia 'Up' verticala. 
	void movePlayer(ActionResults& interact); 
	void rotatePlayer(const sf::RenderWindow& target, ActionResults& interact);
	void thePlayersAttack(const sf::RenderWindow& target, ActionResults& interact);
	void moveProjectiles(const sf::RenderWindow& target); 
	void enemyGetAttacked(ActionResults& interact); 
	void moveEnemy(ActionResults& interact); 
	void enemyAttack(ActionResults& interact); 

	void updateUiText(const ActionResults& interact) const; 


public:
	//Metodele de initializare sunt chemate in constructor (init all sprites)
	GameInfoBattleScene(const sf::Vector2u& size, const ActionResults& interact); 
	~GameInfoBattleScene() = default; 

	//Draw all sprites
	void drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const override;

	//Check mouse held
	void updatePollEvents(sf::RenderWindow& target, ActionResults& interact) override;
};

