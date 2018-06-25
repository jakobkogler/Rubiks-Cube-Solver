#include "optimal_solver.h"
#include <iostream>
#include <iomanip>
#include <chrono>

class Timer {
public:
    Timer() : start(Clock::now()) {}
    auto getDuration_ms() const {
        auto dur = Clock::now() - start;
        return std::chrono::duration_cast<ms>(dur).count();
    }
private:
    using Clock = std::chrono::high_resolution_clock;
    using ms = std::chrono::milliseconds;
    using double_duration = std::chrono::duration<double>;
    Clock::time_point start;
};

OptimalSolver::OptimalSolver(int edgePruningSize)
    : edgePruningSize(edgePruningSize)
{
    Corners corners;
    cPruning.buildPruneTable(corners);
    cPruning.showPruneInfos(std::cout);
    Edges edges({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, edgePruningSize);
    ePruning.buildPruneTable(edges);
    ePruning.showPruneInfos(std::cout);
}

char OptimalSolver::solve(std::string scramble)
{
    Cube cube(scramble, edgePruningSize);
    
    std::cout << "Solve the scramble \"" << scramble << "\": " << std::endl;
    char depth = IDA(cube);
    std::cout << std::endl;
    return depth;
}

char OptimalSolver::IDA(Cube &cube)
{
    solution = "";
    nodeCnt = 0;
    Timer timer;

    std::cout << "Start solving" << std::endl;
    char depth;
    for (depth = 0; depth <= 20; depth++)
    {
        std::cout << "Depth " << std::setfill(' ') << std::setw(2) << (int)depth << ": " << std::flush;
        if (treeSearch(cube, depth, -1)) //reset cube???
        {
            std::cout << "solution, " << std::setfill(' ') << std::setw(10) << nodeCnt << " nodes visited" << std::endl;
            std::cout << solution.c_str() << std::endl;
            break;
        }
        else
        {
            std::cout << "nothing,  " << std::setfill(' ') << std::setw(10) << nodeCnt << " nodes visited" << std::endl;
        }
    }
    std::cout << "total: " << nodeCnt << " nodes visited" << std::endl;
    double seconds = static_cast<double>(timer.getDuration_ms()) / 1000.;
    int nodes_per_second = static_cast<int>(static_cast<double>(nodeCnt) / seconds);
    std::cout << "Time: " << seconds << " seconds(" << nodes_per_second << " nodes / second)" << std::endl;

    return depth;
}

bool OptimalSolver::treeSearch(Cube &cube, int depth, int lastMove)
{
    nodeCnt++;
    if (depth == 0)
    {
        return cube.is_solved();
    }
    else
    {
        if (cPruning.pruning_number(cube.corners) > depth)
            return false;
        if (ePruning.pruning_number(cube.edges) > depth)
            return false;
        if (ePruning.pruning_number(cube.edges2) > depth)
            return false;

        for (int move = 0; move < 6; move++)
        {
            if (move == lastMove)
                continue;
            if ((lastMove & 1) == 1 && move == lastMove - 1)
                continue;

            for (int j = 0; j < 3; j++)
            {
                cube.apply_move(move);
                if (treeSearch(cube, depth - 1, move))
                {
                    solution = moveNames[move] + moveCntNames[j] + std::string(" ") + solution;
                    return true;
                }
            }
            cube.apply_move(move);
        }

        return false;
    }
}
