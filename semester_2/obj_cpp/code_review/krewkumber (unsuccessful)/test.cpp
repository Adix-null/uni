#include <cassert>
#include <iostream>
#include <vector>
#include "CombatantAttack.h"
#include "RangedAttack.h"

/*
Create a class RangedAttack that inherits from AttackStrategy
*/

// =====================
// Forces rolls for random value testing
// =====================
void testWithRolls(const std::vector<float> &rolls, auto testFunc)
{
    AttackStrategy::setTestRolls(rolls);
    testFunc();
    AttackStrategy::clearTestRolls();
}

void testMeleeAttack()
{
    std::cout << "Testing MeleeAttack...\n";
    MeleeAttack melee(15, 0.25f);

    assert(melee.getName() == "Melee Slash");
    assert(melee.getDamageType() == "Physical");
    assert(melee.canUse()); // Always usable

    testWithRolls({0.24f}, [&]()
                  { assert(melee.calculateDamage() == 30); }); // Crit
    testWithRolls({0.26f}, [&]()
                  { assert(melee.calculateDamage() == 15); }); // Normal

    std::cout << "MeleeAttack tests passed!\n";
}

// ===================== Tests for class to be created ====================

void testRangedAttack()
{
    std::cout << "Testing RangedAttack...\n";
    RangedAttack ranged(10, 0.75f, 0.2f, 5);

    assert(ranged.getName() == "Ranged Shot");
    assert(ranged.getDamageType() == "Physical");

    testWithRolls(std::vector<float>(10, 0.5f), [&]()
                  {
        for (int i = 0; i < 5; i++) {
            assert(ranged.canUse());
            ranged.use();
        }

        assert(!ranged.canUse());
        ranged.use();
        
        assert(ranged.canUse());
        ranged.use(); });

    testWithRolls({0.5f, 0.5f}, [&]()
                  { assert(ranged.calculateDamage() == 10); }); // Normal

    testWithRolls({0.5f, 0.19f}, [&]()
                  { assert(ranged.calculateDamage() == 20); }); // Crit

    testWithRolls({0.8f, 0.5f}, [&]()
                  { assert(ranged.calculateDamage() == 0); }); // Miss

    std::cout << "RangedAttack tests passed!\n";
}

// ========================================================

void testFireballAttack()
{
    std::cout << "Testing FireballAttack...\n";
    int mana = 100;
    Combatant mage("Mage");
    FireballAttack fireball(mage.getMana(), 20, 0.3f, 10, 3);
    assert(fireball.getName() == "Fireball");
    assert(fireball.getDamageType() == "Magical");
    assert(fireball.canUse());
    assert(fireball.calculateDamage() == 20);

    testWithRolls(std::vector<float>(5, 0.3f), [&]()
                  {
        for (int i = 0; i < 3; i++) {
            assert(fireball.canUse());
            fireball.use();
            std::cout << mage.getMana();
            assert(mage.getMana() == 100 - ((i+1) * 10));
        }

        assert(!fireball.canUse());
        fireball.use();
        
        assert(fireball.canUse());
        fireball.use();
        assert(mage.getMana() == 60); });

    std::cout << "FireballAttack tests passed!\n";
}

void testCombatant()
{
    std::cout << "Testing Combatant...\n";

    Combatant mage("Mage");
    mage.setStrategy<FireballAttack>(mage.getMana(), 20, 0.3f, 10, 3);

    testWithRolls({0.5f, 0.5f, 0.5f, 0.5f}, [&]()
                  {
        assert(mage.getMana() == 100);
        mage.performAttack(); 
        assert(mage.getMana() == 90);
        
        mage.performAttack();
        mage.performAttack();
        mage.performAttack();
        assert(mage.getMana() == 70); });

    std::cout << "Combatant tests passed!\n";
}

int main()
{
    std::srand(43);
    g_debugEnabled = true;

    try
    {
        testMeleeAttack();
        testRangedAttack();
        testFireballAttack();
        testCombatant();

        std::cout << "\nALL TESTS PASSED!\n";
        return 0;
    }
    catch (...)
    {
        std::cerr << "\nTESTS FAILED!\n";
        return 1;
    }
}