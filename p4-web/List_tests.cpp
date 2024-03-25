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
    list.push_back(1);
    list.push_back(1);
    list.push_back(1);
    ASSERT_EQUAL(list.size(), 4);
}

TEST(test_front_n_back) {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    ASSERT_EQUAL(list.front(), 0);
    ASSERT_EQUAL(list.back(), 3);
    
    List<int> list1;
    list1.push_back(100);
    ASSERT_EQUAL(list1.front(), 100);
    ASSERT_EQUAL(list1.back(), 100);
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
    
    List<double> list1;
    list1.clear();
    ASSERT_TRUE(list1.empty());
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
    list2.pop_back();
    ASSERT_EQUAL(list2.back(), 2);
}

TEST(test_assign) {
	List<int> list1;
	list1.push_back(0);
    List<int> list2;
    list2.push_back(0);
    list2 = list1;
    ASSERT_EQUAL(list2.front(), 0);
    ASSERT_EQUAL(list2.back(), 0);
    ASSERT_EQUAL(&(list2 = list1), &list2);
}

TEST(test_assign_1) {
    List<int> list1;
    list1.push_back(0);
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    List<int> list2;
    list2.push_back(100);
    list2 = list1;
    ASSERT_EQUAL(list2.front(), 0);
    ASSERT_EQUAL(list2.back(), 3);
    ASSERT_EQUAL(&(list2 = list1), &list2);
}

TEST(test_erase_1) {
	List<int> list;
	list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
	List<int>::Iterator iter = list.begin();
	list.erase(iter);
	ASSERT_EQUAL(list.front(), 1);
}

TEST(test_erase_2) {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    List<int>::Iterator iter = list.begin();
    ++iter;
    ++iter; 
    list.erase(iter);
    ASSERT_EQUAL(list.back(), 1);
}

TEST(test_erase_3) {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator iter = list.begin();
    ++iter;
    list.erase(iter);
    //ASSERT_EQUAL(*iter, 1);
    
    List<int>::Iterator iter1 = list.begin();
    ++iter1;
    ASSERT_EQUAL(*iter1, 2);
}

TEST(test_insert_1) {
	List<int> list;
	list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
	List<int>::Iterator iter = list.begin();
	list.insert(iter, 10);
	ASSERT_EQUAL(list.front(), 10);
    /*
	iter = list.end();
	list.insert(iter, 20);
	list.insert(iter,30);
	ASSERT_EQUAL(*iter, 30);
	ASSERT_EQUAL(list.back(), 20);
     */
}

TEST(test_insert_2) {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator iter = list.end();
    list.insert(iter, 20);
    ASSERT_EQUAL(list.back(), 20);
}

TEST(test_insert_3) {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator iter = list.begin();
    ++iter;
    list.insert(iter, 100);
    
    List<int>::Iterator iter1 = list.begin();
    ++iter1;
    ASSERT_EQUAL(*iter1, 100);
}

TEST(test_iter_equality) {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator iter = list.begin();
    List<int>::Iterator iter1 = list.begin();
    ASSERT_TRUE(iter == iter1);
    ++iter;
    ASSERT_FALSE(iter == iter1);
}

TEST(test_iter_equality_1) {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator iter1 = list.begin();
    List<int>::Iterator null;
    ASSERT_TRUE(list.end() == null);
    ASSERT_EQUAL(*iter1, 0);
    ASSERT_EQUAL(*(++iter1), 1);
    ASSERT_EQUAL(*(--iter1), 0);
    List<int>::Iterator iter2;
    iter2 = iter1;
    ASSERT_TRUE(iter2 == iter1);
    ASSERT_FALSE(iter2 == (++iter1));
}

TEST(test_iter_copy) {
    List<int> list;
    list.push_back(0);
    list.push_back(101);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator iter = list.begin();
    ++iter;
    
    List<int>::Iterator iter1(iter);
    ASSERT_EQUAL(*iter1, 101);
    ASSERT_EQUAL(iter1, iter);
    
    
}

TEST(test_iter_assign) {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator iter = list.begin();
    ++iter;
    
    List<int>::Iterator iter1 = list.begin();
    ++iter1;
    ++iter1;
    iter1 = iter;
    ASSERT_EQUAL(*iter1, 1);
    ASSERT_EQUAL(iter1, iter);
    
    List<int>::Iterator iter2 = list.begin();
    ++iter2;
    iter2 = iter;
    ASSERT_EQUAL(*iter2, 1);
    ASSERT_EQUAL(iter2, iter);
}

TEST_MAIN()
