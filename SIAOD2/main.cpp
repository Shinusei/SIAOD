#include <iostream>
#include <fstream>

using namespace std;

void printInFile(int n[], string name) {
    ofstream out(name, ios::out | ios::binary);
    if (!out) {
        cout << "Не удается открыть файл";
        return;
    }
    out.write((char*)&n, sizeof n);
    out.close();
}

void printFromFile(string name) {
    int n[3]{};
    ifstream in(name, ios::in | ios::binary);
    if (!in) {
        cout << "Не удается открыть файл";
        return;
    }
    in.read((char*)&n, sizeof n);
    for (int i = 0; i < 3; i++) {
        cout << n[i] << endl;
    }
    in.close();
}

void fromBinTotext(string from, string to) {
    ofstream fileOut;
    fileOut.open(to, ios::out | ios::trunc);
    ifstream fileIn;
    fileIn.open(from, ios::in | ios::binary);
    int n[1024] = {};
    fileIn.read((char*)&n, sizeof n);
    fileOut.write((char*)&n, sizeof n);
    fileIn.close();
    fileOut.close();
}

int main() {

}