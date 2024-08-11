#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "Player.h"

//Structura interfata
struct GameInfo
{
	GameInfo() = default; 
	virtual ~GameInfo() = default;

	virtual void drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const = 0;
	virtual void updatePollEvents(sf::RenderWindow& target, ActionResults& interact) = 0;
};

#endif //GAMEINFO_H