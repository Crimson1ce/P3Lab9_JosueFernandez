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
    
    csv* file = new csv("archivo.csv",true);
    
    file->print_data();
    
    delete file;
    
    return 0;
}

