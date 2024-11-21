/**
 * @file crypt.h
 * @author Федякина Т.Н.
 * @version 1.0
 * @brief Описание класса Crypt
 * @date 21.11.2024
 */

#pragma once
#include <string>
#include <stdexcept>
#include <codecvt>
#include <sstream>
#include <iostream>
#include <locale>
#include <UnitTest++/UnitTest++.h>

/** 
 * @brief Шифрование методом табличной маршрутной перестановки
 * 
 * Класс `Crypt` реализует шифрование и расшифрование текста с использованием
 * метода табличной маршрутной перестановки. Ключ задается в конструкторе,
 * а методы `encrypt` и `decrypt` используются для шифрования и расшифрования
 * текста соответственно.
 * 
 * @warning Реализация предназначена только для русского языка.
 */
class Crypt {
private:
    int key; ///< Ключ для шифрования/расшифрования

    /**
     * @brief Проверка, является ли строка целым числом
     * 
     * Этот метод проверяет, может ли строка быть преобразована в целое число.
     * 
     * @param str Строка для проверки.
     * @return true Если строка является целым числом.
     * @return false Если строка не является целым числом.
     */
    bool isInteger(const std::string& str);

public:
    Crypt() = delete; ///< Запрет на использование конструктора по умолчанию

    /**
     * @brief Конструктор класса Crypt
     * 
     * @param keyStr Строка, представляющая ключ для шифрования.
     * @throw CryptException Если ключ недействителен.
     */
    Crypt(const std::string& keyStr);

    /**
     * @brief Зашифрование текста
     * 
     * Метод шифрует переданный текст с использованием установленного ключа.
     * 
     * @param text Открытый текст для шифрования.
     * @return Зашифрованный текст в виде строки.
     */
    std::wstring encrypt(const std::wstring& text);

    /**
     * @brief Расшифрование текста
     * 
     * Метод расшифровывает переданный зашифрованный текст с использованием установленного ключа.
     * 
     * @param encrypted_text Зашифрованный текст для расшифрования.
     * @return Открытый текст в виде строки.
     */
    std::wstring decrypt(const std::wstring& encrypted_text);

    /**
     * @brief Валидация ключа
     * 
     * Проверяет, является ли ключ допустимым для шифрования текста.
     * 
     * @param key Ключ для проверки.
     * @param text Открытый текст, для которого проверяется ключ.
     * @return Допустимый ключ.
     * @throw CryptException Если ключ недействителен.
     */
    int getValidKey(const int& key, const std::wstring& text);

    /**
     * @brief Валидация открытого текста
     * 
     * Проверяет, что открытый текст содержит только допустимые символы.
     * 
     * @param s Открытый текст для проверки.
     * @return Проверенный открытый текст.
     * @throw CryptException Если открытый текст содержит недопустимые символы.
     */
    std::wstring getValidOpenText(const std::wstring& s);

    /**
     * @brief Валидация зашифрованного текста
     * 
     * Проверяет, что зашифрованный текст содержит только допустимые символы.
     * 
     * @param s Зашифрованный текст для проверки.
     * @return Проверенный зашифрованный текст.
     * @throw CryptException Если зашифрованный текст содержит недопустимые символы.
     */
    std::wstring getValidCipherText(const std::wstring& s);
};

/**
 * @brief Исключение для ошибок в классе Crypt
 * 
 * Класс исключений, используемый для обработки ошибок, связанных с
 * шифрованием и расшифрованием.
 */
class CryptException : public std::invalid_argument {
public:
    /**
     * @brief Конструктор с аргументом типа std::string
     * 
     * @param what_arg Сообщение об ошибке.
     */
    explicit CryptException(const std::string& what_arg)
        : std::invalid_argument(what_arg) {}

    /**
     * @brief Конструктор с аргументом типа const char*
     * 
     * @param what_arg Сообщение об ошибке.
     */
    explicit CryptException(const char* what_arg)
        : std::invalid_argument(what_arg) {}
};
