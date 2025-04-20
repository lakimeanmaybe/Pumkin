#pragma once

#include <msclr/marshal_cppstd.h>
#include "Cryptodll.h"
#include <fstream>

namespace Pumpkin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Pumpkin
	/// </summary>
	public ref class Pumpkin : public System::Windows::Forms::Form
	{
	public:
		Pumpkin(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Pumpkin()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ComboBox^ AlgCrypt;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;




	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Pumpkin::typeid));
			this->AlgCrypt = (gcnew System::Windows::Forms::ComboBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// AlgCrypt
			// 
			this->AlgCrypt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->AlgCrypt->BackColor = System::Drawing::Color::DarkGray;
			this->AlgCrypt->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->AlgCrypt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->AlgCrypt->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.875F));
			this->AlgCrypt->FormattingEnabled = true;
			this->AlgCrypt->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"AES-128", L"AES-192", L"AES-256", L"Магма", L"Магма на тройном ключе" });
			this->AlgCrypt->Location = System::Drawing::Point(3, 3);
			this->AlgCrypt->Margin = System::Windows::Forms::Padding(3, 3, 10, 3);
			this->AlgCrypt->Name = L"AlgCrypt";
			this->AlgCrypt->Size = System::Drawing::Size(587, 37);
			this->AlgCrypt->TabIndex = 0;
			this->AlgCrypt->Text = L"Выберете алгоритм шифрования...";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// textBox1
			// 
			this->textBox1->AllowDrop = true;
			this->textBox1->BackColor = System::Drawing::Color::DarkGray;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204), true));
			this->textBox1->ForeColor = System::Drawing::Color::DimGray;
			this->textBox1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->textBox1->Location = System::Drawing::Point(5, 76);
			this->textBox1->Margin = System::Windows::Forms::Padding(5, 5, 10, 0);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(585, 216);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"\r\n\r\n\r\nПеретащите файл";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Pumpkin::textBox1_DragDrop);
			this->textBox1->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Pumpkin::textBox1_DragEnter);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::LimeGreen;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox2->Location = System::Drawing::Point(610, 75);
			this->textBox2->Margin = System::Windows::Forms::Padding(10, 5, 5, 0);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(585, 217);
			this->textBox2->TabIndex = 2;
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button1->AutoSize = true;
			this->button1->BackColor = System::Drawing::Color::DarkGray;
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::DarkGray;
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightGray;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(610, 3);
			this->button1->Margin = System::Windows::Forms::Padding(10, 3, 3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(587, 64);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Зашифровать";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Pumpkin::button1_Click);
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::Black;
			this->textBox3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox3->ForeColor = System::Drawing::Color::White;
			this->textBox3->Location = System::Drawing::Point(3, 3);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(1194, 200);
			this->textBox3->TabIndex = 3;
			// 
			// button2
			// 
			this->button2->AutoSize = true;
			this->button2->BackColor = System::Drawing::Color::DarkGray;
			this->button2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button2->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
			this->button2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightGray;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(5, 292);
			this->button2->Margin = System::Windows::Forms::Padding(5, 0, 10, 5);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(585, 87);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Выберете файл";
			this->button2->UseVisualStyleBackColor = false;
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::DarkGray;
			this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button3->FlatAppearance->BorderColor = System::Drawing::Color::DarkGray;
			this->button3->FlatAppearance->BorderSize = 3;
			this->button3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightGray;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->ForeColor = System::Drawing::Color::Black;
			this->button3->Location = System::Drawing::Point(3, 3);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(291, 58);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Сгенерировать ключ";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Pumpkin::button3_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::DarkGray;
			this->button4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button4->Dock = System::Windows::Forms::DockStyle::Top;
			this->button4->FlatAppearance->BorderColor = System::Drawing::Color::DarkGray;
			this->button4->FlatAppearance->BorderSize = 3;
			this->button4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightGray;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Location = System::Drawing::Point(603, 387);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(594, 54);
			this->button4->TabIndex = 6;
			this->button4->Text = L"Выполнить";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &Pumpkin::button4_Click);
			// 
			// button5
			// 
			this->button5->AutoSize = true;
			this->button5->BackColor = System::Drawing::Color::LimeGreen;
			this->button5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button5->FlatAppearance->BorderColor = System::Drawing::Color::ForestGreen;
			this->button5->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Lime;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Location = System::Drawing::Point(610, 292);
			this->button5->Margin = System::Windows::Forms::Padding(10, 0, 5, 5);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(585, 87);
			this->button5->TabIndex = 7;
			this->button5->Text = L"Сохранить как";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &Pumpkin::button5_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->BackColor = System::Drawing::Color::DarkGray;
			this->comboBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->comboBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->ForeColor = System::Drawing::Color::Black;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"Режим простой замены.", L"Режим гаммирования.",
					L"Режим гаммирования с обратной связью.", L"Режим выработки имитовставки.", L"ECB", L"CBC", L"CTR"
			});
			this->comboBox1->Location = System::Drawing::Point(300, 3);
			this->comboBox1->MinimumSize = System::Drawing::Size(280, 0);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(291, 45);
			this->comboBox1->TabIndex = 8;
			this->comboBox1->Text = L"Режим простой замены.";
			// 
			// progressBar1
			// 
			this->progressBar1->BackColor = System::Drawing::Color::White;
			this->progressBar1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->progressBar1->ForeColor = System::Drawing::Color::IndianRed;
			this->progressBar1->Location = System::Drawing::Point(3, 209);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(1194, 35);
			this->progressBar1->TabIndex = 9;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->AutoSize = true;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->textBox1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel3, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->textBox2, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->button5, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->button2, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->AlgCrypt, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->button1, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->button4, 1, 3);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 4;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 70)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 222)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 92)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 70)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1200, 454);
			this->tableLayoutPanel1->TabIndex = 10;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->AutoSize = true;
			this->tableLayoutPanel3->ColumnCount = 2;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->Controls->Add(this->button3, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->comboBox1, 1, 0);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(3, 387);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 1;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(594, 64);
			this->tableLayoutPanel3->TabIndex = 13;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel2->AutoSize = true;
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel2->Controls->Add(this->progressBar1, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->textBox3, 0, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(0, 482);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 83.58209F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.41791F)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(1200, 247);
			this->tableLayoutPanel2->TabIndex = 12;
			// 
			// Pumpkin
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DimGray;
			this->ClientSize = System::Drawing::Size(1200, 729);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(1200, 800);
			this->Name = L"Pumpkin";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Pumpkin";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Pumpkin_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	
		   // Обновление статуса в progressBar1
	private: System::Void UpdateProgress(String^ status) {
		progressBar1->Value = 100; // Устанавливаем прогресс на максимум (или можно сделать динамическим)
		textBox2->Text = status;   // textBox2 используется для отображения текста статуса
}

	private: System::Void Pumpkin::button1_Click(System::Object^ sender, System::EventArgs^ e) {
		// Переключаем текст кнопки
		if (button1->Text == "Зашифровать") {
			button1->Text = "Расшифровать";  // Меняем текст на "Расшифровать"
		}
		else {
			button1->Text = "Зашифровать";  // Меняем текст обратно на "Зашифровать"
		}

	}
		// Обработчик события DragEnter
	private: System::Void textBox1_DragEnter(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
			e->Effect = DragDropEffects::Copy; // Разрешить перетаскивание файлов
		}
		else {
			e->Effect = DragDropEffects::None;
		}
	}

		   // Обработчик события DragDrop
	private: System::Void textBox1_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
		array<String^>^ files = (array<String^>^)e->Data->GetData(DataFormats::FileDrop);
		if (files->Length > 0) {
			textBox1->Text = files[0]; // Отобразить путь к файлу в текстовом поле
		}
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		// Получаем выбранный тип алгоритма из ComboBox (AlgCrypt)
		String^ selectedAlg = AlgCrypt->Text;
		if (String::IsNullOrWhiteSpace(selectedAlg)) {
			MessageBox::Show("Выберите алгоритм для генерации ключа.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Преобразуем .NET строку в std::string
		msclr::interop::marshal_context ctx;
		const char* nativeAlg = ctx.marshal_as<const char*>(selectedAlg);

		// Генерируем ключ
		const char* key = GenerateKey(nativeAlg);
		if (key == nullptr) {
			MessageBox::Show("Ошибка при генерации ключа.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Отображаем ключ в textBox3
		textBox3->Text = gcnew String(key);

		// Освобождаем память
		FreeKeyString(key);
	}


	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
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

		// Сохраняем результат в файл
		processedContent = std::string(result); // Сохраняем результат для дальнейшего сохранения через button5_Click
		FreeKeyString(result);

		UpdateProgress(mode == "encrypt" ? "Файл зашифрован." : "Файл расшифрован.");
	}

	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		// Проверяем, есть ли данные для сохранения
		if (processedContent.empty()) {
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

			outputFile.write(processedContent.data(), processedContent.size());
			outputFile.close();

			UpdateProgress("Файл сохранен.");
		}
	}
	

};
}