#include "optimal_solver.h"
#include "indexing.h"
#include "corner_permutation.h"
#include "corner_orientation.h"
#include "corner.h"
#include "edge_orientation.h"
#include "edge_permutation.h"
#include <iostream>

OptimalSolver::OptimalSolver()
{
	CornerPermutation cp;
	cp.buildTransitionTable();
	cp.buildPruneTable();
	cp_transition = cp.getTransitionTable();

	CornerOrientation co;
	co.buildTransitionTable();
	co.buildPruneTable();
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
	ep_transition = ep.getTransitionTable();

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

int OptimalSolver::IDA(vector<int> cornerPermutation, vector<int> cornerOrientation, vector<int> edgeOrientation, vector<int> edgePermutation1, vector<int> edgePermutation2)
{
	int cornerPerm = Indexing::permutation_to_index(cornerPermutation);
	int cornerOrient = Indexing::orientation_to_index_dependent(cornerOrientation, 3);
	int edgeOrient = Indexing::orientation_to_index_dependent(edgeOrientation, 2);
	EdgePermutation ep;
	int edgePerm1 = ep.array_to_index(edgePermutation1);
	int edgePerm2 = ep.array_to_index(edgePermutation2);

	solution = "";
	nodeCnt = 0;

	cout << "Start solving" << endl;
	int depth;
	for (depth = 0; depth <= 20; depth++)
	{
		nodeResentCnt = 0;
		cout << "Depth " << depth << ": ";
		if (treeSearch(cornerPerm, cornerOrient, edgeOrient, edgePerm1, edgePerm2, depth, -1))
		{
			cout << "solution found (" << nodeResentCnt << " nodes visited)\n" << solution.c_str() << endl;
			break;
		}
		else
		{
			cout << "nothing (" << nodeResentCnt << " nodes visited)" << endl;
		}
		nodeCnt += nodeResentCnt;
	}
	cout << "total: " << nodeResentCnt << " nodes visited" << endl;

	return depth;
}

bool OptimalSolver::treeSearch(int cornerPermutation, int cornerOrientation, int edgeOrientation, int edgePermutation1, int edgePermutation2, int depth, int lastMove)
{
	nodeResentCnt++;
	if (depth == 0)
	{
		return (cornerPermutation == 0 && cornerOrientation == 0 && edgeOrientation == 0 && edgePermutation1 == 0 && edgePermutation2 == 366288);
	}
	else
	{
		if (c_prune[cornerPermutation * 2187 + cornerOrientation] <= depth && eo_prune[edgeOrientation] <= depth)
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
