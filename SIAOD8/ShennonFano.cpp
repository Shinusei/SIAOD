#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

struct ShannonFanoNode {
    string symbol;
    double probability;
    string code;
};

vector<ShannonFanoNode> ShannonFanoEncoding(const string& data) {
    vector<ShannonFanoNode> symbols;

    // Подсчет частоты появления символов
    map<char, int> frequency;
    int totalSymbols = 0;
    for (char c : data) {
        frequency[c]++;
        totalSymbols++;
    }

    // Создание узлов для каждого символа
    for (const auto& pair : frequency) {
        ShannonFanoNode node;
        node.symbol = pair.first;
        node.probability = static_cast<double>(pair.second) / totalSymbols;
        symbols.push_back(node);
    }

    // Рекурсивная функция для назначения кодов каждому символу
    function<void(int, int)> assignCodes = [&](int start, int end) {
        if (start == end) {
            return;
        }

        double sum = 0.0;
        for (int i = start; i <= end; ++i) {
            sum += symbols[i].probability;
        }

        double halfSum = 0.0;
        int splitIndex = -1;
        for (int i = start; i <= end; ++i) {
            halfSum += symbols[i].probability;
            if (halfSum >= sum / 2) {
                splitIndex = i;
                break;
            }
        }

        // Назначение кодов символам до разделителя
        for (int i = start; i <= splitIndex; ++i) {
            symbols[i].code += '0';
        }

        // Назначение кодов символам после разделителя
        for (int i = splitIndex + 1; i <= end; ++i) {
            symbols[i].code += '1';
        }

        assignCodes(start, splitIndex);
        assignCodes(splitIndex + 1, end);
    };

    // Сортировка символов по вероятности (в убывающем порядке)
    sort(symbols.begin(), symbols.end(),
        [](const ShannonFanoNode& a, const ShannonFanoNode& b) {
            return a.probability > b.probability;
        });

    // Назначение кодов
    assignCodes(0, symbols.size() - 1);

    return symbols;
}


int main() {
    setlocale(LC_ALL, "rus");

    //====================Shennon-Fano coding=========================
    string data = "Эне, бене, лики, паки, Цуль, буль-буль, Калики-цваки, Эус-беус, кликмадеус, бокс...";
    vector<ShannonFanoNode> encodedSymbols = ShannonFanoEncoding(data);

    // Вывод закодированных символов и соответствующих кодов
    for (const auto& symbol : encodedSymbols) {
        cout << symbol.symbol << ": " << symbol.code << endl;
    }

    string message = "";

    for (char c : data) {
        for (const auto& symbol : encodedSymbols) {
            if (symbol.symbol.compare(string(1, c)) == 0)
                message += symbol.code + " ";
        }
    }

    cout << "Закодированное сообщение: " << message;
    system("pause");
    return 0;
}