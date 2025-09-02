#include "FishingRod.h"
#include "FishCategory.h"
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

int main()
{
    FishingRod rod;

    struct TestCase
    {
        int baitChoice;
        FishCategory expectedCategory;
        std::set<std::string> validFish;
    };

    std::vector<TestCase> tests = {
        {1, FishCategory::ShallowWater, {"Kuojyte", "Plakis", "Raude", "Grundzulas", "Karosiukas"}},
        {2, FishCategory::MediumWater,  {"Eserys", "Karsis", "Starkis", "Lydeka", "Samas"}},
        {3, FishCategory::DeepWater,    {"Ungurys", "Skumbre", "Menke", "Otas", "Juru eserys"}}
    };

    std::cout << "Testuojamos visos 3 masalo pasirinktys:\n";

    for (const auto& test : tests)
    {
        rod.prepare(test.baitChoice);
        std::string fish = rod.getChosenFish();
        FishCategory cat = rod.getFishCategory();

        std::cout << "Bait choice: " << test.baitChoice
                  << " -> Kategorija: " << static_cast<int>(cat)
                  << ", Pagauta: " << fish << std::endl;

        assert(cat == test.expectedCategory);
        assert(test.validFish.count(fish) > 0);
    }

    // Test with invalid input
    rod.prepare(999);
    std::string randomFish = rod.getChosenFish();
    std::cout << "Netinkama pasirinktis -> Gauta: " << randomFish << std::endl;

    std::set<std::string> allFish = {
        "Kuojyte", "Plakis", "Raude", "Grundzulas", "Karosiukas",
        "Eserys", "Karsis", "Starkis", "Lydeka", "Samas",
        "Ungurys", "Skumbre", "Menke", "Otas", "Juru eserys"
    };

    assert(allFish.count(randomFish) > 0);

    std::cout << "\nVisi testai praeiti sekmingai!" << std::endl;
    return 0;
}
