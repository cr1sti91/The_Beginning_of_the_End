#include "GameIntroInfo.h"


//--------------------------------------------METODE ALE STRUCTURII GameIntroInfo_1 (scena_0)--------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameIntroInfo_1::initBackground()
{
	//Initializare background
	initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_Main_Menu_BackG, "ERROR::GameIntroInfo_1::Background inaccesibil!");
}

void GameIntroInfo_1::initGameName(const sf::Vector2u& size)
{
	//Initializare Game_Name
	initTexAndSpr(this->Game_NameTex, this->Game_NameSpr, path_Main_Menu_GameN, "ERROR::GameIntroInfo_1::Game name inaccesibil!");

	//Scalare
	Game_NameSpr->scale(0.5f, 0.45f);
	//Setare pozitie
	float coeficient = size.x / 2;
	Game_NameSpr->setPosition(coeficient, coeficient / 20);
}



void GameIntroInfo_1::initOptions(const sf::Vector2u& size)
{
	//Initializare 'play'
	initTexAndSpr(this->playTex_1, this->playSpr, path_Main_Menu_play, "ERROR::GameIntroInfo_1::play inaccesibil!");


	//Scalare 'play'
	this->playSpr->scale(0.2f, 0.2f);
	//Setare pozitie 'play'
	float coeficient = size.x / 2 - size.x / 3;
	playSpr->setPosition(coeficient + 30, coeficient * 2 - 250);

	//Initializare 'exit'
	initTexAndSpr(this->exitTex_1, this->exitSpr, path_Main_Menu_exit, "ERROR::GameIntroInfo_1::exit inaccesibil!");

	//Scalare 'exit'
	this->exitSpr->scale(0.2f, 0.2f);
	//Setare pozitie 'exit'
	exitSpr->setPosition(coeficient + 30, coeficient * 2 - 90);


	///////////////////////////////////////////////////////////////
	//Initializare texturi ce vor fi aplicate in cazul indicarii spre 
	initTex(this->playTex_2, path_Main_Menu_playH, "ERROR::GameIntroInfo_1::play_mouseHeld inaccesibil!");
	initTex(this->exitTex_2, path_Main_Menu_exitH, "ERROR::GameIntroInfo_1::exit_mouseHeld inaccesibil!");

}

void GameIntroInfo_1::initVariables()
{
	this->mouseHeld = false;
	this->mouseIndication = false;
	this->isPlayPressed = false;
	this->isExecuted = false;
}

GameIntroInfo_1::GameIntroInfo_1(const sf::Vector2u& size, const ActionResults& interact)
{
	this->initBackground();
	this->initGameName(size);
	this->initOptions(size);
	this->initVariables();
}



void GameIntroInfo_1::drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const
{
	target.draw(*this->backgroundSpr);
	target.draw(*this->Game_NameSpr);
	target.draw(*this->playSpr);
	target.draw(*this->exitSpr);
}

void GameIntroInfo_1::updatePollEvents(sf::RenderWindow& target, ActionResults& interact)
{
	if (this->playSpr->getGlobalBounds().contains(getMousePosView(target)) && !mouseIndication)
	{
		playSpr->setTexture(*playTex_2);
		mouseIndication = true;
		isPlayPressed = true;
	}
	else
	{
		playSpr->setTexture(*playTex_1);
		mouseIndication = false;
		isPlayPressed = false;
	}

	if (this->exitSpr->getGlobalBounds().contains(getMousePosView(target)) && !mouseIndication)
	{
		exitSpr->setTexture(*exitTex_2);
		mouseIndication = true;
	}
	else
	{
		exitSpr->setTexture(*exitTex_1);
		mouseIndication = false;
	}



	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;

			//Daca pozitia mouse-lui nimereste atat in sprite-ul 'play' cat si in 'exit', atunci va 
			//fi ales sprite-ul care contine textura cu indicele 2
			if (this->playSpr->getGlobalBounds().contains(getMousePosView(target)) && this->isPlayPressed)
			{
				////////////////////////////////////
				//Cod de test
				interact.sceneEnd = true;
				this->isExecuted = true;
				return;
				////////////////////////////////////
			}
			else if (this->exitSpr->getGlobalBounds().contains(getMousePosView(target)))
			{
				////////////////////////////////////
				//Cod de test
				interact.sceneEnd = false; //sceneEnd se considera TRUE doar cand jocul trece la alta scena
										   //daca sceneEnd devine explicit false in timpul pollEvent, atunci jocul se finalizeaza
				this->isExecuted = true;
				target.close();
				return;
				////////////////////////////////////
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}





//--------------------------------------------METODE ALE STRUCTURII GameIntroInfo_2 (scena_1)--------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameIntroInfo_2::initVariables()
{
	this->mouseHeld = false;
	this->isContinue = false;
	this->wasReseted = false;
	this->afterChoosing = false;

	this->continueCount = 0;
}

void GameIntroInfo_2::initBackground()
{
	//Initializare background
	initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_IntroBackG, "ERROR::GameIntroInfo_2::Background inaccesibil!");

	//Initializare background for text
	initTex(this->BlackTextureForText, path_BlackTextureForText, "ERROR::GameIntroInfo_2::BlackTextureForText inaccesbil!"); 
}

void GameIntroInfo_2::initTextTexture(const sf::Vector2u& size)
{
	//Initializare Text
	initTexAndSpr(this->Text_1_Tex, this->Text_Spr, path_IntroText_1, "ERROR::GameIntroInfo_2::Text_1 inaccesibil!");

	//Scalare
	Text_Spr->scale(1.f, 1.f);
	//Setare pozitie
	float coeficient_x = size.x / 2;
	float coeficient_y = size.y / 2;

	this->Text_Spr->setPosition(coeficient_x - coeficient_x / 1.2, coeficient_y + coeficient_y / 1.5);

	this->textPosition = this->Text_Spr->getPosition();

	initTex(this->Text_2_Tex, path_IntroText_2, "ERROR::GameIntroInfo_2::Text_2_Tex inaccesibil!");
	initTex(this->Text_3_Tex, path_IntroText_3, "ERROR::GameIntroInfo_2::Text_3_Tex inaccesibil!");
	initTex(this->Text_4_Tex, path_IntroText_4, "ERROR::GameIntroInfo_2::Text_4_Tex inaccesibil!");
	initTex(this->Text_5_Tex, path_IntroText_5, "ERROR::GameIntroInfo_2::Text_4_Tex inaccesibil!");
	initTex(this->Text_6_Tex, path_IntroText_6, "ERROR::GameIntroInfo_2::Text_4_Tex inaccesibil!");


	initTex(this->Text_Wa_Tex, path_Warrior_IntroText, "ERROR::GameIntroInfo_2::Warrior_IntroText inaccesibil!");
	initTex(this->Text_Wi_Tex, path_Wizard_IntroText,  "ERROR::GameIntroInfo_2::Wizard_IntroText inaccesibil!");
	initTex(this->Text_R_Tex, path_Rogue_IntroText,    "ERROR::GameIntroInfo_2::Rogue_IntroText inaccesibil!");
}

void GameIntroInfo_2::initContinue(const sf::Vector2u& size)
{
	//Initializare 
	initTexAndSpr(this->continueTex_1, this->continueSpr, path_continue, "ERROR::GameIntroInfo_2::Continue inaccesibil!");

	//Scalare
	this->continueSpr->scale(0.2f, 0.2f);
	//Setare pozitie
	float coeficient_x = size.x / 2;
	float coeficient_y = size.y / 2;
	this->continueSpr->setPosition(coeficient_x + coeficient_x / 1.3, coeficient_y + coeficient_y / 1.5);

	initTex(this->continueTex_2, path_continueH, "ERROR::GameIntroInfo_2::continue_mouseHeld inaccesibil!");
}

void GameIntroInfo_2::initOldMan(const sf::Vector2u& size)
{
	//Initializare 
	initTexAndSpr(this->OldMan_Tex, this->OldMan_Spr, path_OldMan, "ERROR::GameIntroInfo_2::OldMan inaccesibil!");

	//Scalare
	this->OldMan_Spr->scale(0.5f, 0.5f);
	//Setare pozitie
	float coeficient_x = size.x / 2;
	float coeficient_y = size.y / 2;
	this->OldMan_Spr->setPosition(coeficient_x + 150, coeficient_y - coeficient_y / 2.2);
}

void GameIntroInfo_2::initFonts()
{
	this->font = std::make_unique<sf::Font>(); 

	if (!this->font->loadFromFile(path_Font_CopperPLateGhothicLight))
		std::cout << "ERROR::GameIntroInfo_2::INITFONTS::Failed to load font CopperPlateGothicLight!" << std::endl;
}

void GameIntroInfo_2::initText(const sf::Vector2u& size)
{
	this->uiText = std::make_unique<sf::Text>(); 

	this->uiText->setFont(*this->font);
	this->uiText->setCharacterSize(30);
	this->uiText->setFillColor(sf::Color::White);
	this->uiText->setPosition(990.f, 851.f);
	this->uiText->setString("NONE");
}


//Constructor
GameIntroInfo_2::GameIntroInfo_2(const sf::Vector2u& size, const ActionResults& interact)
{
	this->initBackground();
	this->initOldMan(size);
	this->initTextTexture(size); //Fiindca textPosition se utilizeaza in initText, initTextTexture(size) trebuie chemata prima
	this->initContinue(size);
	this->initVariables();
	this->initFonts();
	this->initText(size);
}



void GameIntroInfo_2::drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const
{
	target.draw(*this->backgroundSpr);
	target.draw(*this->Text_Spr);
	target.draw(*this->continueSpr);

	if (this->isContinue)
		target.draw(*this->OldMan_Spr);

	if (this->continueCount == 3) //Se afiseaza numele player-ului
		target.draw(*this->uiText); 
}

void GameIntroInfo_2::updatePollEvents(sf::RenderWindow& target, ActionResults& interact)
{
	this->update(interact.clasaPlayer, interact.playerName);


	if (this->continueSpr->getGlobalBounds().contains(getMousePosView(target)))
	{
		this->continueSpr->setTexture(*this->continueTex_2);
	}
	else
	{
		this->continueSpr->setTexture(*this->continueTex_1);
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;

			//Daca pozitia mouse-lui nimereste atat in sprite-ul 'play' cat si in 'exit', atunci va 
			//fi ales sprite-ul care contine textura cu indicele 2
			if (this->continueSpr->getGlobalBounds().contains(getMousePosView(target)))
			{
				this->isContinue = true;
				++this->continueCount;
				this->wasReseted = false;
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}


	if (this->continueCount == 3 && !this->afterChoosing)
	{
		interact.sceneEnd = true; 
		this->afterChoosing = true;
		return;
	}
	else if (this->continueCount == 8 && this->afterChoosing)
	{
		interact.sceneEnd = true; 
		return; 
	}
}

void GameIntroInfo_2::update(const CategoriePlayer& categorie, const std::string& numePlayer)
{
	this->reset(categorie, numePlayer);
}

void GameIntroInfo_2::reset(const CategoriePlayer& categorie, const std::string& numePlayer)
{
	if (this->continueCount == 1 && !this->wasReseted)
	{
		resetSprite(this->Text_Spr, this->Text_2_Tex, this->textPosition); 
		this->wasReseted = true;
	}
	else if (this->continueCount == 2 && !this->wasReseted)
	{
		resetSprite(this->Text_Spr, this->Text_3_Tex, this->textPosition); 
		this->wasReseted = true;
	}
	else if (this->continueCount == 3 && !this->wasReseted)
	{
		this->uiText->setString(numePlayer); 

		resetSprite(this->Text_Spr, this->BlackTextureForText, this->textPosition);//////////////////////////
		this->wasReseted = true;
	}
	else if (this->continueCount == 4 && !this->wasReseted && this->afterChoosing)
	{   
		//In acest moment categoria va fi initializata corect
		switch (categorie)
		{
		case CategoriePlayer::Warrior: 
		{
			resetSprite(this->Text_Spr, this->Text_Wa_Tex, this->textPosition);
			this->wasReseted = true;

		}break; 
		case CategoriePlayer::Rogue:
		{
			resetSprite(this->Text_Spr, this->Text_R_Tex, this->textPosition);
			this->wasReseted = true;

		}break;
		case CategoriePlayer::Wizard:
		{
			resetSprite(this->Text_Spr, this->Text_Wi_Tex, this->textPosition);
			this->wasReseted = true;

		}break;

		default:
		{
			std::cerr << "ERROR::GameIntroInfo_2::reset::Categoria nu este valida!" << std::endl;
		}break;
		}
	}
	else if (this->continueCount == 5 && !this->wasReseted && this->afterChoosing)
	{
		resetSprite(this->Text_Spr, this->Text_4_Tex, this->textPosition);
		this->wasReseted = true;
	}
	else if (this->continueCount == 6 && !this->wasReseted && this->afterChoosing)
	{
		resetSprite(this->Text_Spr, this->Text_5_Tex, this->textPosition);
		this->wasReseted = true;
	}
	else if (this->continueCount == 7 && !this->wasReseted && this->afterChoosing)
	{
		resetSprite(this->Text_Spr, this->Text_6_Tex, this->textPosition);
		this->wasReseted = true;
	}
}



