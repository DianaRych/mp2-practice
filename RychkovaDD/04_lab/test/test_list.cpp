#include <gtest.h> 
#include "HeadRingList.h"
#include "HeadList.h"
#include "TList.h"
#include "Polinoms.h"
#include "TMonom.h"


// Тест на создание пустого списка
TEST(TList, can_create_empty_list) {
    ASSERT_NO_THROW(TList<int>());  // Проверка, что создание пустого списка не вызывает исключений
}

// Тест на вставку первого элемента в список
TEST(TList, can_insert_first_element) {
    TList<int> list;
    ASSERT_NO_THROW(list.InsertFirst(10));  // Проверка, что вставка первого элемента не вызывает исключений
    EXPECT_EQ(list.GetFirst()->key, 10);   // Проверка, что первый элемент в списке равен 10
}

// Тест на вставку элемента перед существующим элементом
TEST(TList, can_insert_before_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    ASSERT_NO_THROW(list.InsertBefore(20, 15));  // Проверка, что вставка элемента перед элементом 20 не вызывает исключений
    EXPECT_EQ(list.GetFirst()->pNext->key, 15);  // Проверка, что второй элемент теперь равен 15
}

// Тест на вставку элемента после существующего элемента
TEST(TList, can_insert_after_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    ASSERT_NO_THROW(list.InsertAfter(10, 15));  // Проверка, что вставка элемента после элемента 10 не вызывает исключений
    EXPECT_EQ(list.GetFirst()->pNext->key, 15);  // Проверка, что второй элемент теперь равен 15
}

// Тест на удаление первого элемента
TEST(TList, can_delete_first_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    ASSERT_NO_THROW(list.DeleteFirst());  // Проверка, что удаление первого элемента не вызывает исключений
    EXPECT_EQ(list.GetFirst()->key, 20);  // Проверка, что теперь первый элемент равен 20
}

// Тест на удаление последнего элемента
TEST(TList, can_delete_last_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    ASSERT_NO_THROW(list.DeleteLast());  // Проверка, что удаление последнего элемента не вызывает исключений
    EXPECT_EQ(list.GetFirst()->key, 10);  // Проверка, что теперь первый элемент равен 10
}

// Тест на удаление элемента по ключу
TEST(TList, can_delete_by_key) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    ASSERT_NO_THROW(list.DeleteByKey(10));  // Проверка, что удаление элемента с ключом 10 не вызывает исключений
    EXPECT_EQ(list.GetFirst()->key, 20);  // Проверка, что первый элемент теперь равен 20
}

// Тест на поиск существующего элемента
TEST(TList, search_existing_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    TNode<int>* foundNode = list.Search(20);  // Поиск элемента с ключом 20
    EXPECT_EQ(foundNode->key, 20);  // Проверка, что найденный элемент равен 20
}

// Тест на поиск несуществующего элемента
TEST(TList, search_non_existing_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    TNode<int>* foundNode = list.Search(30);  // Поиск элемента с ключом 30, которого нет в списке
    EXPECT_EQ(foundNode, nullptr);  // Проверка, что элемент не найден, т.е. возвращается nullptr
}

// Тест на сброс и переход к следующему элементу
TEST(TList, reset_and_next) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    list.Reset();  // Сброс указателя текущего элемента
    EXPECT_EQ(list.GetCurrent()->key, 10);  // Проверка, что текущий элемент равен 10 после сброса
    list.Next();  // Переход к следующему элементу
    EXPECT_EQ(list.GetCurrent()->key, 20);  // Проверка, что текущий элемент теперь равен 20
}

TEST(HeadList, can_initialize_headlist) {
    ASSERT_NO_THROW(HeadList<int> list;);
}

// Тест на вставку в начало
TEST(HeadList, can_insert_first_element) {
    HeadList<int> list;
    list.InsertFirst(10);
    EXPECT_EQ(list.GetFirst()->key, 10);
    EXPECT_EQ(list.GetFirst()->pNext, nullptr);
}

TEST(HeadList, can_insert_end_element) {
    HeadList<int> list;
    list.InsertEnd(10);
    EXPECT_EQ(list.GetFirst()->key, 10);

    list.InsertEnd(20);
    EXPECT_EQ(list.GetFirst()->pNext->key, 20);
}

TEST(HeadList, can_copy_headlist) {
    HeadList<int> list;
    list.InsertFirst(10);
    list.InsertEnd(20);

    HeadList<int> copiedList = list;
    EXPECT_EQ(copiedList.GetFirst()->key, 10);
    EXPECT_EQ(copiedList.GetFirst()->pNext->key, 20);
}

TEST(HeadList, can_assign_headlist) {
    HeadList<int> list;
    list.InsertFirst(10);
    list.InsertEnd(20);

    HeadList<int> assignedList;
    assignedList = list;

    EXPECT_EQ(assignedList.GetFirst()->key, 10);
    EXPECT_EQ(assignedList.GetFirst()->pNext->key, 20);
}

TEST(HeadList, head_pointer_updates_correctly) {
    HeadList<int> list;
    list.InsertFirst(10);
    EXPECT_EQ(list.GetFirst()->key, 10);
    EXPECT_EQ(list.GetFirst()->pNext, nullptr);

    list.InsertEnd(20);
    EXPECT_EQ(list.GetFirst()->pNext->key, 20);
    EXPECT_EQ(list.GetFirst()->pNext->pNext, nullptr);
}

//////////////////////////

TEST(ListRingHead, can_initialize_ring_list) {
    ListRingHead<int> list;

    EXPECT_EQ(list.GetFirst(), nullptr);
    EXPECT_EQ(list.GetCurrent(), nullptr);
}


TEST(TPolinom, copied_polinom_is_equal_to_source_one) {
    TPolinom p("z+2x");
    TPolinom p1(p);
    TPolinom p2(p);
    EXPECT_EQ(p2, p1);
}

TEST(TPolinom, can_compare_polinom) {
    TPolinom p("1z+2x");
    TPolinom p1("z+2x");
    EXPECT_EQ(p, p1);
}

TEST(TPolinom, can_equate_polinoms) {
    TPolinom p("1z+2x");
    TPolinom p1("2z+2x");
    p = p1;
    EXPECT_EQ(p, p1);
}

TEST(TPolinom, can_sum_polinom_and_scalar) {
    TPolinom p("1z+2x");
    TPolinom p1("2x+1z+1");
    TPolinom p2;
    p2 = p + 1;
    EXPECT_EQ(p1, p2);
}

TEST(TPolinom, can_sum_polinom_and_scalar_with_minus) {
    TPolinom p("1z+2x");
    TPolinom p1("2x+1z-1");
    TPolinom p2;
    p2 = p + (-1.0);
    EXPECT_EQ(p1, p2);
}

TEST(TPolinom, can_sub_polinom_and_scalar) {
    TPolinom p("1z+2x");
    TPolinom p1("2x+1z-1");
    TPolinom p2 = p - 1;
    EXPECT_EQ(p1, p2);
}

TEST(TPolinom, can_sub_polinom_and_scalar_with_minus) {
    TPolinom p("1z+2x");
    TPolinom p1("2x+1z+1");
    TPolinom p2;
    p2 = p - (-1.0);
    EXPECT_EQ(p1, p2);
}

TEST(TPolinom, can_sum_polinoms) {
    TPolinom p("5x+3z");
    TPolinom p1("1z+3x");
    TPolinom p2("2z+2x");
    p2 = p2 + p1;
    EXPECT_EQ(p2, p);
}

TEST(TPolinom, can_sum_big_polinoms) {
    TPolinom p("5x^2y^5z^2+3x^3y^2z^3");
    TPolinom p1("2xyz+z+3x^2y^2z^2");
    TPolinom p2("3x^3y^2z^3+5x^2y^5z^2+3x^2y^2z^2+2xyz+z");
    p = p + p1;
    EXPECT_EQ(p2, p);
}

TEST(TPolinom, can_sub_polinoms) {
    TPolinom p("-1x+1z");
    TPolinom p1("1z+3x");
    TPolinom p2("2z+2x");
    p2 = p2 - p1;
    EXPECT_EQ(p2, p);
}

TEST(TPolinom, can_multiply_polinoms) {
    TPolinom p("1z+2x");
    TPolinom p1("1z+3x");
    TPolinom p2("6x^2+5xz+1z^2");
    p = p * p1;
    EXPECT_EQ(p2, p);
}

TEST(TPolinom, can_sum_polinom_and_monom) {
    TPolinom p("1z+2x");
    TMonom p1("1z");
    TPolinom p2("2x+2z");
    p = p + p1;
    EXPECT_EQ(p2, p);
}

TEST(TPolinom, can_sub_polinom_and_monom) {
    TPolinom p("2x+1z");
    TMonom p1("1z");
    TPolinom p2("2z+2x");
    p2 = p2 - p1;
    EXPECT_EQ(p2, p);
}

TEST(TPolinom, can_multiply_polinom_and_monom) {
    TPolinom p("1z+2x");
    TMonom p1("2z");
    TPolinom p2("4xz+2z^2");
    p = p * p1;
    EXPECT_EQ(p2, p);
}

TEST(TPolinom, can_multiply_polinom_and_scalar) {
    TPolinom p("1z+2x");
    TPolinom p2("16x+8z");
    p = p * 8;
    EXPECT_EQ(p2, p);
}

TEST(TPolinom, can_diff_x_sample_polinom) {
    TPolinom p("1z+2xy");
    TPolinom p2("2y");
    TPolinom p3 = p.DiffX();
    EXPECT_EQ(p2, p3);
}

TEST(TPolinom, can_diff_y_sample_polinom) {
    TPolinom p("1z+2x+3yz");
    TPolinom p2("3z");
    TPolinom p3 = p.DiffY();
    EXPECT_EQ(p2, p3);
}

TEST(TPolinom, can_diff_z_sample_polinom) {
    TPolinom p("1xz+2x");
    TPolinom p2("1x");
    TPolinom p3 = p.DiffZ();
    EXPECT_EQ(p2, p3);
}

TEST(TPolinom, can_diff_x_polinom) {
    TPolinom p("5xyz+6x^2y^7z^3");
    TPolinom p2("12xy^7z^3+5yz");
    TPolinom p3 = p.DiffX();
    EXPECT_EQ(p2, p3);
}

TEST(TPolinom, can_diff_y_polinom) {
    TPolinom p("5xyz+6x^2y^7z^3");
    TPolinom p2("42x^2y^6z^3+5xz");
    TPolinom p3 = p.DiffY();
    EXPECT_EQ(p2, p3);
}

TEST(TPolinom, can_diff_z_polinom) {
    TPolinom p("5xyz+6x^2y^7z^3");
    TPolinom p2("18x^2y^7z^2+5xy");
    TPolinom p3 = p.DiffZ();
    EXPECT_EQ(p2, p3);
}

TEST(TPolinom, can_multiply_form)
{
    TMonom m1("-z");
    TPolinom p1("1-x");
    TPolinom p2("x+1");
    TPolinom p3("-x^2+1");
    EXPECT_EQ(p3, p1 * p2);
}

TEST(TPolinom, can_multiply_form1)
{
    TPolinom p1("1-x");
    TPolinom p2("x+1+x^2");
    TPolinom p3("-x^3+1");
    EXPECT_EQ(p3, p1 * p2);
}

TEST(TPolinom, can_sum_form)
{
    TPolinom p1("1-x");
    TPolinom p2("x+1");
    TPolinom p3("2");
    EXPECT_EQ(p3, p1 + p2);
}

TEST(TPolinom, can_sub_form)
{
    TPolinom p1("1-x");
    TPolinom p2("x+1");
    TPolinom p3("-2x");
    EXPECT_EQ(p3, p1 - p2);
}

TEST(TPolinom, can_multiply_form2)
{
    TPolinom p1("5xyz-2zy");
    TPolinom p2("-1+4z-5x^2y");
    TPolinom p3("10x^2y^2z-25x^3y^2z+20xyz^2-5xyz-8yz^2+2yz");
    EXPECT_EQ(p3, p1 * p2);
}

TEST(TMonom, can_create_monom) {
    ASSERT_NO_THROW(TMonom("-3xyz"));
}

TEST(TMonom, getvalue_positive) {
    TMonom p("3x");
    double h = p.GetCoeff();
    EXPECT_EQ(3, h);
}

TEST(TMonom, getvalue_negative) {
    TMonom p("-3x");
    double h = p.GetCoeff();
    EXPECT_EQ(-3, h);
}

TEST(TMonom, getvalue_double) {
    TMonom p("-3.5x");
    double h = p.GetCoeff();
    EXPECT_EQ(-3.5, h);
}

TEST(TMonom, getconvolution_double) {
    TMonom p("-3.5x^2");
    int h = p.GetDegree();
    EXPECT_EQ(200, h);
}

TEST(TMonom, getconvolution_more) {
    TMonom p("-3.5x^2y^6z^7");
    int h = p.GetDegree();
    EXPECT_EQ(267, h);
}

TEST(TMonom, getconvolution_without_degree) {
    TMonom p("-3.5xyz");
    int h = p.GetDegree();
    EXPECT_EQ(111, h);
}

TEST(TMonom, getcoeff_simple) {
    TMonom m("3xyz");
    EXPECT_EQ(3, m.GetCoeff());
}

TEST(TMonom, getcoeff_minus_simple) {
    TMonom m("-3xyz");
    EXPECT_EQ(-3, m.GetCoeff());
}

TEST(TMonom, sum_simple_monoms) {
    TMonom m("3xyz");
    TMonom m1("5xyz");
    TMonom m2("8xyz");
    EXPECT_EQ(m2, m + m1);
}

TEST(TMonom, sub_simple_monoms) {
    TMonom m("3xyz");
    TMonom m1("5xyz");
    TMonom m2("2xyz");
    EXPECT_EQ(m2, m1 - m);
}

TEST(TMonom, sum_big_monoms) {
    TMonom m("3x^2y^5z^7");
    TMonom m1("5x^2y^5z^7");
    TMonom m2("8x^2y^5z^7");
    EXPECT_EQ(m2, m + m1);
}

TEST(TMonom, sub_big_monoms) {
    TMonom m("3x^2y^5z^7");
    TMonom m1("5x^2y^5z^7");
    TMonom m2("2x^2y^5z^7");
    EXPECT_EQ(m2, m1 - m);
}

TEST(TMonom, mul_simple_monoms) {
    TMonom m("3xyz");
    TMonom m1("5xyz");
    TMonom m2("15x^2y^2z^2");
    EXPECT_EQ(m2, m1 * m);
}

TEST(TMonom, mul_big_monoms) {
    TMonom m("3x^2y^2z^4");
    TMonom m1("5x^2y^3z^4");
    TMonom m2("15x^4y^5z^8");
    EXPECT_EQ(m2, m1 * m);
}

TEST(TMonom, more_monoms) {
    TMonom m("3xyz");
    TMonom m1("5xyz");
    EXPECT_EQ(true, m1 > m);
}

TEST(TMonom, less_monoms) {
    TMonom m("3xyz");
    TMonom m1("5xyz");
    EXPECT_EQ(true, m < m1);
}

TEST(TMonom, more_equals_monoms) {
    TMonom m("3xyz");
    TMonom m1("5xyz");
    EXPECT_EQ(true, m1 >= m);
}

TEST(TMonom, less_equals_monoms) {
    TMonom m("3xyz");
    TMonom m1("5xyz");
    EXPECT_EQ(true, m <= m1);
}

TEST(TMonom, less_equals_monoms_2) {
    TMonom m("3xyz");
    TMonom m1("3xyz");
    EXPECT_EQ(true, m1 <= m);
}

TEST(TMonom, more_equals_monoms_2) {
    TMonom m("3xyz");
    TMonom m1("3xyz");
    EXPECT_EQ(true, m1 >= m);
}

TEST(TMonom, monoms_nums) {
    TMonom m("3x^2y^3z^2");
    EXPECT_EQ(216, m(1, 2, 3));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS();  // Запуск всех тестов
}