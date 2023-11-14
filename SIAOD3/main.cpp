#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include "hashControl.h"
using namespace std;


int main() {

    //Тесты 3 лабы
    Hash h(4);
    // hash table
    h.insertItem(1,11,"Ivanov");
    h.insertItem(2,33,"Petrov");
    cout<<"Вставка ключей без коллизии"<<endl;
    h.displayHash();
    h.insertItem(5,22,"Ivanov");
    cout<<"Вставка ключа и разрешение коллизии"<<endl;
    h.displayHash();
    h.insertItem(3,22,"Petrov");
    cout<<"Вставка с последующим рехешированием"<<endl;
    h.displayHash();
    h.deleteItem(3);
    cout<<"Удаление ключа 3 из таблицы"<<endl;
    h.displayHash();
    cout<<">>>>"<<(h.findItem(2));
    cout << endl << "file:" << endl;

    ofstream fout;
    ifstream fin;
    if(! fileExist(fin,fout)){
        return 1;
    }
    createBinFile(fin,fout);
    Hash *fileHashTable=new Hash(4);
    fillHashTable(*fileHashTable, fin);
    fileHashTable->displayHash();
    deleteWithHashTable(*fileHashTable,33);
    fileHashTable->displayHash();
    outBinFile(fin,"bin.dat");
    findByHash(*fileHashTable,22);
    for (int i=0;i<10;i++) {
        h.insertItem(i,i,"qwerty");
    }
    h.displayHash();
}