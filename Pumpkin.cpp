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

// ������� ��� ���������� ���������
void Pumpkin::Pumpkin::UpdateProgress(String^ status) {
    progressBar1->Value = 100; // ������������� �������� �� ��������
    textBox2->Text = status;   // textBox2 ������������ ��� ����������� ������ �������
}