#include <iostream>
#include <fstream>
#include <string>

using namespace std;



int main()
{
    string file = "list.h";
    string line;

    int num = 0;

    ifstream myfile;
	    myfile.open(file.c_str());

    while(myfile.good()){
	getline(myfile, line);
	num++;
	}
    cout << num << endl;
}

