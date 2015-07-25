#include "corner.h"
#include <fstream>
#include <iterator>
#include "read_store.h"

void Corner::buildPruneTable()
{
	if (!Read_Store::read_char_vector(prune_table, prune_file_path, state_count))
	{
		prune_table = vector<char>(state_count, 11);
		int visited_count = 0;
		char maxBreathDepthSearch = 8;
	
	
		for (char depth = 0; depth <= maxBreathDepthSearch; depth++)
		{
			pruneTreeSearch(0, depth, depth, -1);
		}
	
	
		for (int i = 0; i < state_count; i++)
		{
			if (prune_table[i] < 11)
				continue;
	
			//Only the position smaller than 11, since 11 is max
			for (char depth = maxBreathDepthSearch + 1; depth < 11; depth++)
			{
				if (solveable(i, depth, maxBreathDepthSearch, -1))
				{
					prune_table[i] = depth;
					break;
				}
			}
		}
		
		Read_Store::store_char_vector(prune_table, prune_file_path);
	}
}

void Corner::pruneTreeSearch(long state, char depth_left, char depth, int lastMove)
{
	if (depth_left == 0)
	{
		if (prune_table[state] > depth)
		{
			prune_table[state] = depth;
		}
	}
	else
	{
		if (prune_table[state] == depth - depth_left)
		{
			for (int move = 0; move < 6; move++)
			{
				if (move == lastMove)
					continue;
				if ((lastMove & 1) == 1 && move == lastMove - 1)
					continue;

				for (int j = 0; j < 3; j++)
				{
					state = apply_transition(state, move);
					pruneTreeSearch(state, depth_left - 1, depth, move);
				}
				state = apply_transition(state, move);
			}
		}
	}
}

long Corner::apply_transition(long state, int move)
{
	long permutation_state = state / 2187;
	long orientation_state = state % 2187;

	permutation_state = permutation_transition_table[permutation_state][move];
	orientation_state = orientation_transition_table[orientation_state][move];

	return permutation_state * 2187 + orientation_state;
}

bool Corner::solveable(long state, char depth, char maxBreathDepthSearch, int lastMove)
{
	if (prune_table[state] == depth)
	{
		return true;
	}
	else if (depth <= maxBreathDepthSearch)
	{
		return false;
	}
	else
	{
		for (int move = 0; move < 6; move++)
		{
			if (move == lastMove)
				continue;
			if ((lastMove & 1) == 1 && move == lastMove - 1)
				continue;

			for (int j = 0; j < 3; j++)
			{
				state = apply_transition(state, move);
				if (solveable(state, depth - 1, maxBreathDepthSearch, move))
				{
					return true;
				}
			}
			state = apply_transition(state, move);
		}

		return false;
	}
}
