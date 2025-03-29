#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int n = 5;
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	TDynamicVector<int> t1(m, n);
	TDynamicVector<int> t2(t1);
	delete[] m;
	EXPECT_EQ(t1, t2);
}



TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int n = 5;
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	TDynamicVector<int> t1(m, n);
	TDynamicVector<int> t2(t1);
	t2[0] = 10;
	delete[] m;
	EXPECT_NE(t2, t1);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{	
	ASSERT_ANY_THROW(TDynamicVector<int> v(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE+1));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	int n = 5;
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	TDynamicVector<int> t1(m, n);
	delete[] m;
	ASSERT_NO_THROW(t1 = t1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	int n = 5;
	int* c = new int[n];
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		c[i] = 2;
	}
	TDynamicVector<int> t1(m, n);
	TDynamicVector<int> t2(c, n);
	t2 = t1;
	delete[] m;
	delete[] c;
	EXPECT_EQ(t2, t1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	int n = 5;
	int b = 6;
	int* c = new int[n];
	int* m = new int[b];
	for (int i = 0; i < b; i++) {
		m[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		c[i] = 1;
	}
	TDynamicVector<int> t1(m, b);
	TDynamicVector<int> t2(c, n);
	delete[] m;
	delete[] c;
	t2 = t1;
	EXPECT_EQ(6, t2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{

	int n = 5;
	int b = 6;
	int* c = new int[n];
	int* m = new int[b];
	for (int i = 0; i < b; i++) {
		m[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		c[i] = 1;
	}
	TDynamicVector<int> t1(m, b);
	TDynamicVector<int> t2(c, n);
	delete[] m;
	delete[] c;
	
	EXPECT_EQ(t1, t1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int n = 5;
	int* c = new int[n];
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		c[i] = 1;
	}
	TDynamicVector<int> t1(m, n);
	TDynamicVector<int> t2(c, n);
	delete[] m;
	delete[] c;
	ASSERT_TRUE(t1 == t2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int n = 5;
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	TDynamicVector<int> t1(m, n);
	delete[] m;
	ASSERT_TRUE(t1 == t1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	int n = 5;
	int b = 6;
	int* c = new int[n];
	int* m = new int[b];
	for (int i = 0; i < b; i++) {
		m[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		c[i] = 1;
	}
	TDynamicVector<int> t1(m, b);
	TDynamicVector<int> t2(c, n);
	delete[] m;
	delete[] c;
	ASSERT_FALSE(t1 == t2);
}


TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int n = 5;
	int* c = new int[n];
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		c[i] = 2;
	}
	TDynamicVector<int> t1(m, n);
	TDynamicVector<int> t2(c, n);
	TDynamicVector<int> t3(n);
	t3 = t1 + 1;
	delete[] m;
	delete[]c;
	EXPECT_EQ(t2, t3);
	
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int n = 5;
	int* c = new int[n];
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		c[i] = 2;
	}
	TDynamicVector<int> t1(m, n);
	TDynamicVector<int> t2(c, n);
	TDynamicVector<int> t3(n);
	t3 = t2 - 1;
	delete[] m;
	delete[]c;
	EXPECT_EQ(t1, t3);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int n = 5;
	int* c = new int[n];
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		c[i] = 2;
	}
	TDynamicVector<int> t1(m, n);
	TDynamicVector<int> t2(c, n);
	TDynamicVector<int> t3(n);
	t3 = t1 * 2;
	delete[] m;
	delete[]c;
	EXPECT_EQ(t2, t3);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int n = 5;
	int* c = new int[n];
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		c[i] = 2;
	}
	TDynamicVector<int> t1(m, n);
	TDynamicVector<int> t2(c, n);
	TDynamicVector<int> t3(n);
	t3 = t1 + t2;
	delete[] m;
	delete[]c;
	EXPECT_EQ(t1+2, t3);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> t1(5);
	TDynamicVector<int> t2(6);
	ASSERT_ANY_THROW(t1 + t2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int n = 5;
	int* c = new int[n];
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		c[i] = 2;
	}
	TDynamicVector<int> t1(m, n);
	TDynamicVector<int> t2(c, n);
	TDynamicVector<int> t3(n);
	t3 = t2 - t1;
	delete[] m;
	delete[]c;
	EXPECT_EQ(t1 , t3);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> t1(5);
	TDynamicVector<int> t2(6);
	ASSERT_ANY_THROW(t1 - t2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int n = 5;
	int* c = new int[n];
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		c[i] = 2;
	}
	TDynamicVector<int> t1(m, n);
	TDynamicVector<int> t2(c, n);
	int a;
	a = t2 * t1;
	delete[] m;
	delete[]c;
	EXPECT_EQ(10, a);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{

	TDynamicVector<int> t1(5);
	TDynamicVector<int> t2(6);
	ASSERT_ANY_THROW(t1 * t2);
}

