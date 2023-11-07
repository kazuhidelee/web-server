#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_push_front)
{
    // push_front to an empty list
    List<int> list;
    list.push_front(100);
    ASSERT_EQUAL(list.front(), 100);
    ASSERT_EQUAL(list.back(), 100);
}

TEST(test_push_back)
{
    // push_back to an empty list
    List<int> list;
    list.push_back(100);
    ASSERT_EQUAL(list.front(), 100);
    ASSERT_EQUAL(list.back(), 100);
}

TEST(test_push_front_mult)
{
    List<int> list;
    list.push_front(100);
    ASSERT_EQUAL(list.front(), 100);
    list.push_front(101);
    ASSERT_EQUAL(list.front(), 101);
    list.push_front(103);
    ASSERT_EQUAL(list.front(), 103);
    list.push_front(104);
    ASSERT_EQUAL(list.front(), 104);
    list.push_front(105);
    ASSERT_EQUAL(list.front(), 105);
    ASSERT_EQUAL(list.back(), 100);
}

TEST(empty_assign)
{
    // assign an empty list
    List<int> list1;
    ASSERT_TRUE(list1.empty());
    List<int> list2 = list1;
    ASSERT_TRUE(list2.empty());
    List<int> list3(list2);
    ASSERT_TRUE(list3.empty());
    list1 = list3;
    ASSERT_TRUE(list1.empty());
    ASSERT_EQUAL(list1.size(), 0);
}

TEST(list_copy)
{
    // copy an list
    List<int> list1;
    list1.push_back(100);
    list1.push_back(101);
    list1.push_back(102);
    List<int> list2 = list1;
    ASSERT_EQUAL(list2.front(), 100);
    ASSERT_EQUAL(list2.back(), 102);
    List<int> list3(list2);
    List<int>::Iterator a = list1.begin();
    List<int>::Iterator b = list3.begin();
    while (a != list1.end() && b != list3.end())
    {
        ASSERT_TRUE(*a == *b);
        ++a;
        ++b;
    }
    list2 = list3;
    List<int>::Iterator c = list2.begin();
    List<int>::Iterator d = list3.begin();
    while (c != list2.end() && d != list3.end())
    {
        ASSERT_TRUE(*c == *d);
        ++c;
        ++d;
    }
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
    ASSERT_EQUAL(list1.back(), 100);
    list1.push_back(101);
    ASSERT_EQUAL(list1.back(), 101);
    list1.push_back(102);
    ASSERT_EQUAL(list1.back(), 102);
    list1.pop_front();
    ASSERT_EQUAL(list1.front(), 101);
    list1.pop_back();
    ASSERT_EQUAL(list1.back(), 101);
    list1.pop_back();
    ASSERT_TRUE(list1.empty());
    list1.push_back(100);
    list1.pop_front();
    ASSERT_TRUE(list1.empty());
    // pop with 2 elements
    list1.push_back(500);
    list1.push_back(600);
    list1.pop_front();
    ASSERT_EQUAL(list1.front(), 600);
    list1.clear();
    list1.push_back(100);
    list1.push_back(200);
    list1.pop_back();
    ASSERT_EQUAL(list1.back(), 100);
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

TEST(middle)
{
    List<int> list1;
    list1.push_back(100);
    list1.push_back(101);
    list1.push_back(102);
    list1.pop_back();
    list1.pop_front();
    List<int>::Iterator i = list1.begin();
    ASSERT_EQUAL(list1.front(), 101);
    ASSERT_EQUAL(list1.back(), 101);
    ASSERT_EQUAL(*i, 101);
}

TEST(decreasing)
{
    List<int> list1;
    list1.push_back(100);
    list1.push_back(101);
    list1.push_back(102);
    List<int>::Iterator i = list1.begin();
    ASSERT_EQUAL(*i, 100);
    ++i;
    ASSERT_EQUAL(*i, 101);
    ++i;
    ASSERT_EQUAL(*i, 102);
    --i;
    ASSERT_EQUAL(*i, 101);
    --i;
    ASSERT_EQUAL(*i, 100);
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

TEST(insert2)
{
    List<int> list2;
    list2.push_front(101);
    List<int>::Iterator i = list2.begin();
    list2.push_back(102);
    ++i;
    list2.insert(i, 100);
    ASSERT_EQUAL(list2.front(), 101);
    ASSERT_EQUAL(list2.back(), 102);
}

TEST(nullptr_compare)
{
    List<int> list1;
    List<int> list2;
    List<int>::Iterator i = list1.begin();
    List<int>::Iterator e = list2.begin();
    ASSERT_TRUE(i == e);
}

TEST(dereference)
{
    List<int> list;
    list.push_front(101);
    List<int>::Iterator i = list.begin();
    list.push_back(102);
    ++i;
    list.insert(i, 100);
    ostringstream expected;
    expected << "101\n"
             << "100\n"
             << "102\n";
    ostringstream actual;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        actual << *it << endl;
    }
    ASSERT_EQUAL(expected.str(), actual.str());
}

TEST(not_equal)
{
    List<int> list1;
    List<int> list2;
    list2.push_back(101);
    List<int>::Iterator i = list1.begin();
    List<int>::Iterator e = list2.begin();
    list2.push_back(102);
    ++e;
    List<int>::Iterator f = list2.begin();
    ASSERT_TRUE(i != e);
    ASSERT_TRUE(f != e);
}

TEST(pop_front)
{
    List<int> list1;
    list1.push_back(100);
    ASSERT_EQUAL(list1.front(), 100);
    list1.pop_front();
    ASSERT_TRUE(list1.empty());
}

TEST(back_insert)
{
    List<int> list1;
    list1.push_back(100);
    List<int>::Iterator f = list1.end();
    list1.insert(f, 200);
    ASSERT_EQUAL(list1.back(), 200);
    ASSERT_EQUAL(list1.size(), 2);
}

TEST(empty_insert)
{
    List<int> list2;
    List<int>::Iterator e = list2.begin();
    list2.insert(e, 100);
    e = list2.begin();
    ASSERT_EQUAL(list2.back(), 100);
    ASSERT_EQUAL(list2.front(), 100);
    list2.insert(e, 102);
    e = list2.begin();
    list2.insert(e, 103);
    e = list2.begin();
    ASSERT_EQUAL(list2.size(), 3);
    ASSERT_EQUAL(list2.front(), 103);
}

TEST(empty_clear)
{
    List<int> list1;
    ASSERT_TRUE(list1.empty());
    list1.clear();
    ASSERT_TRUE(list1.empty());
}

TEST(iterator_assign)
{
    List<int> list1;
    list1.push_back(100);
    List<int>::Iterator f = list1.end();
    List<int>::Iterator e = list1.begin();
    ASSERT_TRUE(f != e);
    f = e;
    ASSERT_TRUE(f == e);
    list1.insert(f, 200);
    ASSERT_EQUAL(list1.front(), 200);
}

TEST(verifying_copy)
{
    List<int> list1;
    list1.push_back(100);
    List<int> list2;
    list2 = list1;
    list2.push_back(200);
    ASSERT_EQUAL(list1.size(), 1);
    ASSERT_EQUAL(list1.back(), 100);
}

TEST(erase_all)
{
    List<int> list1;
    list1.push_back(100);
    list1.push_back(200);
    list1.push_back(300);
    list1.erase(list1.begin());
    ASSERT_EQUAL(list1.front(), 200);
    list1.erase(list1.begin());
    ASSERT_EQUAL(list1.front(), 300);
    list1.erase(list1.begin());
    ASSERT_TRUE(list1.empty());
}
TEST_MAIN()
