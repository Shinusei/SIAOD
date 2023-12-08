#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct LZ77Token {
    int offset;
    int length;
    char nextChar;
};

vector<LZ77Token> LZ77Compress(const string& data, int windowSize) {
    vector<LZ77Token> compressedData;

    int dataSize = static_cast<int>(data.size());
    int currentIndex = 0;

    while (currentIndex < dataSize) {
        LZ77Token token;
        token.offset = 0;
        token.length = 0;
        token.nextChar = data[currentIndex];

        // Поиск наилучшего совпадения в окне
        int searchStart = max(currentIndex - windowSize, 0);
        int searchEnd = currentIndex;
        for (int i = searchStart; i < currentIndex; ++i) {
            int currentLength = 0;

            // Подсчет длины совпадения
            while (currentIndex + currentLength < dataSize &&
                data[i + currentLength] == data[currentIndex + currentLength]) {
                ++currentLength;
            }

            // Обновление наилучшего совпадения
            if (currentLength > token.length) {
                token.offset = currentIndex - i;
                token.length = currentLength;
                token.nextChar = data[currentIndex + currentLength];
            }
        }

        compressedData.push_back(token);

        currentIndex += token.length + 1; // Добавляем длину совпадения + следующий символ
    }

    return compressedData;
}

//int main() {
//    string data = "01011011001010101011";
//    int windowSize = 6;
//    vector<LZ77Token> compressedData = LZ77Compress(data, windowSize);
//
//    // Вывод сжатых данных
//    for (const auto& token : compressedData) {
//        cout << "(" << token.offset << ", " << token.length << ", " << token.nextChar << ") ";
//    }
//    cout << endl;
//
//    return 0;
//}