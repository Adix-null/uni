#include "CombatantAttack.h"
#include "RangedAttack.h"

int main() {
    try {
        std::srand(static_cast<unsigned int>(std::time(nullptr))); 
        g_debugEnabled = true; 
        
        MeleeAttack melee(15, 0.25f);
        Combatant mage("Mage");
        FireballAttack fireball(mage.getMana(), 20, 0.3f, 10, 3);

        melee.use();    //polimorfizmas
        fireball.use(); //polimorfizmas
        return 0;

    } catch (...) {
        std::cerr << "An unknown error occurred: ";
        return 1;
    }
}