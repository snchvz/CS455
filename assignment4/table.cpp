#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream file("ttt.txt");

    double table[10][9];
    double num;

    int i = 0;
    int j = 0;
    for (i = 0; i < 10; i++){
        for (j = 0; j < 9; j++){
            file >> table[i][j];
        }
        j = 0;
    }

    for (i = 0; i < 10; i ++){
        for (j = 0; j < 9; j++){
            cout << " " << table[i][j] << " ";
        }
        j = 0;
        cout << endl;

    }

}

