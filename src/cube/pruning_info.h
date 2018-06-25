#pragma once

#include <cstdint>
#include <string>

struct PruningInfo
{
    uint64_t state_count;
    int maxDepthBFS;
    int maxDepth;
    std::string pruning_file;
};
