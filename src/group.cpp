#include "group.h"
#include "read_store.h"

void Group::buildTransitionTable()
{
	transition_table = vector<vector<long long> >(state_count, vector<long long>(6));
	vector<int> arr(piece_count);

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

void Group::buildPruneTable()
{
	if (!Read_Store::read_char_vector(prune_table, prune_file_path, state_count))
	{
		prune_table = vector<char>(state_count, 20);
	
		int visited_count = 0;
		char depth = 0;
	
		while (visited_count < state_count)
		{
			int cnt = pruneTreeSearch(0, prune_table, depth, depth, -1);
			visited_count += cnt;
			depth++;
		}
	
		Read_Store::store_char_vector(prune_table, prune_file_path);
	}
}

int Group::pruneTreeSearch(int state, vector<char> & table, char depth_left, char depth, int lastMove)
{
	int cnt = 0;

	if (depth_left == 0)
	{
		if (table[state] > depth)
		{
			table[state] = depth;
			cnt = 1;
		}
	}
	else
	{
		if (table[state] == depth - depth_left)
		{
			for (int move = 0; move < 6; move++)
			{
				if (move == lastMove)
					continue;
				if ((lastMove & 1) == 1 && move == lastMove - 1)
					continue;

				for (int j = 0; j < 3; j++)
				{
					state = transition_table[state][move];
					cnt += pruneTreeSearch(state, table, depth_left - 1, depth, move);
				}
				state = transition_table[state][move];
			}
		}
	}

	return cnt;
}
