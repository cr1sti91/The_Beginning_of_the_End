#include "GameCrossRoads.h"

void GameCrossRoads::initVariables()
{
	this->mouseHeld = false; 
	this->isExecuted = false; 

	this->isPlayerSprSeted = false; 

	this->goToCave = false; 
	this->goToForest = false; 
	this->goToVillage = false; 

	this->isInTheCenter = false;
	this->isChestScene = false;
	this->afterChestScene = false; 
	this->isChestReseted = false;
	this->isChestOpen = std::nullopt; 

	this->isAtTheDestination = false; 

	this->center_x = 865;
	this->center_y = 370;

	this->forest_x = 700; 
	this->forest_y = 516.53;

	this->cave_x = 624;
	this->cave_y = 156;

	this->village_x = 1003;
	this->village_y = 250;
}

void GameCrossRoads::initBackground()
{
	initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_CrossRoads_BackG, 
					"ERROR::GameCrossRoads::Background inaccesibil!");
	initTex(this->backgroundTex_chestScene, path_CrossRoads_BackG_chest,
					"ERROR::GameCrossRoads::Background chest inaccesibil!!");
}

void GameCrossRoads::initPlayerSpr()
{
	this->playerSpr = std::make_unique<sf::Sprite>(); 
	this->playerSpr->setPosition(1180.f, 650.f); //Incepem din locatia campul de lupta
}

void GameCrossRoads::initCaveInscription()
{
	//Initializare 
	initTexAndSpr(this->caveInscriptionTex_1, this->caveInscriptionSpr, path_caveInscription, 
					"ERROR::GameCrossRoads::Cave inscription_1 inaccesibil!");

	//Scalare
	this->caveInscriptionSpr->scale(0.4f, 0.4f);
	//Setare pozitie
	this->caveInscriptionSpr->setPosition(160.f, 226.f);

	initTex(this->caveInscriptionTex_2, path_caveInscription_mouseH, 
					"ERROR::GameCrossRoads::Cave inscription_2 inaccesibil!!");
	initTex(this->caveInscriptionTex_3, path_caveInscription_choosed,
					"ERROR::GameCrossRoads::Cave inscription_3 inaccesibil!!");
}

void GameCrossRoads::initForestInscription()
{
	//Initializare 
	initTexAndSpr(this->forestInscriptionTex_1, this->forestInscriptionSpr, path_forestInscription, 
					"ERROR::GameCrossRoads::Forest inscription_1 inaccesibil!");

	//Scalare
	this->forestInscriptionSpr->scale(0.5f, 0.5f);
	//Setare pozitie
	this->forestInscriptionSpr->setPosition(160.f, 705.f);

	initTex(this->forestInscriptionTex_2, path_forestInscription_mouseH, 
					"ERROR::GameCrossRoads::Forest inscription_2 inaccesibil!!");
	initTex(this->forestInscriptionTex_3, path_forestInscription_choosed,
					"ERROR::GameCrossRoads::Forest inscription_3 inaccesibil!!");
}

void GameCrossRoads::initVillageInscription()
{
	//Initializare 
	initTexAndSpr(this->villageInscriptionTex_1, this->villageInscriptionSpr, path_villageInscription, 
					"ERROR::GameCrossRoads::Village inscription_1 inaccesibil!");

	//Scalare
	this->villageInscriptionSpr->scale(0.5f, 0.5f);
	//Setare pozitie
	this->villageInscriptionSpr->setPosition(1414.f, 226.f);

	initTex(this->villageInscriptionTex_2, path_villageInscription_mouseH, 
					"ERROR::GameCrossRoads::village inscription_2 inaccesibil!!");
	initTex(this->villageInscriptionTex_3, path_villageInscription_choosed,
					"ERROR::GameCrossRoads::village inscription_3 inaccesibil!!");
}

void GameCrossRoads::initChest()
{
	//Initializare 
	initTexAndSpr(this->chestTex_1, this->chestSpr, path_CrossRoads_Chest,
					"ERROR::GameCrossRoads::Chest inaccesibil!");

	//Scalare
	this->chestSpr->scale(0.8f, 0.8f);
	//Setare pozitie
	this->chestSpr->setPosition(600.f, 100.f);

	initTex(this->chestTex_2, path_CrossRoads_ChestOpen, "ERROR::GameCrossRoads::ChestOpen inaccesibil!");
}

void GameCrossRoads::initOpen()
{
	//Initializare 
	initTexAndSpr(this->OpenTex_1, this->OpenSpr, path_CrossRoads_Open,
					"ERROR::GameCrossRoads::'Open' inaccesibil!");

	//Scalare
	this->OpenSpr->scale(0.4f, 0.4f);
	//Setare pozitie
	this->OpenSpr->setPosition(813.f, 607.f);

	initTex(this->OpenTex_2, path_CrossRoads_Open_mouseH, "ERROR::GameCrossRoads::'Open' mouse held inaccesibil!");
}


void GameCrossRoads::initAddedItem()
{
	this->addedItem = std::make_unique<sf::Sprite>(); 
}


void GameCrossRoads::initSkip()
{
	//Initializare 
	initTexAndSpr(this->SkipTex_1, this->SkipSpr, path_CrossRoads_Skip,
					"ERROR::GameCrossRoads::'Skip' inaccesibil!");

	//Scalare
	this->SkipSpr->scale(0.4f, 0.4f);
	//Setare pozitie
	this->SkipSpr->setPosition(813.f, 750.f);

	initTex(this->SkipTex_2, path_CrossRoads_Skip_mouseH, "ERROR::GameCrossRoads::'Skip' mouse held inaccesibil!");
}

void GameCrossRoads::initChestInfo()
{
	//Initializare 
	initTexAndSpr(this->chestInfoTex_1, this->chestInfoSpr, path_CrossRoads_ChestInfo_1,
					"ERROR::GameCrossRoads::ChestInfo_1 inaccesibil!");

	//Setare pozitie
	this->chestInfoSpr->setPosition(450.f, 940.f);

	initTex(this->chestInfoTex_2_fireball, path_CrossRoad_ChestInfo_2_fireball, "ERROR::GameCrossRoads::Info fireball inaccesibil!");
	initTex(this->chestInfoTex_2_iceball, path_CrossRoad_ChestInfo_2_iceball, "ERROR::GameCrossRoads::Info iceball inaccesibil!");
}


void GameCrossRoads::initContinue(const sf::Vector2u& size)
{
	//Initializare 
	initTexAndSpr(this->continueTex_1, this->continueSpr, path_continue, "ERROR::GameCrossRoads::Continue inaccesibil!");

	//Scalare
	this->continueSpr->scale(0.2f, 0.2f);
	//Setare pozitie
	float coeficient_x = size.x / 2;
	float coeficient_y = size.y / 2;
	this->continueSpr->setPosition(coeficient_x + coeficient_x / 1.3, coeficient_y + coeficient_y / 1.5);

	initTex(this->continueTex_2, path_continueH, "ERROR::GameCrossRoads::continue_mouseHeld inaccesibil!");
}



//Constructor
GameCrossRoads::GameCrossRoads(const sf::Vector2u& size, const ActionResults& interact)
{
	this->initVariables();
	this->initBackground();

	this->initChest();
	this->initChestInfo();
	this->initOpen();
	this->initAddedItem();
	this->initSkip();
	this->initContinue(size);

	this->initPlayerSpr();
	this->initCaveInscription();
	this->initForestInscription();
	this->initVillageInscription();
}

void GameCrossRoads::drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const
{
	target.draw(*this->backgroundSpr); 

	if (!this->isChestScene)
	{
		target.draw(*this->playerSpr);
		target.draw(*this->caveInscriptionSpr);
		target.draw(*this->forestInscriptionSpr);
		target.draw(*this->villageInscriptionSpr);
	}
	else if (!this->isChestOpen.has_value())
	{
		target.draw(*this->chestSpr); 
		target.draw(*this->OpenSpr);
		target.draw(*this->SkipSpr);
		target.draw(*this->chestInfoSpr); 
	}
	else if (this->isChestOpen.value())
	{
		target.draw(*this->chestSpr);
		target.draw(*this->addedItem); //Desenam sprite-ul ultimului
									   //item adaugat in inventar
		target.draw(*this->chestInfoSpr);
		target.draw(*this->continueSpr); 
	}
}




void GameCrossRoads::updatePollEvents(sf::RenderWindow& target, ActionResults& interact)
{
	this->setPlayerSprite(interact); //Poate fi desenat direct sprite-ul in metoda 'drawGameInfo'

	if (!this->isExecuted)
	{
		//Cave - schimbare culoare
		if (this->caveInscriptionSpr->getGlobalBounds().contains(getMousePosView(target)))
		{
			this->caveInscriptionSpr->setTexture(*this->caveInscriptionTex_2);
		}
		else
		{
			this->caveInscriptionSpr->setTexture(*this->caveInscriptionTex_1);
		}

		//Forest - schimbare culoare
		if (this->forestInscriptionSpr->getGlobalBounds().contains(getMousePosView(target)))
		{
			this->forestInscriptionSpr->setTexture(*this->forestInscriptionTex_2);
		}
		else
		{
			this->forestInscriptionSpr->setTexture(*this->forestInscriptionTex_1);
		}

		//Village - schimbare culoare
		if (this->villageInscriptionSpr->getGlobalBounds().contains(getMousePosView(target)))
		{
			this->villageInscriptionSpr->setTexture(*this->villageInscriptionTex_2);
		}
		else
		{
			this->villageInscriptionSpr->setTexture(*this->villageInscriptionTex_1);
		}
	}
	else
	{
		if (goToCave)
			this->caveInscriptionSpr->setTexture(*this->caveInscriptionTex_3);
		else if (goToForest)
			this->forestInscriptionSpr->setTexture(*this->forestInscriptionTex_3);
		else if (goToVillage)
			this->villageInscriptionSpr->setTexture(*this->villageInscriptionTex_3);
	}

	//Open - schimbare culoare
	if (this->OpenSpr->getGlobalBounds().contains(getMousePosView(target)))
	{
		this->OpenSpr->setTexture(*this->OpenTex_2);
	}
	else
	{
		this->OpenSpr->setTexture(*this->OpenTex_1);
	}

	//Skip - schimbare culoare
	if (this->SkipSpr->getGlobalBounds().contains(getMousePosView(target)))
	{
		this->SkipSpr->setTexture(*this->SkipTex_2);
	}
	else
	{
		this->SkipSpr->setTexture(*this->SkipTex_1);
	}

	//Continue - schimbare culoare
	if (this->continueSpr->getGlobalBounds().contains(getMousePosView(target)))
	{
		this->continueSpr->setTexture(*this->continueTex_2);
	}
	else
	{
		this->continueSpr->setTexture(*this->continueTex_1);
	}
	

	//Verificare click stanga
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;

			if (this->caveInscriptionSpr->getGlobalBounds().contains(getMousePosView(target)) && !this->isExecuted)
			{
				this->goToCave = true; 
				this->isExecuted = true; 
				interact.locatieLupta = BattleLocation::Cave; 
			}
			else if (this->forestInscriptionSpr->getGlobalBounds().contains(getMousePosView(target)) && !this->isExecuted)
			{
				this->goToForest = true;
				this->isExecuted = true;
				interact.locatieLupta = BattleLocation::Forest;
			}
			else if (this->villageInscriptionSpr->getGlobalBounds().contains(getMousePosView(target)) && !this->isExecuted)
			{
				this->goToVillage = true;
				this->isExecuted = true;
				interact.locatieLupta = BattleLocation::Village;
			}
			

			//Verificare pentru deschiderea chest-ului
			if (this->OpenSpr->getGlobalBounds().contains(getMousePosView(target)) && !this->isChestOpen.has_value())
			{
				this->isChestOpen = true; 
			}
			else if (this->SkipSpr->getGlobalBounds().contains(getMousePosView(target)) && !this->isChestOpen.has_value())
			{
				this->isChestOpen = false; 
			}

			//Verificare pentru 'continue'
			if (this->continueSpr->getGlobalBounds().contains(getMousePosView(target)) && !this->afterChestScene)
			{
				this->afterChestScene = true;
				this->isChestScene = false;

				this->isPlayerSprSeted = false; //Player-ul poate sa is schimbe directia, deci si sprite-ul trebuie modificat

				this->backgroundSpr->setTexture(*this->backgroundTex);
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}


	this->deplasareSpreCufar(); 
	this->deplasareSpreDestinatie(); 
	


	//Trecerea la scena cu cufarul 
	if (!this->isChestScene && this->isInTheCenter && !this->afterChestScene)
		this->isChestScene = true; 

	//Nu poate fi unit cu conditia de mai sus pentru ca in acest caz nu vom putea inchide chest scene
	if (isChestScene)
	{
		this->isChestScene = true;

		this->backgroundSpr->setTexture(*this->backgroundTex_chestScene);

		if (this->isChestOpen.has_value())
		{
			if (this->isChestOpen.value() && !this->isChestReseted)
			{
				this->chestSpr.reset(); 
				this->chestSpr = std::make_unique<sf::Sprite>(); 
				this->chestSpr->setTexture(*this->chestTex_2); 
				//Scalare
				this->chestSpr->scale(0.6f, 0.6f);
				//Setare pozitie
				this->chestSpr->setPosition(600.f, 100.f);

				this->isChestReseted = true; 

				//Adaugam in inventar obiectul generat la deschiderea chest-ului
				bool adaugat = false; 
				do
				{
					while (!adaugat) //cat timp item-ul generat random se intalneste deja in inventar, repetam generarea
					{
						//metoda 'generateItem' returneaza un unique_ptr temporar, astfel ca pentru siguranta utilizam std::move() sa 
						//mutam adresa din el catre parametrul metodei 'addItems'
						adaugat = interact.player->addItems(std::move(interact.player->generateItem())); 
					}

					*this->addedItem = *interact.player->getInvetar().at(interact.player->getInvetar().size() - 1)->getSprite(); 
					this->addedItem->setPosition(1050.f, 700.f); 
					this->addedItem->setRotation(90); 

					////////////////////////////////////////////////
					//In dependenta de item trebie setata o scalare individuala
					this->addedItem->setScale(1.f, 1.f); 

					//Chest info reset
					switch (interact.player->getInvetar().at(interact.player->getInvetar().size() - 1)->getTipItem())
					{
						case TypeItem::FireBall: 
						{
							this->chestInfoSpr->setTexture(*this->chestInfoTex_2_fireball);
						}break; 

						case TypeItem::IceBall: 
						{
							this->chestInfoSpr->setTexture(*this->chestInfoTex_2_iceball);
						}break; 

						default:
							std::cout << "ERROR::GameCrossRoads::updatePollEvents::Tip item incorect!" << std::endl;
							break;
					}

				} while (!adaugat); 
			}
			else if (!this->isChestOpen.value() && !this->afterChestScene) //Daca cufarul este inchis (a fost dat skip)
			{
				this->afterChestScene = true; 
				this->isChestScene = false; 

				this->isPlayerSprSeted = false; //Player-ul poate sa is schimbe directia, deci si sprite-ul trebuie modificat

				this->backgroundSpr->setTexture(*this->backgroundTex);
			}
		}
	}


	//Daca este ajuns la destinatie, scena GameCrossRoads este finisata 
	if (this->isAtTheDestination)
		interact.sceneEnd = true; //Iesirea din scena
}



void GameCrossRoads::setPlayerSprite(ActionResults& interact)
{
	//Setam sprite-ul player-ului
	if ((!this->afterChestScene || this->goToCave) && !this->isPlayerSprSeted)
	{
		this->playerSpr->setTexture(interact.player->getToCaveTexture());  //Cave texture este identica cu cea de deplasare spre centru
		this->isPlayerSprSeted = true;

		switch (interact.player->getCategorie())
		{
		case CategoriePlayer::Warrior:
		{
			this->playerSpr->setScale(0.5f, 0.5f);
		} break;
		case CategoriePlayer::Rogue:
		{
			this->playerSpr->setScale(0.4f, 0.4f);
		} break;
		case CategoriePlayer::Wizard:
		{
			this->playerSpr->setScale(0.5f, 0.5f);
		} break;
		default:
			break;
		}
	}
	else if (this->afterChestScene && this->goToForest && !this->isPlayerSprSeted)
	{
		this->playerSpr = std::make_unique<sf::Sprite>();
		this->playerSpr->setTexture(interact.player->getToForestTexture());
		this->playerSpr->setPosition(this->center_x, this->center_y);
		this->isPlayerSprSeted = true;

		switch (interact.player->getCategorie())
		{
		case CategoriePlayer::Warrior:
		{
			this->playerSpr->setScale(0.46f, 0.46f);
		} break;
		case CategoriePlayer::Rogue:
		{
			this->playerSpr->setScale(0.35f, 0.35f);
		} break;
		case CategoriePlayer::Wizard:
		{
			this->playerSpr->setScale(0.46f, 0.46f);
		} break;
		default:
			break;
		}
	}
	else if (this->afterChestScene && this->goToVillage && !this->isPlayerSprSeted)
	{
		this->playerSpr = std::make_unique<sf::Sprite>();
		this->playerSpr->setTexture(interact.player->getToVillageTexture());
		this->playerSpr->setPosition(this->center_x, this->center_y);
		this->isPlayerSprSeted = true;

		switch (interact.player->getCategorie())
		{
		case CategoriePlayer::Warrior:
		{
			this->playerSpr->setScale(0.5f, 0.5f);
		} break;
		case CategoriePlayer::Rogue:
		{
			this->playerSpr->setScale(0.4f, 0.4f);
		} break;
		case CategoriePlayer::Wizard:
		{
			this->playerSpr->setScale(0.5f, 0.5f);
		} break;
		default:
			break;
		}
	}
}

void GameCrossRoads::deplasareSpreCufar()
{
	//DEPLASAREA SPRE CENTRU (SPRE CUFAR)
	if (this->isExecuted && !this->isInTheCenter)
	{
		if (this->playerSpr->getPosition().x > this->center_x)
		{
			this->playerSpr->move(-1.126f, 0.f);
			this->isInTheCenter = false;
		}
		else
		{
			this->isInTheCenter = true;
		}

		if (this->playerSpr->getPosition().y > this->center_y)
		{
			this->playerSpr->move(0.f, -1.f);
			this->isInTheCenter = false;
		}
		else if (!this->isInTheCenter)
		{
			this->isInTheCenter = false;
		}
		else
		{
			this->isInTheCenter = true;
		}
	}
}

void GameCrossRoads::deplasareSpreDestinatie()
{
	if (this->afterChestScene && !this->isAtTheDestination)
	{
		if (this->goToCave)
		{
			if (this->playerSpr->getPosition().x > this->cave_x)
			{
				this->playerSpr->move(-1.126f, 0.f);
				this->isAtTheDestination = false;
			}
			else
			{
				this->isAtTheDestination = true;
			}

			if (this->playerSpr->getPosition().y > this->cave_y)
			{
				this->playerSpr->move(0.f, -1.f);
				this->isAtTheDestination = false;
			}
			else if (!this->isAtTheDestination)
			{
				this->isAtTheDestination = false;
			}
			else
			{
				this->isAtTheDestination = true;
			}
		}
		else if (this->goToForest)
		{
			if (this->playerSpr->getPosition().x > this->forest_x)
			{
				this->playerSpr->move(-1.126f, 0.f);
				this->isAtTheDestination = false;
			}
			else
			{
				this->isAtTheDestination = true;
			}

			if (this->playerSpr->getPosition().y < this->forest_y)
			{
				this->playerSpr->move(0.f, 1.f);
				this->isAtTheDestination = false;
			}
			else if (!this->isAtTheDestination)
			{
				this->isAtTheDestination = false;
			}
			else
			{
				this->isAtTheDestination = true;
			}
		}
		else if (this->goToVillage)
		{
			if (this->playerSpr->getPosition().x < this->village_x)
			{
				this->playerSpr->move(1.126f, 0.f);
				this->isAtTheDestination = false;
			}
			else
			{
				this->isAtTheDestination = true;
			}

			if (this->playerSpr->getPosition().y > this->village_y)
			{
				this->playerSpr->move(0.f, -1.f);
				this->isAtTheDestination = false;
			}
			else if (!this->isAtTheDestination)
			{
				this->isAtTheDestination = false;
			}
			else
			{
				this->isAtTheDestination = true;
			}
		}
	}
}

