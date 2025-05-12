#include <gtest.h> 
#include "TList.h"

// Тест на создание пустого списка
TEST(TList, can_create_empty_list) {
    ASSERT_NO_THROW(TList<int>());  // Проверка, что создание пустого списка не вызывает исключений
}

// Тест на вставку первого элемента в список
TEST(TList, can_insert_first_element) {
    TList<int> list;
    ASSERT_NO_THROW(list.InsertFirst(10));  // Проверка, что вставка первого элемента не вызывает исключений
}

TEST(TList, can_insert_first_element1) {
    TList<int> list;
    list.InsertFirst(10);
    EXPECT_EQ(list.GetFirst()->key, 10);   // Проверка, что первый элемент в списке равен 10
}

// Тест на вставку элемента перед существующим элементом
TEST(TList, can_insert_before_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    ASSERT_NO_THROW(list.InsertBefore(20, 15));  // Проверка, что вставка элемента перед элементом 20 не вызывает исключений
}

TEST(TList, can_insert_before_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    EXPECT_EQ(list.GetFirst()->pNext->key, 15);  // Проверка, что второй элемент теперь равен 15
}

// Тест на вставку элемента после существующего элемента
TEST(TList, can_insert_after_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    ASSERT_NO_THROW(list.InsertAfter(10, 15));  // Проверка, что вставка элемента после элемента 10 не вызывает исключений
}

TEST(TList, can_insert_after_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    EXPECT_EQ(list.GetFirst()->pNext->key, 15);  // Проверка, что второй элемент теперь равен 15
}

// Тест на удаление первого элемента
TEST(TList, can_delete_first_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    ASSERT_NO_THROW(list.DeleteFirst());  // Проверка, что удаление первого элемента не вызывает исключений
}

TEST(TList, can_delete_first_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    EXPECT_EQ(list.GetFirst()->key, 20);  // Проверка, что теперь первый элемент равен 20
}


// Тест на удаление последнего элемента
TEST(TList, can_delete_last_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    ASSERT_NO_THROW(list.DeleteLast());  // Проверка, что удаление последнего элемента не вызывает исключений
}

TEST(TList, can_delete_last_element) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    EXPECT_EQ(list.GetFirst()->key, 10);  // Проверка, что теперь первый элемент равен 10
}

// Тест на удаление элемента по ключу
TEST(TList, can_delete_by_key) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    ASSERT_NO_THROW(list.DeleteByKey(10));  // Проверка, что удаление элемента с ключом 10 не вызывает исключений
}

// Тест на удаление элемента по ключу
TEST(TList, can_delete_by_key) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конеw
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
}

TEST(TList, reset_and_next) {
    TList<int> list;
    list.InsertEnd(10);  // Вставка первого элемента в конец
    list.InsertEnd(20);  // Вставка второго элемента в конец
    list.Reset();  // Сброс указателя текущего элемента
    list.Next();  // Переход к следующему элементу
    EXPECT_EQ(list.GetCurrent()->key, 20);  // Проверка, что текущий элемент теперь равен 20
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();  // Запуск всех тестов
}