#pragma once
#include "GameInfo.h"
#include "Ghoul.h" //Enemy sunt necesar doar in scenele Battle


class GameInfoIntroBattle : public GameInfo
{
private: 
	//Background
	std::unique_ptr<sf::Texture> backgroundTex{ nullptr };
	std::unique_ptr<sf::Sprite>  backgroundSpr{ nullptr };

	//Textul 
	std::unique_ptr<sf::Texture> Text_DescriereLoc_Tex{ nullptr };
	std::unique_ptr<sf::Texture> Text_MesajAtack_Tex{ nullptr };
	std::unique_ptr<sf::Sprite>  TextSpr   { nullptr }; 

	//Options
	std::unique_ptr<sf::Texture> continueTex_1{ nullptr };
	std::unique_ptr<sf::Texture> continueTex_2{ nullptr };
	std::unique_ptr<sf::Sprite>  continueSpr{ nullptr };

	
	//Enemy - este instantia in scena data si apoi mutat cu std::move() in scena de lupta
	std::shared_ptr<Enemy> enemy{ nullptr }; //ca sa il putem share-ui catre scena urmatoare si totodata sa fie utilizat 
											 //in scena data cat timp nu este finisat thread-ul muzicii (+-1200 ms)

	unsigned short continueCount;
	bool isTextReseted; //Pentru a nu reseta si aloca memoria pentru sprite-ul 'TextSpr' la fiecare iterare
	bool isEnemyAttacking; 
	bool mouseHeld; 


	//Private methods
	void initEnemy(const ActionResults& interact); 
	void initVariables(); 
	void initBackground(const ActionResults& interact);
	void initText(const ActionResults& interact);
	void initContinue(); 


public: 
	//Metodele de initializare sunt chemate in constructor (init all sprites)
	GameInfoIntroBattle(const sf::Vector2u& size, const ActionResults& interact); 
	~GameInfoIntroBattle() = default; 

	//Draw all sprites
	void drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const override;

	//Check mouse held
	void updatePollEvents(sf::RenderWindow& target, ActionResults& interact) override;
};

