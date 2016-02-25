#include "gtest/gtest.h"
#include "corner_orientation.h"

class CornerOrientationTest : public ::testing::Test {
protected:
    CornerOrientation co;

    //virtual void SetUp() {}
    // virtual void TearDown() {}

    void test_four_identical_moves(vector<int> state, int move)
    {
        vector<int> current_state(state);
        for (int i = 1; i <= 4; i++)
        {
            co.apply_move(current_state, 0);
        }

        EXPECT_EQ(state, current_state);
    }

    vector<vector<int>> get_all_states()
    {
        vector<vector<int>> states;
        for (int ternary_rep = 0; ternary_rep < 6561; ternary_rep++)
        {
            vector<int> state(8);
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


TEST_F(CornerOrientationTest, four_identical_moves){
    for (auto state : get_all_states())
    {
        for (int move = 0; move < 6; move++)
        {
            test_four_identical_moves(state, move);
        }
    }
}

TEST_F(CornerOrientationTest, solved_state) {
    vector<int> state(8, 0);
    vector<int> current_state(state);

    co.apply_move(current_state, 0); // U
    EXPECT_EQ(state, current_state);

    co.apply_move(current_state, 1); // D
    EXPECT_EQ(state, current_state);

    co.apply_move(current_state, 2); // R
    EXPECT_NE(state, current_state);
    co.apply_move(current_state, 2); // R2
    EXPECT_EQ(state, current_state);

    co.apply_move(current_state, 3); // L
    EXPECT_NE(state, current_state);
    co.apply_move(current_state, 3); // L2
    EXPECT_EQ(state, current_state);

    co.apply_move(current_state, 4); // F
    EXPECT_NE(state, current_state);
    co.apply_move(current_state, 4); // F2
    EXPECT_EQ(state, current_state);


    co.apply_move(current_state, 5); // B
    EXPECT_NE(state, current_state);
    co.apply_move(current_state, 5); // B2
    EXPECT_EQ(state, current_state);
}

TEST_F(CornerOrientationTest, opposite_independance)
{
    for (auto state : get_all_states())
    {
        vector<int> current_state(state);
        for (int axis = 0; axis < 3; axis++)
        {
            int move1 = axis * 2;
            int move2 = axis * 2 + 1;

            for (int i = 0; i < 4; i++) {
                co.apply_move(current_state, move1);
                co.apply_move(current_state, move2);
            }

            EXPECT_EQ(state, current_state);
        }
    }
}
