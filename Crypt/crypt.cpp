#include "crypt.h"
#include <iostream>
#include <locale>
#include <string>
#include <sstream>
#include <codecvt>
#include <UnitTest++/UnitTest++.h>

using namespace std;

Crypt::Crypt(const std::string& keyStr) {
    if (!isInteger(keyStr)) {
        throw CryptException("Некорректный ключ: " + keyStr);
    }
    int key = std::stoi(keyStr);
    this->key = getValidKey(key, L""); // Передаем пустую строку, чтобы проверить только ключ
}

std::wstring Crypt::encrypt(const std::wstring& text) {
    // Проверяем ключ с текстом
    int validKey = getValidKey(key, text);
    wstring tmp = getValidOpenText(text);
    int rows = static_cast<int>((tmp.length() + validKey - 1) / validKey);
    wchar_t table[rows][validKey];

    int index = 0; 
    for (int i = 0; i < rows; i++) { 
        for (int j = 0; j < validKey; j++) { 
            if (index < static_cast<int>(tmp.length())) {
                table[i][j] = tmp[index];
                index++;
            } else {
                table[i][j] = L' '; 
            }
        }
    }

    std::wstring encrypted_text; 

    for (int i = validKey - 1; i >= 0; i--) {
        for (int j = 0; j < rows; j++) {
            if (table[j][i] == L' ') {
                encrypted_text += L'*';
            } else {
                encrypted_text += table[j][i];
            }
        }
    }

    return encrypted_text;
}

std::wstring Crypt::decrypt(const std::wstring& encrypted_text) {
    wstring tmp = getValidCipherText(encrypted_text);
    int validKey = getValidKey(key, tmp); // Проверяем ключ с зашифрованным текстом
    int rows = static_cast<int>((tmp.length() + validKey - 1) / validKey);
    wchar_t table[rows][validKey];

    int index = 0;
    for (int i = validKey - 1; i >= 0; i--) {
        for (int j = 0; j < rows; ++j) {
            if (index < static_cast<int>(tmp.length())) {
                table[j][i] = tmp[index];
                index++;
            } else {
                table[j][i] = L' ';
            }
        }
    }

    std::wstring decrypted_text;
    index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < validKey; j++) {
            if (table[i][j] == L'*') {
                decrypted_text += L' ';
            } else {
                decrypted_text += table[i][j];
            }
        }
    }
    
    return decrypted_text;
}

inline std::wstring Crypt::getValidOpenText(const std::wstring& s) {
    std::wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
        } else if (iswspace(c)) {
            tmp.push_back(c); 
        }
    }
    if (tmp.empty())
        throw CryptException("Пустой открытый текст");
    return tmp;
}

inline std::wstring Crypt::getValidCipherText(const std::wstring& s) {
    if (s.empty())
        throw CryptException("Пустой зашифрованный текст");

    std::wstring tmp(s);
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string m = converter.to_bytes(tmp);

    for (auto c : s) {
        if (c == L'*') {
            continue; 
        }
        if (!iswupper(c)) {
            throw CryptException(std::string("Неправильный зашифрованный текст: ") + m);
        }
    }
    return tmp;
}

inline int Crypt::getValidKey(const int& key, const std::wstring& text) {
    if (key <= 1) {
        throw CryptException("Некорректный ключ: " + std::to_string(key));
    }
    if (text.length() > 0 && key > static_cast<int>(text.length()) / 2) {
        throw CryptException("Длина ключа не должна превышать половину длины текста. Введенный ключ: " + std::to_string(key));
    }

    return key;
}
