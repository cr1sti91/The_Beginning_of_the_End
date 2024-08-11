#ifndef GAMEINFOENDOFTHEFIGHT_H
#define GAMEINFOENDOFTHEFIGHT_H

#include "GameInfo.h"

class GameInfoEndOfTheFight : public GameInfo
{
private:
	std::unique_ptr<sf::Texture> backgroundTex{ nullptr };
	std::unique_ptr<sf::Sprite>  backgroundSpr{ nullptr };

	std::unique_ptr<sf::Texture> messageTex	  { nullptr }; 
	std::unique_ptr<sf::Sprite>  messageSpr   { nullptr }; 

	//Private methods
	void initBackground(const ActionResults& interact); 
	void initMessage(const ActionResults& interact);  
	
public:
	//Metodele de initializare sunt chemate in constructor (init all sprites)
	GameInfoEndOfTheFight(const sf::Vector2u& size, const ActionResults& interact);
	~GameInfoEndOfTheFight() = default;

	//Draw all sprites
	void drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const override;

	void updatePollEvents(sf::RenderWindow& target, ActionResults& interact) override;
};

#endif //GAMEINFOENDOFTHEFIGHT_H