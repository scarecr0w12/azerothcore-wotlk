/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEF_TEMPLE_OF_AHNQIRAJ_H
#define DEF_TEMPLE_OF_AHNQIRAJ_H

#include "CreatureAIImpl.h"

#define TempleOfAhnQirajScriptName "instance_temple_of_ahnqiraj"

enum DataTypes
{
    DATA_SKERAM             = 1,
    DATA_KRI                = 2,
    DATA_VEM                = 3,
    DATA_YAUJ               = 4,
    DATA_BUG_TRIO           = 5,
    DATA_VEKLOR             = 6,
    DATA_VEKLORISDEAD       = 7,
    DATA_VEKLOR_DEATH       = 8,
    DATA_VEKNILASH          = 9,
    DATA_VEKNILASHISDEAD    = 10,
    DATA_VEKNILASH_DEATH    = 11,
    DATA_FANKRISS           = 12,
    DATA_BUG_TRIO_DEATH     = 14,
    DATA_CTHUN_PHASE        = 20,
    DATA_VISCIDUS           = 21,
    DATA_SARTURA            = 22,

    DATA_EYE_OF_CTHUN       = 23
};

enum Creatures
{
    NPC_EYE_OF_CTHUN        = 15589,
    NPC_CTHUN_PORTAL        = 15896,
    NPC_CLAW_TENTACLE       = 15725,
    NPC_EYE_TENTACLE        = 15726,
    NPC_SMALL_PORTAL        = 15904,
    NPC_BODY_OF_CTHUN       = 15809,
    NPC_GIANT_CLAW_TENTACLE = 15728,
    NPC_GIANT_EYE_TENTACLE  = 15334,
    NPC_FLESH_TENTACLE      = 15802,
    NPC_GIANT_PORTAL        = 15910,

    NPC_VISCIDUS            = 15299,
    NPC_GLOB_OF_VISCIDUS    = 15667,

    NPC_SKERAM              = 15263,
    NPC_VEM                 = 15544,
    NPC_KRI                 = 15511,
    NPC_YAUJ                = 15543,
    NPC_VEKLOR              = 15276,
    NPC_VEKNILASH           = 15275,
    NPC_OURO                = 15517,
    NPC_SARTURA             = 15516
};

template <class AI, class T>
inline AI* GetTempleOfAhnQirajAI(T* obj)
{
    return GetInstanceAI<AI>(obj, TempleOfAhnQirajScriptName);
}

#define RegisterTempleOfAhnQirajCreatureAI(ai_name) RegisterCreatureAIWithFactory(ai_name, GetTempleOfAhnQirajAI)

#endif
