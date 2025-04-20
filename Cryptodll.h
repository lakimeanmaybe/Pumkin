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
}