#pragma once

#ifdef CRYPTODLL_EXPORTS
#define CRYPTODLL_API __declspec(dllexport)
#else
#define CRYPTODLL_API __declspec(dllimport)
#endif

extern "C" {
    // Генерация ключа с автоматическим определением длины
    CRYPTODLL_API const char* GenerateKey(const char* algorithm);
    CRYPTODLL_API void FreeKeyString(const char* str);

    CRYPTODLL_API const char* ProcessFileWithKey(const char* fileContent, const char* userKey, const char* mode);
}