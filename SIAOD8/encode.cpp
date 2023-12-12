#include <iostream>
#include <string>
#include <map>
#include <bits/stdc++.h>

using namespace std;

struct node {
    string sym;
    float pro;
    int arr[50];
    int top;
}p[50];

typedef struct node node;

void shannon(int l, int h, node p[]) {

    float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
    int i, d, k, j;
    if ((l + 1) == h or l == h or l > h) {
        if (l == h or l > h)
            return;
        p[h].arr[++(p[h].top)] = 0;
        p[l].arr[++(p[l].top)] = 1;
        return;
    }
    else {
        for (i = l; i <= h - 1; i++)
            pack1 = pack1 + p[i].pro;
        pack2 = pack2 + p[h].pro;
        diff1 = pack1 - pack2;
        if (diff1 < 0)
            diff1 = diff1 * -1;
        j = 2;
        while (j != h - l + 1) {
            k = h - j;
            pack1 = pack2 = 0;
            for (i = l; i <= k; i++)
                pack1 = pack1 + p[i].pro;
            for (i = h; i > k; i--)
                pack2 = pack2 + p[i].pro;
            diff2 = pack1 - pack2;
            if (diff2 < 0)
                diff2 = diff2 * -1;
            if (diff2 >= diff1)
                break;
            diff1 = diff2;
            j++;
        }
        k++;
        for (i = l; i <= k; i++)
            p[i].arr[++(p[i].top)] = 1;
        for (i = k + 1; i <= h; i++)
            p[i].arr[++(p[i].top)] = 0;

        shannon(l, k, p);
        shannon(k + 1, h, p);
    }
}

//Sort
void shannonSortByFreq(int n, node p[]) {
    int i, j;
    node temp;
    for (j = 1; j <= n - 1; j++) {
        for (i = 0; i < n - 1; i++) {
            if ((p[i].pro) > (p[i + 1].pro)) {
                temp.pro = p[i].pro;
                temp.sym = p[i].sym;
                p[i].pro = p[i + 1].pro;
                p[i].sym = p[i + 1].sym;
                p[i + 1].pro = temp.pro;
                p[i + 1].sym = temp.sym;
            }
        }
    }
}

// Output
void ShannonDisplayFreqChars(int n, node p[]) {

    int i, j;
    cout << "Symbol\tPossibility\tCode";
    for (i = 0; i < n; i++) {
        cout << "\n" << p[i].sym << "\t" << p[i].pro << "\t";
        for (j = 0; j <= p[i].top; j++)
            cout << p[i].arr[j];
    }
}
//Coded
string code(string n, node p[], int k) {
    string cod;
    for (int i = 0; i < n.size(); i++) {
        string s(1, n[i]);
        string v = "";
        for (int l = 0; l < k; l++) {
            if (p[l].sym == s) {
                for (int j = 0; j <= p[l].top; j++)
                    v += to_string(p[l].arr[j]);
                cod += v;
            }
        }
    }
    cout << cod;
    return cod;
}

// Decoded
void decode(string code, node p[], int k) {
    string ch = "";
    string n = "";
    for (int i = 0; i < code.size();) {
        ch += code[i];

        for (int l = 0; l < k; l++) {
            string v = "";
            for (int j = 0; j <= p[l].top; j++)
                v += to_string(p[l].arr[j]);
            if (ch == v) {
                n = p[l].sym;
                cout << n;
                ch = "";
            }

        }
        i++;
    }
}


/*Haffman*/
map<char, string> codes;
map<char, int> freq;

struct minim_node {
    char data;
    int freq;
    minim_node* left, * right;

    minim_node(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;

    }
};


struct compare {
    bool operator()(minim_node* l, minim_node* r) {
        return (l->freq > r->freq);
    }
};


void print_code(struct minim_node* root, string str) {
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    print_code(root->left, str + "0");
    print_code(root->right, str + "1");
}


void status_codes(struct minim_node* root, string str) {
    if (root == NULL)
        return;
    if (root->data != '$')
        codes[root->data] = str;
    status_codes(root->left, str + "0");
    status_codes(root->right, str + "1");
}

priority_queue<minim_node*, vector<minim_node*>, compare> minHeap;

void HuffmanCodes(int size) {
    struct minim_node* left, * right, * top;
    for (map<char, int>::iterator v = freq.begin();
         v != freq.end(); v++)
        minHeap.push(new minim_node(v->first, v->second));
    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new minim_node('$',
                             left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    status_codes(minHeap.top(), "");
}

void calcFreq(string str, int n) {
    for (int i = 0; i < str.size(); i++)
        freq[str[i]]++;
}


string decode_file(struct minim_node* root, string s) {
    string ans = "";
    struct minim_node* curr = root;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;
        if (curr->left == NULL and curr->right == NULL) {
            ans += curr->data;
            curr = root;
        }
    }
    return ans + '\0';
}


/*LZ77*/
struct Node77 {
    int offset;
    int length;
    char next;

    string toString() {
        return '{' + to_string(offset) + ',' + to_string(length) + ',' + next + '}';
    }
};


struct Buffer {
private:
    string str;
    int size;
public:
    string buf;
    int pos = 0;
    void shift(int x) {
        pos += x;
        if (pos < size) {
            buf = str.substr(0, pos);
        }
        else {
            buf = str.substr(pos - size, size);
        }
    }

    Buffer(string str, int size) {
        this->str = std::move(str);
        this->size = size;
        buf = "";
    }
};

struct LZ77 {
    string code;
    list<Node77> encoded_list;

    //Coded
    string encode(string line, int size) {
        Buffer buf(line, size);
        list<Node77> res;
        while (buf.pos < line.size()) {
            int offset = 0;
            int length = 0;
            char next = ' ';
            for (int i = 0; i < buf.buf.size(); i++) {
                int j = 0;

                while (buf.buf[i + j % (buf.buf.size() - i)] == line[buf.pos + j])
                    j++;

                if (j >= length && j != 0) {
                    length = j;
                    offset = buf.buf.size() - i;
                    next = line[buf.pos + j];
                }
            }
            if (length == 0)
                next = line[buf.pos];
            res.push_back({ offset,length,next });
            buf.shift(length + 1);
        }
        string result = "";
        for (auto& i : res) {
            result += i.toString();
        }
        code = result;
        encoded_list = res;
        return result;
    }

    //Decode
    string decode() {
        string res = "";
        for (auto& i : encoded_list) {
            if (i.length == 0) {
                res += i.next;
            }
            else {
                for (int j = 0; j < i.length; j++) {
                    res += res[res.size() - i.offset];
                }
                res += i.next;
            }
        }
        return res;
    }
};


/*LZ78*/
struct Node78 {
    int ref;
    string next = "";

    string toString() {
        return "{" + to_string(ref) + "," + next + "}";
    }
};

struct LZ78 {
    string code;
    list<Node78> encoded_list;

    //Coded
    string encode(string line) {
        list<string> dict;
        list<Node78> res;
        int pos = 0;
        while (pos < line.size()) {
            string buf = "";
            int ref = 0;
            int l = 1;
            int length = 0;
            string next = " ";

            for (auto& i : dict) {

                int j = 0;
                while (i[j] == line[pos + j])
                    j++;
                if (j > length) {
                    length = j;
                    ref = l;
                    next = line[pos + j];
                    buf = i + next;
                }
                l++;
            }
            if (length == 0)
            {
                next = line[pos];
                buf = next;
            }
            res.push_back({ ref,next });
            dict.push_back(buf);
            pos += length + 1;
        }

        string result = "";
        for (auto& i : res) {
            result += i.toString();
        }
        code = result;
        encoded_list = res;
        return result;
    }

    //Decoded
    string decode() {
        vector<string> dict;
        string res = "";
        for (auto& i : encoded_list) {
            if (i.ref == 0) {
                res += i.next;
                dict.push_back(i.next);
            }
            else {
                res += dict[i.ref - 1] + i.next;
                dict.push_back(dict.front() + i.next);
            }
        }
        return res;
    }
};


int main() {
    system("chcp 1251");
    int  i, j;
    string n = "Прибавь к ослиной\n"
               "голове\n"
               "Еще одну, получишь\n"
               "две.\n"
               "Но сколько б ни было\n"
               "ослов, Они и двух не свяжут\n"
               "слов. ";
    float total = 0;
    string ch;

    cout << endl << "Shenon-Phano" << endl;
    cout  << "Input: " << n << endl;
    for (i = 0; i < n.size(); i++) {
        ch = n[i];
    }
    int sum = 0;
    int k = 0;
    std::map<char, int> chars;
    for (const char c : n)
        ++chars[c];
    for (const auto& l : chars) {
        sum += l.second;
        p[k].sym = l.first;
        k++;
    }

    float x[50] = { 0 };
    i = 0;
    for (const auto& l : chars) {
        x[i] = (float)l.second / (float)sum;
        p[i].pro = x[i];
        total = total + p[i].pro;
        i++;
    }
    p[i].pro = 1 - total;
    shannonSortByFreq(k, p);
    for (i = 0; i < k; i++)
        p[i].top = -1;
    shannon(0, k - 1, p);
    ShannonDisplayFreqChars(k, p);
    cout << endl << "Coded: ";
    string cod = code(n, p, k);
    cout << endl;
    cout << "ДеCoded: ";
    decode(cod, p, k);


    cout << endl << endl << "Haffman" << endl;

    string encoded_str, coded_str;
    calcFreq(n, n.length());
    HuffmanCodes(n.length());
    cout << "Symbol\tPossibility\tCode" << endl;
    for (auto v = codes.begin(); v != codes.end(); v++) {
        cout << v->first << "\t";
        for (auto v2 = freq.begin(); v2 != freq.end(); v2++) {
            if (v2->first == v->first) {
                cout  << double(v2->second) / double(n.length());
                break;
            }
        }
        cout << "\t" << v->second << endl;
    }


    for (auto i : n)
        encoded_str += codes[i];

    cout << endl << "Coded: " << encoded_str << endl;

    coded_str = decode_file(minHeap.top(), encoded_str);
    cout << "Decoded: " << coded_str << endl;


    cout << endl << "LZ77" << endl;


    string lz77_str = "101000100101010001011";
    LZ77 lz77;
    string code = lz77.encode(lz77_str, 5);
    cout << "Input: " << lz77_str << endl;
    cout << "Coded: " << code << endl << "Decoded: ";
    cout <<  lz77.decode() << endl;


    cout << endl << "LZ78" << endl;

    string lz78_str = "какатанекатанекатата ";
    LZ78 lz78;
    string code2 = lz78.encode(lz78_str);
    cout << "Input: " << lz78_str << endl;
    cout << "Coded: " << code2 << endl << "Decoded: " << lz78.decode() << endl;
    return 0;
}