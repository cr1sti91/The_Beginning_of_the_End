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
