
#pragma once
#include <string>
#include <memory>
#include <queue>
#include <vector>
#include <iostream>
#include <ctime>

// Global debug flag
extern bool g_debugEnabled;

// Base Strategy Interface
class AttackStrategy
{
public:
    virtual ~AttackStrategy() = default;
    virtual std::string getName() const = 0;
    virtual bool canUse() const = 0;
    virtual void use() = 0;
    virtual void tick() = 0;
    virtual std::string getDamageType() const = 0;
    virtual int calculateDamage() const = 0;

    static float randomFloat(float min = 0.0f, float max = 1.0f);
    static void setTestRolls(const std::vector<float> &rolls);
    static void clearTestRolls();

private:
    static std::queue<float> testRolls;
};

// Combatant Class
class Combatant
{
public:
    Combatant(const std::string &name);
    ~Combatant();

    template <typename T, typename... Args>
    void setStrategy(Args &&...args)
    {
        strategy = std::make_unique<T>(std::forward<Args>(args)...);
    }

    void performAttack();
    void tickCooldown();
    int &getMana();
    std::string getName() const;

private:
    std::string name;
    std::unique_ptr<AttackStrategy> strategy;
    int mana = 100;
};

// Concrete Strategies
class MeleeAttack : public AttackStrategy
{
public:
    MeleeAttack(int baseDamage, float critChance);
    std::string getName() const override;
    bool canUse() const override;
    int calculateDamage() const override;
    void use() override;
    void tick() override;
    std::string getDamageType() const override;

private:
    int baseDamage;
    float critChance;
};

class FireballAttack : public AttackStrategy
{
public:
    FireballAttack(int &manaRef, int baseDamage, float burnChance, int manaCost, int maxUses);
    std::string getName() const override;
    bool canUse() const override;
    int calculateDamage() const override;
    void use() override;
    void tick() override;
    std::string getDamageType() const override;

private:
    int baseDamage;
    float burnChance;
    int &mana;
    int manaCost;
    int maxUses;
    int usesLeft;
    bool isCharging;
};