#include "List.h"
#include <gtest.h>

TEST(TList, can_create_stack)
{
	ASSERT_NO_THROW(TList<int> st());
}
TEST(TList, can_check_empty)
{
	TList<int>st = TList<int>();
	EXPECT_EQ(1, st.empty());
}

TEST(TList, can_push)
{
	TList<int>st = TList<int>();
	ASSERT_NO_THROW(st.push(0));
}

TEST(TList, get_front)
{
	TList<int>st = TList<int>();
	st.push(1);
	st.push(2);
	ASSERT_NO_THROW(st.front());

}