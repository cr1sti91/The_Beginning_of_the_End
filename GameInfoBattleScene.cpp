#include "GameInfoBattleScene.h"

void GameInfoBattleScene::initFont()
{
	this->font = std::make_unique<sf::Font>(); 

	if (!this->font->loadFromFile("Fonts/arial.ttf"))
		std::cout << "ERROR::GameInfoBattleScene::initFont::Failed to load font!" << std::endl;
}

void GameInfoBattleScene::initText(const ActionResults& interact)
{
	this->uiText_PlayerName = std::make_unique<sf::Text>();
	this->uiText_PlayerHealth = std::make_unique<sf::Text>();
	
	for (int i{}; i < interact.player->getInvetar().size(); i++)
	{
		this->itemsFromInventar.push_back(std::make_unique<sf::Text>()); 

		this->itemsFromInventar.at(i)->setFont(*this->font); 
		this->itemsFromInventar.at(i)->setCharacterSize(22);
		this->itemsFromInventar.at(i)->setFillColor(sf::Color::Green);
		this->itemsFromInventar.at(i)->setPosition(45.f, 150.f + 30 * (i + 1));
		this->itemsFromInventar.at(i)->setString(Item::typeItemToStr(interact.player->getInvetar().at(i)->getTipItem()));
	}
	
	this->uiText_PlayerName->setFont(*this->font);
	this->uiText_PlayerName->setCharacterSize(30);
	this->uiText_PlayerName->setFillColor(sf::Color::Yellow);
	this->uiText_PlayerName->setPosition(25.f, 50.f);
	this->uiText_PlayerName->setString(interact.player->get_playerName()); 

	this->uiText_PlayerHealth->setFont(*this->font);
	this->uiText_PlayerHealth->setCharacterSize(22);
	this->uiText_PlayerHealth->setFillColor(sf::Color::Green);
	this->uiText_PlayerHealth->setPosition(25.f, 100.f);


	this->uiText_EnemyName = std::make_unique<sf::Text>();
	this->uiText_EnemyHealth = std::make_unique<sf::Text>();

	this->uiText_EnemyName->setFont(*this->font);
	this->uiText_EnemyName->setCharacterSize(30);
	this->uiText_EnemyName->setFillColor(sf::Color::Yellow);
	this->uiText_EnemyName->setPosition(1630.f, 50.f);

	switch (interact.enemy->getCategorie())
	{
	case CategorieEnemy::Ghoul: this->uiText_EnemyName->setString("Ghoul");
		break;
	case CategorieEnemy::Troll: this->uiText_EnemyName->setString("Troll");
		break;
	case CategorieEnemy::Griffon: this->uiText_EnemyName->setString("Griffon");
		break;

	default:
		std::cout << "ERROR::GameInfoBattleScene::initText::Categori enemy incorecta!" << std::endl;
		break;
	}

	this->uiText_EnemyHealth->setFont(*this->font);
	this->uiText_EnemyHealth->setCharacterSize(22);
	this->uiText_EnemyHealth->setFillColor(sf::Color::Green);
	this->uiText_EnemyHealth->setPosition(1630.f, 100.f);
}

void GameInfoBattleScene::initTime()
{
	this->timePoint = sf::Time::Zero;
	this->cooldownTime = sf::seconds(0.4f); 
}

void GameInfoBattleScene::initLimits()
{
	this->min_x = 310; 
	this->max_x = 1440; 
	this->min_y = 150; 
	this->max_y = 850; 
}

void GameInfoBattleScene::initVariables(const ActionResults& interact)
{
	this->keyWasPressed = false;
	this->x_modified = false;
	this->y_modified = false;
	this->mouseHeld = false; 
	this->keyHeld = false; 

	this->enemyWasAttacked = false; 
	this->newEnemyAttack = true; 

	this->itemChanged = false; 

	this->isCloseAttack = false; 
	this->isHoldClosedAttack = false; 
	
	//In mod implicit, este folosit primul item din inventar
	if (interact.player->getInvetar().size() != 0)
		this->currentItem = interact.player->getInvetar().at(0);
	else
		this->currentItem = nullptr;
}

void GameInfoBattleScene::initBackground(const ActionResults& interact)
{
	// Initializare background
	switch (interact.locatieLupta)
	{
		case BattleLocation::Cave:
		{
			initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_BattleScene_BackGCave,
				"ERROR::GameInfoBattleScene::Background inaccesibil!");
		}break;

		case BattleLocation::Forest:
		{
			initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_BattleScene_BackGForest,
				"ERROR::GameInfoBattleScene::Background inaccesibil!");
		}break;

		case BattleLocation::Village:
		{
			initTexAndSpr(this->backgroundTex, this->backgroundSpr, path_BattleScene_BackGVillage,
				"ERROR::GameInfoBattleScene::Background inaccesibil!");
		}break;

		default:
		{
			std::cout << "Locatie lupta incorecta!" << std::endl;
		}break;
	}
}



//Constructor
GameInfoBattleScene::GameInfoBattleScene(const sf::Vector2u& size, const ActionResults& interact)
{
	this->initFont();
	this->initText(interact);
	this->initTime();
	this->initLimits();
	this->initVariables(interact);
	this->initBackground(interact);
}


void GameInfoBattleScene::drawGameInfo(sf::RenderTarget& target, ActionResults& interact) const
{
	target.draw(*this->backgroundSpr); 

	target.draw(*this->uiText_PlayerName);
	target.draw(*this->uiText_EnemyName);

	target.draw(*this->uiText_PlayerHealth);
	target.draw(*this->uiText_EnemyHealth);

	for (const auto& itemName : this->itemsFromInventar)
	{
		target.draw(*itemName); 
	}
	
	target.draw(interact.player->getPlayerSpr());
	target.draw(interact.enemy->getBattleSprite());

	for (auto& projectile : this->projectilesPlayer)
	{
		target.draw(*projectile->getSprite()); 
	}

	for (auto& projectile : this->projectilesEnemy)
	{
		target.draw(*projectile->getSprite());
	}
}

void GameInfoBattleScene::updatePollEvents(sf::RenderWindow& target, ActionResults& interact)
{
	//Move player
	this->movePlayer(interact); 

	//Rotate player
	this->rotatePlayer(target, interact); 

	//Player attack
	this->thePlayersAttack(target, interact); 

	//Resetare
	this->keyWasPressed = false; //Conteaza doar pentru player

	//Move projectiles
	this->moveProjectiles(target); 

	//IEnemy is attacked
	this->enemyGetAttacked(interact); 

	//Enemy is moving or is wainting
	this->moveEnemy(interact); 

	//Enemy is attacking
	this->enemyAttack(interact); 	

	//Player is attacked
	this->playerGetAttacked(interact); 

	//Update text
	this->updateUiText(interact); 


	this->checkStatus(interact); 
}





void GameInfoBattleScene::movePlayer(ActionResults& interact)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		if (interact.player->getPosition().x > this->min_x)
		{
			interact.player->move(-1.f, 0.f);
			if (pixelPerfectCollision(interact.player->getPlayerSpr(), interact.enemy->getBattleSprite()))
				interact.player->move(1.f, 0.f);
		}
		interact.dir_x = -1;
		this->keyWasPressed = true;
		this->x_modified = true;
	}
	else
	{
		interact.dir_x = 0;
		this->x_modified = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (interact.player->getPosition().x < this->max_x)
		{
			interact.player->move(1.f, 0.f);
			if (pixelPerfectCollision(interact.player->getPlayerSpr(), interact.enemy->getBattleSprite()))
				interact.player->move(-1.f, 0.f);
		}
		interact.dir_x = 1;
		this->keyWasPressed = true;
	}
	else if (!this->x_modified)
	{  
		interact.dir_x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (interact.player->getPosition().y > this->min_y)
		{
			interact.player->move(0.f, -1.f);
			if (pixelPerfectCollision(interact.player->getPlayerSpr(), interact.enemy->getBattleSprite()))
				interact.player->move(0.f, 1.f);
		}
		interact.dir_y = 1;
		this->keyWasPressed = true;
		this->y_modified = true;
	}
	else
	{
		interact.dir_y = 0;
		this->y_modified = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (interact.player->getPosition().y < this->max_y)
		{
			interact.player->move(0.f, 1.f);
			if (pixelPerfectCollision(interact.player->getPlayerSpr(), interact.enemy->getBattleSprite()))
				interact.player->move(0.f, -1.f);
		}
		interact.dir_y = -1;
		this->keyWasPressed = true;
	}
	else if (!this->y_modified)
	{
		interact.dir_y = 0;
	}
}




void GameInfoBattleScene::rotatePlayer(const sf::RenderWindow& target, ActionResults& interact)
{
	if (this->keyWasPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		interact.player->setSpriteDirection(interact.dir_x, interact.dir_y);
		this->mouseHeld = false;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->mouseHeld)
	{
		interact.player->setSpriteDirection(0, 0);
		interact.player->setRotation(calculateAngle(getMousePosView(target), interact.player->getPosition()));
	}
	else
	{
		this->mouseHeld = false;
	}
}

void GameInfoBattleScene::thePlayersAttack(const sf::RenderWindow& target, ActionResults& interact)
{
	//Fiindca este conditia 'this->currentItem != nullptr', orice player trebuie sa detina in inventar
	//cel putin un item pentru ca metoda 'rotatePlayer' sa functioneze corect (este dependenta de 'mouseHeld').
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->currentItem != nullptr)
	{
		if (this->currentItem->getTipItem() == TypeItem::FireBall ||
			this->currentItem->getTipItem() == TypeItem::IceBall  ||
			this->currentItem->getTipItem() == TypeItem::Knive    ||
			this->currentItem->getTipItem() == TypeItem::Spear)
		{
			if (this->clock.getElapsedTime() - this->timePoint > this->cooldownTime && this->keyWasPressed)
			{
				this->timePoint = this->clock.getElapsedTime();

				this->mouseHeld = true;

				interact.player->attack(this->projectilesPlayer, this->currentItem->getTipItem(),
					calculateAngle(getMousePosView(target), interact.player->getPosition()),
					interact.player->getPlayerSpr().getTransform().transformPoint(210.f, 124));
			}
			else if (!this->mouseHeld && !this->keyWasPressed) //Player-ul nu se deplaseaza
			{
				this->mouseHeld = true;

				interact.player->attack(this->projectilesPlayer, this->currentItem->getTipItem(),
					calculateAngle(getMousePosView(target), interact.player->getPosition()),
					interact.player->getPlayerSpr().getTransform().transformPoint(210.f, 124));
			}
			//'sprite.getTransform().transformPoint()' returneaza adresa (Vector2f) punctului (210, 124) ce se afla pe sprite in  
			//coordonatele window-ului dupa ce a avut loc ultima transforamare (aplicare a unei matrici 3x3 asupra sprite-ului dat).
			//In acest mod, fireballurile vor fi create la adresa actualizata a punctului de pe sprite. 
		}
		else if (this->currentItem->getTipItem() == TypeItem::Sword)
		{
		if (this->clock.getElapsedTime() - this->timePoint > this->cooldownTime && !this->mouseHeld)
			{
				this->timePoint = this->clock.getElapsedTime();

				this->mouseHeld = true;

				interact.player->attack(this->projectilesPlayer, this->currentItem->getTipItem(),
										calculateAngle(getMousePosView(target), interact.player->getPosition()),
										interact.player->getPlayerSpr().getTransform().transformPoint(210.f, 124));

				

				sf::Sprite swordSpr = interact.player->getPlayerSpr(); 
				swordSpr.setTextureRect(interact.player->getInvetar().at(0)->getItemLimits()); //Sword-ul va fi cu indexul 0

				if (pixelPerfectCollision(swordSpr, interact.enemy->getBattleSprite()) && !this->isHoldClosedAttack)
				{
					this->isCloseAttack = true; 
				}
			}
			else
			{
				interact.player->stopAttack(); 
			}
		}
	}
	else
	{
		this->mouseHeld = false;
		this->isHoldClosedAttack = false; 
		
		//Stop attack
		interact.player->stopAttack(); 
	}

	//Comutarea intre item-uri in inventar este facuta atunci cand avem mai mult de un singur item
	if (interact.player->getInvetar().size() > 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
		{
			if (!this->itemChanged && !this->keyHeld)
			{
				this->keyHeld = true;
				this->itemChanged = true;
				this->currentItem = interact.player->getInvetar().at(1);
			}
			else if (this->itemChanged && !this->keyHeld)
			{
				this->keyHeld = true;
				this->itemChanged = false;
				this->currentItem = interact.player->getInvetar().at(0);
			}
		}
		else
		{
			this->keyHeld = false; 
		}
	}
}



void GameInfoBattleScene::playerGetAttacked(ActionResults& interact)
{
	//Daca enemy-ul se apropie deajuns de player in timp ce ataca, player-ul primeste damage
	if (this->newEnemyAttack && interact.enemy->getIsAttacking())
	{
		if (distanceBetweenPoints(interact.player->getPosition(), interact.enemy->getBattleSprite().getPosition()) < 210)
		{
			interact.player->getAttacked(interact.enemy->getIsAttacking(), interact.enemy->get_attackPower());
			this->newEnemyAttack = false;
		}
	}
	else if (!interact.enemy->getIsAttacking())
	{
		this->newEnemyAttack = true;
		interact.player->getAttacked(false, interact.enemy->get_attackPower());
	}
	else
	{
		interact.player->getAttacked(false, interact.enemy->get_attackPower());
	}

	//Attacked from projectiles
	for (size_t i{}; i < this->projectilesEnemy.size(); i++)
	{
		if (pixelPerfectCollision(*this->projectilesEnemy.at(i)->getSprite(), interact.player->getPlayerSpr()))
		{
			if (!this->projectilesEnemy.at(i)->getCountDown().has_value())
				interact.player->getAttacked(true, this->projectilesEnemy.at(i)->getAttackPower());


			if (this->projectilesEnemy.at(i)->getCountDown().has_value())
				this->projectilesEnemy.at(i)->decrCountDown();
			else
				this->projectilesEnemy.at(i)->setCountDown(7); //Proiectilele sunt distruse dupa 7 iterari

			//Proiectilele vor fi distruse dupa un numar de iteratii 
			if (this->projectilesEnemy.at(i)->getCountDown() <= 0)
			{
				this->projectilesEnemy.erase(this->projectilesEnemy.begin() + i);
				i--;
			}
		}
	}
}



void GameInfoBattleScene::moveProjectiles(const sf::RenderWindow& target)
{
	for (size_t i{}; i < this->projectilesPlayer.size(); i++)
	{
		this->projectilesPlayer.at(i)->move();

		if (this->projectilesPlayer.at(i)->getSprite()->getPosition().x > target.getSize().x ||
			this->projectilesPlayer.at(i)->getSprite()->getPosition().x < 0 ||
			this->projectilesPlayer.at(i)->getSprite()->getPosition().y > target.getSize().y ||
			this->projectilesPlayer.at(i)->getSprite()->getPosition().y < 0)
		{
			this->projectilesPlayer.erase(this->projectilesPlayer.begin() + i);

			i--; 
		}
	}

	for (size_t i{}; i < this->projectilesEnemy.size(); i++)
	{
		this->projectilesEnemy.at(i)->move();

		if (this->projectilesEnemy.at(i)->getSprite()->getPosition().x > target.getSize().x ||
			this->projectilesEnemy.at(i)->getSprite()->getPosition().x < 0 ||
			this->projectilesEnemy.at(i)->getSprite()->getPosition().y > target.getSize().y ||
			this->projectilesEnemy.at(i)->getSprite()->getPosition().y < 0)
		{
			this->projectilesEnemy.erase(this->projectilesEnemy.begin() + i);

			i--;
		}
	}
}

void GameInfoBattleScene::enemyGetAttacked(ActionResults& interact)
{
	if (this->isCloseAttack && !this->isHoldClosedAttack)
	{
		//Close attack este doar pentru sword
		this->enemyWasAttacked = true;
		this->isCloseAttack = false; 
	}

	for (size_t i{}; i < this->projectilesPlayer.size(); i++)
	{
		if (pixelPerfectCollision(*this->projectilesPlayer.at(i)->getSprite(), interact.enemy->getBattleSprite()))
		{
			if (!this->projectilesPlayer.at(i)->getCountDown().has_value())
				this->enemyWasAttacked = true; 

			if (this->projectilesPlayer.at(i)->getCountDown().has_value())
				this->projectilesPlayer.at(i)->decrCountDown();
			else
				this->projectilesPlayer.at(i)->setCountDown(7); //Proiectilele sunt distruse dupa 7 iterari

			//Proiectilele vor fi distruse dupa un numar de iteratii 
			if (this->projectilesPlayer.at(i)->getCountDown() <= 0)
			{
				this->projectilesPlayer.erase(this->projectilesPlayer.begin() + i);
				i--;
			}
		}
	}

	if (this->enemyWasAttacked)
	{
		interact.enemy->getAttacked(true, this->currentItem->getAttackPower(), this->currentItem->getTipItem());
		this->enemyWasAttacked = false;
	}
	else
	{
		interact.enemy->getAttacked(false, this->currentItem->getAttackPower(), this->currentItem->getTipItem());
	}
}

void GameInfoBattleScene::moveEnemy(ActionResults& interact)
{
	interact.enemy->move(calculateAngle(interact.enemy->getBattleSprite().getPosition(), interact.player->getPosition()), 
						 interact.player->getPlayerSpr());
}



void GameInfoBattleScene::enemyAttack(ActionResults& interact)
{
	//Enemy attack's
	interact.enemy->closeAttack(interact.player->getPosition(), interact.enemy->getBattleSprite().getPosition());

	interact.enemy->projectileAttack(this->projectilesEnemy, interact.enemy->getBattleSprite().getRotation(),
									 interact.enemy->getBattleSprite().getTransform().transformPoint(201.f, 249.f),
									 distanceBetweenPoints(interact.player->getPosition(), interact.enemy->getBattleSprite().getPosition())); 
}


	

void GameInfoBattleScene::updateUiText(const ActionResults& interact) const
{
	std::stringstream ss; 

	//For player
	ss << "Health: " << interact.player->get_health() << "\n\n"
	   << "Inventar [Press F]: ";
	this->uiText_PlayerHealth->setString(ss.str()); 

	for (int i{}; i < this->itemsFromInventar.size(); i++)
	{
		if (this->currentItem == interact.player->getInvetar().at(i))
		{
			this->itemsFromInventar.at(i)->setFillColor(sf::Color::Red);
		}
		else
		{
			this->itemsFromInventar.at(i)->setFillColor(sf::Color::Green);
		}
	}
	

	ss.str(""); 
	ss.clear(); 


	//For enemy
	ss << "Health: " << interact.enemy->get_health(); 

	this->uiText_EnemyHealth->setString(ss.str()); 
}



void GameInfoBattleScene::checkStatus(ActionResults& interact)
{
	if (interact.player->get_health() < 0 || interact.enemy->get_health() < 0)
	{
		interact.sceneEnd = true; 

		if (interact.player->get_health() > 0)
			interact.defeatedEnemy = true;
		else
			interact.defeatedEnemy = false; 
	}
}

