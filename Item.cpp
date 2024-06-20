#include "Item.h"

Item::Item(const TypeItem& tip, const std::optional<sf::Time> time) 
	: tipItem(tip), countDown(std::nullopt), lifeTime(time)
{
	switch (tip)
	{
	case TypeItem::FireBall: this->attackPower = 20; 
		break; 
	case TypeItem::IceBall: this->attackPower = 5; 
		break; 
	case TypeItem::Sword: this->attackPower = 25;
		break;
	case TypeItem::Knive: this->attackPower = 15;
		break;
	case TypeItem::Spear: this->attackPower = 20;
		break;
	case TypeItem::Rock: this->attackPower = 30;
		break;
	case TypeItem::SpikedTrap: this->attackPower = 25;
		break;
	default:
	{
		std::cout << "ERROR::Item::Item::TypeItem incorect!" << std::endl;
		this->attackPower = 1;
	}
		break;
	}
}

void Item::setCountDown(const short& value)
{
	this->countDown = value; 
}

void Item::decrCountDown()
{
	if (this->countDown.has_value())
		this->countDown.value()--;
}

const TypeItem& Item::getTipItem() const
{
	return this->tipItem; 
}

const short& Item::getAttackPower() const
{
	return this->attackPower; 
}

const std::optional<short>& Item::getCountDown() const
{
	return this->countDown; 
}

const sf::IntRect& Item::getItemLimits() const
{
	return this->itemLimits; 
}

const std::optional<sf::Time>& Item::getLifeTime() const
{
	return this->lifeTime; 
}

const std::string Item::typeItemToStr(const TypeItem& typeItem)
{
	switch (typeItem)
	{
	case TypeItem::FireBall:
			return "FireBall";
	case TypeItem::IceBall:
			return "IceBall";
	case TypeItem::Sword: 
			return "Sword"; 
	case TypeItem::Knive:
			return "Knive"; 
	case TypeItem::Spear:
			return "Spear";
	case TypeItem::SpikedTrap: 
			return "SpikedTrap"; 
	default:
			return "GameInfoBattleScene::updateUiText::Incorect argument for lambda function!";
		break;
	}
}
