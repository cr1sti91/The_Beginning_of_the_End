#ifndef ROGUE_H
#define ROGUE_H

#include "Player.h"
#include "Projectile.h"
#include "Trap.h"

class Rogue : public Player
{
private:
	//Private methods
	void initTexture() override;
	void initPlayerSpr() override;

public:
	// Constructor / Destructor
	Rogue(const std::string& name);
	~Rogue() = default;


	void attack(std::vector<std::unique_ptr<Item>>& projectiles, const TypeItem& tipAttack, const float& angle,
					      const sf::Vector2f& pos) override;

	void stopAttack() override;

	void getAttacked(const bool& isAttacked, const short& attackPower);


	std::unique_ptr<Item> generateItem() const;
};

#endif //ROGUE_H