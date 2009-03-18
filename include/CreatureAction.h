#ifndef CREATUREACTION_H
#define CREATUREACTION_H

#include "Tile.h"
class CreatureAction;
#include "Creature.h"

class CreatureAction
{
	public:
		enum ActionType {walkToTile=1, digTile=2, attackCreature=3, idle=4};

		CreatureAction();
		CreatureAction(ActionType nType, Tile *nTile=NULL, Creature *nCreature=NULL);

		ActionType type;
		Tile *tile;
		Creature *creature;
};

#endif

