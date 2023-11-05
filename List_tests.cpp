#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_push_front)
{
    List<int> list;
    list.push_front(100);
    ASSERT_EQUAL(list.front(), 100);
    ASSERT_EQUAL(list.back(), 100);
}

TEST(test_push_back)
{
    List<int> list;
    list.push_back(100);
    ASSERT_EQUAL(list.front(), 100);
    ASSERT_EQUAL(list.back(), 100);
}

TEST(empty_assign)
{
    List<int> list1;
    ASSERT_TRUE(list1.empty());
    List<int> list2 = list1;
    ASSERT_TRUE(list2.empty());
}

TEST(list_copy)
{
    List<int> list1;
    list1.push_back(100);
    list1.push_back(101);
    list1.push_back(102);
    List<int> list2 = list1;
    ASSERT_EQUAL(list2.front(), 100);
    ASSERT_EQUAL(list2.back(), 102);
}

TEST(recopying)
{
    List<int> list1;
    list1.push_back(100);
    list1.push_back(101);
    list1.push_back(102);
    ASSERT_EQUAL(list1.size(), 3);
    List<int> list2 = list1;
    list2.push_front(99);
    list2.push_back(103);
    list1 = list2;
    ASSERT_EQUAL(list1.front(), 99);
    ASSERT_EQUAL(list1.back(), 103);
    ASSERT_EQUAL(list1.size(), 5);
}

TEST(pop)
{
    List<int> list1;
    list1.push_back(100);
    list1.push_back(101);
    list1.push_back(102);
    list1.pop_front();
    ASSERT_EQUAL(list1.front(), 101);
    list1.pop_back();
    ASSERT_EQUAL(list1.back(), 101);
    list1.pop_back();
    ASSERT_TRUE(list1.empty());
}

TEST(clear)
{
    List<int> list1;
    list1.push_back(100);
    list1.push_back(101);
    list1.push_back(102);
    list1.clear();
    ASSERT_TRUE(list1.empty());
    ASSERT_EQUAL(list1.size(), 0);
}

TEST(operators)
{
    List<int>::Iterator i;
    ASSERT_TRUE(i == i);
    List<int> list;
    list.push_back(100);
    list.push_back(101);
    list.push_back(102);
    list.push_back(100);
    list.push_back(101);
    list.push_back(102);
    ostringstream expected;
    expected << "100\n"
             << "101\n"
             << "102\n"
             << "100\n"
             << "101\n"
             << "102\n";
    ostringstream actual;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        actual << *it << endl;
    }
    ASSERT_EQUAL(expected.str(), actual.str());
}

TEST(erase)
{
    List<int>::Iterator i;
    List<int> list;
    list.push_back(100);
    list.push_back(101);
    list.push_back(102);
    list.push_back(100);
    list.push_back(101);
    list.push_back(102);
    i = list.begin();
    list.erase(i);
    ASSERT_EQUAL(list.front(), 101);
    List<int> list2;
    list2.push_back(100);
    i = list2.begin();
    list2.erase(i);
    ASSERT_TRUE(list2.empty());
    ASSERT_EQUAL(list2.size(), 0);
}

TEST(insert)
{
    List<int> list2;
    list2.push_front(101);
    List<int>::Iterator i = list2.begin();
    list2.insert(i, 100);
    ASSERT_EQUAL(list2.front(), 100);
    ASSERT_EQUAL(list2.size(), 2);
}
TEST_MAIN()
