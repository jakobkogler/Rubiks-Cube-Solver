#pragma once

#include <vector>
#include <array>
#include <cstdint>

using TransitionTable = std::vector<std::array<uint32_t, 6>>;

class Group
{
protected:
    int state_count;
    int piece_count;
    TransitionTable transition_table;

public:
    TransitionTable getTransitionTable(){ return transition_table; }
    void buildTransitionTable();
    virtual void apply_move(std::vector<int> & arr, int move) = 0;
    int get_state_count(){ return state_count; }
protected:
    Group(int state_count, int piece_count) : state_count(state_count), piece_count(piece_count) {}
    virtual void index_to_array(int index, std::vector<int> & arr) = 0;
    virtual int array_to_index(std::vector<int> const& arr) = 0;
};
