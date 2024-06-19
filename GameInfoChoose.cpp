#include "GameInfoChoose.h"


void GameInfoChoose::initVariables()
{
	this->mouseHeld = false;
	this->mouseIndication = false;
	this->isExecuted = false;
	this->isEnteringName = false;
	this->inputName = ""; 
}

void GameInfoChoose::initBackground()
{
	// Initializare background
	initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_Choosing_BackG, "ERROR::GameInfoChoose::Background inaccesibil!");

	initTex(this->background_Wi_Tex, path_Choosing_BackG_Wi, "ERROR::GameInfoChoose::Background_Wi inaccesibil!!");
	initTex(this->background_Wa_Tex, path_Choosing_BackG_Wa, "ERROR::GameInfoChoose::Background_Wa inaccesibil!!");
	initTex(this->background_R_Tex, path_Choosing_BackG_R, "ERROR::GameInfoChoose::Background_R inaccesibil!!");
}



void GameInfoChoose::initWarrior(const sf::Vector2u& size)
{

	//Initializare 
	initTexAndSpr(this->WarriorTex_1, this->WarriorSpr, path_Choosing_Warrior, "ERROR::GameInfoChoose::Warrior inaccesibil!");

	//Scalare
	this->WarriorSpr->scale(0.5f, 0.5f);
	//Setare pozitie
	float coeficient_x = size.x / 2;
	float coeficient_y = size.y / 2;
	this->WarriorSpr->setPosition(coeficient_x - coeficient_x / 1.5 + 50, coeficient_y - coeficient_y / 2.2);

	initTex(this->WarriorTex_2, path_Choosing_WarriorH, "ERROR::GameInfoChoose::WarriorH inaccesibil!!");
}

void GameInfoChoose::initWizard(const sf::Vector2u& size)
{
	//Initializare 
	initTexAndSpr(this->WizardTex_1, this->WizardSpr, path_Choosing_Wizard, "ERROR::GameInfoChoose::Wizard inaccesibil!");

	//Scalare
	this->WizardSpr->scale(0.5f, 0.5f);
	//Setare pozitie
	float coeficient_x = size.x / 2;
	float coeficient_y = size.y / 2;
	this->WizardSpr->setPosition(coeficient_x + coeficient_x / 4 + 50, coeficient_y - coeficient_y / 2.2);

	initTex(this->WizardTex_2, path_Choosing_WizardH, "ERROR::GameInfoChoose::WizardH inaccesibil!!");
}

void GameInfoChoose::initRogue(const sf::Vector2u& size)
{
	//Initializare 
	initTexAndSpr(this->RogueTex_1, this->RogueSpr, path_Choosing_Rogue, "ERROR::GameInfoChoose::Rogue inaccesibil!");

	//Scalare
	this->RogueSpr->scale(0.5f, 0.5f);
	//Setare pozitie
	float coeficient_x = size.x / 2;
	float coeficient_y = size.y / 2;
	this->RogueSpr->setPosition(coeficient_x - coeficient_x / 6.5 + 50, coeficient_y - coeficient_y / 2.2);

	initTex(this->RogueTex_2, path_Choosing_RogueH, "ERROR::GameInfoChoose::RogueH inaccesibil!!");
}

void GameInfoChoose::initFonts()
{
	this->font = std::make_unique<sf::Font>();

	if (!this->font->loadFromFile(path_Font_TimesNewRoman))
		std::cout << "ERROR::GameInfoChoose::INITFONTS::Failed to load font CopperPlateGothicLight!" << std::endl;
}

void GameInfoChoose::initText(const sf::Vector2u& size)
{
	this->uiText = std::make_unique<sf::Text>();

	this->uiText->setFont(*this->font);
	this->uiText->setCharacterSize(28);
	this->uiText->setFillColor(sf::Color::Black);
	this->uiText->setPosition(772.f, 857.f);
	this->uiText->setString("ENTER THE NAME");

	this->uiInputText = std::make_unique<sf::Text>();

	this->uiInputText->setFont(*this->font);
	this->uiInputText->setCharacterSize(28);
	this->uiInputText->setFillColor(sf::Color::Black);
	this->uiInputText->setPosition(762.f, 857.f);
}

//Constructor
GameInfoChoose::GameInfoChoose(const sf::Vector2u& size, const ActionResults& interact)
{
	this->initVariables();
	this->initBackground();
	this->initWarrior(size);
	this->initWizard(size);
	this->initRogue(size);
	this->initFonts();
	this->initText(size);
}

void GameInfoChoose::drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const
{
	target.draw(*this->backgroundSpr); 
	target.draw(*this->WarriorSpr); 
	target.draw(*this->WizardSpr);
	target.draw(*this->RogueSpr);

	if (this->backgroundSpr->getTexture() == backgroundTex.get()) //Daca pe ecran este afisat background-ul gol, atunci afisam uiText
		target.draw(*this->uiText); 

	if (this->isEnteringName)
		target.draw(*this->uiInputText); 
}

void GameInfoChoose::updatePollEvents(sf::RenderWindow& target, ActionResults& interact)
{
	if (!this->isEnteringName)
	{
		//Warrior
		if (this->WarriorSpr->getGlobalBounds().contains(getMousePosView(target)))
		{
			this->WarriorSpr->setTexture(*this->WarriorTex_2);
			this->backgroundSpr->setTexture(*this->background_Wa_Tex);
			this->mouseIndication = true;
		}
		else
		{
			this->WarriorSpr->setTexture(*this->WarriorTex_1);
		}

		//Wizard
		if (this->WizardSpr->getGlobalBounds().contains(getMousePosView(target)))
		{
			this->WizardSpr->setTexture(*this->WizardTex_2);
			this->backgroundSpr->setTexture(*this->background_Wi_Tex);
			this->mouseIndication = true;
		}
		else
		{
			this->WizardSpr->setTexture(*this->WizardTex_1);
		}

		//Rogue
		if (this->RogueSpr->getGlobalBounds().contains(getMousePosView(target)))
		{
			this->RogueSpr->setTexture(*this->RogueTex_2);
			this->backgroundSpr->setTexture(*this->background_R_Tex);
			this->mouseIndication = true;
		}
		else
		{
			this->RogueSpr->setTexture(*this->RogueTex_1);
		}
	}
	

	//'ENTER THE NAME' - schimbare culoare
	if (this->uiText->getGlobalBounds().contains(getMousePosView(target)) && !this->isEnteringName)
	{
		this->uiText->setFillColor(sf::Color::Blue);
	}
	else
	{
		this->uiText->setFillColor(sf::Color::Black);
	}

	//Daca nu este indicat nici un sprite, atunci setam fundalul implicit
	if (this->mouseIndication)
		this->mouseIndication = false; 
	else 
		this->backgroundSpr->setTexture(*this->backgroundTex);




	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;


			if (!this->isEnteringName)
			{
				//Daca pozitia mouse-lui nimereste atat in sprite-ul 'play' cat si in 'exit', atunci va 
				//fi ales sprite-ul care contine textura cu indicele 2
				if (this->WarriorSpr->getGlobalBounds().contains(getMousePosView(target)))
				{
					interact.sceneEnd = true;
					interact.clasaPlayer = CategoriePlayer::Warrior;
					return;
				}
				else if (this->RogueSpr->getGlobalBounds().contains(getMousePosView(target)))
				{
					interact.sceneEnd = true;
					interact.clasaPlayer = CategoriePlayer::Rogue;
					return;
				}
				else if (this->WizardSpr->getGlobalBounds().contains(getMousePosView(target)))
				{
					interact.sceneEnd = true;
					interact.clasaPlayer = CategoriePlayer::Wizard;
					return;
				}
			}

			if (this->uiText->getGlobalBounds().contains(getMousePosView(target)))
			{
				this->isEnteringName = true;

				this->uiText->setPosition(650.f, 857.f);
				this->uiText->setString("NAME:");
			}
			else
			{
				this->isEnteringName = false;
				
				this->uiText->setPosition(772.f, 857.f);
				this->uiText->setString("ENTER THE NAME");
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}


	//Daca a fost dat click dreapta pe 'ENTER THE NAME' atunci incepem sa citim de la tastatura
	if (this->isEnteringName)
	{
		this->uiInputText->setString(interact.playerName);
		interact.isEnteringText = this->isEnteringName; 
	}
}


