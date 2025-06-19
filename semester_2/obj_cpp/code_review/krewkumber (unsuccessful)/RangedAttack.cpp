#include "CombatantAttack.h"
#include "RangedAttack.h"
#include <iostream>
#include <cstdlib>

RangedAttack::RangedAttack(int baseDamage, float burnChance, int manaCost, int maxUses)
    : baseDamage(baseDamage), burnChance(burnChance), manaCost(manaCost), maxUses(maxUses)
{
    this->usesLeft = maxUses;
    this->isCharging = false;
}

std::string RangedAttack::getName() const
{
    return "Ranged Shot";
}

bool RangedAttack::canUse() const
{
    return usesLeft > 0 && !isCharging && mana >= manaCost;
}

int RangedAttack::calculateDamage() const
{
    if (randomFloat() < burnChance || g_debugEnabled)
    {
        std::cout << "Target is burning!\n";
    }
    return baseDamage;
}

void RangedAttack::use()
{
    if (isCharging)
    {
        tick();
        return;
    }

    if (usesLeft > 0 && mana >= manaCost)
    {
        usesLeft--;
        mana -= manaCost;
        if (g_debugEnabled)
        {
            std::cout << "Cast fireball (" << usesLeft << " charges left, "
                      << mana << " mana remaining)\n";
        }
        if (usesLeft == 0)
        {
            isCharging = true;
            if (g_debugEnabled)
            {
                std::cout << "Spell exhausted! Will recharge on next attempt.\n";
            }
        }
    }
    else
    {
        isCharging = true;
        if (g_debugEnabled)
        {
            std::cout << "Insufficient resources! Recharging...\n";
        }
    }
}

void RangedAttack::tick()
{
    if (isCharging)
    {
        usesLeft = maxUses;
        isCharging = false;
        if (g_debugEnabled)
        {
            std::cout << "Fireball recharged (" << usesLeft << " charges available).\n";
        }
    }
}

std::string RangedAttack::getDamageType() const
{
    return "Physical";
}