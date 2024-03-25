// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include <cassert>
#include <vector>
#include "p1_library.h"
#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

vector<vector<double> > summarize(vector<double> v) {
    assert(!v.empty());
    vector<vector<double>> summary;
    vector<double> elem;
    double num = v[0];
    double count = 1;
    sort(v);
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] == num) {
            count += 1;
        } else {
            elem = {num, count};
            summary.push_back(elem);
            num = v[i];
            count = 1;
        }
    }
    // last one
    elem = {num, count};
    summary.push_back(elem);
    return summary;
}

int count(vector<double> v) {
  return v.size();
}

double sum(vector<double> v) {
  assert(!v.empty());
    double sum = 0;
    for (size_t i = 0; i < v.size(); i++){
	   sum += v[i];
    }
    return sum;  
}

double mean(vector<double> v) {
    assert(!v.empty());
    double mean = 0;
    for (size_t i = 0; i < v.size(); i++) {
	   mean += v[i];
    }
    mean = mean / v.size();
    return mean;  
}

double median(vector<double> v) {
    assert(!v.empty());
    sort(v);
    double median;
    if (v.size() % 2 == 0) { // even size
	   double left;
       double right;
	   left = v[(v.size() / 2) - 1];
	   right = v[(v.size() / 2)];
	   median = (left + right)/2;
    } else { // odd size
	   median = v[((v.size() + 1) / 2) - 1];
    }
    return median;  
}

double mode(vector<double> v) {
    assert(!v.empty());
    int freq = 0;
    int index = 0;
    vector<vector<double> > summary = summarize(v);   
    for (size_t i = 0; i < summary.size(); i++) {
        if (summary[i][1] > freq) {
            index = i;
		    freq = summary[i][1];
	    }  
    }
    return summary[index][0];  
}

double min(vector<double> v) {
    assert(!v.empty());
    sort(v);
    return v[0];  
}

double max(vector<double> v) {
    assert(!v.empty());
    sort(v);
    return v[v.size() - 1];  
}

double stdev(vector<double> v) {
    assert(v.size() >= 2);
    double mean_num = mean(v);
    double stdev = 0;
    for (size_t i = 0; i < v.size(); i++) {
	   stdev += pow((v[i] - mean_num), 2);
    }
    stdev = sqrt(stdev/(v.size() - 1));
    return stdev;
}

double percentile(vector<double> v, double p) {
    assert(!v.empty());
    assert(p <= 1 && p >= 0);
    sort(v);
    if (p == 1) {
        return v[v.size() - 1];
    } else {
        double rank = (p * (v.size() - 1) ) + 1;
        double fracpart = 0;
        double intpart = 0;
        fracpart = modf(rank, &intpart);
        double percentile = v[intpart-1] + (fracpart*(v[intpart]-v[intpart-1]));
        return percentile;  
    }
}