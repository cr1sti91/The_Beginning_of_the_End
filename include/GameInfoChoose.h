#ifndef GAMEINFOCHOOSE_H
#define GAMEINFOCHOOSE_H

#include "GameInfo.h"

class GameInfoChoose : public GameInfo
{
private: 
	//Background
	std::unique_ptr<sf::Texture> backgroundTex{ nullptr };
	std::unique_ptr<sf::Texture> background_Wi_Tex{ nullptr };
	std::unique_ptr<sf::Texture> background_Wa_Tex{ nullptr };
	std::unique_ptr<sf::Texture> background_R_Tex{ nullptr };

	std::unique_ptr<sf::Sprite> backgroundSpr{ nullptr };

	//Warrior
	std::unique_ptr<sf::Texture> WarriorTex_1{ nullptr };
	std::unique_ptr<sf::Texture> WarriorTex_2{ nullptr };
	std::unique_ptr<sf::Sprite> WarriorSpr{ nullptr };

	//Wizard
	std::unique_ptr<sf::Texture> WizardTex_1{ nullptr };
	std::unique_ptr<sf::Texture> WizardTex_2{ nullptr };
	std::unique_ptr<sf::Sprite> WizardSpr{ nullptr };

	//Rogue
	std::unique_ptr<sf::Texture> RogueTex_1{ nullptr };
	std::unique_ptr<sf::Texture> RogueTex_2{ nullptr };
	std::unique_ptr<sf::Sprite> RogueSpr{ nullptr };

	//Font
	std::unique_ptr<sf::Font> font;

	//Text 
	std::unique_ptr<sf::Text> uiText;
	std::unique_ptr<sf::Text> uiInputText;
	

	//Event - pentru citirea numelui jucatorului de la tastatura
	sf::Event event; 
	std::string inputName; 

	bool mouseHeld;
	bool isExecuted;
	bool mouseIndication; 
	bool isEnteringName; 

	void initVariables();


	void initBackground();
	void initWarrior(const sf::Vector2u& size);
	void initWizard(const sf::Vector2u& size);
	void initRogue(const sf::Vector2u& size);

	void initFonts();
	void initText(const sf::Vector2u& size);
	

public: 
	//Metodele de initializare sunt chemate in constructor (init all sprites)
	GameInfoChoose(const sf::Vector2u& size, const ActionResults& interact);
	~GameInfoChoose() = default;

	//Draw all sprites
	void drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const override;

	//Check mouse held
	void updatePollEvents(sf::RenderWindow& target, ActionResults& interact) override;
};

#endif //GAMEINFOCHOOSE_H