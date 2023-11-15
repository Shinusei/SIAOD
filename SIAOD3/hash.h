#ifndef HASH_H
#define HASH_H

#include <bits/stdc++.h>

using namespace std;
struct HashNode {
    int number;
    int code;
    char name[30];
};

struct Hash {
    int HASHNUM;
    list <HashNode> *hashArray;

    Hash(int V);

    void addItem(int x, int y, string name);

    void deleteItem(int number);

    int hashFunction(int x) {
        return (x % HASHNUM);
    }

    int findItem(int);

    void printHash();

    void reHash();
};

Hash::Hash(int b) {
    this->HASHNUM = b;
    hashArray = new list<HashNode>[HASHNUM];
}

void Hash::addItem(int number, int code, string name) {
    int index = hashFunction(number);
    HashNode h;
    h.number = number;
    h.code = code;
    strcpy(h.name, name.c_str());
    hashArray[index].push_back(h);
    reHash();
}

void Hash::deleteItem(int number) {
    int index = hashFunction(number);
    list<HashNode>::iterator i;
    for (i = hashArray[index].begin();
         i != hashArray[index].end(); i++) {
        if (i->number == number)
            break;
    }
    if (i != hashArray[index].end())
        hashArray[index].erase(i);
}

void Hash::printHash() {
    for (int i = 0; i < HASHNUM; i++) {
        cout << i;
        for (auto x: hashArray[i])
            cout << " >>>> " << x.number << " " << x.code << " " << x.name;
        cout << endl;
    }
}

void Hash::reHash() {
    list <HashNode> *hashArray2;
    int n = 0;
    for (int i = 0; i < HASHNUM; i++) {
        if (!hashArray[i].empty()) {
            n++;
        }
    }
    if ((n * 1.0 / (this->HASHNUM)) >= 0.75) {
        hashArray2 = new list<HashNode>[HASHNUM * 2];
        for (int i = 0; i < HASHNUM; i++) {
            if (!hashArray[i].empty()) {
                for (auto j: hashArray[i]) {
                    hashArray2[i].push_back(j);
                }
            }
        }
        HASHNUM = HASHNUM * 2;
        hashArray->clear();
        hashArray = new list<HashNode>[HASHNUM];
        for (int i = 0; i < HASHNUM; i++) {
            if (!hashArray2[i].empty()) {
                for (auto j: hashArray2[i]) {
                    int index = hashFunction(j.number);
                    hashArray[index].push_back(j);
                }
            }
        }
    }
}

int Hash::findItem(int number) {
    int index = hashFunction(number);
    list<HashNode>::iterator i;
    for (i = hashArray[index].begin();
         i != hashArray[index].end(); i++) {
        if (i->number == number) {
            cout << number << " Элемент найден в таблице" << endl;
            return i->number;
        }
    }
    cout << number << " Элемент не найден в таблице" << endl;
    return -1;
}

#endif