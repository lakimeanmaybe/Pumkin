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
    Pumpkin::Pumpkin form; // ����� ���������� �����������
    Application::Run(% form);
}

// ���������� ������ "���������" (button4_Click)
void Pumpkin::Pumpkin::button4_Click(System::Object^ sender, System::EventArgs^ e) {

    // ���������, ���� �� ���� � textBox1
    String^ filePath = textBox1->Text;
    if (String::IsNullOrWhiteSpace(filePath)) {
        UpdateProgress("����������, �������� ���� ����� Drag&Drop.");
        return;
    }

    // ���������, ���� �� ���� � textBox3
    String^ keyText = textBox3->Text;
    if (String::IsNullOrWhiteSpace(keyText)) {
        UpdateProgress("������� ������������ ����, ����� ������ '������������� ����'.");
        return;
    }

    // ����������� ���� ����� � ���� � std::string
    msclr::interop::marshal_context ctx;
    std::string nativeFilePath = ctx.marshal_as<std::string>(filePath);
    std::string nativeKey = ctx.marshal_as<std::string>(keyText);

    // ������ ���������� �����
    std::ifstream inputFile(nativeFilePath, std::ios::binary);
    if (!inputFile.is_open()) {
        UpdateProgress("�� ������� ������� ����.");
        return;
    }

    std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // ���������� ����� (���������� ��� �������������)
    String^ button1Text = button1->Text;
    std::string mode = (button1Text == "�����������") ? "encrypt" : "decrypt";

    // ��������� ����� � �������������� �����
    const char* result = ProcessFileWithKey(fileContent.c_str(), nativeKey.c_str(), mode.c_str());
    if (result == nullptr) {
        UpdateProgress("������ ��� ��������� �����.");
        return;
    }

    // ��������� ��������� � ��������� processedContent
    *processedContent = result; // ���������� ���������
    FreeKeyString(result);

    UpdateProgress(mode == "encrypt" ? "���� ����������." : "���� �����������.");
}

// ���������� ������ "��������� ���" (button5_Click)
void Pumpkin::Pumpkin::button5_Click(System::Object^ sender, System::EventArgs^ e) {
    // ���������, ���� �� ������ ��� ����������
    if (processedContent->empty()) {
        UpdateProgress("��� ������ ��� ����������. ��������� ���������� ��� �������������.");
        return;
    }

    // ��������� ������ ���������� �����
    SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
    saveFileDialog->Filter = "��� ����� (*.*)|*.*";
    if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        String^ savePath = saveFileDialog->FileName;
        msclr::interop::marshal_context ctx;
        std::string nativeSavePath = ctx.marshal_as<std::string>(savePath);

        // ��������� ������ � ����
        std::ofstream outputFile(nativeSavePath, std::ios::binary);
        if (!outputFile.is_open()) {
            UpdateProgress("�� ������� ��������� ����.");
            return;
        }

        outputFile.write(processedContent->data(), processedContent->size());
        outputFile.close();

        UpdateProgress("���� ��������.");
    }
}

// ���������� ������ "������������� ����" (button3_Click)
void Pumpkin::Pumpkin::button3_Click(System::Object^ sender, System::EventArgs^ e) {
    // �������� ��������� ��� ��������� �� ComboBox (AlgCrypt)
    String^ selectedAlg = AlgCrypt->Text;
    if (String::IsNullOrWhiteSpace(selectedAlg)) {
        UpdateProgress("�������� �������� ��� ��������� �����.");
        return;
    }

    // ����������� .NET ������ � std::string
    msclr::interop::marshal_context ctx;
    const char* nativeAlg = ctx.marshal_as<const char*>(selectedAlg);

    // ���������� ����
    const char* key = GenerateKey(nativeAlg);
    if (key == nullptr) {
        UpdateProgress("������ ��� ��������� �����.");
        return;
    }

    // ���������� ���� � textBox3
    textBox3->Text = gcnew String(key);

    // ����������� ������
    FreeKeyString(key);
    UpdateProgress("���� ������������.");
}

// ������� ��� ���������� ���������
void Pumpkin::Pumpkin::UpdateProgress(String^ status) {
    progressBar1->Value = 100; // ������������� �������� �� ��������
    textBox2->Text = status;   // textBox2 ������������ ��� ����������� ������ �������
}