#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, char>> LZ78Encode(const string& data) {
    vector<pair<int, char>> encodedData;
    map<string, int> dictionary;
    int currentIndex = 0;

    for (char c : data) {
        string currentPhrase = string(1, c);

        // Проверка, существует ли текущая фраза в словаре
        if (dictionary.count(currentPhrase) > 0) {
            currentIndex = dictionary[currentPhrase];
        }
        else {
            encodedData.emplace_back(currentIndex, c);
            dictionary[currentPhrase] = currentIndex + 1;
            currentIndex++;
        }
    }

    return encodedData;
}

string LZ78Decode(const vector<pair<int, char>>& encodedData) {
    string decodedData = "";
    map<int, string> dictionary;

    for (const auto& pair : encodedData) {
        int index = pair.first;
        char c = pair.second;

        string currentPhrase;

        // Проверка, существует ли текущий индекс в словаре
        if (dictionary.count(index) > 0) {
            currentPhrase = dictionary[index];
        }

        currentPhrase += c;
        decodedData += currentPhrase;
        dictionary[index + 1] = currentPhrase;
    }

    return decodedData;
}

//int main() {
//    setlocale(LC_ALL, "rus");
//    string data = "webwerbweberweberweb";
//    vector<pair<int, char>> encodedData = LZ78Encode(data);
//
//    // Вывод закодированных данных
//    cout << "Закодированные данные: ";
//    for (const auto& pair : encodedData) {
//        cout << "(" << pair.first << ", " << pair.second << ") ";
//    }
//    cout << endl;
//
//    // Раскодирование данных
//    string decodedData = LZ78Decode(encodedData);
//    cout << "Раскодированные данные: " << decodedData << endl;
//
//    return 0;
//}