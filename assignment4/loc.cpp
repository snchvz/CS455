//Andrew Sanchez
//2/5/18
//professor: A. Concepcion
//loc.cpp

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include "loc.h"

using namespace std;

int main()
{
    cout << "assignment 4" << endl;
    Loc list_file("correlation.h");
    list_file.read_lines();

}
