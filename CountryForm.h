#pragma once
#include <msclr/marshal_cppstd.h>
#include "Country.h"
using namespace msclr::interop;

namespace TourAgency {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для CountryForm
	/// </summary>
	public ref class CountryForm : public System::Windows::Forms::Form
	{
	public:
		CountryForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

		CountryForm(const Country& country)
		{
			InitializeComponent();
			isEditMode = true;
			editingCountryName = gcnew String(country.getName().c_str());
			buttonCountry->Text = L"Сохранить";
			this->Text = L"Редактирование страны";

			textBoxCountryName->Text = gcnew String(country.getName().c_str());
			numericUpDownRisk->Value = (Decimal)(country.getRiskFactor() / 100.0);
			comboBoxVisaType->SelectedItem = country.isVisaRequired() ? "Нужна" : "Не нужна";
			numericUpDownVisaCost->Value = (Decimal)(country.getVisaCost() / 100.0);
			numericUpDownInsuranceCost->Value = (Decimal)(country.getInsuranceCost() / 100.0);

			comboBoxVisaType_SelectedIndexChanged(nullptr, nullptr);

			// Медицинские справки через ;
			std::string certsStr;
			for (size_t i = 0; i < country.getMedicalCerts().size(); ++i) {
				certsStr += country.getMedicalCerts()[i];
				if (i + 1 < country.getMedicalCerts().size())
					certsStr += ";";
			}
			richTextBoxMedicalCertificates->Text = gcnew String(certsStr.c_str());
		}


	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~CountryForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	protected:
	private:
		bool isEditMode = false;
		String^ editingCountryName = nullptr;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ comboBoxVisaType;
	private: System::Windows::Forms::Label^ label3;

	private: System::Windows::Forms::Label^ label15;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label4;

	private: System::Windows::Forms::Label^ label5;

	private: System::Windows::Forms::RichTextBox^ richTextBoxMedicalCertificates;
	private: System::Windows::Forms::Button^ buttonCountry;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::NumericUpDown^ numericUpDownInsuranceCost;
	private: System::Windows::Forms::NumericUpDown^ numericUpDownVisaCost;
	private: System::Windows::Forms::NumericUpDown^ numericUpDownRisk;
	private: System::Windows::Forms::TextBox^ textBoxCountryName;
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
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->numericUpDownInsuranceCost = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDownVisaCost = (gcnew System::Windows::Forms::NumericUpDown());
			this->richTextBoxMedicalCertificates = (gcnew System::Windows::Forms::RichTextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->comboBoxVisaType = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->buttonCountry = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->numericUpDownRisk = (gcnew System::Windows::Forms::NumericUpDown());
			this->textBoxCountryName = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownInsuranceCost))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownVisaCost))->BeginInit();
			this->tableLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownRisk))->BeginInit();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->numericUpDownInsuranceCost, 0, 5);
			this->tableLayoutPanel1->Controls->Add(this->numericUpDownVisaCost, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->richTextBoxMedicalCertificates, 0, 7);
			this->tableLayoutPanel1->Controls->Add(this->label5, 0, 6);
			this->tableLayoutPanel1->Controls->Add(this->label3, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->label15, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->label4, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->comboBoxVisaType, 0, 1);
			this->tableLayoutPanel1->Location = System::Drawing::Point(14, 250);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 8;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10.37347F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10.37347F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10.37347F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10.37347F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10.37347F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10.37347F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10.37347F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 27.38573F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(397, 263);
			this->tableLayoutPanel1->TabIndex = 33;
			// 
			// numericUpDownInsuranceCost
			// 
			this->numericUpDownInsuranceCost->DecimalPlaces = 2;
			this->numericUpDownInsuranceCost->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->numericUpDownInsuranceCost->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->numericUpDownInsuranceCost->Location = System::Drawing::Point(3, 138);
			this->numericUpDownInsuranceCost->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->numericUpDownInsuranceCost->Name = L"numericUpDownInsuranceCost";
			this->numericUpDownInsuranceCost->Size = System::Drawing::Size(103, 23);
			this->numericUpDownInsuranceCost->TabIndex = 40;
			// 
			// numericUpDownVisaCost
			// 
			this->numericUpDownVisaCost->DecimalPlaces = 2;
			this->numericUpDownVisaCost->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->numericUpDownVisaCost->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->numericUpDownVisaCost->Location = System::Drawing::Point(3, 84);
			this->numericUpDownVisaCost->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->numericUpDownVisaCost->Name = L"numericUpDownVisaCost";
			this->numericUpDownVisaCost->Size = System::Drawing::Size(103, 23);
			this->numericUpDownVisaCost->TabIndex = 39;
			// 
			// richTextBoxMedicalCertificates
			// 
			this->richTextBoxMedicalCertificates->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->richTextBoxMedicalCertificates->Location = System::Drawing::Point(3, 192);
			this->richTextBoxMedicalCertificates->Name = L"richTextBoxMedicalCertificates";
			this->richTextBoxMedicalCertificates->Size = System::Drawing::Size(347, 68);
			this->richTextBoxMedicalCertificates->TabIndex = 31;
			this->richTextBoxMedicalCertificates->Text = L"";
			this->richTextBoxMedicalCertificates->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CountryForm::richTextBoxMedicalCertificates_KeyPress);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label5->Location = System::Drawing::Point(3, 162);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(145, 15);
			this->label5->TabIndex = 29;
			this->label5->Text = L"Медицинские справки:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label3->Location = System::Drawing::Point(3, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(38, 15);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Виза:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label15->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label15->Location = System::Drawing::Point(3, 108);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(134, 15);
			this->label15->TabIndex = 27;
			this->label15->Text = L"Стоимость страховки:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label4->Location = System::Drawing::Point(3, 54);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(105, 15);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Стоимость визы:";
			// 
			// comboBoxVisaType
			// 
			this->comboBoxVisaType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxVisaType->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->comboBoxVisaType->FormattingEnabled = true;
			this->comboBoxVisaType->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Нужна", L"Не нужна" });
			this->comboBoxVisaType->Location = System::Drawing::Point(3, 30);
			this->comboBoxVisaType->Name = L"comboBoxVisaType";
			this->comboBoxVisaType->Size = System::Drawing::Size(116, 23);
			this->comboBoxVisaType->TabIndex = 2;
			this->comboBoxVisaType->SelectedIndexChanged += gcnew System::EventHandler(this, &CountryForm::comboBoxVisaType_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(110, 15);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Название страны:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label2->Location = System::Drawing::Point(3, 74);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(112, 15);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Риск в процентах:";
			// 
			// buttonCountry
			// 
			this->buttonCountry->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(243)));
			this->buttonCountry->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonCountry->ForeColor = System::Drawing::Color::White;
			this->buttonCountry->Location = System::Drawing::Point(474, 539);
			this->buttonCountry->Name = L"buttonCountry";
			this->buttonCountry->Size = System::Drawing::Size(98, 47);
			this->buttonCountry->TabIndex = 34;
			this->buttonCountry->Text = L"Добавить";
			this->buttonCountry->UseVisualStyleBackColor = false;
			this->buttonCountry->Click += gcnew System::EventHandler(this, &CountryForm::buttonCountry_Click);
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel2->Controls->Add(this->numericUpDownRisk, 0, 3);
			this->tableLayoutPanel2->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->textBoxCountryName, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->label2, 0, 2);
			this->tableLayoutPanel2->Location = System::Drawing::Point(16, 42);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 4;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(183, 150);
			this->tableLayoutPanel2->TabIndex = 35;
			// 
			// numericUpDownRisk
			// 
			this->numericUpDownRisk->DecimalPlaces = 2;
			this->numericUpDownRisk->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->numericUpDownRisk->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->numericUpDownRisk->Location = System::Drawing::Point(3, 114);
			this->numericUpDownRisk->Name = L"numericUpDownRisk";
			this->numericUpDownRisk->Size = System::Drawing::Size(103, 23);
			this->numericUpDownRisk->TabIndex = 38;
			// 
			// textBoxCountryName
			// 
			this->textBoxCountryName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxCountryName->Location = System::Drawing::Point(3, 40);
			this->textBoxCountryName->Name = L"textBoxCountryName";
			this->textBoxCountryName->Size = System::Drawing::Size(116, 23);
			this->textBoxCountryName->TabIndex = 0;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
			this->label17->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label17->Location = System::Drawing::Point(13, 8);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(142, 20);
			this->label17->TabIndex = 36;
			this->label17->Text = L"Основные данные";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
			this->label6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label6->Location = System::Drawing::Point(13, 209);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(142, 20);
			this->label6->TabIndex = 37;
			this->label6->Text = L"Виза и документы";
			// 
			// CountryForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				static_cast<System::Int32>(static_cast<System::Byte>(252)));
			this->ClientSize = System::Drawing::Size(582, 596);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->buttonCountry);
			this->Controls->Add(this->tableLayoutPanel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"CountryForm";
			this->Text = L"Добавление страны";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownInsuranceCost))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownVisaCost))->EndInit();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownRisk))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void comboBoxVisaType_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	bool visaRequired = (comboBoxVisaType->SelectedItem != nullptr &&
		comboBoxVisaType->SelectedItem->ToString() == "Нужна");

	numericUpDownVisaCost->Enabled = visaRequired;
	if (!visaRequired) {
		numericUpDownVisaCost->Value = 0;
	}
}
private: System::Void richTextBoxMedicalCertificates_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	wchar_t c = e->KeyChar;

	if (c == '\b' || c < 32) {
		return;
	}
	bool isLetter = Char::IsLetter(c);
	bool isDigit = Char::IsDigit(c);
	bool isSpace = (c == L' ');
	bool isSemicolon = (c == L';');

	if (!(isLetter || isDigit || isSpace || isSemicolon)) {
		e->Handled = true;
		System::Media::SystemSounds::Beep->Play();
	}
}
private: System::Void buttonCountry_Click(System::Object^ sender, System::EventArgs^ e) {

	if (textBoxCountryName->Text->Trim() == "" ||
		numericUpDownRisk->Text->Trim() == "" ||
		comboBoxVisaType->SelectedItem == nullptr ||
		numericUpDownVisaCost->Text->Trim() == "" ||
		numericUpDownInsuranceCost->Text->Trim() == "")
	{
		MessageBox::Show("Не все поля заполнены! Заполните все обязательные поля.",
			"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	std::string name = marshal_as<std::string>(textBoxCountryName->Text->Trim());
	double riskDouble = (double)numericUpDownRisk->Value;
	percent_t risk = static_cast<percent_t>(riskDouble * 100 + 0.5);
	bool visaRequired = comboBoxVisaType->SelectedItem->ToString() == "Нужна";
	money_t visaCost = 0;
	if (comboBoxVisaType->SelectedItem->ToString() == "Нужна") {
		visaCost = static_cast<money_t>((double)numericUpDownVisaCost->Value * 100 + 0.5);
	}
	money_t insuranceCost = static_cast<money_t>((double)numericUpDownInsuranceCost->Value * 100 + 0.5);

	std::string certsStr = marshal_as<std::string>(richTextBoxMedicalCertificates->Text->Trim());
	std::vector<std::string> medicalCerts;
	if (!certsStr.empty()) {
		std::string cleanCerts = certsStr;
		cleanCerts.erase(std::remove(cleanCerts.begin(), cleanCerts.end(), ' '), cleanCerts.end());

		if (cleanCerts.find(";;") != std::string::npos ||
			cleanCerts.front() == ';' ||
			cleanCerts.back() == ';') {
			MessageBox::Show(
				"Медицинские справки должны быть перечислены через точку с запятой (;) без пробелов.\n"
				"Пример: Справка А;Справка Б;Анализы",
				"Ошибка формата", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		std::stringstream ss(certsStr);
		std::string cert;
		while (std::getline(ss, cert, ';')) {
			size_t start = 0, end = cert.size();
			while (start < cert.size() && isspace(static_cast<unsigned char>(cert[start]))) ++start;
			while (end > start && isspace(static_cast<unsigned char>(cert[end - 1]))) --end;
			std::string cleaned = (start < end) ? cert.substr(start, end - start) : "";

			if (!cleaned.empty()) {
				medicalCerts.push_back(cleaned);
			}
		}
	}

	std::vector<Country> allCountries;
	try {
		allCountries = Country::loadCountriesFromCSV("Countries.csv");
	}
	catch (...) {
		allCountries.clear();
	}

	std::string newName = name;

	if (isEditMode) {
		for (size_t i = 0; i < allCountries.size(); ++i) {
			if (gcnew String(allCountries[i].getName().c_str()) == editingCountryName) {
				allCountries[i] = Country(newName, risk, visaRequired, visaCost, insuranceCost, medicalCerts);
				break;
			}
		}
	}
	else {
		for (const auto& existing : allCountries) {
			if (existing.getName() == newName) {
				MessageBox::Show("Страна с таким названием уже существует!",
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}
		allCountries.push_back(Country(newName, risk, visaRequired, visaCost, insuranceCost, medicalCerts));
	}

	try {
		Country::saveCountriesToCSV("Countries.csv", allCountries);
	}
	catch (std::exception& ex) {
		MessageBox::Show("Ошибка сохранения: " + gcnew String(ex.what()),
			"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	this->Close();
	MessageBox::Show(isEditMode ? "Страна обновлена!" : "Страна добавлена!", "Успех",
		MessageBoxButtons::OK, MessageBoxIcon::Information);
}
};
}
