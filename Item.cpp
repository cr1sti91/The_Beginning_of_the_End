#include "Item.h"

Item::Item(const TypeItem& tip) : tipItem(tip), countDown(std::nullopt)
{
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

const std::optional<short>& Item::getCountDown() const
{
	return this->countDown; 
}

const std::string Item::typeItemToStr(const TypeItem& typeItem)
{
	switch (typeItem)
	{
	case TypeItem::FireBall:
			return "FireBall";
	case TypeItem::IceBall:
			return "IceBall";
	default:
			return "GameInfoBattleScene::updateUiText::Incorect argument for lambda function!";
		break;
	}
}
