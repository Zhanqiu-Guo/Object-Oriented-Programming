// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    string filename;
    string col;
    cout << "enter a filename\n";
    cin >> filename;
    cout << "enter a column name\n";
    cin >> col;
    cout << "reading column " << col << " from " << filename << endl;
    vector<double> col_data = extract_column(filename, col);
    cout << "Summary (value: frequency)\n";
    vector<vector<double> > summary = summarize(col_data);
    for(size_t i = 0; i < summary.size(); i++) {
        double val = summary[i][0];
        double freq = summary[i][1];
        cout << val << ": " << freq << endl;
    }
    cout << endl;
    cout << "count = " << count(col_data) << endl;
    cout << "sum = " << sum(col_data) << endl;
    cout << "mean = " << mean(col_data) << endl;
    cout << "stdev = " << stdev(col_data) << endl;
    cout << "median = " << median(col_data) << endl;
    cout << "mode = " << mode(col_data) << endl;
    cout << "min = " << min(col_data) << endl;
    cout << "max = " << max(col_data) << endl;
    cout << "  0th percentile = " << percentile(col_data, 0) << endl;
    cout << " 25th percentile = " << percentile(col_data, 0.25) << endl;
    cout << " 50th percentile = " << percentile(col_data, 0.5) << endl;
    cout << " 75th percentile = " << percentile(col_data, 0.75) << endl;
    cout << "100th percentile = " << percentile(col_data, 1.0) << endl;
    return 0;
}
