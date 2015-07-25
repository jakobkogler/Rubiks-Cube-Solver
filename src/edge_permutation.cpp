#include "edge_permutation.h"

void EdgePermutation::apply_move(vector<int> & arr, int move)
{
	if (move == 0)
	{
		//move U
		for (int i = 0; i < 6; i++)
		{
			if (arr[i] == 0)
			{
				arr[i] = 1;
			}
			else if (arr[i] == 1)
			{
				arr[i] = 2;
			}
			else if (arr[i] == 2)
			{
				arr[i] = 3;
			}
			else if (arr[i] == 3)
			{
				arr[i] = 0;
			}
		}
	}
	else if (move == 1)
	{
		//move D
		for (int i = 0; i < 6; i++)
		{
			if (arr[i] == 8)
			{
				arr[i] = 11;
			}
			else if (arr[i] == 11)
			{
				arr[i] = 10;
			}
			else if (arr[i] == 10)
			{
				arr[i] = 9;
			}
			else if (arr[i] == 9)
			{
				arr[i] = 8;
			}
		}
	}
	else if (move == 2)
	{
		//move R
		for (int i = 0; i < 6; i++)
		{
			if (arr[i] == 1)
			{
				arr[i] = 5;
			}
			else if (arr[i] == 5)
			{
				arr[i] = 9;
			}
			else if (arr[i] == 9)
			{
				arr[i] = 6;
			}
			else if (arr[i] == 6)
			{
				arr[i] = 1;
			}
		}
	}
	else if (move == 3)
	{
		//move L
		for (int i = 0; i < 6; i++)
		{
			if (arr[i] == 3)
			{
				arr[i] = 7;
			}
			else if (arr[i] == 7)
			{
				arr[i] = 11;
			}
			else if (arr[i] == 11)
			{
				arr[i] = 4;
			}
			else if (arr[i] == 4)
			{
				arr[i] = 3;
			}
		}
	}
	else if (move == 4)
	{
		//move F
		for (int i = 0; i < 6; i++)
		{
			if (arr[i] == 2)
			{
				arr[i] = 6;
			}
			else if (arr[i] == 6)
			{
				arr[i] = 10;
			}
			else if (arr[i] == 10)
			{
				arr[i] = 7;
			}
			else if (arr[i] == 7)
			{
				arr[i] = 2;
			}
		}
	}
	else if (move == 5)
	{
		//move B
		for (int i = 0; i < 6; i++)
		{
			if (arr[i] == 0)
			{
				arr[i] = 4;
			}
			else if (arr[i] == 4)
			{
				arr[i] = 8;
			}
			else if (arr[i] == 8)
			{
				arr[i] = 5;
			}
			else if (arr[i] == 5)
			{
				arr[i] = 0;
			}
		}
	}
}

int EdgePermutation::array_to_index(vector<int> const& arr)
{
	static const unsigned int factorial[] = { 1, 1, 2, 6, 24, 120, 720,	5040, 40320, 362880, 3628800, 39916800, 479001600 };

	int index = 0;
	bool usedPieces[12];
	for (int i = 0; i < 12; i++)
		usedPieces[i] = false;

	for (int i = 0; i < 6; i++)
	{
		int pieceCnt = 0;
		for (int j = 0; j < arr[i]; j++)
		{
			if (!usedPieces[j])
				pieceCnt++;
		}
		index += factorial[11 - i] / factorial[6] * pieceCnt;
		usedPieces[arr[i]] = true;
	}

	return index;
}


void EdgePermutation::index_to_array(int index, vector<int> & arr)
{
	static const unsigned int factorial[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600 };
	bool usedPieces[12];
	for (int i = 0; i < 12; i++)
		usedPieces[i] = false;

	for (int i = 0; i < 6; i++)
	{
		int pieceIdx = index / (factorial[11 - i] / factorial[6]);
		index %= (factorial[11 - i] / factorial[6]);

		int piece = 0;
		while (usedPieces[piece] || pieceIdx > 0)
		{
			if (!usedPieces[piece])
				pieceIdx--;
			piece++;
		}

		arr[i] = piece;
		usedPieces[piece] = true;
	}
}

void EdgePermutation::buildPruneTable2()
{
	prune_table2 = vector<char>(state_count, 20);

	int visited_count = 0;
	char depth = 0;

	while (visited_count < state_count)
	{
		int cnt = pruneTreeSearch(366288, prune_table2, depth, depth, -1);
		visited_count += cnt;
		depth++;
	}
}
