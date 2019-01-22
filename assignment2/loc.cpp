//Andrew Sanchez
//2/5/18
//professor: A. Concepcion
//loc.cpp

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

using namespace std;

int main()
{
    cout << "assignment 1" << endl;
    Loc list_file("list.h");
    list_file.read_lines();

    cout << endl << "assignment 2" << endl;
    Loc loc_file("loc.h");
    loc_file.read_lines();
    Loc loc_cpp("loc.cpp");
    loc_cpp.read_lines();
}
