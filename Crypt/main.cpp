#include "crypt.cpp"
#include "crypt.h"
#include <iostream>
#include <limits>
#include <locale>
#include <string>
#include <codecvt>
#include <UnitTest++/UnitTest++.h>

using namespace std;

SUITE(KeyTest) {
    TEST(ValidKey) {
        CHECK(L"РВТПИЕ" == Crypt("2").encrypt(L"привет"));
    }
    TEST(LenKey2) {
        CHECK(L"ИТРЕПВ" == Crypt("3").encrypt(L"привет"));
    }
    TEST(BigLenKey) {
        std::wstring text = L"привет";
        CHECK_THROW(Crypt("4").encrypt(text), CryptException);
    }
    TEST(InvalidKey) {
        CHECK_THROW(Crypt("q"), CryptException);
    }
    TEST(EmptyKey) {
        CHECK_THROW(Crypt(""), CryptException);
    }
    TEST(SimKey) {
        CHECK_THROW(Crypt("1!2"), CryptException);
    }
    TEST(NegKey) {
        CHECK_THROW(Crypt("-3"), CryptException);
    }
    TEST(DoubleKey) {
        CHECK_THROW(Crypt("2.5"), CryptException);
    }
    TEST(Key0) {
        CHECK_THROW(Crypt("0"), CryptException);
    }
}

SUITE(EncryptTest) {
    TEST(EncBigLet) {
        CHECK(L"ИТРЕПВ" == Crypt("3").encrypt(L"ПРИВЕТ"));
    }
    TEST(EncSmLit) {
        CHECK(L"ИТРЕПВ" == Crypt("3").encrypt(L"привет")); 
    }
    TEST(EncAllinText) {
        CHECK(L"ИТВ*У*РЕТЮР*ПВСУДГ" == Crypt("3").encrypt(L"Приветствую, друг!")); 
    }
    TEST(EncryptEmptyText) {
        CHECK_THROW(Crypt("3").encrypt(L""), CryptException);
    }
    TEST(EncryptOnlyDig) {
        CHECK_THROW(Crypt("3").encrypt(L"123123123"), CryptException);
    }
}

SUITE(DecryptTest) {
    TEST(DecBigLet) {
        CHECK(L"ПРИВЕТ" == Crypt("3").decrypt(L"ИТРЕПВ"));
    }
    TEST(DecSmLit) {
        CHECK_THROW(Crypt("3").decrypt(L"рвтпие"), CryptException); 
    }
    TEST(DecAllinTextDig) {
        CHECK_THROW(Crypt("3").decrypt(L"ИТВ*У*РЕТЮР*ПВСУДГ12"), CryptException); 
    }
    TEST(DecryptEmptyText) {
        CHECK_THROW(Crypt("3").decrypt(L""), CryptException);
    }
    TEST(DecryptOnlyDig) {
        CHECK_THROW(Crypt("3").decrypt(L"123123123"), CryptException);
    }
}

int main() {
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    return UnitTest::RunAllTests();
}
