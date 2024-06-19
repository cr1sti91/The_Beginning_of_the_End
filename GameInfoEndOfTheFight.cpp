#include "GameInfoEndOfTheFight.h"

void GameInfoEndOfTheFight::initBackground(const ActionResults& interact)
{
	switch (interact.locatieLupta)
	{
	case BattleLocation::Cave: initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_EndOfTheFight_BackGCave, 
											 "ERROR::GameInfoEndOfTheFight::initBackground::Cave background inaccesibil!"); 
		break;
	case BattleLocation::Forest: initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_EndOfTheFight_BackGForest,
											   "ERROR::GameInfoEndOfTheFight::initBackground::Forest background inaccesibil!");
		break;
	case BattleLocation::Village: initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_EndOfTheFight_BackGVillage,
												"ERROR::GameInfoEndOfTheFight::initBackground::Village background inaccesibil!");
		break;
	default: std::cerr << "ERROR::GameInfoEndOfTheFight::initBackground::Locatie lupta incorecta!" << std::endl;
		break;
	}
}

void GameInfoEndOfTheFight::initMessage(const ActionResults& interact)
{
	if (interact.defeatedEnemy)
	{
		initTexAndSpr(this->messageTex, this->messageSpr, path_EndOfTheFight_win,
					  "ERROR::GameInfoEndOfTheFight::initBackground::Win message inaccesibil!");

		this->messageSpr->setPosition(896.f, 400.f);
		this->messageSpr->setOrigin(245.f, 208.f);
		this->messageSpr->setScale(0.8f, 0.8f);
	}
	else 
	{
		initTexAndSpr(this->messageTex, this->messageSpr, path_EndOfTheFight_defeat,
					  "ERROR::GameInfoEndOfTheFight::initBackground::Defeat message inaccesibil!");

		this->messageSpr->setPosition(896.f, 400.f);
		this->messageSpr->setOrigin(255.f, 203.f);
	}
}


GameInfoEndOfTheFight::GameInfoEndOfTheFight(const sf::Vector2u& size, const ActionResults& interact)
{
	this->initBackground(interact); 
	this->initMessage(interact); 
}

void GameInfoEndOfTheFight::drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const
{
	target.draw(*this->backgroundSpr); 
	target.draw(*this->messageSpr);  
}

void GameInfoEndOfTheFight::updatePollEvents(sf::RenderWindow& target, ActionResults& interact)
{
}
