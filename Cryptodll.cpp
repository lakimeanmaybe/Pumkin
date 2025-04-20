#include "pch.h"
#include "Cryptodll.h"
#include <aes.h>
#include <gost.h> // Для Магмы
#include <osrng.h>
#include <hex.h>
#include <modes.h>
#include <files.h>
#include <string>

using namespace CryptoPP;

// Генерация AES-ключа
std::string GenerateAESKey(int keySize) {
    AutoSeededRandomPool rng;
    SecByteBlock key(keySize / 8);
    rng.GenerateBlock(key, key.size());

    std::string hexKey;
    HexEncoder encoder(new StringSink(hexKey));
    encoder.Put(key, key.size());
    encoder.MessageEnd();

    return hexKey;
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

    return hexKey;
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

    std::cout << "Triple GOST key length: " << hexKey.size() << std::endl; // Должно быть 192
    return hexKey;
}

// Главная функция генерации
CRYPTODLL_API const char* GenerateKey(const char* algorithm) {
    std::string algo(algorithm);
    std::string result;

    if (algo.find("AES") != std::string::npos) {
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