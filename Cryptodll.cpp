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

// Шифрование файла с использованием AES
void EncryptFileAES(const char* inputFile, const char* outputFile, const char* hexKey) {
    // Декодируем ключ из hex-строки
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    StringSource(hexKey, true, new HexDecoder(new ArraySink(key, key.size())));

    // Настраиваем шифрование в режиме CBC
    AutoSeededRandomPool rng;
    byte iv[AES::BLOCKSIZE];
    rng.GenerateBlock(iv, sizeof(iv));

    CBC_Mode<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);

    // Сохраняем IV в начало выходного файла
    FileSink out(outputFile, true);
    out.Put(iv, sizeof(iv)); // Записываем IV

    // Шифруем файл
    FileSource(inputFile, true,
        new StreamTransformationFilter(encryptor,
            new Redirector(out) // Направляем зашифрованный вывод в файл
        )
    );

    std::cout << "Файл успешно зашифрован: " << outputFile << std::endl;
}

// Расшифрование файла с использованием AES
void DecryptFileAES(const char* inputFile, const char* outputFile, const char* hexKey) {
    try {
        // Декодируем ключ из hex-строки
        SecByteBlock key(AES::DEFAULT_KEYLENGTH);
        StringSource(hexKey, true, new HexDecoder(new ArraySink(key, key.size())));

        // Настраиваем расшифрование в режиме CBC
        byte iv[AES::BLOCKSIZE];

        // Открываем входной файл
        FileSource inFile(inputFile, false);

        // Читаем IV из первых 16 байт файла
        inFile.Pump(sizeof(iv));
        inFile.Get(iv, sizeof(iv));

        CBC_Mode<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(key, key.size(), iv);

        // Расшифровываем оставшуюся часть файла
        FileSource(inputFile, true,
            new StreamTransformationFilter(decryptor,
                new FileSink(outputFile)
            ),
            true // Пропускаем первые 16 байт (где хранится IV)
        );

        std::cout << "Файл успешно расшифрован: " << outputFile << std::endl;

        // Отладочный вывод: Содержимое расшифрованного файла
        std::ifstream resultFile(outputFile, std::ios::binary);
        char buffer[256] = { 0 };
        resultFile.read(buffer, 256); // Читаем первые байты расшифрованного файла
        resultFile.close();

        std::cout << "Первые байты расшифрованного файла: " << buffer << std::endl;

    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "Ошибка криптографии: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

// Генерация AES-ключа
std::string GenerateAESKey(int keySize) {
    AutoSeededRandomPool rng;
    SecByteBlock key(keySize / 8);
    rng.GenerateBlock(key, key.size());

    std::string hexKey;
    HexEncoder encoder(new StringSink(hexKey));
    encoder.Put(key, key.size());
    encoder.MessageEnd();
    
    std::cout << "AES key length: " << hexKey.size() << std::endl; // Должно быть 128
	std::cout << "AES key: " << hexKey << std::endl; // Выводим ключ в шестнадцатеричном формате
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

	std::cout << "GOST key length: " << hexKey.size() << std::endl; // Должно быть 256 бит
	std::cout << "GOST key: " << hexKey << std::endl; // Выводим ключ в шестнадцатеричном формате
    return hexKey;
}

// Генерация ключа Магмы на тройном ключе (ГОСТ 34.12-2015)
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
	std::cout << "Triple GOST key: " << hexKey << std::endl; // Выводим ключ в шестнадцатеричном формате
    return hexKey;
}

// Главная функция генерации
CRYPTODLL_API const char* GenerateKey(const char* algorithm) {
    if (!algorithm) {
        return _strdup("Invalid input: algorithm is null");
    }

    std::string algo(algorithm);
    std::string result;

    try {
        if (algo == "AES-128" || algo == "AES-192" || algo == "AES-256") {
            int keySize = (algo == "AES-128") ? 128 : (algo == "AES-192") ? 192 : 256;
            result = GenerateAESKey(keySize);
        }
        else if (algo == "Магма на тройном ключе") {
            result = GenerateTripleGOSTKey();
        }
        else if (algo.find("Магма") != std::string::npos) {
            result = GenerateGOSTKey();
        }
        else {
            result = "Unsupported Algorithm";
        }
    }
    catch (const std::exception& e) {
        result = std::string("Error: ") + e.what();
    }

    return _strdup(result.c_str());
}

/*
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    GenerateAESKey(128);
	GenerateGOSTKey();
    GenerateTripleGOSTKey();
    return 0;
}
*/