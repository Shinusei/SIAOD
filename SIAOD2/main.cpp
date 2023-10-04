#include <iostream>
#include <fstream>

using namespace std;

struct pacient{
    int number;
    int code;
    char* sName=new char[20];
};

void formatPrint(pacient n){
    cout << n.number << " " << n.code << " " << n.sName << endl;
}

void createFile(string fileName){
    ofstream fileOut;
    pacient n;
    n.code=000;
    n.number=000;
    n.sName="Test";
    fileOut.open(fileName, ios::out | ios::binary);
    fileOut.write((char*)&n, sizeof( pacient));
    n.code=1;
    fileOut.write((char*)&n, sizeof( pacient));
    n.code=2;
    fileOut.write((char*)&n, sizeof( pacient));
    fileOut.close();
}

void printInFile(pacient n, string name) {
    ofstream out(name, ios::out | ios::binary);
    if (!out) {
        cout << "Не удаётся открыть файл";
        return;
    }
    out.write((char*)&n, sizeof( pacient));
    out.close();
}

void printFromFile(string name) {
    pacient n;
    ifstream in(name, ios::in | ios::binary);
    if (!in) {
        cout << "Не удается открыть файл";
        return;
    }
    while(!in.eof()) {
        in.read((char*)&n, sizeof( pacient));
        formatPrint(n);
    }

    in.close();
}

void fromBinToText(string from, string to) {
    ofstream fileOut;
    fileOut.open(to, ios::out | ios::trunc);
    ifstream fileIn;
    fileIn.open(from, ios::in | ios::binary);
    pacient n;
    fileIn.read((char*)&n, sizeof( pacient));
    fileOut.write((char*)&n, sizeof( pacient));
    fileIn.close();
    fileOut.close();
}

int main() {
    createFile("A.bin");
    printFromFile("A.bin");
}