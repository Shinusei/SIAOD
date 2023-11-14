#ifndef BIN_H
#define BIN_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include "hash.h"
using namespace std;

struct Struct{
    int num;
    int code;
    char name[30];
};

void createBinFile(ifstream &ft, ofstream &fb){
    fb.open("bin.dat",ios::out | ios::binary);
    ft.open("text.txt",ios::in);
    Struct x;
    while (!ft.eof()){
        ft>>x.num;
        ft.get();
        ft>>x.code;
        ft.get();
        ft>>x.name;
        ft.get();
        fb.write((char *)&x,sizeof(Struct));
    }
    fb.close();
    ft.close();
}

void outBinFile(ifstream &fb,string fName){
    fb.open(fName,ios::in | ios::binary);
    Struct x;
    fb.read((char *)&x,sizeof(Struct));
    while(!fb.eof()){
        cout<<x.num<<" ";
        cout<<x.code<<" ";
        cout<<x.name<<" ";
        fb.read((char *)&x,sizeof(Struct));
    }
    cout << endl;
    fb.close();
}

void existIndex(ifstream &fb,int j) {
    Struct x;
    int i=1;
    fb.open("bin.dat",ios::in | ios::binary);
    while(!fb.eof()){
        fb.read((char *)&x , sizeof(Struct));

        if(j==i){
            cout << "Запись "<<j<<"  " <<x.num << " " << x.code << " " << x.name;
            fb.close();
            return;
        }
        i++;
    };
    fb.close();
    cout<<"Записи с номером "<< i<<" нет!"<<endl;
}

void saveTxt(ifstream &ft, ofstream &ft2){
    ft.open("bin.dat",ios::in | ios::binary);
    ft2.open("saveFile.txt",ios::out | ios::trunc);
    Struct x;
    while(!ft.eof()){
        ft.read((char *)&x , sizeof(Struct));
        ft2<<x.num <<endl<< x.code<<endl<< x.name << endl;
    }
    ft.close();
    ft2.close();
}

void deleteFromBin(string sName){
    fstream file;
    file.open("bin.dat",  ios::in | ios::binary);
    if(!file.is_open()){cout<<"Ошибка чтения файла";return;}

    Struct currentStruct;
    vector<Struct> records;
    while(!file.eof()) {
        file.read(reinterpret_cast<char*>(&currentStruct), sizeof(Struct));
        records.push_back(currentStruct);
    }
    file.seekg(0);
    bool found= false;
    for (int j = 0; j < records.size(); j++) {
        if (records[j].name == sName) {
            records[j] = records.back();
            records.pop_back();
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
        std::cout << "Запись с ключом " << sName << " не найдена." << std::endl;
    } else {
        std::cout << "Запись с ключом " << sName << " заменена." << std::endl;
    }
    file.close();
    return;
}

void formByCode(int codeNum, ifstream &fb){
    ofstream fn;
    fb.open("bin.dat",ios::in | ios::binary);
    fn.open("code.dat",ios::out | ios::binary);
    Struct x;
    fb.read((char *)&x,sizeof(Struct));
    while(!fb.eof()){
        if(x.code==codeNum){
            fn.write((char *)&x,sizeof(Struct));
        }
        fb.read((char *)&x,sizeof(Struct));
    }
    cout << endl;
    fb.close();
    fn.close();
}

void changeName(string sName, int mas[],int count){
    fstream fb;
    Struct x;
    vector<Struct> record;
    fb.open("bin.dat",ios::in | ios::binary);
    if(!fb.is_open()){cout<<"Ошибка чтения файла";return;}
    while(!fb.eof()){
        fb.read((char *)&x , sizeof(Struct));
        for (int i = 0; i< count;i++) {
            if(mas[i]==x.code){
                strcpy(x.name,sName.c_str());
            }
        }
        record.push_back(x);
    }
    fb.close();
    fb.open("bin.dat",  ios::out | ios::in | ios::binary | ios::trunc);
    int len=record.size();
    for(int j=0;j<len-1;j++) {
        fb.write(reinterpret_cast<const char *>(&record[j]), sizeof(Struct));
    }
    fb.close();
}

bool fileExist(ifstream &fin, ofstream &fout){
    fin.open("text.txt",ios::out );
    fout.open("bin.dat",ios::in | ios::binary);
    if(!fin.good() ){
        cout<<"Файл txt не открыт";
        return false;
    }
    if(!fout.good() ){
        cout<<"Файл dat не открыт";
        return false;
    }
    fout.close();
    fin.close();
    return true;
}
#endif