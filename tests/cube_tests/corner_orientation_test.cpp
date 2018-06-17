#define BOOST_TEST_MODULE solver_tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "corner_orientation.h"

class CornerOrientationTest
{
public:
    CornerOrientation co;
    
    void test_four_identical_moves(std::vector<int> state, int move)
    {
        std::vector<int> current_state(state);
        for (int i = 1; i <= 4; i++)
        {
            co.apply_move(current_state, 0);
        }

        BOOST_CHECK(state == current_state);
    }

    std::vector<std::vector<int>> get_all_states()
    {
        std::vector<std::vector<int>> states;
        for (int ternary_rep = 0; ternary_rep < 6561; ternary_rep++)
        {
            std::vector<int> state(8);
            int ternary_rep_cur = ternary_rep;
            for (int i = 0; i < 8; i++)
            {
                state[i] = ternary_rep_cur % 3;
                ternary_rep_cur /= 3;
            }
            states.push_back(state);
        }
        return states;
    }
};


BOOST_AUTO_TEST_SUITE(corner_orientation_tests)

    BOOST_AUTO_TEST_CASE(four_identical_moves)
    {
        auto cot = CornerOrientationTest();
        for (auto state : cot.get_all_states()) {
            for (int move = 0; move < 6; move++) {
                cot.test_four_identical_moves(state, move);
            }
        }
    }

    BOOST_AUTO_TEST_CASE(solved_state)
    {
        auto cot = CornerOrientationTest();
        std::vector<int> state(8, 0);
        std::vector<int> current_state(state);
    
        cot.co.apply_move(current_state, 0); // U
        BOOST_CHECK(state == current_state);
    
        cot.co.apply_move(current_state, 1); // D
        BOOST_CHECK(state == current_state);
    
        cot.co.apply_move(current_state, 2); // R
        BOOST_CHECK(state != current_state);
        cot.co.apply_move(current_state, 2); // R2
        BOOST_CHECK(state == current_state);
    
        cot.co.apply_move(current_state, 3); // L
        BOOST_CHECK(state != current_state);
        cot.co.apply_move(current_state, 3); // L2
        BOOST_CHECK(state == current_state);
    
        cot.co.apply_move(current_state, 4); // F
        BOOST_CHECK(state != current_state);
        cot.co.apply_move(current_state, 4); // F2
        BOOST_CHECK(state == current_state);
        
        cot.co.apply_move(current_state, 5); // B
        BOOST_CHECK(state != current_state);
        cot.co.apply_move(current_state, 5); // B2
        BOOST_CHECK(state == current_state);
    }

BOOST_AUTO_TEST_CASE(opposite_independance)
{
    auto cot = CornerOrientationTest();
    for (auto state : cot.get_all_states())
    {
        std::vector<int> current_state(state);
        for (int axis = 0; axis < 3; axis++)
        {
            int move1 = axis * 2;
            int move2 = axis * 2 + 1;

            for (int i = 0; i < 4; i++) {
                cot.co.apply_move(current_state, move1);
                cot.co.apply_move(current_state, move2);
            }

            BOOST_CHECK(state == current_state);
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
