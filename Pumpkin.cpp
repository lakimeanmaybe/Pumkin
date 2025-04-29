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

// Функция для обновления прогресса
void Pumpkin::Pumpkin::UpdateProgress(String^ status) {
    progressBar1->Value = 100; // Устанавливаем прогресс на максимум
    textBox2->Text = status;   // textBox2 используется для отображения текста статуса
}