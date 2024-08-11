#ifndef GAMEINTROINFO_H
#define GAMEINTROINFO_H

#include "GameInfo.h"

//	BEGINNING  ///////////////////////////////////////////////////////////////////////////////////////////////////

class GameIntroInfo_1 : public GameInfo
{
private: 
	//Background
	std::unique_ptr<sf::Texture> backgroundTex{ nullptr };
	std::unique_ptr<sf::Sprite>  backgroundSpr{ nullptr };

	//Game Name
	std::unique_ptr<sf::Texture> Game_NameTex{ nullptr };
	std::unique_ptr<sf::Sprite>  Game_NameSpr{ nullptr };

	//Options
	std::unique_ptr<sf::Texture> playTex_1{ nullptr };
	std::unique_ptr<sf::Texture> playTex_2{ nullptr };
	std::unique_ptr<sf::Sprite>  playSpr  { nullptr };

	std::unique_ptr<sf::Texture> exitTex_1{ nullptr };
	std::unique_ptr<sf::Texture> exitTex_2{ nullptr };
	std::unique_ptr<sf::Sprite>  exitSpr  { nullptr };




	//Check if the mouse was pressed while on the "play" or "exit" sprites
	bool mouseHeld;
	bool mouseIndication;
	bool isPlayPressed;
	bool isExecuted;


	//Private methods
	void initBackground();
	void initGameName(const sf::Vector2u& size);
	void initOptions(const sf::Vector2u& size);
	void initVariables();

public: 
	//Metodele de initializare sunt chemate in constructor (init all sprites)
	GameIntroInfo_1(const sf::Vector2u& size, const ActionResults& interact); 
	~GameIntroInfo_1() = default; 


	//Draw all sprites
	void drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const override;

	//Check mouse held
	void updatePollEvents(sf::RenderWindow& target, ActionResults& interact) override;
};


//	BEGINNING  ///////////////////////////////////////////////////////////////////////////////////////////////////

class GameIntroInfo_2 : public GameInfo
{
private: 
	//Background
	std::unique_ptr<sf::Texture> backgroundTex{ nullptr };
	std::unique_ptr<sf::Sprite>  backgroundSpr{ nullptr };

	//Background for text
	std::unique_ptr<sf::Texture> BlackTextureForText{ nullptr };


	//Text_1
	std::unique_ptr<sf::Texture> Text_1_Tex{ nullptr };
	std::unique_ptr<sf::Texture> Text_2_Tex{ nullptr };
	std::unique_ptr<sf::Texture> Text_3_Tex{ nullptr };
	std::unique_ptr<sf::Texture> Text_4_Tex{ nullptr };
	std::unique_ptr<sf::Texture> Text_5_Tex{ nullptr };
	std::unique_ptr<sf::Texture> Text_6_Tex{ nullptr };

	//After choosing player
	std::unique_ptr<sf::Texture> Text_Wa_Tex{ nullptr };
	std::unique_ptr<sf::Texture> Text_Wi_Tex{ nullptr };
	std::unique_ptr<sf::Texture> Text_R_Tex { nullptr };

	std::unique_ptr<sf::Sprite>  Text_Spr   { nullptr };

	//The old man
	std::unique_ptr<sf::Texture> OldMan_Tex{ nullptr };
	std::unique_ptr<sf::Sprite>  OldMan_Spr{ nullptr };

	//Options
	std::unique_ptr<sf::Texture> continueTex_1{ nullptr };
	std::unique_ptr<sf::Texture> continueTex_2{ nullptr };
	std::unique_ptr<sf::Sprite>  continueSpr  { nullptr };

	//Font
	std::unique_ptr<sf::Font> font;

	//Text 
	std::unique_ptr<sf::Text> uiText; //Doar pentru afisarea numelui jucatorului cand 'continueCount == 3'


	bool mouseHeld;
	bool isContinue;
	bool wasReseted;
	bool afterChoosing; 
	unsigned short continueCount;

	sf::Vector2f textPosition;

	//Private methods
	void initVariables();
	void initBackground();
	void initTextTexture(const sf::Vector2u& size);
	void initContinue(const sf::Vector2u& size);
	void initOldMan(const sf::Vector2u& size);

	void initFonts();
	void initText(const sf::Vector2u& size); 

	//Update
	void update(const CategoriePlayer& categorie, const std::string& numePlayer);
	void reset(const CategoriePlayer& categorie, const std::string& numePlayer);

public: 
	//Metodele de initializare sunt chemate in constructor (init all sprites)
	GameIntroInfo_2(const sf::Vector2u& size, const ActionResults& interact);
	~GameIntroInfo_2() = default;


	//Draw all sprites
	void drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const override;

	//Check mouse held
	void updatePollEvents(sf::RenderWindow& target, ActionResults& interact) override;
};

#endif //GAMEINTROINFO_H