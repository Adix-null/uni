#include "CombatantAttack.h"
#include <iostream>
#include <cstdlib>

FireballAttack::FireballAttack(int &manaRef, int baseDamage, float burnChance, int manaCost, int maxUses)
    : mana(manaRef), baseDamage(baseDamage), burnChance(burnChance), manaCost(manaCost), maxUses(maxUses)
{
    this->usesLeft = maxUses;
    this->isCharging = false;
}

std::string FireballAttack::getName() const
{
    return "Fireball";
}

bool FireballAttack::canUse() const
{
    return usesLeft > 0 && !isCharging && mana >= manaCost;
}

int FireballAttack::calculateDamage() const
{
    if (randomFloat() < burnChance || g_debugEnabled)
    {
        std::cout << "Target is burning!\n";
    }
    return baseDamage;
}

void FireballAttack::use()
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

void FireballAttack::tick()
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

std::string FireballAttack::getDamageType() const
{
    return "Magical";
}