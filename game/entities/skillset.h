#pragma once

#include <stdint.h>
#include "../common.h"

//Class represents all the skills that a player has.
class Skills
{
	public:

		Skills(unsigned int woodcutting, unsigned int fishing, unsigned int mining, unsigned int smithing, unsigned int attack, unsigned int defence);

		void AddLevel();
		void SetLevel();

		//Gives damage output that player can deal. 
		const unsigned int GetDmg();

	private:

		unsigned int _woodcutting;
		unsigned int _fishing;
		unsigned int _mining;
		unsigned int _smithing;
		unsigned int _attack;
		unsigned int _defence;

};