#include "cube.h"
#include <vector>
#include <sstream>
#include <regex>

Cube::Cube(int edgePruningSize)
{
    CornerOrientation cornerOrientation;
    CornerPermutation cornerPermutation;
    coState = cornerOrientation.array_to_index(std::vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 });
    cpState = cornerPermutation.array_to_index(std::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7 });
    edges = Edges{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, edgePruningSize};
    edges2 = Edges{{10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1}, edgePruningSize};

    cornerOrientation.buildTransitionTable();
    coTransition = cornerOrientation.getTransitionTable();

    cornerPermutation.buildTransitionTable();
    cpTransition = cornerPermutation.getTransitionTable();
}

Cube::Cube(std::string scramble, int edgePruningSize) : Cube(edgePruningSize)
{
    std::map<char, int> moveNames{{'U', 0}, {'D', 1}, {'R', 2}, {'L', 3}, {'F', 4}, {'B', 5}};
    std::map<char, int> repeatNames{{'\'', 3}, {'2', 2}};

    std::smatch sm;
    std::regex r("([UDRLFB][2']?)");
    std::regex_iterator<std::string::iterator> it(scramble.begin(), scramble.end(), r);
    std::regex_iterator<std::string::iterator> end;

    while (it != end)
    {
        std::string match = it->str();
        int move = moveNames[match[0]];
        int repeats = 1;
        if (match.size() > 1)
            repeats = repeatNames[match[1]];

        for (int i = 0; i < repeats; i++)
            apply_move(move);

        ++it;
    }
}

void Cube::apply_move(int move)
{
    coState = coTransition[coState][move];
    cpState = cpTransition[cpState][move];
    edges.apply_move(move);
    edges2.apply_move(move);
}

bool Cube::is_solved()
{
    return cpState == 0 && coState == 0 && edges.to_index() == std::pair<uint32_t, uint32_t>{0, 0} && edges2.to_index() == std::pair<uint32_t, uint32_t>{0, 0};
}
