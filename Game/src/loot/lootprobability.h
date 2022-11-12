// Copyright 2014 Pedro Nunes
//
// This file is part of Hexterminate.
//
// Hexterminate is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Hexterminate is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hexterminate. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include "ship/moduleinfo.h"

namespace Hexterminate
{

class LootProbability
{
public:
    LootProbability();
    LootProbability( float commonChance, float uncommonChance, float rareChance, float artifactChance, float legendaryChance );
    ~LootProbability(){};
    bool Get( ModuleRarity& rarity ) const;

private:
    float m_Value[ static_cast<unsigned int>( ModuleRarity::Count ) ];
};

} // namespace Hexterminate
