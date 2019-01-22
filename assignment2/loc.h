#ifndef LOC_H
#define LOC_H

/*
Andrew Sanchez
2/5/18
professor: A. Concepcion
loc.cpp
*/

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

using namespace std;

//class takes name of file and reads total number of line, classes, and functions per class
class Loc
{
public: 	
    Loc(string file);	//overload contructor @
    ~Loc(); //destructor @

    void read_lines();	//output total lines, total classes, and total func per class @
protected:
    unsigned int total_lines() const; //@
    unsigned int total_classes() const; //@
    void number_functions();	//@
private:	
    string filename;
};	

Loc::Loc(string file)
{
    filename = file;
}

Loc::~Loc()
{}


unsigned int Loc::total_lines() const
{
    
    string line;
    int total_lines = 0;

    ifstream myfile;
    myfile.open(filename.c_str());

    while (myfile.good()){
	getline(myfile, line);
	if (line != "" and line.substr(0,1) != "/" and line != "\n"){
            total_lines++;
	}
    }

    return total_lines;    
}

unsigned int Loc::total_classes() const
{
    string line;
    int total_class = 0;

    ifstream myfile;
    myfile.open(filename.c_str());
    while (myfile.good()){
	getline(myfile, line);
	if (line.substr(0,5) == "class")
	    total_class++;
    }

    return total_class;
}

void Loc::number_functions()
{
    string line;
    int num_function = 0;
    
    ifstream myfile;
    myfile.open(filename.c_str());
    
    while (myfile.good()){
	getline(myfile, line);
	if (line.substr(0,5) == "class"){
	    cout << line << endl;
            while (line.substr(0,2) != "};"){
		getline(myfile, line);
		if (line.find("@") != -1)
		    num_function++;
	       
	    }
	    cout << num_function << endl;
	    num_function = 0;
        }
		    
    }
}


void Loc::read_lines()
{
    cout << "File: " << filename << endl;
    cout << "Total number of lines: " << total_lines() << endl;
    cout << "Total number of classes: " << total_classes() << endl;
   
    if (total_classes() > 0){
        cout << "Included classes: " << endl;
        number_functions();
    }
}



#endif
