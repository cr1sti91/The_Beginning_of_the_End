#include "Wizard.h"


Wizard::Wizard(const std::string& name, const CategoriePlayer& categorie)
	: Player(name, categorie, 100, 10, 6) 
{
	//Ordinea este foarte importanta
	this->initTexture(); 
	this->initPlayerSpr(); 

	this->woundedTime = sf::seconds(0.4f); 
	this->lastAttacked = sf::Time::Zero; 
}



void Wizard::initTexture()
{
	//For CrossRoads scene
	initTex(this->textureToCave, path_Wizard_toCave, "ERROR::Wizard::Wizard to cave inaccesibil!");
	initTex(this->textureToForest, path_Wizard_toForest, "ERROR::Wizard::Wizard to forest inaccesibil!");
	initTex(this->textureToVillage, path_Wizard_toVillage, "ERROR::Wizard::Wizard to village inaccesibil!");

	//For Battle scene
	initTex(this->textureUp, path_Wizard_BattleUp, "ERROR::Wizard::Wizard Up inaccesibil!");
	initTex(this->textureUpAttacked, path_Wizard_BattleUpAttacked, "ERROR::Wizard::WizardAttacked inaccesibil!"); 
}

void Wizard::initPlayerSpr()
{
	this->playerSpr = std::make_unique<sf::Sprite>(*this->textureUp);
	this->playerSpr->setScale(0.3f, 0.3f); 
	this->playerSpr->setOrigin(212.f, 315.f); 
	this->playerSpr->setPosition(900.f, 800.f); 

	this->setSpriteDirection(0, 1); //In mod implicit, player-ul o sa fie setat cu textura indreptata in sus
}


void Wizard::attack(std::vector<std::unique_ptr<Item>>& attacks, const TypeItem& tipAttack, const float& angle,
				    const sf::Vector2f& pos)
{
	//
	switch (tipAttack)
	{
	case TypeItem::FireBall :
	{
		attacks.push_back(std::make_unique<ThrownBall>(TypeItem::FireBall, pos.x, pos.y, angle));
	}break; 

	case TypeItem::IceBall:
	{
		attacks.push_back(std::make_unique<ThrownBall>(TypeItem::IceBall, pos.x, pos.y, angle));
	}break;

	default:
		break;
	}
}

void Wizard::getAttacked(const bool& isAttacked, const short& attackPower)
{
	if (isAttacked)
	{
		this->lastAttacked = this->getPlayerClock().getElapsedTime(); 
		this->playerSpr->setTexture(*this->textureUpAttacked); 

		this->healthDecreases(attackPower); 
	}
	else if (this->getPlayerClock().getElapsedTime() - this->lastAttacked > this->woundedTime)
	{
		this->playerSpr->setTexture(*this->textureUp); 
	}
}

void Wizard::move(const float& dir_x, const float& dir_y)
{
	this->playerSpr->move(this->get_speedMovement() * dir_x, this->get_speedMovement() * dir_y); 
}


void Wizard::setRotation(const float& angle)
{
	this->playerSpr->setRotation(angle); 
}


//Este chemata o singura data atunci cand in inventar se adauga un item nou
std::shared_ptr<Item> Wizard::generateItem() const
{ 
	std::uniform_int_distribution<int> dist(0, 1);  //La moment, pentru wizard avem doua item-uri
	static std::random_device rd; //fiindca este static, va fi declarat o singura data si va fi utilizat in apelurile ulterioare

	//switch (dist(rd))
	switch (1)
	{
		case 0: //Pentru wizard, 0 va fi fireball
		{
			return std::make_shared<ThrownBall>(TypeItem::FireBall, this->getPosition().x,
												this->getPosition().y, this->playerSpr->getRotation());
		}break; 

		case 1: //Pentru wizard, 1 va fi iceball
		{
			return std::make_shared<ThrownBall>(TypeItem::IceBall, this->getPosition().x,
												this->getPosition().y, this->playerSpr->getRotation());
		}break;
		
	
		default:
			std::cout << "ERROR::Wizard::GenerateItem::numar random incorect!" << std::endl;
			break;
	}
}

void Wizard::setSpriteDirection(const short& dir_x, const short& dir_y)
{
	this->playerSpr->setRotation(dirToDegree(dir_x, dir_y));
}



const sf::Texture& Wizard::getToCaveTexture() const
{
	return *this->textureToCave;
}

const sf::Texture& Wizard::getToForestTexture() const
{
	return *this->textureToForest;
}

const sf::Texture& Wizard::getToVillageTexture() const
{
	return *this->textureToVillage;
}





