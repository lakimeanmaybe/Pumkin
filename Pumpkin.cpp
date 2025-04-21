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

void Pumpkin::Pumpkin::SaveProcessedFile(const char* data, const std::string& fileSuffix) {
    String^ filePath = textBox1->Text;
    std::string originalPath = msclr::interop::marshal_as<std::string>(filePath);
    std::string newFilePath = originalPath + "." + fileSuffix;

    std::ofstream outputFile(newFilePath, std::ios::binary);
    if (!outputFile) {
        UpdateProgress("������ ��� ���������� �����.");
        return;
    }

    outputFile.write(data, strlen(data));
    outputFile.close();

    UpdateProgress("���� ������� ���: " + gcnew String(newFilePath.c_str()));
}

void Pumpkin::Pumpkin::button4_Click(System::Object^ sender, System::EventArgs^ e) {
    // �������� ���� �� textBox3
    String^ keyHex = textBox3->Text;
    if (String::IsNullOrWhiteSpace(keyHex)) {
        UpdateProgress("������: ���� �� �����.");
        return;
    }

    // �������������� ����� � ������ char*
    IntPtr keyPtr = Marshal::StringToHGlobalAnsi(keyHex);
    const char* userKey = static_cast<const char*>(keyPtr.ToPointer());

    // ������ ���������� �����
    String^ filePath = textBoxFile->Text;
    if (String::IsNullOrWhiteSpace(filePath)) {
        UpdateProgress("������: �������� ����.");
        Marshal::FreeHGlobal(keyPtr);
        return;
    }

    std::ifstream inputFile(msclr::interop::marshal_as<std::string>(filePath), std::ios::binary);
    if (!inputFile) {
        UpdateProgress("������ ��� �������� �����.");
        Marshal::FreeHGlobal(keyPtr);
        return;
    }

    std::string fileData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // ��������� ���������� ��� ����������� � ����������� �� ��������� button1
    const char* processedData = nullptr;
    if (button1->Text == "�����������") {
        processedData = ProcessFileWithKey(fileData.c_str(), userKey, "encrypt");
    }
    else if (button1->Text == "������������") {
        processedData = ProcessFileWithKey(fileData.c_str(), userKey, "decrypt");
    }
    else {
        UpdateProgress("������: �������� ��������� ������.");
        Marshal::FreeHGlobal(keyPtr);
        return;
    }

    Marshal::FreeHGlobal(keyPtr);

    if (!processedData) {
        UpdateProgress("������ ��� ��������� �����.");
        return;
    }

    // ��������� ������������ ������
    SaveProcessedFile(processedData, (button1->Text == "�����������") ? "encrypted" : "decrypted");
    FreeKeyString(processedData);

    UpdateProgress("���� ������� ���������.");
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

void Pumpkin::Pumpkin::button3_Click(System::Object^ sender, System::EventArgs^ e) {
    // �������� ��������� ��������
    String^ selectedAlg = AlgCrypt->Text;
    if (String::IsNullOrWhiteSpace(selectedAlg)) {
        UpdateProgress("�������� �������� ��� ��������� �����.");
        return;
    }

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

    // ��������� �������� ���� � processedContent
    *processedContent = binaryKey;

    // ����������� �������� ���� � hex ����� Cryptodll
    const char* hexKey = ConvertToHex(binaryKey, strlen(binaryKey));
    if (hexKey == nullptr) {
        UpdateProgress("������ ��� �������������� ����� � hex.");
        FreeKeyString(binaryKey);
        return;
    }

    // ���������� ���� � ������� hex
    textBox3->Text = gcnew String(hexKey);

    // ����������� ������, ���������� Cryptodll
    FreeKeyString(binaryKey);
    FreeKeyString(hexKey);

    UpdateProgress("���� ������������.");
}

// ������� ��� ���������� ���������
void Pumpkin::Pumpkin::UpdateProgress(String^ status) {
    progressBar1->Value = 100; // ������������� �������� �� ��������
    textBox2->Text = status;   // textBox2 ������������ ��� ����������� ������ �������
}