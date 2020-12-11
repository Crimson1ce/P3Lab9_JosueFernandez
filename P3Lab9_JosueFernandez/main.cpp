/* 
 * File:   main.cpp
 * Author: Josue_Fernandez
 */

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include "csv.h"

int main(int argc, char** argv) {
    
    csv* file = new csv("archivo.csv",false);
    
    file->print_data();
    
    file->truncate_column(2);
    
    cout << endl << endl;
    file->print_data();
    
    delete file;
    
    return 0;
}

