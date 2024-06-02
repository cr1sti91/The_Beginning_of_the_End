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
	this->waitingBegin = sf::seconds(-3);  //cand incepe scena, enemy-ul nu va fi stopat
	this->cooldownTime = sf::seconds(0.4f); 
	this->waitingTime = sf::seconds(3.f); 
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

	this->enemyIsWainting = false; 
	this->enemyWasAttacked = false; 
	this->enemyAttacked = false; 
	this->newEnemyAttack = true; 

	this->itemChanged = false; 
	
	//In mod implicit, este folosit primul item din inventar
	if (interact.player->getInvetar().size() != 0)
		this->currentItem = interact.player->getInvetar().at(0); 
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

	for (auto& projectile : this->projectiles)
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
	this->keyWasPressed = false;

	//Move projectiles
	this->moveProjectiles(target); 

	//If enemy is attacked
	this->enemyGetAttacked(interact); 

	//Enemy is moving or is wainting
	this->moveEnemy(interact); 

	//Enemy is attacking
	this->enemyAttack(interact); 	

	//Update text
	this->updateUiText(interact); 
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
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (this->mouseHeld || !this->keyWasPressed))
	{
		interact.player->setSpriteDirection(0, 0);
		interact.player->setRotation(calculateAngle(getMousePosView(target), interact));
	}
	else
	{
		this->mouseHeld = false;
	}
}

void GameInfoBattleScene::thePlayersAttack(const sf::RenderWindow& target, ActionResults& interact)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->clock.getElapsedTime() - this->timePoint >= this->cooldownTime && this->keyWasPressed)
		{
			this->timePoint = this->clock.getElapsedTime(); 

			this->mouseHeld = true;

			interact.player->attack(this->projectiles, this->currentItem->getTipItem(),
									this->calculateAngle(getMousePosView(target), interact),
									interact.player->getPlayerSpr().getTransform().transformPoint(210.f, 124));
		}
		else if (!this->mouseHeld && !this->keyWasPressed) //Player-ul nu se deplaseaza
		{
			this->mouseHeld = true;

			interact.player->attack(this->projectiles, this->currentItem->getTipItem(),
									this->calculateAngle(getMousePosView(target), interact),
									interact.player->getPlayerSpr().getTransform().transformPoint(210.f, 124));
		}
		//'sprite.getTransform().transformPoint()' returneaza adresa (Vector2f) punctului (210, 124) ce se afla pe sprite in  
		//coordonatele window-ului dupa ce a avut loc ultima transforamare (aplicare a unei matrici 3x3 asupra sprite-ului dat).
		//In acest mod, fireballurile vor fi create la adresa actualizata a punctului de pe sprite. 
	}
	else
	{
		this->mouseHeld = false;
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

void GameInfoBattleScene::moveProjectiles(const sf::RenderWindow& target)
{
	for (size_t i{}; i < this->projectiles.size(); i++)
	{
		this->projectiles.at(i)->move();

		if (this->projectiles.at(i)->getSprite()->getPosition().x > target.getSize().x ||
			this->projectiles.at(i)->getSprite()->getPosition().x < 0 ||
			this->projectiles.at(i)->getSprite()->getPosition().y > target.getSize().y ||
			this->projectiles.at(i)->getSprite()->getPosition().y < 0)
		{
			this->projectiles.erase(this->projectiles.begin() + i);

			i--; 
		}
	}
}

void GameInfoBattleScene::enemyGetAttacked(ActionResults& interact)
{
	for (size_t i{}; i < this->projectiles.size(); i++)
	{
		if (this->projectiles.at(i)->getSprite()->getGlobalBounds().intersects(interact.enemy->getBattleSprite().getGlobalBounds()))
		{
			if (!this->projectiles.at(i)->getCountDown().has_value())
				this->enemyWasAttacked = true; 

			if (this->projectiles.at(i)->getCountDown().has_value())
				this->projectiles.at(i)->decrCountDown();
			else
				this->projectiles.at(i)->setCountDown(7); //Proiectilele sunt distruse dupa 7 iterari

			//Proiectilele vor fi distruse dupa un numar de iteratii 
			if (this->projectiles.at(i)->getCountDown() <= 0)
			{
				this->projectiles.erase(this->projectiles.begin() + i);
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
	//The enemy is directed towards the player
	interact.enemy->setRotation(calculateAngle(interact.enemy->getBattleSprite().getPosition(), interact));

	//The enemy moves towards the player or enemy is waiting
	std::uniform_int_distribution<int> waitingChance(1, 500);
	if (!this->enemyIsWainting && this->clock.getElapsedTime() - this->waitingBegin > this->waitingTime)
	{
		this->enemyIsWainting = (waitingChance(rd) == 1);
		if (this->enemyIsWainting)
		{
			this->waitingBegin = this->clock.getElapsedTime();
			this->enemyIsWainting = false;
		}
	}

	if (this->clock.getElapsedTime() - this->waitingBegin > this->waitingTime)
	{
		interact.enemy->move(calculateAngle(interact.enemy->getBattleSprite().getPosition(), interact), interact.player->getPlayerSpr());
	}
}

void GameInfoBattleScene::enemyAttack(ActionResults& interact)
{
	//Enemy attack
	std::uniform_int_distribution<int> attackChance(1, 150); //atacurile sa fie random
	const float distance = distanceBetweenPoints(interact.player->getPosition(), interact.enemy->getBattleSprite().getPosition());
	if (distance > 200 && distance < 400 && attackChance(rd) == 1)
	{
		interact.enemy->attack(true);
		this->enemyAttacked = true; 
	}
	else
	{
		interact.enemy->attack(false);
		this->enemyAttacked = false; 
	}

	//Daca enemy-ul se apropie deajuns de player in timp ce ataca, player-ul primeste damage
	if (this->newEnemyAttack && interact.enemy->getIsAttacking())
	{
		if (distance < 210)
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




//Unghiul returnat va fi fata de directia 'Up' verticala si player
const double GameInfoBattleScene::calculateAngle(const sf::Vector2f referencePoint, const ActionResults& interact)
{
	double angle = 0;

	if (referencePoint.y <= interact.player->getPosition().y
		&& referencePoint.x < interact.player->getPosition().x)
	{
		angle = 270 + (std::atan(abs((interact.player->getPosition().y - referencePoint.y)
			/ (interact.player->getPosition().x - referencePoint.x))) * (180.0 / M_PI));

		return angle; 
	}
	else if (referencePoint.y < interact.player->getPosition().y
		&& referencePoint.x >= interact.player->getPosition().x)
	{
		angle = std::atan(abs((interact.player->getPosition().x - referencePoint.x)
			/ (interact.player->getPosition().y - referencePoint.y))) * (180.0 / M_PI);

		return angle; 
	}
	else if (referencePoint.y >= interact.player->getPosition().y
		&& referencePoint.x > interact.player->getPosition().x)
	{
		angle = 90 + (std::atan(abs((interact.player->getPosition().y - referencePoint.y)
			/ (interact.player->getPosition().x - referencePoint.x))) * (180.0 / M_PI));

		return angle;
	}
	else if (referencePoint.y > interact.player->getPosition().y
		&& referencePoint.x <= interact.player->getPosition().x)
	{
		angle = 180 + (std::atan(abs((interact.player->getPosition().x - referencePoint.x)
			/ (interact.player->getPosition().y - referencePoint.y))) * (180.0 / M_PI));

		return angle;
	}
}


