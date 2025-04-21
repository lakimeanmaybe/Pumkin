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

// Обработчик кнопки "Выполнить" (button4_Click)
void Pumpkin::Pumpkin::button4_Click(System::Object^ sender, System::EventArgs^ e) {

    // Проверяем, есть ли файл в textBox1
    String^ filePath = textBox1->Text;
    if (String::IsNullOrWhiteSpace(filePath)) {
        UpdateProgress("Пожалуйста, добавьте файл через Drag&Drop.");
        return;
    }

    // Проверяем, есть ли ключ в textBox3
    String^ keyText = textBox3->Text;
    if (String::IsNullOrWhiteSpace(keyText)) {
        UpdateProgress("Сначала сгенерируйте ключ, нажав кнопку 'Сгенерировать ключ'.");
        return;
    }

    // Преобразуем путь файла и ключ в std::string
    msclr::interop::marshal_context ctx;
    std::string nativeFilePath = ctx.marshal_as<std::string>(filePath);
    std::string nativeKey = ctx.marshal_as<std::string>(keyText);

    // Читаем содержимое файла
    std::ifstream inputFile(nativeFilePath, std::ios::binary);
    if (!inputFile.is_open()) {
        UpdateProgress("Не удалось открыть файл.");
        return;
    }

    std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // Определяем режим (шифрование или расшифрование)
    String^ button1Text = button1->Text;
    std::string mode = (button1Text == "Зашифровать") ? "encrypt" : "decrypt";

    // Обработка файла с использованием ключа
    const char* result = ProcessFileWithKey(fileContent.c_str(), nativeKey.c_str(), mode.c_str());
    if (result == nullptr) {
        UpdateProgress("Ошибка при обработке файла.");
        return;
    }

    // Сохраняем результат в указатель processedContent
    *processedContent = result; // Используем указатель
    FreeKeyString(result);

    UpdateProgress(mode == "encrypt" ? "Файл зашифрован." : "Файл расшифрован.");
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

// Обработчик кнопки "Сгенерировать ключ" (button3_Click)
void Pumpkin::Pumpkin::button3_Click(System::Object^ sender, System::EventArgs^ e) {
    // Получаем выбранный тип алгоритма из ComboBox (AlgCrypt)
    String^ selectedAlg = AlgCrypt->Text;
    if (String::IsNullOrWhiteSpace(selectedAlg)) {
        UpdateProgress("Выберите алгоритм для генерации ключа.");
        return;
    }

    // Преобразуем .NET строку в std::string
    msclr::interop::marshal_context ctx;
    const char* nativeAlg = ctx.marshal_as<const char*>(selectedAlg);

    // Генерируем ключ
    const char* key = GenerateKey(nativeAlg);
    if (key == nullptr) {
        UpdateProgress("Ошибка при генерации ключа.");
        return;
    }

    // Отображаем ключ в textBox3
    textBox3->Text = gcnew String(key);

    // Освобождаем память
    FreeKeyString(key);
    UpdateProgress("Ключ сгенерирован.");
}

// Функция для обновления прогресса
void Pumpkin::Pumpkin::UpdateProgress(String^ status) {
    progressBar1->Value = 100; // Устанавливаем прогресс на максимум
    textBox2->Text = status;   // textBox2 используется для отображения текста статуса
}