#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cassert>
#include <vector>
#include <memory>

using namespace std;

static int objectID = 0;
static int objectCount = 0;

class Product
{
private:
    int barcode;
    string name;
    float weight;
    int id;

    void setName(string name)
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

public:
    Product(int barcode, string name, float weight)
    {
        setBarcode(barcode);
        setName(name);
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
        return to_string(getId()) + " " + to_string(getBarcode()) + " " + getName() + " " + to_string(getWeight());
    }
};

int main()
{
    {
        vector<unique_ptr<Product>> products;
        products.push_back(make_unique<Product>(123, "Strawberry Miau", 1.3f));
        products.push_back(make_unique<Product>(28279, "Shirt", 1.8f));

        assert(objectCount == 2);
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
    }
    assert(objectCount == 0);

    return 0;
}
