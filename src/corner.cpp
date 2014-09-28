#include "corner.h"

void Corner::buildPruneTable()
{
	prune_table = vector<int>(state_count, 11);
	int visited_count = 0;
	int maxBreathDepthSearch = 8;


	for (int depth = 0; depth <= maxBreathDepthSearch; depth++)
	{
		pruneTreeSearch(0, depth, depth, -1);
	}


	for (int i = 0; i < state_count; i++)
	{
		if (prune_table[i] < 11)
			continue;

		//Only the position smaller than 11, since 11 is max
		for (int depth = maxBreathDepthSearch + 1; depth < 11; depth++)
		{
			if (solveable(i, depth, maxBreathDepthSearch, -1))
			{
				prune_table[i] = depth;
				break;
			}
		}
	}
}

void Corner::pruneTreeSearch(long state, int depth_left, int depth, int lastMove)
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

bool Corner::solveable(int state, int depth, int maxBreathDepthSearch, int lastMove)
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
