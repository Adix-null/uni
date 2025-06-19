#include "FishingRod.h"
#include "FishSelector.h"
#include "FishingDepth.h"
#include <iostream>

void FishingRod::prepare()
{
    int choice;
    std::cout << "Pasirinkite meškerės tipą (1 - ShallowWater, 2 - MediumWater, 3 - DeepWater): ";
    std::cin >>
        choice;
    prepare(choice);
}

void FishingRod::prepare(int baitChoice)
{
    static const std::unordered_map<int, FishingDepth> depthMap = {
        {1, FishingDepth::Shallow},
        {2, FishingDepth::Medium},
        {3, FishingDepth::Deep}};

    static const std::unordered_map<int, FishCategory> fishMap = {
        {1, FishCategory::ShallowWater},
        {2, FishCategory::MediumWater},
        {3, FishCategory::DeepWater}};

    auto it = depthMap.find(baitChoice);
    if (it != depthMap.end())
    {
        depthLevel = it->second;
        category = fishMap.at(baitChoice);
        chosenFish = FishSelector::getFish(category, 1).front();
    }
    else
    {
        std::cout << "Netinkamas pasirinkimas. Naudojamas vidutinis gylis." << std::endl;
        category = FishCategory::MediumWater;
        chosenFish = FishSelector::getFish(category, 1).front();
    }
}

void FishingRod::fish() const
{
    std::cout << "Gaudoma naudojant meškerę." << std::endl;

    auto caughtFish = FishSelector::getFish(category, 1);

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
std::string FishingRod::getChosenFish() const
{
    return chosenFish;
}
FishCategory FishingRod::getFishCategory() const
{
    return category;
}