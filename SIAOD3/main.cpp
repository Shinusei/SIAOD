#include <iostream>
#include <fstream>
#include <vector>
#include "hashControl.h"

using namespace std;


int main() {
    Hash h(4);
    cout << endl << "file:" << endl;

    ofstream fout;
    ifstream fin;
    if (!fileExist(fin, fout)) {
        return 1;
    }
    createBinFile(fin, fout);
    Hash *fileHashArray = new Hash(4);
    fillHashArray(*fileHashArray, fin);
    fileHashArray->printHash();
    deleteWithHash(*fileHashArray, 2);
    fileHashArray->printHash();
    outBinFile(fin, "bin.dat");
    findByHash(*fileHashArray, 2);
    cout << "Count to 10000" << endl;
    for (int i = 0; i < 10000; i++) {
        h.addItem(i, i, "qwerty");
    }
    h.printHash();
}