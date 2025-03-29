#include <gtest.h>
#include "stacklist.h"
#include "stackarray.h"

TEST(TStack, can_create_stack_with_positive_length) {
	ASSERT_NO_THROW(TStackList<int> s);
}
TEST(TStack, can_create_copied_stack) {
	TStackList<int> s;
	ASSERT_NO_THROW(TStackList<int> s1(s));
}
TEST(TStack, can_push_and_get_top_element) {
	TStackList<int> s;
	s.push(1);
	EXPECT_EQ(s.Top(), 1);
}
TEST(TStack, new_stack_is_empty) {
	TStackList<int> s;
	ASSERT_TRUE(s.isEmpty());
}
TEST(TStack, can_pop_and_element) {
	TStackList<int> s;
	s.push(1);
	s.pop();
	ASSERT_TRUE(s.isEmpty());
}
TEST(TStack, copied_stack_is_equal_to_source_one) {
	TStackList<int> s;
	ASSERT_NO_THROW(TStackList<int> s1(s));
}
TEST(TStack, cant_pop_from_empty_stack) {
	TStackList<int> s;
	ASSERT_ANY_THROW(s.pop());
}



TEST(TStack, can_create_array_stack_with_positive_length) {
	ASSERT_NO_THROW(TStackArray<int> s(2));
}
TEST(TStack, cant_create_array_stack_with_negative_length) {
	ASSERT_ANY_THROW(TStackArray<int> s(-2));
}
TEST(TStack, can_create_copied_array_stack) {
	TStackArray<int> s(2);
	ASSERT_NO_THROW(TStackArray<int> s1(s));
}
TEST(TStack, can_array_push_and_get_top_element) {
	TStackArray<int> s(2);
	s.push(1);
	EXPECT_EQ(s.Top(), 1);
}
TEST(TStack, new_array_stack_is_empty) {
	TStackArray<int> s(2);
	ASSERT_TRUE(s.isEmpty());
}
TEST(TStack, array_stack_is_full) {
	TStackArray<int> s(2);
	for (int i = 0; i < 2; i++) {
		s.push(1);
	}
	ASSERT_TRUE(s.isFull());
}
TEST(TStack, can_array_pop_and_element) {
	TStackArray<int> s(2);
	s.push(1);
	s.pop();
	ASSERT_TRUE(s.isEmpty());
}
TEST(TStack, copied_array_stack_is_equal_to_source_one) {
	TStackArray<int> s(2);
	ASSERT_NO_THROW(TStackArray<int> s1(s));
}
TEST(TStack, cant_array_pop_from_empty_stack) {
	TStackArray<int> s(2);
	ASSERT_ANY_THROW(s.pop());
}
TEST(TStack, cant_array_push_from_full_stack) {
	TStackArray<int> s(2);
	for (int i = 0; i < 2; i++) {
		s.push(1);
	}
	ASSERT_ANY_THROW(s.push(1));
}
