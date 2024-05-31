#include "GameInfoIntroBattle.h"



void GameInfoIntroBattle::initEnemy()
{
	/*std::random_device rd; 
	std::uniform_int_distribution<unsigned short> dist(); 
	unsigned short randomNum = dist(rd); */

	unsigned short randomNum = 1; 

	switch (static_cast<CategorieEnemy>(randomNum))
	{
		case CategorieEnemy::Ghoul: 
		{
			this->enemy = std::make_unique<Ghoul>(CategorieEnemy::Ghoul, 100, 25, 2); 
			
			//Scalare si pozitionare intrSprite
			this->enemy->setScaleIntroSpr(0.8f, 0.8f); 
			this->enemy->setPosIntroSpr(410.f, 550.f); 

		}break; 

		case CategorieEnemy::Troll:
		{

		}break;

		case CategorieEnemy::Griffon:
		{

		}break;

		default:
		{
			std::cout << "ERROR::GameInfoIntroBattle::initEnemy::Categorie enemy incorect aleasa!" << std::endl;
		}break;
	}
}

void GameInfoIntroBattle::initVariables()
{
	this->continueCount = 0; 
	this->isTextReseted = false; 
	this->isEnemyAttacking = false; 
	this->mouseHeld = false; 
}

void GameInfoIntroBattle::initBackground(const ActionResults& interact)
{
	// Initializare background
	switch (interact.locatieLupta)
	{
		case BattleLocation::Cave: 
		{
			initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_IntroBattle_BackG, 
							"ERROR::GameInfoIntroBattle::Background inaccesibil!");
		}break;

		case BattleLocation::Forest:
		{

		}break;

		case BattleLocation::Village:
		{

		}break;

		default:
		{
			std::cout << "Locatie lupta incorecta!" << std::endl;
		}break;
	}
}

void GameInfoIntroBattle::initText(const ActionResults& interact)
{
	//Initializare text
	switch (interact.locatieLupta)
	{
		case BattleLocation::Cave:
		{
			initTexAndSpr(this->Text_DescriereLoc_Tex, TextSpr, path_IntroBattle_CaveDescrip, 
							"ERROR::GameInfoIntroBattle::Descriere cave inaccesibil!");
			this->TextSpr->setPosition(149.f, 853.f); 

		}break;

		case BattleLocation::Forest:
		{

		}break;

		case BattleLocation::Village:
		{

		}break;

		default:
		{
			std::cout << "Locatie lupta incorecta!" << std::endl;
		}break;
	}

	switch (this->enemy->getCategorie())
	{
		case CategorieEnemy::Ghoul: 
		{
			initTex(this->Text_MesajAtack_Tex, path_Ghoul_IntroMesajAtack,
					"ERROR::GameInfoIntroBattle::Mesaj atac ghoul inaccesibil!"); 
		}break; 

		case CategorieEnemy::Troll:
		{

		}break;

		case CategorieEnemy::Griffon:
		{

		}break;
	}
}

void GameInfoIntroBattle::initContinue()
{
	//Initializare 
	initTexAndSpr(this->continueTex_1, this->continueSpr, path_continue, "ERROR::GameIntroInfo_2::Continue inaccesibil!");

	//Scalare
	this->continueSpr->scale(0.2f, 0.2f);
	//Setare pozitie
	this->continueSpr->setPosition(1585.f, 853.f);

	initTex(this->continueTex_2, path_continueH, "ERROR::GameIntroInfo_2::continue_mouseHeld inaccesibil!");
}


//Constructor
GameInfoIntroBattle::GameInfoIntroBattle(const sf::Vector2u& size, const ActionResults& interact)
{
	this->initEnemy();
	this->initVariables();
	this->initBackground(interact);
	this->initText(interact);
	this->initContinue();
}

void GameInfoIntroBattle::drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const
{
	target.draw(*this->backgroundSpr);
	target.draw(*this->TextSpr);
	target.draw(*this->continueSpr);

	if (this->isEnemyAttacking)
		target.draw(this->enemy->getIntroSprite()); 
}

void GameInfoIntroBattle::updatePollEvents(sf::RenderWindow& target, ActionResults& interact)
{
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

			if (this->continueSpr->getGlobalBounds().contains(getMousePosView(target)))
			{
				this->isEnemyAttacking = true; 
				this->continueCount++; 
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}

	if (this->continueCount == 1 && !this->isTextReseted)
	{
		this->TextSpr.reset(); 
		this->TextSpr = std::make_unique<sf::Sprite>(); 
		this->TextSpr->setTexture(*this->Text_MesajAtack_Tex);
		this->TextSpr->setPosition(500.f, 900.f);
		this->isTextReseted = true; 
	}
	else if (this->continueCount == 2)
	{
		interact.sceneEnd = true; //Iesirea din scena IntroBattle
		interact.enemy = this->enemy; //Transmitem this->enemy catre scena urmatoare de lupta
									  //Nu este unique_ptr si nu se foloseste std::move(), fiindca
									  //dupa ce continueCound devine 2, enemy-ul poate inca fi nesar in scena data pana muzica se reseteaza
	}
}
