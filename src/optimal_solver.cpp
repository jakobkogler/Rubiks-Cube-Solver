#include "optimal_solver.h"
#include "indexing.h"
#include "corner_permutation.h"
#include "corner_orientation.h"
#include "corner.h"
#include "edge_orientation.h"
#include "edge_permutation.h"
#include <iostream>
#include <ctime>
#include <sstream>

double diffclock(clock_t clock1, clock_t clock2)
{
	double diffticks = abs(clock1 - clock2);
	double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
	return diffms;
}

OptimalSolver::OptimalSolver()
{
	CornerPermutation cp;
	cp.buildTransitionTable();
	cp_transition = cp.getTransitionTable();

	CornerOrientation co;
	co.buildTransitionTable();
	co_transition = co.getTransitionTable();

	Corner corner(cp_transition, co_transition);
	corner.buildPruneTable();
	c_prune = corner.getPruneTable();

	EdgeOrientation eo;
	eo.buildTransitionTable();
	eo.buildPruneTable();
	eo_transition = eo.getTransitionTable();
	eo_prune = eo.getPruneTable();

	EdgePermutation ep;
	ep.buildTransitionTable();
	ep.buildPruneTable();
	//ep.buildPruneTable2();
	ep_transition = ep.getTransitionTable();
	ep1_prune = ep.getPruneTable();
	//ep2_prune = ep.getPruneTable2();

	// IDA* for e_prune
	prune_count = 0;
	e_prune.clear();
	char depth = 0;
	long max = 12 * 11 * 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;
	cout << endl << "Edge Prune Table:" << endl;
	while (prune_count < max && depth < 7)
	{
		prune_treeSearch(0, 366288, depth, depth, -1);
		cout << "Depth " << (int)depth << ": " << prune_count << endl;
		depth++;
	}

	long sum_c_prune = 0;
	for (long i = 0; i < c_prune.size(); i++)
		sum_c_prune += c_prune[i];
	cout << "average prune depth corners: " << (sum_c_prune / (double)c_prune.size()) << endl;

	long sum_e1_prune = 0;
	for (long i = 0; i < ep1_prune.size(); i++)
		sum_e1_prune += ep1_prune[i];
	cout << "average prune depth corners: " << (sum_e1_prune / (double)ep1_prune.size()) << endl;

	moveNames[0] = string("U");
	moveNames[1] = string("D");
	moveNames[2] = string("R");
	moveNames[3] = string("L");
	moveNames[4] = string("F");
	moveNames[5] = string("B");
	moveCntNames[0] = string(" ");
	moveCntNames[1] = string("2");
	moveCntNames[2] = string("'");
};

char OptimalSolver::solve(string scramble)
{
	vector<int> cp_vec{ 0, 1, 2, 3, 4, 5, 6, 7 };
	vector<int> co_vec{ 0, 0, 0, 0, 0, 0, 0, 0 };
	vector<int> eo_vec{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	vector<int> ep1_vec{ 0, 1, 2, 3, 4, 5 };
	vector<int> ep2_vec{ 6, 7, 8, 9, 10, 11, 12 };
	
	apply_scramble(scramble, cp_vec, co_vec, eo_vec, ep1_vec, ep2_vec);
	
	cout << "Solve the scramble \"" << scramble << "\": " << endl;
	char depth = IDA(cp_vec, co_vec, eo_vec, ep1_vec, ep2_vec);
	cout << endl;
	return depth;
}

char OptimalSolver::IDA(vector<int> cornerPermutation, vector<int> cornerOrientation, vector<int> edgeOrientation, vector<int> edgePermutation1, vector<int> edgePermutation2)
{
	int cornerPerm = Indexing::permutation_to_index(cornerPermutation);
	int cornerOrient = Indexing::orientation_to_index_dependent(cornerOrientation, 3);
	int edgeOrient = Indexing::orientation_to_index_dependent(edgeOrientation, 2);
	EdgePermutation ep;
	int edgePerm1 = ep.array_to_index(edgePermutation1);
	int edgePerm2 = ep.array_to_index(edgePermutation2);

	solution = "";
	nodeCnt = 0;
	clock_t start = clock();

	cout << "Start solving" << endl;
	char depth;
	for (depth = 0; depth <= 20; depth++)
	{
		cout << "Depth " << (int)depth << ": ";
		if (treeSearch(cornerPerm, cornerOrient, edgeOrient, edgePerm1, edgePerm2, depth, -1))
		{
			cout << "solution found (" << nodeCnt << " nodes visited)\n" << solution.c_str() << endl;
			break;
		}
		else
		{
			cout << "nothing (" << nodeCnt << " nodes visited)" << endl;
		}
	}
	cout << "total: " << nodeCnt << " nodes visited" << endl;
	clock_t end = clock();
	double seconds = diffclock(start, end) / 1000.0;
	cout << "Time: " << seconds << " seconds(" << (int)(nodeCnt / seconds) << " nodes / second)" << endl;

	return depth;
}

bool OptimalSolver::treeSearch(int cornerPermutation, int cornerOrientation, int edgeOrientation, int edgePermutation1, int edgePermutation2, char depth, int lastMove)
{
	nodeCnt++;
	if (depth == 0)
	{
		return (cornerPermutation == 0 && cornerOrientation == 0 && edgeOrientation == 0 && edgePermutation1 == 0 && edgePermutation2 == 366288);
	}
	else
	{
		long p = edgePermutation1 * 665280L + edgePermutation2;
		char ep_prune_value = 7;
		if (e_prune.count(p) == 1)
			ep_prune_value = e_prune[p];

		if (c_prune[cornerPermutation * 2187 + cornerOrientation] <= depth && eo_prune[edgeOrientation] <= depth && ep_prune_value <= depth)
		{
			for (int move = 0; move < 6; move++)
			{
				if (move == lastMove)
					continue;
				if ((lastMove & 1) == 1 && move == lastMove - 1)
					continue;

				for (int j = 0; j < 3; j++)
				{
					cornerPermutation = cp_transition[cornerPermutation][move];
					cornerOrientation = co_transition[cornerOrientation][move];
					edgeOrientation = eo_transition[edgeOrientation][move];
					edgePermutation1 = ep_transition[edgePermutation1][move];
					edgePermutation2 = ep_transition[edgePermutation2][move];

					if (treeSearch(cornerPermutation, cornerOrientation, edgeOrientation, edgePermutation1, edgePermutation2, depth - 1, move))
					{
						solution = moveNames[move] + moveCntNames[j] + string(" ") + solution;
						return true;
					}
				}
				cornerPermutation = cp_transition[cornerPermutation][move];
				cornerOrientation = co_transition[cornerOrientation][move];
				edgeOrientation = eo_transition[edgeOrientation][move];
				edgePermutation1 = ep_transition[edgePermutation1][move];
				edgePermutation2 = ep_transition[edgePermutation2][move];
			}
		}

		return false;
	}
}

void OptimalSolver::prune_treeSearch(long ep1, long ep2, char depth_left, char depth, int lastMove)
{
	long p = ep1 * 665280 + ep2;

	if (depth_left == 0)
	{
		if (e_prune.count(p) == 0)
		{
			e_prune[p] = depth;
			prune_count++;
		}
	}
	else
	{
		if (e_prune[p] == depth - depth_left)
		{
			for (int move = 0; move < 6; move++)
			{
				if (move == lastMove)
					continue;
				if ((lastMove & 1) == 1 && move == lastMove - 1)
					continue;

				for (int j = 0; j < 3; j++)
				{
					ep1 = ep_transition[ep1][move];
					ep2 = ep_transition[ep2][move];
					prune_treeSearch(ep1, ep2, depth_left - 1, depth, move);
				}
				ep1 = ep_transition[ep1][move];
				ep2 = ep_transition[ep2][move];
			}
		}
	}
}

void OptimalSolver::apply_scramble(string scramble, vector<int> &cp_vec, vector<int> &co_vec, vector<int> &eo_vec, vector<int> &ep1_vec, vector<int> &ep2_vec)
{
	CornerPermutation cp;
	CornerOrientation co;
	EdgeOrientation eo;
	EdgePermutation ep;
	
	stringstream ss(scramble);
	string turn;
	
	while (ss >> turn)
	{
		int move;
		switch (turn[0])
		{
			case 'U':
				move = 0;
				break;
			case 'D':
				move = 1;
				break;
			case 'R':
				move = 2;
				break;
			case 'L':
				move = 3;
				break;
			case 'F':
				move = 4;
				break;
			case 'B':
				move = 5;
				break;
			default:
				move = 0;
		}
		
		int count = 1;
		if (turn.size() == 2)
		{
			switch (turn[1])
			{
				case '2':
					count = 2;
					break;
				case '\'':
					count = 3;
					break;
				default:
					count = 1;
			}
		}
		
		for (int i = 0; i < count; i++)
		{
			cp.apply_move(cp_vec, move);
			co.apply_move(co_vec, move);
			eo.apply_move(eo_vec, move);
			ep.apply_move(ep1_vec, move);
			ep.apply_move(ep2_vec, move);
		}
	}
}