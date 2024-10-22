#include "GameInfoIntroBattle.h"



void GameInfoIntroBattle::initEnemy(const ActionResults& interact)
{
	std::random_device rd; 
	std::uniform_int_distribution<unsigned short> dist(1, 3); 
	unsigned short randomNum = dist(rd); 

	//randomNum = 3; 

	switch (static_cast<CategorieEnemy>(randomNum))
	{
		case CategorieEnemy::Ghoul: 
		{
			this->enemy = std::make_unique<Ghoul>(CategorieEnemy::Ghoul, 
						  enemyStats.at("Ghoul").health, enemyStats.at("Ghoul").attackPower, enemyStats.at("Ghoul").speedMovement);
			
			//Scalare
			this->enemy->setScaleIntroSpr(0.8f, 0.8f); 

			//Pozitionarea lui enemy in dependenta de locatia de lupta
			switch (interact.locatieLupta)
			{
			case BattleLocation::Cave: this->enemy->setPosIntroSpr(410.f, 550.f);
				break; 
			case BattleLocation::Forest: this->enemy->setPosIntroSpr(410.f, 550.f);
				break;
			case BattleLocation::Village: this->enemy->setPosIntroSpr(758.f, 575.f);
				break;

			default: std::cout << "ERROR::GameInfoIntroBattle::initEnemy::Locatie lupta incorecta!" << std::endl;
				break;
			}

		}break; 

		case CategorieEnemy::Troll:
		{
			this->enemy = std::make_unique<Troll>(CategorieEnemy::Troll, 
							enemyStats.at("Troll").health, enemyStats.at("Troll").attackPower, enemyStats.at("Troll").speedMovement);

			//Scalare
			this->enemy->setScaleIntroSpr(0.8f, 0.8f);

			//Pozitionarea lui enemy in dependenta de locatia de lupta
			switch (interact.locatieLupta)
			{
			case BattleLocation::Cave: this->enemy->setPosIntroSpr(410.f, 550.f);
				break;
			case BattleLocation::Forest: this->enemy->setPosIntroSpr(750.f, 520.f);
				break;
			case BattleLocation::Village: this->enemy->setPosIntroSpr(720.f, 500.f);
				break;

			default: std::cout << "ERROR::GameInfoIntroBattle::initEnemy::Locatie lupta incorecta!" << std::endl;
				break;
			}
		}break;

		case CategorieEnemy::Griffon:
		{
			this->enemy = std::make_unique<Griffon>(CategorieEnemy::Griffon, 
						  enemyStats.at("Griffon").health, enemyStats.at("Griffon").attackPower, enemyStats.at("Griffon").speedMovement);

			//Scalare
			this->enemy->setScaleIntroSpr(1.1f, 1.1f);

			//Pozitionarea lui enemy in dependenta de locatia de lupta
			switch (interact.locatieLupta)
			{
			case BattleLocation::Cave: this->enemy->setPosIntroSpr(410.f, 400.f);
				break;
			case BattleLocation::Forest: this->enemy->setPosIntroSpr(750.f, 380.f);
				break;
			case BattleLocation::Village: this->enemy->setPosIntroSpr(720.f, 400.f);
				break;

			default: std::cout << "ERROR::GameInfoIntroBattle::initEnemy::Locatie lupta incorecta!" << std::endl;
				break;
			}
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
			initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_IntroBattle_BackGCave, 
							"ERROR::GameInfoIntroBattle::Background inaccesibil!");
		}break;

		case BattleLocation::Forest:
		{
			initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_IntroBattle_BackGForest,
							"ERROR::GameInfoIntroBattle::Background inaccesibil!");
		}break;

		case BattleLocation::Village:
		{
			initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_IntroBattle_BackGVillage,
							"ERROR::GameInfoIntroBattle::Background inaccesibil!");
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
			initTexAndSpr(this->Text_DescriereLoc_Tex, TextSpr, path_IntroBattle_ForestDescrip,
							"ERROR::GameInfoIntroBattle::Descriere cave inaccesibil!");
			this->TextSpr->setPosition(149.f, 853.f);
		}break;

		case BattleLocation::Village:
		{
			initTexAndSpr(this->Text_DescriereLoc_Tex, TextSpr, path_IntroBattle_VillageDescrip,
							"ERROR::GameInfoIntroBattle::Descriere cave inaccesibil!");
			this->TextSpr->setPosition(149.f, 853.f);
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
			initTex(this->Text_MesajAtack_Tex, path_Troll_IntroMesajAtack,
					"ERROR::GameInfoIntroBattle::Mesaj atac ghoul inaccesibil!");

		}break;

		case CategorieEnemy::Griffon:
		{
			initTex(this->Text_MesajAtack_Tex, path_Griffon_IntroMesajAtack,
					"ERROR::GameInfoIntroBattle::Mesaj atac ghoul inaccesibil!");

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
	this->initEnemy(interact);
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
