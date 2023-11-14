#ifndef HASH_H
#define HASH_H
#include <bits/stdc++.h>
using namespace std;
struct HashNode{
    int key;
    int value;
    char name[30];
};

struct Hash
{
    int BUCKET;
    list<HashNode> *table;
    Hash(int V);
    void insertItem(int x, int y, string name);
    void deleteItem(int key);
    int hashFunction(int x) {
        return (x % BUCKET);
    }
    int findItem(int);
    void displayHash();
    void reHash();
};
Hash::Hash(int b)
{
    this->BUCKET = b;
    table = new list<HashNode>[BUCKET];
}
void Hash::insertItem(int key, int value, string name)
{
    int index = hashFunction(key);
    HashNode h;
    h.key=key;
    h.value=value;
    strcpy(h.name,name.c_str());
    table[index].push_back(h);
    reHash();
}

void Hash::deleteItem(int key)
{
    //Получаем хэш индекс по ключу
    int index = hashFunction(key);
    // find the key in (index)th list поиск элемента  хэш таблицы поключу
    list <HashNode> :: iterator i;
    for (i = table[index].begin();
         i != table[index].end(); i++) {
        if (i->key == key)
            break;
    }
    // если ключ найден, то удаляем элемент хэш таблицы
    if (i != table[index].end())
        table[index].erase(i);
}
// Функция для отображения хэш таблицы
void Hash::displayHash() {
    for (int i = 0; i < BUCKET; i++) {
        cout << i;
        for (auto x : table[i])
            cout << " >>>> " << x.key<<" "<<x.value<<" "<<x.name;
        cout << endl;
    }
}

void Hash::reHash(){
    list<HashNode> *table2;
    int n=0;
    for(int i = 0; i < BUCKET; i++){
        if(!table[i].empty()){
            n++;
        }
    }
    if((n*1.0/(this->BUCKET))>=0.75){
        table2 = new list<HashNode>[BUCKET*2];
        for(int i = 0; i < BUCKET; i++){
            if(!table[i].empty()){
                for(auto j : table[i] ){
                    table2[i].push_back(j);
                }
            }
        }
        BUCKET=BUCKET*2;
        table->clear();
        table = new list<HashNode>[BUCKET];
        for(int i = 0; i < BUCKET; i++){
            if(!table2[i].empty()){
                for(auto j : table2[i] ){
                    int index= hashFunction(j.key);
                    table[index].push_back(j);
                }
            }
        }
    }
}

int Hash::findItem(int key) {

    //Получаем хэш индекс по ключу
    int index = hashFunction(key);
    list <HashNode> :: iterator i;
    for (i = table[index].begin();
         i != table[index].end(); i++) {
        if (i->key == key) {
            cout << key << " Элемент найден в таблице" << endl;
            return i->value;
        }
    }
    cout<<key<<" Элемент не найден в таблице"<<endl;
    return -1;
}

#endif