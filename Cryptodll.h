#pragma once

#ifdef CRYPTODLL_EXPORTS
#define CRYPTODLL_API __declspec(dllexport)
#else
#define CRYPTODLL_API __declspec(dllimport)
#endif

extern "C" {
    // Генерация ключа с автоматическим определением длины
    CRYPTODLL_API const char* GenerateKey(const char* algorithm);

    // Шифрование файла
    CRYPTODLL_API void EncryptFileAES(const char* inputFile, const char* outputFile, const char* hexKey);

    // Расшифрование файла
    CRYPTODLL_API void DecryptFileAES(const char* inputFile, const char* outputFile, const char* hexKey);
}