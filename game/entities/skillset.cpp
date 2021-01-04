#include "../common.h"

Skills::Skills(unsigned int woodcutting, unsigned int fishing, unsigned int mining, unsigned int smithing, unsigned int attack, unsigned int defence)
	: _woodcutting(woodcutting), _fishing(fishing), _mining(mining), _smithing(smithing), _attack(attack), _defence(defence) {}

void Skills::AddLevel()
{
	//Todo
}

void Skills::SetLevel()
{
	//Todo
}

const unsigned int Skills::GetDmg()
{
	unsigned int dmg = rand() % _attack;

	return dmg; 
}