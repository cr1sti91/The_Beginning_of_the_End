#include "Rogue.h"


void Rogue::initTexture()
{
	//For CrossRoads scene
	initTex(this->textureToCave, path_Rogue_toCave, "ERROR::Rogue::Rogue to cave inaccesibil!");
	initTex(this->textureToForest, path_Rogue_toForest, "ERROR::Rogue::Rogue to forest inaccesibil!");
	initTex(this->textureToVillage, path_Rogue_toVillage, "ERROR::Rogue::Rogue to village inaccesibil!");

	this->textureToCave->setSmooth(true);
	this->textureToForest->setSmooth(true);
	this->textureToVillage->setSmooth(true);

	//For BattleScene
	initTex(this->textureUp, path_Rogue_BattleUp, "ERROR::Rogue::Rogue Up inaccesibil!");
	initTex(this->textureUpAttacked, path_Rogue_BattleUpAttacked, "ERROR::Rogue::Rogue Up inaccesibil!");
}

void Rogue::initPlayerSpr()
{
	this->playerSpr = std::make_unique<sf::Sprite>(*this->textureUp);
	this->playerSpr->setScale(0.5f, 0.5f);
	this->playerSpr->setOrigin(210.f, 115.f);
	this->playerSpr->setPosition(900.f, 800.f);

	this->setSpriteDirection(0, 1); //In mod implicit, player-ul o sa fie setat cu textura indreptata in sus
}

Rogue::Rogue(const std::string& name)
	: Player(name, CategoriePlayer::Rogue, 150, 8)
{
	this->initTexture(); 
	this->initPlayerSpr(); 

	//Init variables
	this->woundedTime = sf::seconds(0.8f);
	this->lastAttacked = sf::Time::Zero;

	//In mod random in inventar este plasat un item pentru rogue
	this->inventar.push_back(std::move(this->generateItem()));
}



void Rogue::attack(std::vector<std::unique_ptr<Item>>& projectiles, const TypeItem& tipAttack, const float& angle,
				   const sf::Vector2f& pos)
{
	switch (tipAttack)
	{
	case TypeItem::Knive:
	{
		projectiles.push_back(std::make_unique<Projectile>(TypeItem::Knive, pos.x, pos.y, angle));
	}break;

	case TypeItem::SpikedTrap:
	{
		projectiles.push_back(std::make_unique<Trap>(TypeItem::SpikedTrap, pos.x, pos.y, angle));
	}break;

	default:
		break;
	}
}

void Rogue::stopAttack()
{
	//La moment nu necesita implementare, fiindca atacand, rogue-ul nu isi modifica textura
}


void Rogue::getAttacked(const bool& isAttacked, const short& attackPower)
{
	if (isAttacked)
	{
		this->lastAttacked = this->playerClock.getElapsedTime();
		this->playerSpr->setTexture(*this->textureUpAttacked);

		this->healthDecreases(attackPower);
	}
	else if (this->playerClock.getElapsedTime() - this->lastAttacked > this->woundedTime)
	{
		this->playerSpr->setTexture(*this->textureUp);
	}
}


std::unique_ptr<Item> Rogue::generateItem() const
{
	static std::random_device rd;
	std::vector<int> unownedItems; //Vector de itemi (pentru wizard) care nu sunt prezenti in inventar

	for (int i{}; i < possItemsWizard; i++)
	{
		bool exist = false;
		for (int j{}; j < this->inventar.size(); j++)
		{
			if (this->inventar.at(j)->getTipItem() == static_cast<TypeItem>(i + 4))
			{
				exist = true;
				break;
			}
		}

		if (!exist)
			unownedItems.push_back(i + 4);
	}

	if (unownedItems.size() == 0)
	{
		std::cerr << "ERROR::Rogue::generateItem::A avut loc incercarea de generare cand unownedItems.size = 0" << std::endl;
		return nullptr;
	}

	std::uniform_int_distribution<int> dist(0, unownedItems.size() - 1);

	const TypeItem item = static_cast<TypeItem>(unownedItems.at(dist(rd))); 

	if (item == TypeItem::SpikedTrap)
	{
		return std::make_unique<Trap>(item, this->getPosition().x,
			this->getPosition().y, this->playerSpr->getRotation());
	}
	else
	{
		return std::make_unique<Projectile>(item, this->getPosition().x,
			this->getPosition().y, this->playerSpr->getRotation());
	}
}


