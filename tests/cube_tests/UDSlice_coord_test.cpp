#include <boost/test/unit_test.hpp>

#include "UDSlice_coord.h"
#include <set>
#include <algorithm>

class UDSliceCoordTest
{
public:
    UDSlice_Coord udslice;
    
    void test_four_identical_moves(vector<int> state, int move)
    {
        vector<int> current_state(state);
        for (int i = 1; i <= 4; i++)
        {
            udslice.apply_move(current_state, move);
        }

        BOOST_CHECK(state == current_state);
    }

    vector<vector<int>> get_all_states()
    {
        vector<vector<int>> states;
        vector<int> arr(4);
        for (arr[0] = 0; arr[0] < 12; arr[0]++) {
            for (arr[1] = arr[0] + 1; arr[1] < 12; arr[1]++) {
                for (arr[2] = arr[1] + 1; arr[2] < 12; arr[2]++) {
                    for (arr[3] = arr[2] + 1; arr[3] < 12; arr[3]++) {
                        states.push_back(arr);
                    }
                }
            }
        }
        return states;
    }
};


BOOST_AUTO_TEST_SUITE(UFSlice_coord_tests)

    BOOST_AUTO_TEST_CASE(enough_states) 
    {
        auto udslice_test = UDSliceCoordTest();
        auto states = udslice_test.get_all_states();
        BOOST_CHECK(states.size() == udslice_test.udslice.get_state_count());

        std::set<std::vector<int>> set(states.begin(), states.end());
        BOOST_CHECK(set.size() == states.size());

        std::set<int> set_indices;
        for (auto state : states) {
            int index = udslice_test.udslice.array_to_index(state);
            BOOST_CHECK(set_indices.count(index) == 0);
            set_indices.insert(index);
            BOOST_CHECK(index >= 0);
            BOOST_CHECK(index < states.size());
        }
    }

    BOOST_AUTO_TEST_CASE(four_identical_moves)
    {
        auto udslice_test = UDSliceCoordTest();
        for (auto state : udslice_test.get_all_states()) {
            for (int move = 0; move < 6; move++) {
                udslice_test.test_four_identical_moves(state, move);
            }
        }
    }

    BOOST_AUTO_TEST_CASE(solved_state)
    {
        auto udslice_test = UDSliceCoordTest();
        vector<int> state = {4, 5, 6, 7};
        vector<int> current_state(state);

        int index = udslice_test.udslice.array_to_index(state);
        BOOST_CHECK(index == 425);
    
        udslice_test.udslice.apply_move(current_state, 0); // U
        BOOST_CHECK(state == current_state);
    
        udslice_test.udslice.apply_move(current_state, 1); // D
        BOOST_CHECK(state == current_state);
    
        udslice_test.udslice.apply_move(current_state, 2); // R
        std::sort(current_state.begin(), current_state.end());
        BOOST_CHECK(state != current_state);
        udslice_test.udslice.apply_move(current_state, 2); // R2
        std::sort(current_state.begin(), current_state.end());
        BOOST_CHECK(state == current_state);
    
        udslice_test.udslice.apply_move(current_state, 3); // L
        std::sort(current_state.begin(), current_state.end());
        BOOST_CHECK(state != current_state);
        udslice_test.udslice.apply_move(current_state, 3); // L2
        std::sort(current_state.begin(), current_state.end());
        BOOST_CHECK(state == current_state);
    
        udslice_test.udslice.apply_move(current_state, 4); // F
        std::sort(current_state.begin(), current_state.end());
        BOOST_CHECK(state != current_state);
        udslice_test.udslice.apply_move(current_state, 4); // F2
        std::sort(current_state.begin(), current_state.end());
        BOOST_CHECK(state == current_state);
        
        udslice_test.udslice.apply_move(current_state, 5); // B
        std::sort(current_state.begin(), current_state.end());
        BOOST_CHECK(state != current_state);
        udslice_test.udslice.apply_move(current_state, 5); // B2
        std::sort(current_state.begin(), current_state.end());
        BOOST_CHECK(state == current_state);
    }

    BOOST_AUTO_TEST_CASE(permutations)
    {
        auto udslice_test = UDSliceCoordTest();
        for (auto state : udslice_test.get_all_states()) {
            int start_index = udslice_test.udslice.array_to_index(state);
            while (std::next_permutation(state.begin(), state.end()))
            {
                int index = udslice_test.udslice.array_to_index(state);
                BOOST_CHECK(index == start_index);
            } 
        }
    }

    BOOST_AUTO_TEST_CASE(opposite_independance)
    {
        auto udslice_test = UDSliceCoordTest();
        for (auto state : udslice_test.get_all_states())
        {
            vector<int> current_state(state);
            for (int axis = 0; axis < 3; axis++)
            {
                int move1 = axis * 2;
                int move2 = axis * 2 + 1;

                for (int i = 0; i < 4; i++) {
                    udslice_test.udslice.apply_move(current_state, move1);
                    udslice_test.udslice.apply_move(current_state, move2);
                }

                BOOST_CHECK(state == current_state);
            }
        }
    }

    BOOST_AUTO_TEST_CASE(transition_table)
    {
        auto udslice_test = UDSliceCoordTest();
        auto& udslice = udslice_test.udslice;
        udslice.buildTransitionTable();
        auto transition_table = udslice.getTransitionTable();

        int solved = 425;
        int state = 425;

        state = transition_table[state][0]; // U
        BOOST_CHECK(state == solved);

        state = transition_table[state][1]; // D
        BOOST_CHECK(state == solved);

        state = transition_table[state][2]; // R
        BOOST_CHECK(state != solved);
        state = transition_table[state][2]; // R2
        BOOST_CHECK(state == solved);

        state = transition_table[state][3]; // L
        BOOST_CHECK(state != solved);
        state = transition_table[state][3]; // L2
        BOOST_CHECK(state == solved);

        state = transition_table[state][4]; // F
        BOOST_CHECK(state != solved);
        state = transition_table[state][4]; // F2
        BOOST_CHECK(state == solved);

        state = transition_table[state][5]; // B
        BOOST_CHECK(state != solved);
        state = transition_table[state][5]; // B2
        BOOST_CHECK(state == solved);
    }

BOOST_AUTO_TEST_SUITE_END()
