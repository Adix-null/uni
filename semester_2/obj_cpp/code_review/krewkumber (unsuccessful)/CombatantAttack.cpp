#include "CombatantAttack.h"

bool g_debugEnabled = false; // Global debug flag

std::queue<float> AttackStrategy::testRolls;

float AttackStrategy::randomFloat(float min, float max) {
    if (!testRolls.empty()) {
        float val = testRolls.front();
        testRolls.pop();
        return val;
    }
    return min + static_cast<float>(rand()) / (RAND_MAX / (max - min));
}

void AttackStrategy::setTestRolls(const std::vector<float>& rolls) {
    testRolls = std::queue<float>();
    for (float r : rolls) testRolls.push(r);
}

void AttackStrategy::clearTestRolls() {
    testRolls = std::queue<float>();
}