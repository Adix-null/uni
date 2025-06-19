#include "FishingSpear.h"
#include "FishSelector.h"
#include <iostream>
#include <random>

void FishingSpear::prepare()
{
    int choice;
    std::cout << "Pasirinkite nardymo gyli:\n";
    std::cout << "1. Seklus\n2. Vidutinis\n3. Gilus\n";
    std::cin >> choice;

    static const std::unordered_map<int, FishingDepth> depthMap = {
        {1, FishingDepth::Shallow},
        {2, FishingDepth::Medium},
        {3, FishingDepth::Deep}
    };

    auto it = depthMap.find(choice);
    if (it != depthMap.end())
    {
        prepare(it->second);
    }
    else
    {
        std::cout << "Netinkamas pasirinkimas. Naudojamas vidutinis gylis.\n";
        prepare(FishingDepth::Medium);
    }
}

void FishingSpear::prepare(FishingDepth depth)
{
    struct Config {
        double success;
        double doubleChance;
        FishCategory category;
    };

    static const std::unordered_map<FishingDepth, Config> configMap = {
        {FishingDepth::Shallow, {0.8, 0.3, FishCategory::ShallowWater}},
        {FishingDepth::Medium,  {0.6, 0.5, FishCategory::MediumWater}},
        {FishingDepth::Deep,    {0.4, 0.8, FishCategory::DeepWater}}
    };

    const auto& config = configMap.at(depth);
    depthLevel = depth;
    successChance = config.success;
    doubleCatchChance = config.doubleChance;
    category = config.category;
}

void FishingSpear::fish() const
{
   static const std::unordered_map<FishingDepth, std::string> depthNames = {
        {FishingDepth::Shallow, "Seklus"},
        {FishingDepth::Medium,  "Vidutinis"},
        {FishingDepth::Deep,    "Gilus"}
    };

    std::cout << "Nardoma i gyli: " << depthNames.at(depthLevel);
    std::cout << ". Pradedamas harpunavimas..." << std::endl;

    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_real_distribution<> chanceDist(0.0, 1.0);

    if (chanceDist(rng) > successChance)
    {
        std::cout << "Nepavyko pagauti zuvies." << std::endl;
        return;
    }

    int count = (chanceDist(rng) < doubleCatchChance) ? 2 : 1;
    auto caught = FishSelector::getFish(category, count);

    std::cout << "Pagauta zuvu: ";
    for (size_t i = 0; i < caught.size(); ++i)
    {
        std::cout << caught[i];
        if (i != caught.size() - 1)
            std::cout << ", ";
    }
    std::cout << "." << std::endl;
}
