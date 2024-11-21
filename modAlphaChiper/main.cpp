#include "modAlphaCipher.h"

#include <iostream>
#include <cctype>
#include <string>

using namespace std;
void check(const wstring& Text, const wstring& key, const bool destructCipherText = false)
{
try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text); // зашифровывание
        if(destructCipherText) {
            cipherText.front() = towlower(cipherText.front());
        }
        decryptedText = cipher.decrypt(cipherText);
        wcout << L"Ключ = " << key << endl;
        wcout << L"Введенный текст: "<< Text << endl;
        wcout << L"Зашифрованный текст: "<< cipherText << endl;
        wcout << L"Расшифрованный текст: "<<decryptedText << endl;

    } catch(const cipher_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
int main(int argc, char** argv)
{
    locale loc("ru_RU.UTF-8");
	locale::global(loc); 
    wcout << L"ТЕСТ" << endl;
    
    wcout << L"Тест на ключ:" << endl;
    check(L"Я не провалил тест. Я просто нашёл сто способов написать его неправильно.", L"КЛЮ1");
    wcout << endl;

    wcout << L"Тест на преобразование регистра и удаление пробелов:" << endl;
    check(L"Я не провалил тест. Я просто нашёл сто способов написать его неправильно.", L"КЛЮЧ");
    wcout << endl;
    
    wcout << L"Тест на ввод одних цифр:" << endl;
    check(L"123", L"КЛЮЧ");
    wcout << endl;

    wcout << L"Тест на испорченный зашифрованный текст:" << endl;
    check(L"Я не провалил тест. Я просто нашёл сто способов написать его неправильно.", L"КЛЮЧ", true);
    wcout << endl;
    
    wcout << L"ТЕСТ" << endl;
    return 0;
}