#include "CombatantAttack.h"


MeleeAttack::MeleeAttack(int baseDamage, float critChance)
    : baseDamage(baseDamage), critChance(critChance) {}

std::string MeleeAttack::getName() const {
    return "Melee Slash";
}

bool MeleeAttack::canUse() const {
    return true;
}

int MeleeAttack::calculateDamage() const {
    float roll = randomFloat();
    int damage = baseDamage;
    if (roll < critChance) {
        damage *= 2;
        if (g_debugEnabled) {
            std::cout << "Critical hit!\n";
        }
    }
    return damage;
}

void MeleeAttack::use() {
    if (g_debugEnabled) {
        std::cout << "Dealt " << calculateDamage() << " physical damage.\n";
    }
}

void MeleeAttack::tick() {

}

std::string MeleeAttack::getDamageType() const {
    return "Physical";
}