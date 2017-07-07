#include "kociemba_solver.h"
#include <iostream>
#include <iomanip>
#include "Phase1Pruning.h"
#include "cornerPruning.h"
#include "ep1Pruning.h"
#include "ep2Pruning.h"
#include "edgePruning.h"
#include <chrono>

KociembaSolver::KociembaSolver()
{
    phase2pruning.push_back(new cornerPruning());
    phase2pruning.push_back(new ep1Pruning());
    phase2pruning.push_back(new ep2Pruning());
    phase2pruning.push_back(new edgePruning());
}

KociembaSolver::~KociembaSolver()
{
    for (auto pruning_method : phase2pruning)
    {
        delete pruning_method;
    }
    phase2pruning.clear();
}

char KociembaSolver::solve(string scramble)
{
    Cube cube(scramble);
    
    cout << "Solve the scramble \"" << scramble << "\" with KociembaSolver: " << endl;
    char depth = IDA(cube);
    char depth2 = IDAPhase2(cube);
    std::cout << "Total length: " << depth + depth2 << std::endl;
    std::cout << std::endl;
    return depth + depth2;
}

char KociembaSolver::IDA(Cube &cube)
{
    solution = "";
    nodeCnt = 0;
    
    auto start_time = std::chrono::high_resolution_clock::now();

    cout << "Start solving" << endl;
    char depth;
    for (depth = 0; depth <= 20; depth++)
    {
        cout << "Depth " << setfill(' ') << setw(2) << (int)depth << ": " << flush;
        if (treeSearch(cube, depth, -1)) //reset cube???
        {
            cout << "solution, " << setfill(' ') << setw(10) << nodeCnt << " nodes visited" << endl;
            cout << solution.c_str() << endl;
            break;
        }
        else
        {
            cout << "nothing,  " << setfill(' ') << setw(10) << nodeCnt << " nodes visited" << endl;
        }
    }
    cout << "total: " << nodeCnt << " nodes visited" << endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_in_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0;
    cout << "Time: " << duration_in_seconds << " seconds";
    cout << "(" << (int)(nodeCnt / duration_in_seconds) << " nodes / second)" << endl;

    return depth;
}

char KociembaSolver::IDAPhase2(Cube &cube)
{
    solution = "";
    nodeCnt = 0;
    
    auto start_time = std::chrono::high_resolution_clock::now();

    cout << "Start solving" << endl;
    char depth;
    for (depth = 0; depth <= 20; depth++)
    {
        cout << "Depth " << setfill(' ') << setw(2) << (int)depth << ": " << flush;
        if (treeSearchPhase2(cube, depth, -1)) //reset cube???
        {
            cout << "solution, " << setfill(' ') << setw(10) << nodeCnt << " nodes visited" << endl;
            cout << solution.c_str() << endl;
            break;
        }
        else
        {
            cout << "nothing,  " << setfill(' ') << setw(10) << nodeCnt << " nodes visited" << endl;
        }
    }
    cout << "total: " << nodeCnt << " nodes visited" << endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_in_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0;
    cout << "Time: " << duration_in_seconds << " seconds";
    cout << "(" << (int)(nodeCnt / duration_in_seconds) << " nodes / second)" << endl;

    return depth;
}

bool KociembaSolver::treeSearch(Cube &cube, char depth, int lastMove)
{
    nodeCnt++;
    if (depth == 0)
    {
        return cube.is_phase1_solved();
    }
    else
    {
        if (phase1pruning.pruning_number(cube) > depth)
        {
            return false;
        }

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
                    solution = moveNames[move] + moveCntNames[j] + string(" ") + solution;
                    return true;
                }
            }
            cube.apply_move(move);
        }

        return false;
    }
}

bool KociembaSolver::treeSearchPhase2(Cube &cube, char depth, int lastMove)
{
    nodeCnt++;
    if (depth == 0)
    {
        return cube.is_solved();
    }
    else
    {
        for (auto pruning_method : phase2pruning)
        {
            if (pruning_method->pruning_number(cube) > depth)
            {
                return false;
            }
        }

        for (int move = 0; move < 6; move++)
        {
            if (move == lastMove)
                continue;
            if ((lastMove & 1) == 1 && move == lastMove - 1)
                continue;

            for (int j = 0; j < 3; j++)
            {
                cube.apply_move(move);
                if (move < 2 || j == 1) {
                    if (treeSearchPhase2(cube, depth - 1, move))
                    {
                        solution = moveNames[move] + moveCntNames[j] + string(" ") + solution;
                        return true;
                    }
                }
            }
            cube.apply_move(move);
        }

        return false;
    }
}
