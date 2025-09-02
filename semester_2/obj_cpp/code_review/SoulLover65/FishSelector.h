#ifndef FISHSELECTOR_H_INCLUDED
#define FISHSELECTOR_H_INCLUDED

#include "FishCategory.h"
#include <string>
#include <vector>

class FishSelector
{
public:
    static std::vector<std::string> getFish(FishCategory category, int count);
};

#endif // FISHSELECTOR_H_INCLUDED
