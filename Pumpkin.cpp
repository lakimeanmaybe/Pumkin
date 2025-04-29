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

void Pumpkin::Pumpkin::button3_Click(System::Object^ sender, System::EventArgs^ e) {
    // �������� ��������� ��������
    String^ selectedAlg = AlgCrypt->Text;
    if (String::IsNullOrWhiteSpace(selectedAlg)) {
        UpdateProgress("�������� �������� ��� ��������� �����.");
        return;
    }

    msclr::interop::marshal_context ctx;
    const char* nativeAlg = ctx.marshal_as<const char*>(selectedAlg);

    // ��������� ����� ����� Cryptodll
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
    else if (selectedAlg == "�����") {
        binaryKey = GenerateKey("�����");
    }
    else if (selectedAlg == "����� �� ������� �����") {
        binaryKey = GenerateKey("����� �� ������� �����");
    }
    else {
        UpdateProgress("���������������� ��������.");
        return;
    }

    if (binaryKey == nullptr) {
        UpdateProgress("������ ��� ��������� �����.");
        return;
    }

    textBox3->Text = gcnew String(binaryKey);

    UpdateProgress("���� ������������.");
}

void Pumpkin::Pumpkin::button4_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // ��������: ������ �� ����
        String^ filePath = textBox1->Text;
        if (String::IsNullOrWhiteSpace(filePath)) {
            UpdateProgress("������: ���� �� ������!");
            return;
        }

        // ��������: ������������ �� ����
        String^ key = textBox3->Text;
        if (String::IsNullOrWhiteSpace(key)) {
            UpdateProgress("������: ���� �� ������������!");
            return;
        }

        // ������������ ���� � ���� � std::string
        std::string inputFile = msclr::interop::marshal_as<std::string>(filePath);
        std::string outputFile = inputFile + ((button1->Text == "�����������") ? ".enc" : ".dec");
        std::string hexKey = msclr::interop::marshal_as<std::string>(key);

        // ��������� ����������/�������������
        if (button1->Text == "�����������") {
            UpdateProgress("���������� ����� ��������...");
            EncryptFileAES(inputFile.c_str(), outputFile.c_str(), hexKey.c_str());
            UpdateProgress("���� ������� ����������: " + gcnew String(outputFile.c_str()));
        }
        else {
            UpdateProgress("������������� ����� ��������...");
            DecryptFileAES(inputFile.c_str(), outputFile.c_str(), hexKey.c_str());
            UpdateProgress("���� ������� �����������: " + gcnew String(outputFile.c_str()));
        }

        // ��������� ���� ��������� ����� � textBox1
        textBox1->Text = gcnew String(outputFile.c_str());
    }
    catch (const std::exception& ex) {
        // ������� ��������� �� ������ ����� UpdateProgress
        UpdateProgress("������: " + gcnew String(ex.what()));
    }
}

void Pumpkin::Pumpkin::button5_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // ���������, ���� �� ��������� � textBox1 (���� � ��������������/��������������� �����)
        String^ currentFilePath = textBox1->Text;
        if (String::IsNullOrWhiteSpace(currentFilePath)) {
            UpdateProgress("������: ���� ��� ���������� �� ������.");
            return;
        }

        // ����������� SaveFileDialog
        SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
        saveFileDialog->Title = "��������� ���� ���";
        saveFileDialog->Filter = "��� ����� (*.*)|*.*";
        saveFileDialog->FileName = System::IO::Path::GetFileName(currentFilePath); // ���������� ��� �������� �����

        // ���������� ���������� ����
        if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            // �������� ��������� ������������� ����
            String^ destinationPath = saveFileDialog->FileName;

            // �������� ����
            System::IO::File::Copy(currentFilePath, destinationPath, true);

            UpdateProgress("���� ������� �������: " + destinationPath);
        }
        else {
            UpdateProgress("���������� �������� �������������.");
        }
    }
    catch (System::Exception^ ex) {
        // ������������ ������ � ������� ��������� � textBox2
        UpdateProgress("������: " + ex->Message);
    }
}

// ������� ��� ���������� ���������
void Pumpkin::Pumpkin::UpdateProgress(String^ status) {
    progressBar1->Value = 100; // ������������� �������� �� ��������
    textBox2->Text = status;   // textBox2 ������������ ��� ����������� ������ �������
}