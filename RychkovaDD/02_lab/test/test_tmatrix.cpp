#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1;
	TDynamicMatrix<int> m1(m);
	TDynamicMatrix<int> m2(m);
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(3);	
	TDynamicMatrix<int> m1(m);
	m1[0][0] = 1;
	EXPECT_NE(m, m1);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(1);
	EXPECT_EQ(1, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element) // todo
{

  int n = 3;
  TDynamicVector<int> v1(n);
  v1[0] = 1;
  TDynamicMatrix<int> m(3);
  m[0] = v1;
  EXPECT_EQ(v1, m[0]);

}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{

	TDynamicMatrix<int> m(3);
	ASSERT_ANY_THROW(m[1].at(-1) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);
	ASSERT_ANY_THROW(m[1].at(4) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3), m1(3);
	m[0][0] = 1;
	m1 = m;
	EXPECT_EQ(m1, m1);
	
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(3), m1(3);
	m[0][0] = 1;
	m1 = m;
	EXPECT_EQ(m1, m);

}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(4);
	TDynamicMatrix<int> m1(3);
	m[0][0] = 1;
	m1 = m;
	
	EXPECT_EQ(4, m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(4);
	m[0][0] = 1;
	EXPECT_NE(m, m1);

}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(3), m1(3);
	m[0][0] = 1;
	m1[0][0] = 1;
	ASSERT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1;
	ASSERT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(4);
	m[0][0] = 1;
	m1[0][0] = 1;
	ASSERT_TRUE(m != m1); 
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);
	TDynamicMatrix<int> m3(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3-i; j++) {
			m[i][j] = 1;
			m1[i][j] = 2;
			m3[i][j] = 3;
		}
	}
	m2 = m1 + m;
	EXPECT_EQ(m2, m3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(4);
	m[0][0] = 1;
	m1[0][0] = 1;
	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);
	TDynamicMatrix<int> m3(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3-i; j++) {
			m[i][j] = 1;
			m1[i][j] = 2;
			m3[i][j] = 3;
		}
	}
	m2 = m3 - m1;
	EXPECT_EQ(m2, m);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(4);
	m[0][0] = 1;
	m1[0][0] = 1;
	ASSERT_ANY_THROW(m - m1);
}
TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);
	TDynamicMatrix<int> m3(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3-i; j++) {
			m[i][j] = 1;
			m1[i][j] = 2;
			m3[i][j] = 2+j*2;
		}
	}
	m2 = m * m1;
	EXPECT_EQ(m2, m3);
}
TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(4);
	m[0][0] = 1;
	m1[0][0] = 1;
	ASSERT_ANY_THROW(m * m1);
}
TEST(TDynamicMatrix, can_multiply_matrices_and_vector_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicVector<int> m(3);
	TDynamicVector<int> m2(3);
	TDynamicVector<int> m3(3);
	for (int i = 0; i < 3; i++) {
		m3[i] = 2 + i * 2;
		m[i] = 1;
		for (int j = 0; j < 3 - i; j++) {
			m1[i][j] = 2;
		}
	}
	m2 = m1*m;
	EXPECT_EQ(m2, m3);
}
TEST(TDynamicMatrix, cant_multiply_matrices_and_vector_with_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> m1(4);
	m[0][0] = 1;
	m1[0] = 1;
	ASSERT_ANY_THROW(m * m1);
}
TEST(TDynamicMatrix, can_multiply_matrices_and_scalar_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m2(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3 - i; j++) {
			m[i][j] = 1;
			m1[i][j] = 2;
		}
	}
	m2 = m * 2;
	EXPECT_EQ(m2, m1);
}