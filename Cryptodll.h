#pragma once

#ifdef CRYPTODLL_EXPORTS
#define CRYPTODLL_API __declspec(dllexport)
#else
#define CRYPTODLL_API __declspec(dllimport)
#endif


std::vector<uint8_t> HexToBinary(const char* hexKey);
const char* Encrypt(const char* fileContent, const uint8_t* key, size_t keyLength);
const char* Decrypt(const char* fileContent, const uint8_t* key, size_t keyLength);

extern "C" {
    // Генерация ключа с автоматическим определением длины
    CRYPTODLL_API const char* GenerateKey(const char* algorithm);
    CRYPTODLL_API void FreeKeyString(const char* str);

    CRYPTODLL_API const char* ProcessFileWithKey(const char* fileContent, const char* userKey, const char* mode);
    
    // Добавляем объявление ConvertToHex
    CRYPTODLL_API const char* ConvertToHex(const char* binaryKey, size_t length);

}