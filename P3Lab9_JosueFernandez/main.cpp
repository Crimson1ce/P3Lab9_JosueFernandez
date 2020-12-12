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
    
    csv* file = new csv("prototipoChikito.csv",true);
    file->print_data();
    
    file->truncate_column(4);
    file->truncate_row(2);
    file->truncate_row(2);
    
    cout << ((vector<string>)file->get_max(3)).at(3)<< endl;
    cout << ((vector<string>)file->get_min(3)).at(3);

    
    cout << endl << endl;
    file->print_data();
    
    delete file;
    
    return 0;
}

