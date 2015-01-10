/*
 *  Copyright (C) 2011-2015  OpenDungeons Team
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GOALCLAIMNTILES_H
#define GOALCLAIMNTILES_H

#include "goals/Goal.h"

class GoalClaimNTiles: public Goal
{
public:
    GoalClaimNTiles(const std::string& nName, const std::string& nArguments, GameMap* gameMap);
    virtual ~GoalClaimNTiles()
    {}

    // Inherited functions
    bool isMet(Seat *s);
    std::string getDescription(Seat *s);
    std::string getSuccessMessage(Seat *s);
    std::string getFailedMessage(Seat *s);

private:
    unsigned int mNumberOfTiles;
};

#endif // GOALCLAIMNTILES_H
