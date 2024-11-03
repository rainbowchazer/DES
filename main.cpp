#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

string AddedSymbol;

vector<int> left_shifts = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
vector<vector<vector<int>>> SBOX = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
       {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
       {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
       {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
       {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
       {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
       {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
       {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};
//Таблица для сжатия ключа до 56 бит
vector <int> PC1 = { 57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4 };

//Таблица для сжатия ключей Фейстеля до 48 бит
vector <int>   PC2 = { 14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32 };

// Начальная перестановка IP
vector <int>    IP = { 58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7 };

// Функция расширения r(32 bits) in 48 bits
vector <int>   E = { 32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1 };

vector <int>    P = { 16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25 };

//Обратная перестановка IP
vector <int> IP_FINAL = { 40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25 };


//переводим строку в биты
//получаем код по аски буквы цифру переводим в биты
std::string stringToBits(const std::string& str) {
    std::string result;
    for (char c : str) {
        for (int i = 7; i >= 0; --i) {
            result += ((c >> i) & 1) ? '1' : '0';
        }
    }
    return result;
}

//перестановка
std::string permute(const std::string& binary_block, const std::vector<int>& table) {
    std::string result;
    for (int i = 0; i < table.size(); ++i) {
        result += binary_block[table[i] - 1];
    }
    return result;
}

//разделение строк на две части
std::pair<std::string, std::string> split(const std::string& block_bin) {
    size_t middle = block_bin.length() / 2;
    std::string first_half = block_bin.substr(0, middle);
    std::string second_half = block_bin.substr(middle);
    return std::make_pair(first_half, second_half);
}

//сдвинуть строку на shift_by влево
string shift_left(const string& str, int shift_by) {
    int length = str.size();
    shift_by %= length; // Обработка случая, если сдвиг больше длины строки
    string shifted_str = str.substr(shift_by) + str.substr(0, shift_by);
    return shifted_str;
}

//функция где мы генерируем ключи
void GenKeys(vector<string>& keys, string key) {

    //Делаем ключ 64 битным
    key = stringToBits("0" + key);
    //ужимаем ключ до 56 бит
    key = permute(key, PC1);
    for (auto i : left_shifts) {
        string left = split(key).first;
        string right = split(key).second;
        left = shift_left(left, i);
        right = shift_left(right, i);
        key = left + right;
        keys.push_back(permute(key, PC2));
    }

}

std::string strXOR(const std::string& str1, const std::string& str2) {
    std::string result;
    for (int i = 0; i < str1.length() && i < str2.length(); ++i) {
        result += std::to_string(int(str1[i]) ^ int(str2[i]));
    }
    return result;
}


int BinToInt(string bin) {
    int result = 0;
    int len = bin.length();
    for (int i = len - 1; i >= 0; i--) {
        if (bin[i] == '1') {
            result += pow(2, len - 1 - i);
        }
    }
    return result;
}

std::string IntToBin(int number, int n) {
    if (number == 0)
        return std::string(n, '0');

    std::string binary_string = "";
    while (number > 0) {
        binary_string = (number % 2 == 0 ? "0" : "1") + binary_string;
        number /= 2;
    }
    // Дополнить строку до длины n при необходимости
    while (binary_string.length() < n) {
        binary_string = "0" + binary_string;
    }
    return binary_string;
}

string des(string block, vector<string>& keys) {
    block = permute(block, IP);
    string left = split(block).first;
    string right = split(block).second;
    //теперь мы начинаем шифровать наш блок
    //на каждой итерации цикла снизу мы по сути генирируем новый Ri
    for (auto i : keys) {
        string Ri = "";
        //наши сгенерированные ключи имеют длину в 48 бит
        //правая часть блока имеет длину в 32 бита
        //мы её расшираем перестановка с таблицей E
        string Ri_and_key = strXOR(permute(right, E), i);
        vector<string> grups[2];
        for (int j = 0; j < Ri_and_key.size(); j += 6) {
            grups[0].push_back(Ri_and_key.substr(j, 1) + Ri_and_key.substr(j + 5, 1)); // row
            grups[1].push_back(Ri_and_key.substr(j + 1, 4)); // col
        }
        for (int j = 0; j < 8; j++) {
            int row = BinToInt(grups[0][j]);
            int col = BinToInt(grups[1][j]);
            Ri += (IntToBin(SBOX[j][row][col], 4));
        }
        Ri = permute(Ri, P);
        string temp = strXOR(left, Ri);
        left = right;
        right = temp;
    }
    block = right + left;
    block = permute(block, IP_FINAL);
    return block;
}


string crypt(string m, string key, bool decrypt = false) {
    vector<string> keys;
    GenKeys(keys, key);
    string result = "";
    //когда мы шифруем передаём буквы сообщение
    if (!decrypt) {
        for (size_t i = 0; i < m.length(); i += 8) {
            string block = m.substr(i, 8);
            if (block.length() != 8) {
                AddedSymbol = to_string(8 - block.length());
                for (size_t j = block.length(); j < 8; j++) {
                    block += AddedSymbol;
                }
            }
            block = stringToBits(block);
            result += des(block, keys);
        }
    }
    //когда выполняем расшифровку передаём битовую последовательсть
    else {
        reverse(keys.begin(), keys.end());
        for (size_t i = 0; i < m.length(); i += 64) {
            string block = m.substr(i, 64);
            result += des(block, keys);
        }
    }
    return result;
}

string BinToStr(string str) {
    string result = "";
    for (int i = 0; i < str.size(); i += 8) {
        int num = BinToInt(str.substr(i, 8));
        result += char(num);
    }
    return result;
}

string stringDelAddSym(string str) {
    string res = "";
    for (int i = 0; i < str.size() - stoi(AddedSymbol); i++) {
        res += str[i];
    }
    return res;
}

std::string generateRandomString(int length) {
    const std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int charsetLength = charset.length();
    std::string randomString;

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < length; ++i) {
        randomString += charset[std::rand() % charsetLength];
    }

    return randomString;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    srand(time(nullptr));
    int offset = 65;
    char option;
    std::cout << "\t\tЛабораторная работа №3" << std::endl;
    for (int i = 0; i < offset; i++) std::cout << "-";
    std::cout << std::endl;
    std::cout << "Используем алгоритм шифрования DES для зашифровки сообщения." << std::endl;
    do
    {
        std::cout << "1. Зашифровать заранее заготовленные сообщения (введите '1')." << std::endl
            << "2. Зашифровать что-то свое (введите '2')." << std::endl
            << "3. Выход из программы (введите '0')" << std::endl
            << "Ввод: ";
        std::cin >> option;
        for (int i = 0; i < offset; i++) std::cout << "-";
        std::cout << std::endl;
        switch (option)
        {
        case '1':
        {
            //ключ длинной в 7 символов;
            string key = generateRandomString(7);
            cout << "Сгенерированный ключ: " << key << std::endl;
            string text = "Bochkareva Anastasia Alekseevna";

            string enc_text = crypt(text, key);
            string dec_text = crypt(enc_text, key, true);

            cout << "Сообщение, которое мы вводим: " << text << endl;
            cout << "Его вид в зашифрованной форме: " << enc_text << endl;
            cout << "Расшифрованное сообщение: " << stringDelAddSym(BinToStr(dec_text)) << endl;

            //ключ длинной в 7 символов;
            string key1 = generateRandomString(7);
            cout << "Сгенерированный ключ: " << key1 << std::endl;
            string text1 = "Nizhegorodskij gosudarstvennyj tekhnicheskij universitet";

            string enc_text1 = crypt(text1, key1);
            string dec_text1 = crypt(enc_text1, key1, true);

            cout << "Сообщение, которое мы вводим: " << text1 << endl;
            cout << "Его вид в зашифрованной форме: " << enc_text1 << endl;
            cout << "Расшифрованное сообщение: " << stringDelAddSym(BinToStr(dec_text1)) << endl;
            std::cout << std::endl;
            break;
        }
        case '2':
        {
            string mes3 = "";
            //ключ длинной в 7 символов;
            string key = generateRandomString(7);
            cout << "Сгенерированный ключ: " << key << std::endl;
            cout << "Введите сообщение: ";
            std::cin.ignore();
            std::getline(std::cin, mes3);
            string enc_text = crypt(mes3, key);
            string dec_text = crypt(enc_text, key, true);
            cout << "Сообщение, которое мы вводим: " << mes3 << std::endl;
            cout << "Его вид в зашифрованной форме: " << enc_text << std::endl;
            cout << "Расшифрованное сообщение: " << stringDelAddSym(BinToStr(dec_text)) << std::endl;
            system("pause");
            std::cout << std::endl;
            break;
        }
        case '0':
        {
            system("pause");
            break;
        }
        default:
            std::cout << "Некорректный ввод, попробуйте ещё раз!" << std::endl;
            std::cout << std::endl;
            system("pause");
            std::cout << std::endl;
            break;
        }
    } while (option != '0');
    return 0;
}