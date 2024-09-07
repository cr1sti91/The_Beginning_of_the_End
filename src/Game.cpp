#include "Game.h"



//------------------------------------------------METODE ALE CLASEI Game------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::initMusic()
{
	this->music = std::make_unique<sf::Music>();

	if (!(this->music->openFromFile(path_Main_Menu_music)))
		std::cout << "ERROR::iNTRO_1::Muzica inaccesibila!" << std::endl;

	this->music->setLoop(true);

	this->musicIsInitialized = true; 
}

void Game::initWindowFeatures(const short& width, const short& height, const std::string& name, unsigned short fLimit)
{
	this->videoMode = sf::VideoMode(width, height); 
	this->windowName = name; 
	this->frameLimit = fLimit; 
}

void Game::initWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(videoMode, windowName, sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(this->frameLimit);
	this->window->setVerticalSyncEnabled(false);
}


Game::Game(const short& width, const short& height, const std::string& name, unsigned short fLimit)
//Nu este bine de utilizat aici initializer list, fiindca putem avea o exceptie din cauza initializarii intarziate a lui videomode
{
	//Ordinea initializarii este foarte imporatanta
	this->initWindowFeatures(width, height, name, fLimit); 
	this->initVariables();
	this->initWindow(); 
	this->initMusic();
	this->initInfoPtr();
}


Game::~Game()
{
	std::cout << "Obiectul Game este distrus" << std::endl;
}

void Game::run()
{
	while (this->window->isOpen())
	{

		this->update(); //Daca in GameMenuInfo::updatePollEvents window-ul este inchis, atunci are loc 
						//metoda this->render() doar o singura data si ...

		this->render();

	}
}


void Game::playMusic()
{
	if (this->window->isOpen() && !this->stopMusic && this->musicIsInitialized)
	{
		this->music->play();
		this->musicIsStopped = false;
	}
	else if (this->window->isOpen())
	{
		//Daca intram in metoda playMusic() atunci inseamna ca este necesar ca muzica sa ruleze - metoda data este chemata de un 
		//numar fix de ori.
		while (!this->musicIsInitialized || this->stopMusic)
		{
			//Asteptam pana cand muzica devine initializata si are permisiunea de a rula
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		
		//Daca se intampla ca la acest moment muzica este initializata, atunci incercam din nou sa rulam muzica
		if (!this->isMusicPlaying())
		{
			this->music->play();
			this->musicIsStopped = false;
		}
	}


	while (!stopMusic && this->window->isOpen() && music->getStatus() == sf::Music::Playing)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	if (this->musicIsInitialized)
	{
		for (short i{ 100 }; i >= 0; i--)
		{
			music->setVolume(i);
			std::this_thread::sleep_for(std::chrono::milliseconds(8));
		}
		
		this->music->stop();
	}
	
	this->musicIsStopped = true;
}





void Game::renderGameInfo()
{
	this->gameInfoPtr->drawGameInfo(*this->window, this->interact); 
}



void Game::initInfoPtr()
{
	this->gameInfoPtr = std::make_unique<GameIntroInfo_1>(this->getWindowSize(), this->interact);
}

void Game::initVariables()
{
	this->interact.sceneEnd = std::nullopt;
	this->interact.isEnteringText = false; 
	this->interact.clasaPlayer = CategoriePlayer::Warrior; //In modi implicit va fi warrior
	this->interact.player = nullptr; 
	this->interact.defeatedEnemy = false; 
	this->interact.dir_x = 0;
	this->interact.dir_y = 0;

	this->musicIsInitialized = false; //initial muzica nu este initializata
	this->stopMusic = false;
	this->musicIsStopped = true; //initial muzica nu canta
	this->currentScene = 1; //se foloseste doar in metode reset.
							//scena 0 este cea de la initializare
}




void Game::initPlayer(const CategoriePlayer& categorie, const std::string& nume)
{
	switch (categorie)
	{
		case CategoriePlayer::Warrior: 
		{
			this->player = std::make_shared<Warrior>(nume); 
		} break;

		case CategoriePlayer::Rogue:
		{
			this->player = std::make_shared<Rogue>(nume);
		} break;

		case CategoriePlayer::Wizard:
		{
			this->player = std::make_shared<Wizard>(nume);
		} break;

		default: 
		{
			std::cout << "ERROR::GAME::Categorie player inexistenta!" << std::endl;
		}
	}
}

void Game::resetMusic(unsigned short scena)
{
	switch (scena)
	{
	case 1:
	{
		resetMusicForCase(this->musicIsStopped, this->musicIsInitialized, this->music,
					      path_IntroAfterBattle_music, "ERROR::Scena_1::Muzica inaccesibila!"); 
	}
	break;

	case 2:
	{
		//Ramenm cu muzica 'path_IntroAfterBattle_music'
		this->musicIsInitialized = true; 
	}
	break;

	case 3:
	{
		//Ramenm cu muzica 'path_IntroAfterBattle_music'
		this->musicIsInitialized = true;
	}
	break;

	case 4:
	{
		resetMusicForCase(this->musicIsStopped, this->musicIsInitialized, this->music,
			              path_Exploring_music, "ERROR::Scena_4::Muzica inaccesibila!");
	}
	break; 

	case 5:
	{
		resetMusicForCase(this->musicIsStopped, this->musicIsInitialized, this->music,
			              path_IntroBattle_music, "ERROR::Scena_5::Muzica inaccesibila!");
	}
	break;

	case 6:
	{
		resetMusicForCase(this->musicIsStopped, this->musicIsInitialized, this->music,
						  path_BattleFinal_music, "ERROR::Scena_6::Muzica inaccesibila!");
	}
	break;

	case 7:
	{
		resetMusicForCase(this->musicIsStopped, this->musicIsInitialized, this->music,
						  path_TheEnd_music, "ERROR::Scena_7::Muzica inaccesibila!");
	}
	}
}

void Game::resetInfoPtr(unsigned short scena)
{

	switch (scena)
	{
	case 1: 
	{
		this->gameInfoPtr.reset(); //obiectul precedent este distrus
		this->gameInfoPtr = std::make_unique<GameIntroInfo_2>(this->getWindowSize(), this->interact);
	}
	break;

	case 2:
	{
		this->temp = std::move(this->gameInfoPtr); //pastram scena_1 ca in scena_3 sa continuam scena_1
		this->gameInfoPtr = std::make_unique<GameInfoChoose>(this->getWindowSize(), this->interact);
	}
	break;

	case 3:
	{
		this->gameInfoPtr.reset(); //Distrugem scena_2
		this->gameInfoPtr = std::move(temp); //In scena_3 continua unde ne-am oprit in scena_1
	}
	break;

	case 4:
	{
		this->gameInfoPtr.reset(); 
		this->gameInfoPtr = std::make_unique<GameCrossRoads>(this->getWindowSize(), this->interact);
	}
	break;

	case 5:
	{
		this->gameInfoPtr.reset();
		this->gameInfoPtr = std::make_unique<GameInfoIntroBattle>(this->getWindowSize(), this->interact);
	}
	break;

	case 6:
	{
		this->gameInfoPtr.reset();
		this->gameInfoPtr = std::make_unique<GameInfoBattleScene>(this->getWindowSize(), this->interact);
	}
	break;

	case 7:
	{
		this->gameInfoPtr.reset();
		this->gameInfoPtr = std::make_unique<GameInfoEndOfTheFight>(this->getWindowSize(), this->interact);
	}
	break;

	default: 
	{
		this->window->close(); //Final joc - cand nu este gasita urmatoarea scena, window-ul se inchide
	}
	break;
	}
}



void Game::resetVariables()
{
	this->interact.sceneEnd = std::nullopt;
	this->stopMusic = false;

	if (this->currentScene == 4)
		this->interact.player = this->player; //De la scena_4 si in continuare, toate scenele vor avea acces la adresa obiectului player
}



void Game::UpdateAll(unsigned short scena) //Reset si update au acelasi sens in acest context
{
	if (this->stopMusic)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1200));
		this->resetMusic(scena);
	}
		
	this->resetInfoPtr(scena); 
	this->resetVariables(); 

	//La finalul scenei 2 si inceputul scenei 3 avem datele necesare pentru a crea obiectul 'player'
	if (this->currentScene == 3)
		this->initPlayer(this->interact.clasaPlayer, this->interact.playerName);
}



//Daca muzica sa initializat, insa nu a reusit metoda music->play() sa functioneze
//atunci returnam 'false', in caz contrar - 'true'
const bool Game::isMusicPlaying() const
{
	if (musicIsStopped)
	{
		if (musicIsInitialized)
		{
			return false;
		}
	}
	return true;
}



void Game::updatePollEvents()
{
	while (this->window->pollEvent(this->event))
	{
        if (this->event.type == sf::Event::Closed)
        {
            this->window->close();
        }
        else if (this->event.type == sf::Event::KeyPressed)
        {
            if (this->event.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
        }
        // Citim textul de la tastatură numai dacă evenimentul este TextEntered
        else if (this->event.type == sf::Event::TextEntered && this->interact.isEnteringText)
        {
            if (this->event.text.unicode < 128)
            {
                if (this->event.text.unicode == '\b') // Backspace
                {
                    if (!this->interact.playerName.empty())
                    {
                        this->interact.playerName.pop_back();
                    }
                }
                else
                {
                    this->interact.playerName += static_cast<char>(this->event.text.unicode);
                }
            }
        }
    
	}



	this->gameInfoPtr->updatePollEvents(*this->window, this->interact);
	
	if (this->interact.sceneEnd.has_value() && this->currentScene != 2 && this->currentScene != 3)
		this->stopMusic = true;
	else
		this->stopMusic = false; 
}


void Game::update()
{
	this->updatePollEvents();

	if (this->interact.sceneEnd.has_value())
	{
		if (this->interact.sceneEnd.value())		//Cand sceneEnd este true, atunci trecem la scena urmatoare, 
		{											//iar daca este false - jocul se inchide
			this->UpdateAll(this->currentScene); 
			currentScene++; 
		}
	}
}

void Game::render()
{
	this->window->clear(); //Clear the old frame

	this->renderGameInfo(); 

	this->window->display(); //Afiseaza frame-ul actualizat
}



const sf::Vector2u Game::getWindowSize() const
{
	return this->window->getSize();
}

const bool Game::getWindowStatus() const
{
	return this->window->isOpen();
}


