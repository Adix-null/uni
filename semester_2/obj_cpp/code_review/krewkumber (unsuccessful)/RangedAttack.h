

class RangedAttack : public AttackStrategy
{
public:
    RangedAttack(int baseDamage, float burnChance, int manaCost, int maxUses);
    std::string getName() const override;
    bool canUse() const override;
    int calculateDamage() const override;
    void use() override;
    void tick() override;
    std::string getDamageType() const override;

private:
    int baseDamage;
    float burnChance;
    int manaCost;
    int maxUses;
    int usesLeft;
    bool isCharging;
};