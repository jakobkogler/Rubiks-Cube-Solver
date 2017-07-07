#include "Phase1Pruning.h"
#include "fileio.h"
#include <iostream>
#include <algorithm>

Phase1Pruning::Phase1Pruning()
{
    file_path = "Phase1Pruning.data";

    buildPruneTable();
}

int Phase1Pruning::pruning_number(Cube &cube)
{
    return prune_table[(cube.getCoState() * 2048LL + cube.getEoState()) * 495LL + cube.getUDSliceState()];
}

void Phase1Pruning::buildPruneTable()
{
    CornerOrientation cornerOrientation;
    EdgeOrientation edgeOrientation;
    UDSlice_Coord UDSlice;

    cornerOrientation.buildTransitionTable();
    coTransition = cornerOrientation.getTransitionTable();

    edgeOrientation.buildTransitionTable();
    eoTransition = edgeOrientation.getTransitionTable();

    UDSlice.buildTransitionTable();
    UDSliceTransition = UDSlice.getTransitionTable();

    long long state_count = (long long)cornerOrientation.get_state_count() * (long long)edgeOrientation.get_state_count() * (long long)UDSlice.get_state_count();

    if (!FileIO::read_char_vector(prune_table, file_path, state_count))
    {
        prune_table = vector<char>(state_count, 20);
        long long sum = 0;

        std::cout << "Generating Pruning Table for Phase1: (" << state_count << " states)" << std::endl;
        prune_table[425] = 0;
        std::cout << "Depth 0: 1" << std::endl;
        for (int i = 0; i < 15; i++) {
            std::cout << "Depth " << i + 1 << ": ";
            long long cnt = 0;
            for (int co_state = 0; co_state < cornerOrientation.get_state_count(); co_state++) {
                for (int eo_state = 0; eo_state < edgeOrientation.get_state_count(); eo_state++) {
                    for (int UDSlice_state = 0; UDSlice_state < UDSlice.get_state_count(); UDSlice_state++) {
                        long long state = (co_state * 2048LL + eo_state) * 495LL + UDSlice_state;
                        char depth = prune_table[state];
                        if (depth != i) continue;
                        for (int move = 0; move < 6; move++)
                        {
                            for (int j = 0; j < 3; j++)
                            {
                                co_state = coTransition[co_state][move];
                                eo_state = eoTransition[eo_state][move];
                                UDSlice_state = UDSliceTransition[UDSlice_state][move];
                                state = (co_state * 2048LL + eo_state) * 495LL + UDSlice_state;
                                if (prune_table[state] > depth + 1) {
                                    prune_table[state] = depth + 1;
                                    cnt++;
                                }
                                // prune_table[state] = std::min(prune_table[state], (char)(depth + 1));
                            }
                            co_state = coTransition[co_state][move];
                            eo_state = eoTransition[eo_state][move];
                            UDSlice_state = UDSliceTransition[UDSlice_state][move];
                        }
                    }
                }
            }
            std::cout << cnt << std::endl;
            sum += cnt * (i + 1);
        }
        std::cout << "Average pruning value: " << sum / (double)state_count << std::endl;

        FileIO::store_char_vector(prune_table, file_path);
    }
}

