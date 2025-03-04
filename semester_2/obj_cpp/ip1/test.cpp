#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <exception>
#include <stdexcept>

using namespace std;

#define MAX_NAME 32
#define MAX_HEALTH 1000
#define MAX_POWER 500

class GameCharacter
{
public:
    string name;
    int health;
    int attackPower;

    int id;

    static int uniqueId;
    static int ObjectCount;

    GameCharacter()
    {
        init("Name", -1, 0);
    }

    GameCharacter(string name, int health, int attackPower)
    {
        init(name, health, attackPower);
    }

    ~GameCharacter()
    {
        --ObjectCount;
    }

    void setName(string characterName)
    {
        validateName(characterName);
        name = characterName;
    }

    string getName()
    {
        return name;
    }

    int getHealth()
    {
        return health;
    }

    int getAttackPower()
    {
        return attackPower;
    }

    int getPersonalId()
    {
        return id;
    }

    string toString()
    {
        stringstream ss;
        ss << name << " " << health << " " << attackPower;
        return ss.str();
    }

    static int getObjectCount()
    {
        return ObjectCount;
    }

    static int getIdCount()
    {
        return uniqueId;
    }

private:
    void init(string name, int health, int attackPower)
    {
        setName(name);
        setHealth(health);
        setAttackPower(attackPower);
        id = uniqueId++;
        ++ObjectCount;
    }

    void setHealth(int characterHealth)
    {
        validateHealth(characterHealth);
        health = characterHealth;
    }

    void setAttackPower(int characterAttackPower)
    {
        validateAttackPower(characterAttackPower);
        attackPower = characterAttackPower;
    }

    void validateHealth(int characterHealth)
    {
        if (characterHealth <= 0 && characterHealth != -1)
        {
            throw invalid_argument("Health must be positive or -1 for invincible character.");
        }
        if (characterHealth > MAX_HEALTH)
        {
            throw invalid_argument("Health cannot exceed " + to_string(MAX_HEALTH) + ".");
        }
    }

    void validateAttackPower(int characterAttackPower)
    {
        if (characterAttackPower > MAX_POWER)
        {
            throw invalid_argument("Attack power cannot exceed " + to_string(MAX_POWER) + ".");
        }
    }

    void validateName(string characterName)
    {
        if (characterName == "")
        {
            throw invalid_argument("Character name cannot be empty.");
        }
        if (characterName[0] < 'A' || characterName[0] > 'Z')
        {
            throw invalid_argument("Name must start with an uppercase letter.");
        }
        if (characterName.length() > MAX_NAME)
        {
            throw invalid_argument("Name length cannot exceed " + to_string(MAX_NAME) + " characters.");
        }
        bool space = false;
        for (int i = 0; i < characterName.length(); ++i)
        {
            if (characterName[i] == ' ' && characterName[i + 1] == '\0')
            {
                throw invalid_argument("Invalid character name. Last character cannot be space.");
            }
            if ((characterName[i] < 'A' || characterName[i] > 'Z') && (characterName[i] < 'a' || characterName[i] > 'z'))
            {
                if (characterName[i] == ' ' && !space)
                {
                    space = true;
                    continue;
                }
                else if (space)
                {
                    throw invalid_argument("Invalid character name. It should not contain spaces following another space.");
                }
                throw invalid_argument("Name must contain only alphabetic characters and spaces.");
            }
            space = false;
        }
    }
};

int GameCharacter::uniqueId = 0;
int GameCharacter::ObjectCount = 0;

int main()
{
    try
    {
        assert(GameCharacter::getObjectCount() == 0);

        GameCharacter *npc[3];

        npc[0] = new GameCharacter("Leonardo da Vinci", 1000, 20);

        assert(npc[0]->toString() == "Leonardo da Vinci 1000 20");
        assert(GameCharacter::getObjectCount() == 1);

        assert(npc[0]->getPersonalId() == 0);
        assert(npc[0]->getName() == "Leonardo da Vinci");
        assert(npc[0]->getHealth() == 1000);
        assert(npc[0]->getAttackPower() == 20);

        npc[1] = new GameCharacter();

        assert(npc[1]->toString() == "Name -1 0");
        assert(GameCharacter::getObjectCount() == 2);
        assert(GameCharacter::getIdCount() == 2);

        assert(npc[1]->getPersonalId() == 1);
        assert(npc[1]->getName() == "Name");
        assert(npc[1]->getHealth() == -1);
        assert(npc[1]->getAttackPower() == 0);

        npc[1]->setName("B");
        assert(npc[1]->getName() == "B");

        npc[2] = new GameCharacter("Jack", 10, 30);

        assert(GameCharacter::getObjectCount() == 3);
        assert(GameCharacter::getIdCount() == 3);

        assert(npc[2]->getPersonalId() == 2);
        assert(npc[2]->getName() == "Jack");
        assert(npc[2]->getHealth() == 10);
        assert(npc[2]->getAttackPower() == 30);

        for (int i = 0; i < 3; ++i)
        {
            delete npc[i];
        }
        assert(GameCharacter::getObjectCount() == 0);
        assert(GameCharacter::getIdCount() == 3);
    }
    catch (invalid_argument e)
    {
        cout << e.what() << endl;
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown error." << endl;
    }
}