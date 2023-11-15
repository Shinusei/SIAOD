#include <iostream>
#include <fstream>

using namespace std;

bool isFileExist(string fileName) {
    ifstream file;
    file.open(fileName, ios::in);
    return file.good();
}

void createFile(string fileName) {
    ofstream fileOut;
    fileOut.open(fileName, ios::out | ios::trunc);
    for (int i = 0; i < 10; i++) {
        fileOut << i<< endl;
    }
    fileOut.close();
}

void printFromFile(string fileName) {
    if (!isFileExist(fileName)){
        return;
    }
    ifstream fin;
    fin.open(fileName, ios::in);
    int x;
    while (fin>>x) {
        fin.get();
        cout << x << endl;
    }
    fin.close();
}

void addToEnd(string fileName, int addNum) {
    if (!isFileExist(fileName)){
        return;
    }
    ofstream fin;
    fin.open(fileName, ios::app);
    fin << addNum;
    fin.close();
}

void seekInFile(string fileName, int num) {
    if (!isFileExist(fileName)){
        return;
    }
    int x;
    ifstream fin;
    fin.open(fileName, ios::in);
    int i;
    for (i = 0; (i < num)&&(!fin.eof()); i++)
    {
        fin >> x;
        fin.get();
    }
    if (i == num) {
        cout << endl << x << endl;
    }
    fin.close();
}

void countNum(string fileName) {
    if (!isFileExist(fileName)){
        return;
    }
    ifstream fin;
    fin.open(fileName, ios::in);
    int count = 0;
    float i = 0;
    while (fin>>i) {
        count++;
    }
    cout << endl << count-1;
    fin.close();
}

int getLast(string fileName) {
    if (!isFileExist(fileName)){
        return 0;
    }
    ifstream fin;
    fin.open(fileName, ios::in);
    int n;
    while (fin) {
        fin >> n;
    }

    return n;
}

void createFile(string fileName, string fileName2) {
    ofstream fileOut;
    int n = getLast(fileName2);
    cout << endl << n << endl;
    fileOut.open(fileName, ios::out | ios::trunc);
    for (int i = 0; i < 10; i++) {
        fileOut << i*n << endl;
    }
    fileOut.close();
}

int main() {
    createFile("A.txt");
    printFromFile("A.txt");
    addToEnd("A.txt", 15);
    seekInFile("A.txt", 5);
    countNum("A.txt");
    createFile("B.txt", "A.txt");
    cout << endl;
    printFromFile("B.txt");
}