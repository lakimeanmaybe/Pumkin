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

void Pumpkin::Pumpkin::button3_Click(System::Object^ sender, System::EventArgs^ e) {
    // Получаем выбранный алгоритм
    String^ selectedAlg = AlgCrypt->Text;
    if (String::IsNullOrWhiteSpace(selectedAlg)) {
        UpdateProgress("Выберите алгоритм для генерации ключа.");
        return;
    }

    msclr::interop::marshal_context ctx;
    const char* nativeAlg = ctx.marshal_as<const char*>(selectedAlg);

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

    textBox3->Text = gcnew String(binaryKey);

    UpdateProgress("Ключ сгенерирован.");
}

void Pumpkin::Pumpkin::button4_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Проверка: выбран ли файл
        String^ filePath = textBox1->Text;
        if (String::IsNullOrWhiteSpace(filePath)) {
            UpdateProgress("Ошибка: файл не выбран!");
            return;
        }

        // Проверка: сгенерирован ли ключ
        String^ key = textBox3->Text;
        if (String::IsNullOrWhiteSpace(key)) {
            UpdateProgress("Ошибка: ключ не сгенерирован!");
            return;
        }

        // Конвертируем пути и ключ в std::string
        std::string inputFile = msclr::interop::marshal_as<std::string>(filePath);
        std::string outputFile = inputFile + ((button1->Text == "Зашифровать") ? ".enc" : ".dec");
        std::string hexKey = msclr::interop::marshal_as<std::string>(key);

        // Выполняем шифрование/расшифрование
        if (button1->Text == "Зашифровать") {
            UpdateProgress("Шифрование файла началось...");
            EncryptFileAES(inputFile.c_str(), outputFile.c_str(), hexKey.c_str());
            UpdateProgress("Файл успешно зашифрован: " + gcnew String(outputFile.c_str()));
        }
        else {
            UpdateProgress("Расшифрование файла началось...");
            DecryptFileAES(inputFile.c_str(), outputFile.c_str(), hexKey.c_str());
            UpdateProgress("Файл успешно расшифрован: " + gcnew String(outputFile.c_str()));
        }

        // Сохраняем путь выходного файла в textBox1
        textBox1->Text = gcnew String(outputFile.c_str());
    }
    catch (const std::exception& ex) {
        // Выводим сообщение об ошибке через UpdateProgress
        UpdateProgress("Ошибка: " + gcnew String(ex.what()));
    }
}

void Pumpkin::Pumpkin::button5_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Проверяем, есть ли результат в textBox1 (путь к зашифрованному/расшифрованному файлу)
        String^ currentFilePath = textBox1->Text;
        if (String::IsNullOrWhiteSpace(currentFilePath)) {
            UpdateProgress("Ошибка: файл для сохранения не найден.");
            return;
        }

        // Настраиваем SaveFileDialog
        SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
        saveFileDialog->Title = "Сохранить файл как";
        saveFileDialog->Filter = "Все файлы (*.*)|*.*";
        saveFileDialog->FileName = System::IO::Path::GetFileName(currentFilePath); // Предлагаем имя текущего файла

        // Показываем диалоговое окно
        if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            // Получаем выбранный пользователем путь
            String^ destinationPath = saveFileDialog->FileName;

            // Копируем файл
            System::IO::File::Copy(currentFilePath, destinationPath, true);

            UpdateProgress("Файл успешно сохранён: " + destinationPath);
        }
        else {
            UpdateProgress("Сохранение отменено пользователем.");
        }
    }
    catch (System::Exception^ ex) {
        // Обрабатываем ошибки и выводим сообщение в textBox2
        UpdateProgress("Ошибка: " + ex->Message);
    }
}

// Функция для обновления прогресса
void Pumpkin::Pumpkin::UpdateProgress(String^ status) {
    progressBar1->Value = 100; // Устанавливаем прогресс на максимум
    textBox2->Text = status;   // textBox2 используется для отображения текста статуса
}