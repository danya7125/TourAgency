#pragma once
#include "Client.h"
#include <msclr/marshal_cppstd.h>
using namespace msclr::interop;
namespace TourAgency {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для ClientForm
	/// </summary>
	public ref class ClientForm : public System::Windows::Forms::Form
	{
	public:
		ClientForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		ClientForm(const Client& client)
		{
			InitializeComponent();
			isEditMode = true;
			editingClientId = client.getId();
			buttonClient->Text = L"Сохранить";
			this->Text = L"Редактирование клиента";

			textBoxF->Text = gcnew String(client.getInfo().first_name.c_str());
			textBoxI->Text = gcnew String(client.getInfo().last_name.c_str());
			textBoxO->Text = gcnew String(client.getInfo().patronymic.c_str());
			comboBoxGender->SelectedItem = gcnew String(client.getInfo().gender.c_str());

			String^ dateStr = gcnew String(client.getInfo().birth_date.c_str());
			try {
				dateTimePickerBirthDate->Value = DateTime::ParseExact(dateStr, "dd.MM.yyyy", nullptr);
			}
			catch (...) {}

			textBoxAdress->Text = gcnew String(client.getInfo().adress.c_str());
			textBoxPhone->Text = gcnew String(client.getInfo().phone_number.c_str());
			textBoxEmail->Text = gcnew String(client.getInfo().email.c_str());

			textBoxDomesticNumber->Text = gcnew String(client.getDomesticPassport().number.c_str());
			textBoxDomesticIssuedBy->Text = gcnew String(client.getDomesticPassport().issued_by.c_str());
			try {
				dateTimePickerDomesticIssue->Value = DateTime::ParseExact(gcnew String(client.getDomesticPassport().issue_date.c_str()), "dd.MM.yyyy", nullptr);
			}
			catch (...) {}

			textBoxForeignNumber->Text = gcnew String(client.getForeignPassport().number.c_str());
			textBoxForeignIssuedBy->Text = gcnew String(client.getForeignPassport().issued_by.c_str());
			try {
				dateTimePickerForeignIssue->Value = DateTime::ParseExact(gcnew String(client.getForeignPassport().issue_date.c_str()), "dd.MM.yyyy", nullptr);
			}
			catch (...) {}
		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ClientForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		bool isEditMode = false;
		int editingClientId = -1;
	private: System::Windows::Forms::TextBox^ textBoxO;

	protected:

	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ comboBoxGender;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::DateTimePicker^ dateTimePickerBirthDate;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBoxAdress;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBoxPhone;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBoxEmail;

	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ textBoxDomesticNumber;


	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ textBoxDomesticIssuedBy;

	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Button^ buttonClient;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::TextBox^ textBoxForeignNumber;

	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ textBoxForeignIssuedBy;


	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::DateTimePicker^ dateTimePickerDomesticIssue;
	private: System::Windows::Forms::DateTimePicker^ dateTimePickerForeignIssue;
private: System::Windows::Forms::Label^ label16;
private: System::Windows::Forms::TextBox^ textBoxI;
private: System::Windows::Forms::TextBox^ textBoxF;
private: System::Windows::Forms::Label^ label15;







	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBoxO = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBoxGender = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->dateTimePickerBirthDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBoxAdress = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBoxPhone = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBoxEmail = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBoxDomesticNumber = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBoxDomesticIssuedBy = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->buttonClient = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBoxI = (gcnew System::Windows::Forms::TextBox());
			this->textBoxF = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->dateTimePickerDomesticIssue = (gcnew System::Windows::Forms::DateTimePicker());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->dateTimePickerForeignIssue = (gcnew System::Windows::Forms::DateTimePicker());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBoxForeignNumber = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBoxForeignIssuedBy = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBoxO
			// 
			this->textBoxO->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxO->Location = System::Drawing::Point(3, 133);
			this->textBoxO->Name = L"textBoxO";
			this->textBoxO->Size = System::Drawing::Size(116, 23);
			this->textBoxO->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label1->Location = System::Drawing::Point(3, 104);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(63, 15);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Отчество:";
			// 
			// comboBoxGender
			// 
			this->comboBoxGender->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxGender->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->comboBoxGender->FormattingEnabled = true;
			this->comboBoxGender->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Мужской", L"Женский" });
			this->comboBoxGender->Location = System::Drawing::Point(3, 185);
			this->comboBoxGender->Name = L"comboBoxGender";
			this->comboBoxGender->Size = System::Drawing::Size(116, 23);
			this->comboBoxGender->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label2->Location = System::Drawing::Point(3, 156);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(33, 15);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Пол:";
			// 
			// dateTimePickerBirthDate
			// 
			this->dateTimePickerBirthDate->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->dateTimePickerBirthDate->Location = System::Drawing::Point(3, 237);
			this->dateTimePickerBirthDate->Name = L"dateTimePickerBirthDate";
			this->dateTimePickerBirthDate->Size = System::Drawing::Size(116, 23);
			this->dateTimePickerBirthDate->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label3->Location = System::Drawing::Point(3, 208);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(99, 15);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Дата рождения:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label4->Location = System::Drawing::Point(3, 260);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(45, 15);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Адрес:";
			// 
			// textBoxAdress
			// 
			this->textBoxAdress->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxAdress->Location = System::Drawing::Point(3, 289);
			this->textBoxAdress->Name = L"textBoxAdress";
			this->textBoxAdress->Size = System::Drawing::Size(116, 23);
			this->textBoxAdress->TabIndex = 8;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label5->Location = System::Drawing::Point(3, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(60, 15);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Телефон:";
			// 
			// textBoxPhone
			// 
			this->textBoxPhone->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxPhone->Location = System::Drawing::Point(3, 30);
			this->textBoxPhone->Name = L"textBoxPhone";
			this->textBoxPhone->Size = System::Drawing::Size(116, 23);
			this->textBoxPhone->TabIndex = 10;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label6->Location = System::Drawing::Point(3, 54);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(39, 15);
			this->label6->TabIndex = 11;
			this->label6->Text = L"Email:";
			// 
			// textBoxEmail
			// 
			this->textBoxEmail->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxEmail->Location = System::Drawing::Point(3, 84);
			this->textBoxEmail->Name = L"textBoxEmail";
			this->textBoxEmail->Size = System::Drawing::Size(116, 23);
			this->textBoxEmail->TabIndex = 12;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->label7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label7->Location = System::Drawing::Point(12, 366);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(155, 19);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Внутренний паспорт";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label8->Location = System::Drawing::Point(3, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(97, 15);
			this->label8->TabIndex = 14;
			this->label8->Text = L"Серия и номер:";
			// 
			// textBoxDomesticNumber
			// 
			this->textBoxDomesticNumber->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxDomesticNumber->Location = System::Drawing::Point(3, 31);
			this->textBoxDomesticNumber->Name = L"textBoxDomesticNumber";
			this->textBoxDomesticNumber->Size = System::Drawing::Size(104, 23);
			this->textBoxDomesticNumber->TabIndex = 15;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label9->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label9->Location = System::Drawing::Point(3, 56);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(74, 15);
			this->label9->TabIndex = 16;
			this->label9->Text = L"Кем выдан:";
			// 
			// textBoxDomesticIssuedBy
			// 
			this->textBoxDomesticIssuedBy->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxDomesticIssuedBy->Location = System::Drawing::Point(3, 87);
			this->textBoxDomesticIssuedBy->Name = L"textBoxDomesticIssuedBy";
			this->textBoxDomesticIssuedBy->Size = System::Drawing::Size(104, 23);
			this->textBoxDomesticIssuedBy->TabIndex = 17;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label10->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label10->Location = System::Drawing::Point(3, 112);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(83, 15);
			this->label10->TabIndex = 18;
			this->label10->Text = L"Когда выдан:";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->label14->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label14->Location = System::Drawing::Point(301, 366);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(164, 19);
			this->label14->TabIndex = 20;
			this->label14->Text = L"Заграничный паспорт";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
			this->label17->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label17->Location = System::Drawing::Point(15, 8);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(142, 20);
			this->label17->TabIndex = 30;
			this->label17->Text = L"Основные данные";
			// 
			// buttonClient
			// 
			this->buttonClient->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(243)));
			this->buttonClient->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonClient->ForeColor = System::Drawing::Color::White;
			this->buttonClient->Location = System::Drawing::Point(470, 572);
			this->buttonClient->Name = L"buttonClient";
			this->buttonClient->Size = System::Drawing::Size(98, 47);
			this->buttonClient->TabIndex = 31;
			this->buttonClient->Text = L"Добавить";
			this->buttonClient->UseVisualStyleBackColor = false;
			this->buttonClient->Click += gcnew System::EventHandler(this, &ClientForm::buttonClient_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->label16, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->textBoxAdress, 0, 11);
			this->tableLayoutPanel1->Controls->Add(this->label4, 0, 10);
			this->tableLayoutPanel1->Controls->Add(this->dateTimePickerBirthDate, 0, 9);
			this->tableLayoutPanel1->Controls->Add(this->label3, 0, 8);
			this->tableLayoutPanel1->Controls->Add(this->comboBoxGender, 0, 7);
			this->tableLayoutPanel1->Controls->Add(this->label2, 0, 6);
			this->tableLayoutPanel1->Controls->Add(this->textBoxO, 0, 5);
			this->tableLayoutPanel1->Controls->Add(this->label1, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->textBoxI, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->textBoxF, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->label15, 0, 2);
			this->tableLayoutPanel1->Location = System::Drawing::Point(18, 36);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 12;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333402F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333402F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333402F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333402F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333402F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333402F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333402F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333402F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333402F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333402F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333402F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.332568F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(247, 315);
			this->tableLayoutPanel1->TabIndex = 32;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label16->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label16->Location = System::Drawing::Point(3, 0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(65, 15);
			this->label16->TabIndex = 12;
			this->label16->Text = L"Фамилия:";
			// 
			// textBoxI
			// 
			this->textBoxI->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxI->Location = System::Drawing::Point(3, 81);
			this->textBoxI->Name = L"textBoxI";
			this->textBoxI->Size = System::Drawing::Size(116, 23);
			this->textBoxI->TabIndex = 9;
			// 
			// textBoxF
			// 
			this->textBoxF->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxF->Location = System::Drawing::Point(3, 29);
			this->textBoxF->Name = L"textBoxF";
			this->textBoxF->Size = System::Drawing::Size(116, 23);
			this->textBoxF->TabIndex = 10;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label15->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label15->Location = System::Drawing::Point(3, 52);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(35, 15);
			this->label15->TabIndex = 11;
			this->label15->Text = L"Имя:";
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel2->Controls->Add(this->textBoxPhone, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->label6, 0, 2);
			this->tableLayoutPanel2->Controls->Add(this->textBoxEmail, 0, 3);
			this->tableLayoutPanel2->Controls->Add(this->label5, 0, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(302, 61);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 4;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(171, 111);
			this->tableLayoutPanel2->TabIndex = 33;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
			this->label18->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label18->Location = System::Drawing::Point(298, 36);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(193, 20);
			this->label18->TabIndex = 34;
			this->label18->Text = L"Контактная информация";
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 1;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel3->Controls->Add(this->dateTimePickerDomesticIssue, 0, 5);
			this->tableLayoutPanel3->Controls->Add(this->label8, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->textBoxDomesticNumber, 0, 1);
			this->tableLayoutPanel3->Controls->Add(this->label9, 0, 2);
			this->tableLayoutPanel3->Controls->Add(this->textBoxDomesticIssuedBy, 0, 3);
			this->tableLayoutPanel3->Controls->Add(this->label10, 0, 4);
			this->tableLayoutPanel3->Location = System::Drawing::Point(18, 397);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 6;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(171, 174);
			this->tableLayoutPanel3->TabIndex = 35;
			// 
			// dateTimePickerDomesticIssue
			// 
			this->dateTimePickerDomesticIssue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->dateTimePickerDomesticIssue->Location = System::Drawing::Point(3, 143);
			this->dateTimePickerDomesticIssue->Name = L"dateTimePickerDomesticIssue";
			this->dateTimePickerDomesticIssue->Size = System::Drawing::Size(116, 23);
			this->dateTimePickerDomesticIssue->TabIndex = 20;
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 1;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel4->Controls->Add(this->dateTimePickerForeignIssue, 0, 5);
			this->tableLayoutPanel4->Controls->Add(this->label11, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->textBoxForeignNumber, 0, 1);
			this->tableLayoutPanel4->Controls->Add(this->label12, 0, 2);
			this->tableLayoutPanel4->Controls->Add(this->textBoxForeignIssuedBy, 0, 3);
			this->tableLayoutPanel4->Controls->Add(this->label13, 0, 4);
			this->tableLayoutPanel4->Location = System::Drawing::Point(305, 397);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 6;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(171, 174);
			this->tableLayoutPanel4->TabIndex = 36;
			// 
			// dateTimePickerForeignIssue
			// 
			this->dateTimePickerForeignIssue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->dateTimePickerForeignIssue->Location = System::Drawing::Point(3, 143);
			this->dateTimePickerForeignIssue->Name = L"dateTimePickerForeignIssue";
			this->dateTimePickerForeignIssue->Size = System::Drawing::Size(116, 23);
			this->dateTimePickerForeignIssue->TabIndex = 19;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label11->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label11->Location = System::Drawing::Point(3, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(97, 15);
			this->label11->TabIndex = 14;
			this->label11->Text = L"Серия и номер:";
			// 
			// textBoxForeignNumber
			// 
			this->textBoxForeignNumber->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxForeignNumber->Location = System::Drawing::Point(3, 31);
			this->textBoxForeignNumber->Name = L"textBoxForeignNumber";
			this->textBoxForeignNumber->Size = System::Drawing::Size(104, 23);
			this->textBoxForeignNumber->TabIndex = 15;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label12->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label12->Location = System::Drawing::Point(3, 56);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(74, 15);
			this->label12->TabIndex = 16;
			this->label12->Text = L"Кем выдан:";
			// 
			// textBoxForeignIssuedBy
			// 
			this->textBoxForeignIssuedBy->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxForeignIssuedBy->Location = System::Drawing::Point(3, 87);
			this->textBoxForeignIssuedBy->Name = L"textBoxForeignIssuedBy";
			this->textBoxForeignIssuedBy->Size = System::Drawing::Size(104, 23);
			this->textBoxForeignIssuedBy->TabIndex = 17;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label13->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label13->Location = System::Drawing::Point(3, 112);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(83, 15);
			this->label13->TabIndex = 18;
			this->label13->Text = L"Когда выдан:";
			// 
			// ClientForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				static_cast<System::Int32>(static_cast<System::Byte>(252)));
			this->ClientSize = System::Drawing::Size(580, 631);
			this->Controls->Add(this->tableLayoutPanel4);
			this->Controls->Add(this->tableLayoutPanel3);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->buttonClient);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label7);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->MaximumSize = System::Drawing::Size(610, 670);
			this->Name = L"ClientForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::WindowsDefaultBounds;
			this->Text = L"Добавление клиента";
			this->Load += gcnew System::EventHandler(this, &ClientForm::ClientForm_Load);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void ClientForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tableLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}

private: System::Void buttonClient_Click(System::Object^ sender, System::EventArgs^ e) {

	if (textBoxF->Text->Trim() == "" ||
		textBoxI->Text->Trim() == "" || 
		textBoxO->Text->Trim() == "" ||
		textBoxAdress->Text->Trim() == "" ||
		textBoxEmail->Text->Trim() == "" ||
		textBoxDomesticIssuedBy->Text->Trim() == "" ||
		textBoxDomesticNumber->Text->Trim() == "" ||
		textBoxForeignIssuedBy->Text->Trim() == "" ||
		textBoxForeignNumber->Text->Trim() == "" ||
		textBoxPhone->Text->Trim() == "" ||
		comboBoxGender -> SelectedItem == nullptr) {

		MessageBox::Show("Не все поля заполнены! Заполните все обязательные поля.",
			"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	ClientInfo info;
	info.last_name = marshal_as<std::string>(textBoxF->Text->Trim());
	info.first_name = marshal_as<std::string>(textBoxI->Text->Trim());
	info.patronymic = marshal_as<std::string>(textBoxO->Text->Trim());
	info.gender = marshal_as<std::string>(comboBoxGender->SelectedItem->ToString());
	info.birth_date = marshal_as<std::string>(dateTimePickerBirthDate->Value.ToString("dd.MM.yyyy"));
	info.adress = marshal_as<std::string>(textBoxAdress->Text->Trim());
	info.phone_number = marshal_as<std::string>(textBoxPhone->Text->Trim());
	info.email = marshal_as<std::string>(textBoxEmail->Text->Trim());

	Client temp(0, info, {}, {});

	if (!Client::isValidName(temp.getInfo().getFullName())) {
		MessageBox::Show("Неверный формат ФИО!\n• Только буквы\n• Минимум 2 слова\n• Каждое слово с заглавной буквы",
			"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}


	if (!Client::isValidPhone(temp.getInfo().phone_number)) {
		MessageBox::Show("Неверный формат телефона!\n• Пример: +7(999)123-45-67\n• Только цифры и разрешенные символы (+, -, (), пробелы)",
			"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	if (!Client::isValidEmail(temp.getInfo().email)) {
		MessageBox::Show("Неверная почта!", "Ошибка",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	PassportData domestic;
	domestic.type = "внутренний";
	domestic.number = marshal_as<std::string>(textBoxDomesticNumber->Text->Trim());
	domestic.issued_by = marshal_as<std::string>(textBoxDomesticIssuedBy->Text->Trim());
	domestic.issue_date = marshal_as<std::string>(dateTimePickerDomesticIssue->Value.ToString("dd.MM.yyyy"));

	PassportData foreign;
	foreign.type = "загран";
	foreign.number = marshal_as<std::string>(textBoxForeignNumber->Text->Trim());
	foreign.issued_by = marshal_as<std::string>(textBoxForeignIssuedBy->Text->Trim());
	foreign.issue_date = marshal_as<std::string>(dateTimePickerForeignIssue->Value.ToString("dd.MM.yyyy"));

	if (!domestic.number.empty() && !Client::isValidDomesticPassport(domestic.number)) {
		MessageBox::Show(
			"Неверный формат внутреннего паспорта!\n• Пример: 1234 567890\n• Только 4 цифры (серия) + 6 цифр (номер)",
			"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	if (!foreign.number.empty() && !Client::isValidForeignPassport(foreign.number)) {
		MessageBox::Show(
			"Неверный формат загранпаспорта!\n• Примеры: 12 345678 или 1234 5678901\n• Серия: 2 или 4 цифры, номер: 6 или 7 цифр",
			"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	std::vector<Client> clients;
	try {
		clients = Client::loadClientsFromCSV("Clients.csv");
	}
	catch (...) {
		clients.clear();
	}

	std::vector<Client> allClients;
	try {
		allClients = Client::loadClientsFromCSV("Clients.csv");
	}
	catch (...) {
		allClients.clear();
	}

	if (isEditMode) {
		for (int i = 0; i < allClients.size(); i++) {
			if (allClients[i].getId() == editingClientId) {
				allClients[i] = Client(editingClientId, info, domestic, foreign);
				break;
			}
		}
	}
	else {
		int newId = allClients.empty() ? 1 : allClients.back().getId() + 1;
		Client newClient(newId, info, domestic, foreign);
		allClients.push_back(newClient);
	}

	try {
		Client::saveClientsToCSV("Clients.csv", allClients);
	}
	catch (std::exception& ex) {
		MessageBox::Show("Ошибка сохранения: " + gcnew String(ex.what()),
			"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	this->Close();

	MessageBox::Show("Клиент добавлен!", "Успех",
		MessageBoxButtons::OK, MessageBoxIcon::Information);
}

};
}
