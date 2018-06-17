#include "group.h"

void Group::buildTransitionTable()
{
    transition_table = std::vector<std::vector<long long>>(state_count, std::vector<long long>(6));
    std::vector<int> arr(piece_count);

    for (int index = 0; index < state_count; index++)
    {
        for (int move = 0; move < 6; move++)
        {
            index_to_array(index, arr);
            apply_move(arr, move);
            transition_table[index][move] = array_to_index(arr);
        }
    }
}
