#ifndef HASHCONTROL_H
#define HASHCONTROL_H

#include "bin.h"
#include "hash.h"

using namespace std;

void fillHashArray(Hash &hashArray, ifstream &fb) {
    fb.open("bin.dat", ios::in | ios::binary);
    Struct x;
    fb.read((char *) &x, sizeof(Struct));
    int stn = 0;
    while (!fb.eof()) {
        hashArray.addItem(x.num, x.code, x.name);
        fb.read((char *) &x, sizeof(Struct));
        stn++;
    }
    fb.close();
}

void deleteWithHash(Hash &hashArray, int number) {
    cout << endl;
    int numberNum = hashArray.findItem(number);
    fstream file;
    file.open("bin.dat", ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Ошибка чтения файла";
        return;
    }

    Struct currentStruct;
    vector<Struct> records;
    while (!file.eof()) {
        file.read(reinterpret_cast<char *>(&currentStruct), sizeof(Struct));
        records.push_back(currentStruct);
    }
    file.seekg(0);
    bool found = false;
    for (int j = 0; j < records.size(); j++) {
        if (j == numberNum) {
            records[j] = records.back();
            records.pop_back();
            found = true;
            break;
        }
    }
    file.close();
    file.open("bin.dat", ios::out | ios::in | ios::binary | ios::trunc);
    int len = records.size();
    if (found) { len--; }
    for (int j = 0; j < len; j++) {
        file.write(reinterpret_cast<const char *>(&records[j]), sizeof(Struct));
    }
    file.close();
    hashArray.deleteItem(number);
    cout << endl;
    return;
}

void findByHash(Hash &hashArray, int number) {
    cout << endl;
    int numberNum = hashArray.findItem(number);
    fstream file;
    file.open("bin.dat", ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Ошибка чтения файла";
        return;
    }
    Struct currentStruct;
    while (!file.eof()) {
        file.read(reinterpret_cast<char *>(&currentStruct), sizeof(Struct));
        if (currentStruct.num == numberNum) {
            cout << currentStruct.num << " ";
            cout << currentStruct.code << " ";
            cout << currentStruct.name << " ";
            cout << endl << endl;
        }
    }
    file.close();
}

#endif