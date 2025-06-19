#include "FishingNet.h"
#include "FishSelector.h"
#include <iostream>

void FishingNet::prepare()
{
    int choice;
    std::cout << "Pasirinkite tinklo dydi (1 - mazas, 2 - vidutinis, 3 - didelis): ";
    std::cin >> choice;
    prepare(choice);
}

void FishingNet::prepare(int sizeChoice)
{
    static const std::unordered_map<int, int> netSizes = {
        {1, 3},
        {2, 5},
        {3, 7}};

    auto it = netSizes.find(sizeChoice);
    if (it != netSizes.end())
    {
        netSize = it->second;
    }
    else
    {
        std::cout << "Netinkamas pasirinkimas. Naudojamas vidutinis tinklas." << std::endl;
        netSize = 5;
    }
}

void FishingNet::fish() const
{
    std::cout << "Gaudoma naudojant tinkla." << std::endl;

    auto caughtFish = FishSelector::getFish(FishCategory::ShallowWater, netSize);

    std::cout << "Pagauta zuvu: ";
    for (size_t i = 0; i < caughtFish.size(); ++i)
    {
        std::cout << caughtFish[i];
        if (i != caughtFish.size() - 1)
            std::cout << ", ";
    }
    std::cout << "." << std::endl;
    std::cout << std::endl;
}
