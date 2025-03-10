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

/* ScriptData
SDName: Boss_Huhuran
SD%Complete: 100
SDComment:
SDCategory: Temple of Ahn'Qiraj
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "temple_of_ahnqiraj.h"

enum Huhuran
{
    EMOTE_FRENZY_KILL           = 0,
    EMOTE_BERSERK               = 1,

    SPELL_FRENZY                = 26051,
    SPELL_BERSERK               = 26068,
    SPELL_POISONBOLT            = 26052,
    SPELL_NOXIOUSPOISON         = 26053,
    SPELL_WYVERNSTING           = 26180,
    SPELL_ACIDSPIT              = 26050,
    SPELL_WYVERN_STING_DAMAGE   = 26233
};

struct boss_huhuran : public ScriptedAI
{
    boss_huhuran(Creature* creature) : ScriptedAI(creature) { }

    uint32 Frenzy_Timer;
    uint32 Wyvern_Timer;
    uint32 Spit_Timer;
    uint32 PoisonBolt_Timer;
    uint32 NoxiousPoison_Timer;
    uint32 FrenzyBack_Timer;

    bool Frenzy;
    bool Berserk;

    void Reset() override
    {
        Frenzy_Timer = urand(25000, 35000);
        Wyvern_Timer = urand(18000, 28000);
        Spit_Timer = 8000;
        PoisonBolt_Timer = 4000;
        NoxiousPoison_Timer = urand(10000, 20000);
        FrenzyBack_Timer = 15000;

        Frenzy = false;
        Berserk = false;
    }

    void UpdateAI(uint32 diff) override
    {
        //Return since we have no target
        if (!UpdateVictim())
            return;

        //Frenzy_Timer
        if (!Frenzy && Frenzy_Timer <= diff)
        {
            DoCast(me, SPELL_FRENZY);
            Talk(EMOTE_FRENZY_KILL);
            Frenzy = true;
            PoisonBolt_Timer = 3000;
            Frenzy_Timer = urand(25000, 35000);
        }
        else Frenzy_Timer -= diff;

        // Wyvern Timer
        if (Wyvern_Timer <= diff)
        {
            DoCastAOE(SPELL_WYVERNSTING);
            Wyvern_Timer = urand(15000, 32000);
        }
        else Wyvern_Timer -= diff;

        //Spit Timer
        if (Spit_Timer <= diff)
        {
            DoCastVictim(SPELL_ACIDSPIT);
            Spit_Timer = urand(5000, 10000);
        }
        else Spit_Timer -= diff;

        //NoxiousPoison_Timer
        if (NoxiousPoison_Timer <= diff)
        {
            DoCastVictim(SPELL_NOXIOUSPOISON);
            NoxiousPoison_Timer = urand(12000, 24000);
        }
        else NoxiousPoison_Timer -= diff;

        //PoisonBolt only if frenzy or berserk
        if (Frenzy || Berserk)
        {
            if (PoisonBolt_Timer <= diff)
            {
                DoCastVictim(SPELL_POISONBOLT);
                PoisonBolt_Timer = 3000;
            }
            else PoisonBolt_Timer -= diff;
        }

        //FrenzyBack_Timer
        if (Frenzy && FrenzyBack_Timer <= diff)
        {
            me->InterruptNonMeleeSpells(false);
            Frenzy = false;
            FrenzyBack_Timer = 15000;
        }
        else FrenzyBack_Timer -= diff;

        if (!Berserk && HealthBelowPct(31))
        {
            me->InterruptNonMeleeSpells(false);
            Talk(EMOTE_BERSERK);
            DoCast(me, SPELL_BERSERK);
            Berserk = true;
        }

        DoMeleeAttackIfReady();
    }
};

// 26180 - Wyvern Sting
class spell_huhuran_wyvern_sting : public AuraScript
{
    PrepareAuraScript(spell_huhuran_wyvern_sting);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastCustomSpell(SPELL_WYVERN_STING_DAMAGE, SPELLVALUE_BASE_POINT0, 3000, GetUnitOwner(), true);
        }
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_huhuran_wyvern_sting::HandleRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_boss_huhuran()
{
    RegisterTempleOfAhnQirajCreatureAI(boss_huhuran);
    RegisterSpellScript(spell_huhuran_wyvern_sting);
}
