#include "FishSelector.h"
#include <random>

std::vector<std::string> FishSelector::getFish(FishCategory category, int count)
{
    std::vector<std::string> fishList;
    std::vector<std::string> options;

    if (category == FishCategory::ShallowWater)
    {
        options = {"Kuojyte", "Plakis", "Raude", "Grundzulas", "Karosiukas"};
    }
    else if (category == FishCategory::MediumWater)
    {
        options = {"Eserys", "Karsis", "Starkis", "Lydeka", "Samas"};
    }
    else
    {
        options = {"Ungurys", "Skumbre", "Menke", "Otas", "Juru eserys"};
    }

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, options.size() - 1);

    for (int i = 0; i < count; ++i)
    {
        fishList.push_back(options[dist(rng)]);
    }

    return fishList;
}
