#include "pch.h"
#include "Cryptodll.h"
#include <aes.h>
#include <gost.h> // Для Магмы
#include <osrng.h>
#include <hex.h>
#include <modes.h>
#include <files.h>
#include <string>
#include <iomanip>

using namespace CryptoPP;

// Преобразование бинарного ключа в hex
CRYPTODLL_API const char* ConvertToHex(const char* binaryKey, size_t length) {
    if (!binaryKey || length == 0) {
        return _strdup(""); // Возвращаем пустую строку, если входные данные некорректны
    }

    std::ostringstream oss; // Поток для формирования строки
    for (size_t i = 0; i < length; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (static_cast<unsigned int>(static_cast<unsigned char>(binaryKey[i])));
    }

    return _strdup(oss.str().c_str()); // Возвращаем строку в формате hex
}

std::vector<uint8_t> HexToBinary(const char* hexKey) {
    std::vector<uint8_t> binaryKey;
    size_t len = strlen(hexKey);
    for (size_t i = 0; i < len; i += 2) {
        std::string byteString(hexKey + i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16));
        binaryKey.push_back(byte);
    }
    return binaryKey;
}

/*
void TestConvertToHex() {
    const char binaryKey[] = { 0xDE, 0xAD, 0xBE, 0xEF }; // Пример бинарного ключа
    const char* hexKey = ConvertToHex(binaryKey, sizeof(binaryKey));
    if (hexKey != nullptr) {
        std::cout << "Hex Key: " << hexKey << std::endl;
        FreeKeyString(hexKey); // Освобождаем память
    }
    else {
        std::cout << "Error: ConvertToHex returned nullptr" << std::endl;
    }
}
*/

// Функция для шифрования/расшифрования файла с использованием пользовательского ключа
CRYPTODLL_API const char* ProcessFileWithKey(const char* fileContent, const char* userKey, const char* mode) {
    try {
        // Преобразование ключа из hex в бинарный формат
        std::vector<uint8_t> binaryKey = HexToBinary(userKey);

        if (strcmp(mode, "encrypt") == 0) {
            return Encrypt(fileContent, binaryKey.data(), binaryKey.size());
        }
        else if (strcmp(mode, "decrypt") == 0) {
            return Decrypt(fileContent, binaryKey.data(), binaryKey.size());
        }
        else {
            throw std::invalid_argument("Invalid mode");
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error in ProcessFileWithKey: " << ex.what() << std::endl;
        return nullptr;
    }
}

// Обновленная версия функции GenerateAESKey возвращает бинарный ключ
std::string GenerateAESKey(int keySize) {
    AutoSeededRandomPool rng;
    SecByteBlock key(keySize / 8); // Генерация ключа нужной длины
    rng.GenerateBlock(key, key.size());

    // Возвращаем бинарный ключ как строку
    return std::string(reinterpret_cast<const char*>(key.data()), key.size());
}

// Генерация ключа Магмы (ГОСТ 34.12-2015)
std::string GenerateGOSTKey() {
    AutoSeededRandomPool rng;
    SecByteBlock key(32); // 256 бит
    rng.GenerateBlock(key, key.size());

    std::string hexKey;
    HexEncoder encoder(new StringSink(hexKey));
    encoder.Put(key, key.size());
    encoder.MessageEnd();

    return std::string(reinterpret_cast<const char*>(key.data()), key.size());
}

std::string GenerateTripleGOSTKey() {
    // Генерация 3 ключей по 256 бит
    AutoSeededRandomPool rng;
    SecByteBlock key(96); // 3×256 бит = 768 бит
    rng.GenerateBlock(key, key.size());

    std::string hexKey;
    HexEncoder encoder(new StringSink(hexKey));
    encoder.Put(key, key.size());
    encoder.MessageEnd();

    //std::cout << "Triple GOST key length: " << hexKey.size() << std::endl; // Должно быть 192
    return std::string(reinterpret_cast<const char*>(key.data()), key.size());
}

// Главная функция генерации
CRYPTODLL_API const char* GenerateKey(const char* algorithm) {
    std::string algo(algorithm);
    std::string result;

    if (algo.find("AES-128") != std::string::npos) {
        int keySize = 128;
        if (algo == "AES-192") keySize = 192;
        else if (algo == "AES-256") keySize = 256;
        result = GenerateAESKey(keySize);
    }
    else if (algo.find("Магма") != std::string::npos) {
        result = GenerateGOSTKey();
    }
    else if (algo == "Магма на тройном ключе"){
        result = GenerateTripleGOSTKey();
    }
    else {
        result = "Unsupported Algorithm";
    }

    return _strdup(result.c_str());
}

CRYPTODLL_API void FreeKeyString(const char* str) {
    free(const_cast<char*>(str));
}

/*
int main(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd) {
    std::cout << "Running TestConvertToHex..." << std::endl;
    TestConvertToHex();
    return 0;
}
*/