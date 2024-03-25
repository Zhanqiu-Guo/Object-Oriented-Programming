// Project UID af1f95f547e44c8ea88730dfb185559d

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cstdlib>
#include "processing.h"
using namespace std;

int main(int argc, char *argv[]) { 
    
     if (argc != 4 && argc != 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" 
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return -1;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    if(!fin.is_open()) {
        cout << "Error opening file: " << argv[1] << endl;
        return -1;
    }
    if(!fout.is_open()) {
        cout << "Error opening file: " << argv[2] << endl;
        return -1;
    }
    Image* img = new Image;
    Image_init(img, fin);
    int desired_height;
    int desired_width = atoi(argv[3]);
    if (argc == 4) {
        desired_height = Image_height(img);
    } else {
        desired_height = atoi(argv[4]);
    }
    if (desired_width < 0 || desired_width > Image_width(img) 
    || desired_height < 0 || desired_height > Image_height(img)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" 
            << "WIDTH and HEIGHT must be less than or equal to original" << endl;  
            return -1;
    }
    seam_carve(img, desired_width, desired_height);
    Image_print(img, fout);
    delete img;
    fin.close();
	fout.close();
    return 0;
}