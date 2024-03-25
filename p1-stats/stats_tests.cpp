/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_sum_small_data_set();
void test_summarize();
void test_count();
void test_sum();
void test_mean();
void test_median();
void test_mode();
void test_min();
void test_max();
void test_stdev();
void test_percentile();
// Add prototypes for you test functions here.

int main() {
    test_sum_small_data_set();
    // Call your test functions here
    test_summarize();
    test_count();
    test_sum();
    test_mean();
    test_median();
    test_mode();
    test_min();
    test_max();
    test_stdev();
    test_percentile();
    return 0;
}

void test_sum_small_data_set() {
    cout << "test_sum_small_data_set" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);

    assert(sum(data) == 6);

    cout << "PASS!" << endl;
}

// Add the test function implementations here.

void test_summarize() {
    cout << "test_summarize\n";
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(4);
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(3);
    vector<vector<double> > v {
	   { 1, 2 },
	   { 2, 2 },
	   { 3, 2 },
       { 4, 2 } 
    };
    assert(summarize(data) == v);
    cout << "PASS!\n";
}

void test_count() {
    cout << "test_count\n";
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(4);
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(3);
    assert(count(data) == 8);
    cout << "PASS!\n";
}

void test_sum() {
    cout << "test_sum\n";
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(4);
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(3);
    assert(sum(data) == 20);
    cout << "PASS!\n";
}

void test_mean() {
    cout << "test_mean\n";
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(4);
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(3);
    assert(mean(data) == 2.5);
    cout << "PASS!\n";
}

void test_median() {
    cout << "test_median\n";
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(4);
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(3);
    assert(median(data) == 2.5);
    cout << "PASS!\n";
}

void test_mode() {
    cout << "test_mode\n";
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(4);
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(3);
    assert(mode(data) == 1);
    cout << "PASS!\n";
}

void test_min() {
    cout << "test_min\n";
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(4);
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(3);
    assert(min(data) == 1);
    cout << "PASS!\n";
}

void test_max() {
    cout << "test_max\n";
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(4);
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(3);
    assert(max(data) == 4);
    cout << "PASS!\n";
}

void test_stdev() {
    cout << "test_stdev\n";
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(4);
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(3);
    assert(stdev(data) == sqrt(10.0 / 7.0));
    cout << "PASS!\n";
}

void test_percentile() {
    cout << "test_percentile\n";
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(4);
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(3);
    assert(percentile(data, 0.5) == 2.5);
    cout << "PASS!\n";
}
