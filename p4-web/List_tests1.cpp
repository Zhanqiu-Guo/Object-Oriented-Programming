// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here
TEST(test_empty_size) {
    List<int> list;
	ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
    list.push_back(0);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.size(), 1);
}

TEST(test_push_front_back) {
	List<int> list;
	list.push_back(0);
    list.push_back(1);
	ASSERT_EQUAL(list.front(), 0);
	ASSERT_EQUAL(list.back(), 1);
	list.push_back(2);
	list.push_front(3);
	ASSERT_EQUAL(list.back(), 2);
	ASSERT_EQUAL(list.front(), 3);
}

TEST(test_pop_front_back) {
	List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
	list.push_back(3);
    list.pop_front();		
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 3);
    list.pop_back();
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 2);
    list.pop_front();
    ASSERT_EQUAL(list.front(), 2);
	ASSERT_EQUAL(list.front(), 2);
    list.pop_back();
    ASSERT_TRUE(list.empty());
}

TEST(test_clear) {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
	list.push_back(3);
    list.clear();
    ASSERT_TRUE(list.empty());
}

TEST(test_copy) {
    List<int> list1;
	list1.push_back(0);
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    List<int> list2(list1);
    list1.pop_back();
    list1.pop_front();
    list1.push_back(0);
    list1.push_front(0);
    ASSERT_EQUAL(list2.front(), 0);
    ASSERT_EQUAL(list2.back(), 3);
}

TEST(test_assign) {
	List<int> list1;
	list1.push_back(0);
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    List<int> list2;
    list2.push_back(0);
    list2 = list1;
    ASSERT_EQUAL(list2.front(), 0);
    ASSERT_EQUAL(list2.back(), 3);
    ASSERT_EQUAL(&(list2 = list1), &list2);
}

TEST(test_iter) {
    List<int> list;
	list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator iter1 = list.begin();
	List<int>::Iterator null = list.end();	 
    ASSERT_TRUE(list.end() == null);
	ASSERT_EQUAL(*(++iter1), 1);
	ASSERT_EQUAL(*(--iter1), 0);
	List<int>::Iterator iter2;
	iter2 = iter1;
	ASSERT_TRUE(iter2 == iter1);
	ASSERT_FALSE(iter2 == (++iter1));
}



TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST_MAIN()
