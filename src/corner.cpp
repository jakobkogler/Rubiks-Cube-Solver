#include "corner.h"
#include <fstream>
#include <iterator>

void Corner::buildPruneTable()
{
	if (!try_read_from_file("corner_prune.data"))
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
		
		store_to_file_prune("corner_prune.data");
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

void Corner::store_to_file_prune(string path)
{
	ofstream file(path.c_str(), ios::out | ofstream::binary);
	file.write(reinterpret_cast<const char *>(&prune_table[0]), prune_table.size()*sizeof(char));
	file.close();
}

bool Corner::try_read_from_file(string path)
{
	ifstream file(path.c_str(), ios::binary);
	if (file.good())
	{
		prune_table.reserve(state_count);
		prune_table.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
		file.close();
		return prune_table.size() == state_count;
	}
	else
	{
		file.close();
		return false;
	}
}
