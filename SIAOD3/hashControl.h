#ifndef HASHCONTROL_H
#define HASHCONTROL_H

#include "bin.h"
#include "hash.h"

using namespace std;
void fillHashTable(Hash &table,ifstream &fb){
    fb.open("bin.dat",ios::in | ios::binary);
    Struct x;
    fb.read((char *)&x,sizeof(Struct));
    int stn=0;
    while(!fb.eof()){
        table.insertItem(x.num,stn,x.name);
        fb.read((char *)&x,sizeof(Struct));
        stn++;
    }
    fb.close();
}
void deleteWithHashTable(Hash &table,int key){
    int keyNum=table.findItem(key);
    fstream file;
    file.open("bin.dat",  ios::in | ios::binary);
    if(! file.is_open()){cout<<"Ошибка чтения файла";return;}

    Struct currentStruct; Struct lastStruct;
    vector<Struct> records;
    while(!file.eof()) {
        file.read(reinterpret_cast<char*>(&currentStruct), sizeof(Struct));
        records.push_back(currentStruct);
    }
    file.seekg(0);
    bool found= false;
    for (int j = 0; j < records.size(); j++) {
        if (j==keyNum ) {
            records[j] = records.back();  // Копируем последний элемент вместо текущего
            //delete &records.back();
            records.pop_back();  // Удаляем последний элемен
            //records.erase(records.end());
            found = true;
            break;
        }
    }
    file.close();
    file.open("bin.dat",  ios::out | ios::in | ios::binary | ios::trunc);
    int len=records.size();
    if(found){len--;}
    for(int j=0;j<len;j++) {
        file.write(reinterpret_cast<const char *>(&records[j]), sizeof(Struct));
    }
    if (!found) {
        //std::cout << "Запись с ключом " << key << " не найдена." << std::endl;
    } else {
        //std::cout << "Запись с ключом " << key << " заменена." << std::endl;
    }
    file.close();
    table.deleteItem(key);
    return;
}
void findByHash(Hash &table,int key){
    int keyNum=table.findItem(key);
    fstream file;
    file.open("bin.dat",  ios::in | ios::binary);
    if(! file.is_open()){cout<<"Ошибка чтения файла";return;}
    Struct currentStruct;
    int n=0;
    while(!file.eof()) {
        file.read(reinterpret_cast<char*>(&currentStruct), sizeof(Struct));
        if(n==keyNum){
            cout<<currentStruct.num<<" ";
            cout<<currentStruct.code<<" ";
            cout<<currentStruct.name<<" ";
            break;
        }n++;
    }
    file.close();
}
#endif