#include "Pumpkin.h"
#include <msclr/marshal_cppstd.h>
#include "Cryptodll.h"
#include <iostream>
#include <fstream>

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main(array<String^>^ args)
{
    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();
    Pumpkin::Pumpkin form; // Здесь вызывается конструктор
    Application::Run(% form);
}

void Pumpkin::Pumpkin::SaveProcessedFile(const char* data, const std::string& fileSuffix) {
    String^ filePath = textBox1->Text;
    std::string originalPath = msclr::interop::marshal_as<std::string>(filePath);
    std::string newFilePath = originalPath + "." + fileSuffix;

    std::ofstream outputFile(newFilePath, std::ios::binary);
    if (!outputFile) {
        UpdateProgress("Ошибка при сохранении файла.");
        return;
    }

    outputFile.write(data, strlen(data));
    outputFile.close();

    UpdateProgress("Файл сохранён как: " + gcnew String(newFilePath.c_str()));
}

void Pumpkin::Pumpkin::button4_Click(System::Object^ sender, System::EventArgs^ e) {
    // Получаем ключ из textBox3
    String^ keyHex = textBox3->Text;
    if (String::IsNullOrWhiteSpace(keyHex)) {
        UpdateProgress("Ошибка: Ключ не задан.");
        return;
    }

    // Преобразование ключа в формат char*
    IntPtr keyPtr = Marshal::StringToHGlobalAnsi(keyHex);
    const char* userKey = static_cast<const char*>(keyPtr.ToPointer());

    // Читаем содержимое файла
    String^ filePath = textBoxFile->Text;
    if (String::IsNullOrWhiteSpace(filePath)) {
        UpdateProgress("Ошибка: Выберите файл.");
        Marshal::FreeHGlobal(keyPtr);
        return;
    }

    std::ifstream inputFile(msclr::interop::marshal_as<std::string>(filePath), std::ios::binary);
    if (!inputFile) {
        UpdateProgress("Ошибка при открытии файла.");
        Marshal::FreeHGlobal(keyPtr);
        return;
    }

    std::string fileData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // Выполняем шифрование или расшифровку в зависимости от состояния button1
    const char* processedData = nullptr;
    if (button1->Text == "Зашифровать") {
        processedData = ProcessFileWithKey(fileData.c_str(), userKey, "encrypt");
    }
    else if (button1->Text == "Расшифровать") {
        processedData = ProcessFileWithKey(fileData.c_str(), userKey, "decrypt");
    }
    else {
        UpdateProgress("Ошибка: Неверное состояние кнопки.");
        Marshal::FreeHGlobal(keyPtr);
        return;
    }

    Marshal::FreeHGlobal(keyPtr);

    if (!processedData) {
        UpdateProgress("Ошибка при обработке файла.");
        return;
    }

    // Сохраняем обработанные данные
    SaveProcessedFile(processedData, (button1->Text == "Зашифровать") ? "encrypted" : "decrypted");
    FreeKeyString(processedData);

    UpdateProgress("Файл успешно обработан.");
}

// Обработчик кнопки "Сохранить как" (button5_Click)
void Pumpkin::Pumpkin::button5_Click(System::Object^ sender, System::EventArgs^ e) {
    // Проверяем, есть ли данные для сохранения
    if (processedContent->empty()) {
        UpdateProgress("Нет данных для сохранения. Выполните шифрование или расшифрование.");
        return;
    }

    // Открываем диалог сохранения файла
    SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
    saveFileDialog->Filter = "Все файлы (*.*)|*.*";
    if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        String^ savePath = saveFileDialog->FileName;
        msclr::interop::marshal_context ctx;
        std::string nativeSavePath = ctx.marshal_as<std::string>(savePath);

        // Сохраняем данные в файл
        std::ofstream outputFile(nativeSavePath, std::ios::binary);
        if (!outputFile.is_open()) {
            UpdateProgress("Не удалось сохранить файл.");
            return;
        }

        outputFile.write(processedContent->data(), processedContent->size());
        outputFile.close();

        UpdateProgress("Файл сохранен.");
    }
}

void Pumpkin::Pumpkin::button3_Click(System::Object^ sender, System::EventArgs^ e) {
    // Получаем выбранный алгоритм
    String^ selectedAlg = AlgCrypt->Text;
    if (String::IsNullOrWhiteSpace(selectedAlg)) {
        UpdateProgress("Выберите алгоритм для генерации ключа.");
        return;
    }

    // Генерация ключа через Cryptodll
    const char* binaryKey = nullptr;
    if (selectedAlg == "AES-128") {
        binaryKey = GenerateKey("AES-128");
    }
    else if (selectedAlg == "AES-192") {
        binaryKey = GenerateKey("AES-192");
    }
    else if (selectedAlg == "AES-256") {
        binaryKey = GenerateKey("AES-256");
    }
    else if (selectedAlg == "Магма") {
        binaryKey = GenerateKey("Магма");
    }
    else if (selectedAlg == "Магма на тройном ключе") {
        binaryKey = GenerateKey("Магма на тройном ключе");
    }
    else {
        UpdateProgress("Неподдерживаемый алгоритм.");
        return;
    }

    if (binaryKey == nullptr) {
        UpdateProgress("Ошибка при генерации ключа.");
        return;
    }

    // Сохраняем бинарный ключ в processedContent
    *processedContent = binaryKey;

    // Преобразуем бинарный ключ в hex через Cryptodll
    const char* hexKey = ConvertToHex(binaryKey, strlen(binaryKey));
    if (hexKey == nullptr) {
        UpdateProgress("Ошибка при преобразовании ключа в hex.");
        FreeKeyString(binaryKey);
        return;
    }

    // Отображаем ключ в формате hex
    textBox3->Text = gcnew String(hexKey);

    // Освобождаем память, выделенную Cryptodll
    FreeKeyString(binaryKey);
    FreeKeyString(hexKey);

    UpdateProgress("Ключ сгенерирован.");
}

// Функция для обновления прогресса
void Pumpkin::Pumpkin::UpdateProgress(String^ status) {
    progressBar1->Value = 100; // Устанавливаем прогресс на максимум
    textBox2->Text = status;   // textBox2 используется для отображения текста статуса
}