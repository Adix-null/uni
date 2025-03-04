#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>
#include <cassert>
#include <vector>
#include <memory>

// Adomas Bieliūnas 1k 2.1gr
// camelCase, klasės pavadinimai iš didžiosios raidės, kintamųjų ir funkcijų iš mažosios

using namespace std;

static int objectID = 0;
static int objectCount = 0;

class Product
{
private:
    void Setname(string name)
    {
        this->name = name;
    }
    void modifyCount(bool inc)
    {
        if (inc)
        {
            objectID++;
            objectCount++;
        }
        else
        {
            objectCount--;
        }
    }
    int checksum(int num)
    {
        int sum = 0;
        num %= 10;

        while (num > 0)
        {
            sum += num % 10;
            num /= 10;
        }

        return sum % 10;
    }
    int barcode;
    string name;
    float weight;
    int id;

public:
    Product(int barcode, string name, float weight)
    {
        setBarcode(barcode);
        Setname(name);
        setWeight(weight);
        id = objectID;
        modifyCount(true);
    }
    Product(string name, float weight)
    {
        setBarcode(0);
        Setname(name);
        setWeight(weight);
        id = objectID;
        modifyCount(true);
    }

    ~Product()
    {
        modifyCount(false);
    };

    int getBarcode()
    {
        return barcode;
    }
    void setBarcode(int barcode)
    {
        if (barcode < 0)
        {
            throw invalid_argument("Barcode cannot be negative");
        }
        if (checksum(barcode) != barcode % 10)
        {
            throw invalid_argument("Barcode cannot have wrong checksum");
        }
        this->barcode = barcode;
    }

    string getName()
    {
        return name;
    }

    float getWeight()
    {
        return weight;
    }
    void setWeight(float weight)
    {
        if (weight <= 0)
        {
            throw invalid_argument("Weight cannot be negative or zero");
        }
        this->weight = weight;
    }

    int getId()
    {
        return id;
    }

    string toString()
    {
        return to_string(getId()) + "" + to_string(getBarcode()) + "" + getName() + "" + to_string(getWeight());
    }
};

int main()
{
    {
        vector<unique_ptr<Product>> products;
        products.push_back(make_unique<Product>(123, "Strawberry Miau", 1.3f));
        products.push_back(make_unique<Product>(28279, "Shirt", 1.8f));
        products.push_back(make_unique<Product>("Battery", 0.2f));

        assert(objectCount == 3);
        assert(products[0]->getBarcode() == 123);
        assert(products[0]->getName() == "Strawberry Miau");
        assert(products[0]->getWeight() == 1.3f);
        assert(products[0]->getId() == 0);
        cout << products[0]->toString() << endl;

        products[1]->setBarcode(9991110);
        products[1]->setWeight(2.1f);
        assert(products[1]->getBarcode() == 9991110);
        assert(products[1]->getName() == "Shirt");
        assert(products[1]->getWeight() == 2.1f);
        assert(products[1]->getId() == 1);
        cout << products[1]->toString() << endl;

        assert(products[2]->getBarcode() == 0);
        products[2]->setBarcode(420196);
        assert(products[2]->getBarcode() == 420196);
        assert(products[2]->getName() == "Battery");
        assert(products[2]->getWeight() == 0.2f);
        cout << products[2]->toString() << endl;
    }
    assert(objectCount == 0);

    return 0;
}
