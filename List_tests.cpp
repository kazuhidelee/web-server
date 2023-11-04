#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_stub)
{
    List<int> *list = new List<int>;
    list->push_front(100);
    delete list;
}

TEST_MAIN()
