#include "UDSlice_coord.h"
#include <algorithm>

void UDSlice_Coord::apply_move(vector<int> & arr, int move)
{
    if (move == 0)
    {
        //move U
        for (int i = 0; i < 4; i++)
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
        for (int i = 0; i < 4; i++)
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
        for (int i = 0; i < 4; i++)
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
        for (int i = 0; i < 4; i++)
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
        for (int i = 0; i < 4; i++)
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
        for (int i = 0; i < 4; i++)
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

int UDSlice_Coord::array_to_index(vector<int> const& arr)
{
    auto copy = arr;
    std::sort(copy.begin(), copy.end());
    
    int index = 0;
    for (int a = 0; a < 12; a++) {
        for (int b = a + 1; b < 12; b++) {
            for (int c = b + 1; c < 12; c++) {
                for (int d = c + 1; d < 12; d++) {
                    if (copy[0] == a && copy[1] == b && copy[2] == c && copy[3] == d)
                        return index;
                    index++;
                }
            }
        }
    }

    return -1;
}


void UDSlice_Coord::index_to_array(int index, vector<int> & arr)
{
    for (arr[0] = 0; arr[0] < 12; arr[0]++) {
        for (arr[1] = arr[0] + 1; arr[1] < 12; arr[1]++) {
            for (arr[2] = arr[1] + 1; arr[2] < 12; arr[2]++) {
                for (arr[3] = arr[2] + 1; arr[3] < 12; arr[3]++) {
                    if (index == 0)
                        return;
                    index--;
                }
            }
        }
    }
}
