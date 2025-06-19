#include "CombatantAttack.h"

Combatant::Combatant(const std::string& name) : name(name) {}
Combatant::~Combatant() = default;

void Combatant::performAttack() {
    if (strategy) {
        if (strategy->canUse()) {
            if(g_debugEnabled){
                std::cout << name << " uses " << strategy->getName() << "!\n";
            }
            strategy->use();
        } else {
            if(g_debugEnabled){
                std::cout << strategy->getName() << " is recharging or unavailable.\n";
            }
            strategy->use(); 
        }
    }
}

void Combatant::tickCooldown() {
    if (strategy) {
        strategy->tick();
    }
}

int& Combatant::getMana() {
    return mana;
}

std::string Combatant::getName() const {
    return name;
}
