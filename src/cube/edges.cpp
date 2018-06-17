#include "edges.h"

Edges::Edges() {
    edges_perm = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    edges_orient = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
}

void Edges::apply_move(int move) {
    if (move == 0)
    {
        //move U
        for (int i = 0; i < 12; i++)
        {
            if (edges_perm[i] == 0)
            {
                edges_perm[i] = 1;
            }
            else if (edges_perm[i] == 1)
            {
                edges_perm[i] = 2;
            }
            else if (edges_perm[i] == 2)
            {
                edges_perm[i] = 3;
            }
            else if (edges_perm[i] == 3)
            {
                edges_perm[i] = 0;
            }
        }
    }
    else if (move == 1)
    {
        //move D
        for (int i = 0; i < 12; i++)
        {
            if (edges_perm[i] == 8)
            {
                edges_perm[i] = 11;
            }
            else if (edges_perm[i] == 11)
            {
                edges_perm[i] = 10;
            }
            else if (edges_perm[i] == 10)
            {
                edges_perm[i] = 9;
            }
            else if (edges_perm[i] == 9)
            {
                edges_perm[i] = 8;
            }
        }
    }
    else if (move == 2)
    {
        //move R
        for (int i = 0; i < 12; i++)
        {
            if (edges_perm[i] == 1)
            {
                edges_perm[i] = 5;
            }
            else if (edges_perm[i] == 5)
            {
                edges_perm[i] = 9;
            }
            else if (edges_perm[i] == 9)
            {
                edges_perm[i] = 6;
            }
            else if (edges_perm[i] == 6)
            {
                edges_perm[i] = 1;
            }
        }
    }
    else if (move == 3)
    {
        //move L
        for (int i = 0; i < 12; i++)
        {
            if (edges_perm[i] == 3)
            {
                edges_perm[i] = 7;
            }
            else if (edges_perm[i] == 7)
            {
                edges_perm[i] = 11;
            }
            else if (edges_perm[i] == 11)
            {
                edges_perm[i] = 4;
            }
            else if (edges_perm[i] == 4)
            {
                edges_perm[i] = 3;
            }
        }
    }
    else if (move == 4)
    {
        //move F
        for (int i = 0; i < 12; i++)
        {
            if (edges_perm[i] == 2)
            {
                edges_perm[i] = 6;
                edges_orient[i] ^= 1;
            }
            else if (edges_perm[i] == 6)
            {
                edges_perm[i] = 10;
                edges_orient[i] ^= 1;
            }
            else if (edges_perm[i] == 10)
            {
                edges_perm[i] = 7;
                edges_orient[i] ^= 1;
            }
            else if (edges_perm[i] == 7)
            {
                edges_perm[i] = 2;
                edges_orient[i] ^= 1;
            }
        }
    }
    else if (move == 5)
    {
        //move B
        for (int i = 0; i < 12; i++)
        {
            if (edges_perm[i] == 0)
            {
                edges_perm[i] = 4;
                edges_orient[i] ^= 1;
            }
            else if (edges_perm[i] == 4)
            {
                edges_perm[i] = 8;
                edges_orient[i] ^= 1;
            }
            else if (edges_perm[i] == 8)
            {
                edges_perm[i] = 5;
                edges_orient[i] ^= 1;
            }
            else if (edges_perm[i] == 5)
            {
                edges_perm[i] = 0;
                edges_orient[i] ^= 1;
            }
        }
    }
}
