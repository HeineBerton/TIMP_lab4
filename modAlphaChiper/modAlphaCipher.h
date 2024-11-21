/** @file modAlphaCipher.h
 * @author Федякина Т.Н.
 * @version 1.0
 * @date 21.11.2024
 * @copyright ИБСТ ПГУ
 */

#pragma once
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <cwctype>
#include <codecvt>
#include <locale>

/** @brief Класс для шифрования методом Гронсфельда
 * 
 * Этот класс реализует шифрование и расшифрование текста с использованием
 * метода Гронсфельда. Ключ устанавливается при создании объекта класса.
 * Методы encrypt и decrypt используются для шифрования и расшифрования
 * соответственно.
 *
 * @warning Реализация предназначена только для русского языка.
 */
class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///< Алфавит по порядку
    std::map<char, int> alphaNum; ///< Ассоциативный массив "номер по символу"
    std::vector<int> key; ///< Ключ для шифрования/расшифрования
    std::vector<int> convert(const std::wstring& s); ///< Преобразование строки в вектор
    std::wstring convert(const std::vector<int>& v); ///< Преобразование вектора в строку
    
    /**
     * @brief Валидация ключа
     * 
     * Проверяет, что ключ не пустой и не содержит символов, не принадлежащих алфавиту.
     * 
     * @param s Входная строка, представляющая ключ.
     * @throw cipher_error Если ключ пустой или содержит недопустимые символы.
     */
    std::wstring getValidKey(const std::wstring & s);
    
    /**
     * @brief Валидация открытого текста
     * 
     * Проверяет, что открытый текст содержит только допустимые символы алфавита.
     * 
     * @param ws Входная строка, представляющая открытый текст.
     * @throw cipher_error Если открытый текст содержит недопустимые символы.
     */
    std::wstring getValidOpenText(const std::wstring & ws);
    
    /**
     * @brief Валидация зашифрованного текста
     * 
     * Проверяет, что зашифрованный текст содержит только допустимые символы алфавита.
     * 
     * @param ws Входная строка, представляющая зашифрованный текст.
     * @throw cipher_error Если зашифрованный текст содержит недопустимые символы.
     */
    std::wstring getValidCipherText(const std::wstring & ws);
    
public:
    modAlphaCipher() = delete; ///< Запрет на использование конструктора по умолчанию
    /**
     * @brief Конструктор для установки ключа
     * 
     * @param skey Строка, представляющая ключ для шифрования.
     */
    modAlphaCipher(const std::wstring& skey);
    
    /**
     * @brief Зашифрование открытого текста
     * 
     * @param open_text Открытый текст для шифрования.
     * @return Зашифрованный текст.
     */
    std::wstring encrypt(const std::wstring& open_text);
    
    /**
     * @brief Расшифрование зашифрованного текста
     * 
     * @param cipher_text Зашифрованный текст для расшифрования.
     * @return Открытый текст.
     */
    std::wstring decrypt(const std::wstring& cipher_text);
};

/**
 * @brief Исключение для ошибок шифрования
 * 
 * Класс исключений, используемый для обработки ошибок, связанных с
 * шифрованием и расшифрованием.
 */
class cipher_error : public std::invalid_argument
{
public:
    /**
     * @brief Конструктор с аргументом типа std::string
     * 
     * @param what_arg Сообщение об ошибке.
     */
    explicit cipher_error(const std::string& what_arg)
        : std::invalid_argument(what_arg) {
    }
    
    /**
     * @brief Конструктор с аргументом типа const char*
     * 
     * @param what_arg Сообщение об ошибке.
     */
    explicit cipher_error(const char* what_arg)
        : std::invalid_argument(what_arg) {
    }
};
