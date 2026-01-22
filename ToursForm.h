#pragma once
#include "Tour.h"
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
	/// Сводка для ToursForm
	/// </summary>
	public ref class ToursForm : public System::Windows::Forms::Form
	{
	public:
		ToursForm(void)
		{
			InitializeComponent();
			LoadCountriesToComboBox();

			//
			//TODO: добавьте код конструктора
			//
		}
		ToursForm(const Tour& tour)
		{
			InitializeComponent();
			LoadCountriesToComboBox();
			numericUpDownHotel_cost->Maximum = 1000000;
			numericUpDownFlight_cost->Maximum = 1000000;
			isEditMode = true;
			editingTourId = tour.getId();

			buttonTour->Text = L"Сохранить";
			this->Text = L"Редактирование тура";

			textBoxTourName->Text = gcnew String(tour.getName().c_str());
			textBoxCity->Text = gcnew String(tour.getCity().c_str());
			comboBoxCountry->SelectedItem =
				gcnew String(tour.getCountry().c_str());

			textBoxHotal_name->Text =
				gcnew String(tour.getHotelName().c_str());


			double hotel_price_double = tour.getHotelPrice() / 100.0;
			numericUpDownHotel_cost->Value = (Decimal)hotel_price_double;

			double flight_price_double = tour.getFlightPrice() / 100.0;
			numericUpDownFlight_cost->Value = (Decimal)flight_price_double;


			checkBoxIs_all_inclusive->Checked =
				tour.isAllInclusive();

			checkBoxIs_transfer_included->Checked =
				tour.isTransferIncluded();


			numericUpDownDuration->Value =
				tour.getDuration();

			numericUpDownAvailable_spots->Value =
				tour.getAvailableSeats();

			std::string startDate = tour.getStartDate();
			if (!startDate.empty()) {
				try {
					String^ dateStr = gcnew String(startDate.c_str());
					DateTime startDateObj = DateTime::ParseExact(dateStr, "yyyy-MM-dd",
						System::Globalization::CultureInfo::InvariantCulture);
					dateTimePickerStart_date->Value = startDateObj;
				}
				catch (Exception^ ex) {
					MessageBox::Show("Ошибка чтения даты из БД: " + ex->Message +
						"\nДата в БД: " + gcnew String(startDate.c_str()),
						"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}

			richTextBoxTour_description->Text =
				gcnew String(tour.getDescription().c_str());

			// категория отеля
			if (tour.getHotelCategory() == "3*") radioButton1->Checked = true;
			else if (tour.getHotelCategory() == "4*") radioButton2->Checked = true;
			else if (tour.getHotelCategory() == "5*") radioButton3->Checked = true;
		}

	private:
		bool isEditMode = false;


		   int editingTourId = -1;

		void ToursForm::LoadCountriesToComboBox()
		{
			try {
				std::vector<Country> countries = Country::loadCountriesFromCSV("Countries.csv");
				comboBoxCountry->Items->Clear();
				for (const auto& country : countries) {
					String^ countryName = gcnew String(country.getName().c_str());
					comboBoxCountry->Items->Add(countryName);
				}
				if (comboBoxCountry->Items->Count == 0) {
					comboBoxCountry->Items->Add("Нет стран в базе");
					comboBoxCountry->Enabled = false;
				}
			}
			catch (const std::exception& ex) {
				comboBoxCountry->Items->Clear();
				comboBoxCountry->Items->Add("Ошибка загрузки стран");
				comboBoxCountry->Enabled = false;
				MessageBox::Show("Не удалось загрузить страны из базы данных.\n"
					"Сначала добавьте страны через меню управления странами.",
					"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ToursForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBoxTourName;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::TextBox^ textBoxCity;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ comboBoxCountry;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::NumericUpDown^ numericUpDownDuration;


	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::DateTimePicker^ dateTimePickerStart_date;



	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::CheckBox^ checkBoxIs_all_inclusive;
	private: System::Windows::Forms::CheckBox^ checkBoxIs_transfer_included;


	private: System::Windows::Forms::GroupBox^ groupBoxHotel_category;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;

	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::NumericUpDown^ numericUpDownHotel_cost;

	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::NumericUpDown^ numericUpDownAvailable_spots;

	private: System::Windows::Forms::NumericUpDown^ numericUpDownFlight_cost;




	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::RichTextBox^ richTextBoxTour_description;
	private: System::Windows::Forms::Button^ buttonTour;


	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::TextBox^ textBoxHotal_name;
	protected:
	protected:
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
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxTourName = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->textBoxCity = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBoxCountry = (gcnew System::Windows::Forms::ComboBox());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->numericUpDownDuration = (gcnew System::Windows::Forms::NumericUpDown());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->dateTimePickerStart_date = (gcnew System::Windows::Forms::DateTimePicker());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->checkBoxIs_all_inclusive = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxIs_transfer_included = (gcnew System::Windows::Forms::CheckBox());
			this->groupBoxHotel_category = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->numericUpDownAvailable_spots = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDownFlight_cost = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->numericUpDownHotel_cost = (gcnew System::Windows::Forms::NumericUpDown());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->richTextBoxTour_description = (gcnew System::Windows::Forms::RichTextBox());
			this->buttonTour = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBoxHotal_name = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownDuration))->BeginInit();
			this->groupBoxHotel_category->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownAvailable_spots))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownFlight_cost))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownHotel_cost))->BeginInit();
			this->SuspendLayout();
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel2->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->textBoxTourName, 0, 1);
			this->tableLayoutPanel2->Location = System::Drawing::Point(10, 10);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(183, 66);
			this->tableLayoutPanel2->TabIndex = 36;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(93, 15);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Название тура:";
			// 
			// textBoxTourName
			// 
			this->textBoxTourName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxTourName->Location = System::Drawing::Point(3, 36);
			this->textBoxTourName->Name = L"textBoxTourName";
			this->textBoxTourName->Size = System::Drawing::Size(167, 23);
			this->textBoxTourName->TabIndex = 0;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 4;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				30.92486F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				18.78613F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->Controls->Add(this->textBoxCity, 3, 0);
			this->tableLayoutPanel1->Controls->Add(this->label3, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->label2, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->comboBoxCountry, 1, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(10, 95);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(414, 66);
			this->tableLayoutPanel1->TabIndex = 37;
			// 
			// textBoxCity
			// 
			this->textBoxCity->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxCity->Location = System::Drawing::Point(312, 3);
			this->textBoxCity->Name = L"textBoxCity";
			this->textBoxCity->Size = System::Drawing::Size(71, 23);
			this->textBoxCity->TabIndex = 39;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label3->Location = System::Drawing::Point(234, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(43, 15);
			this->label3->TabIndex = 38;
			this->label3->Text = L"Город:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label2->Location = System::Drawing::Point(3, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(48, 15);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Страна:";
			// 
			// comboBoxCountry
			// 
			this->comboBoxCountry->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->comboBoxCountry->FormattingEnabled = true;
			this->comboBoxCountry->Location = System::Drawing::Point(106, 3);
			this->comboBoxCountry->Name = L"comboBoxCountry";
			this->comboBoxCountry->Size = System::Drawing::Size(103, 23);
			this->comboBoxCountry->TabIndex = 2;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 2;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				44.70284F)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				55.29716F)));
			this->tableLayoutPanel3->Controls->Add(this->label4, 0, 1);
			this->tableLayoutPanel3->Controls->Add(this->numericUpDownDuration, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->label5, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->dateTimePickerStart_date, 1, 1);
			this->tableLayoutPanel3->Location = System::Drawing::Point(10, 166);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 3;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(332, 80);
			this->tableLayoutPanel3->TabIndex = 38;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label4->Location = System::Drawing::Point(3, 26);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(78, 15);
			this->label4->TabIndex = 39;
			this->label4->Text = L"Дата начала:";
			// 
			// numericUpDownDuration
			// 
			this->numericUpDownDuration->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->numericUpDownDuration->Location = System::Drawing::Point(151, 3);
			this->numericUpDownDuration->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDownDuration->Name = L"numericUpDownDuration";
			this->numericUpDownDuration->Size = System::Drawing::Size(51, 23);
			this->numericUpDownDuration->TabIndex = 39;
			this->numericUpDownDuration->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label5->Location = System::Drawing::Point(3, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(125, 15);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Длительность (дни):";
			// 
			// dateTimePickerStart_date
			// 
			this->dateTimePickerStart_date->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->dateTimePickerStart_date->Location = System::Drawing::Point(151, 29);
			this->dateTimePickerStart_date->Name = L"dateTimePickerStart_date";
			this->dateTimePickerStart_date->Size = System::Drawing::Size(121, 23);
			this->dateTimePickerStart_date->TabIndex = 40;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->radioButton1->Location = System::Drawing::Point(3, 16);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(36, 19);
			this->radioButton1->TabIndex = 42;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"3*";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->radioButton2->Location = System::Drawing::Point(93, 16);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(36, 19);
			this->radioButton2->TabIndex = 43;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"4*";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->radioButton3->Location = System::Drawing::Point(171, 16);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(36, 19);
			this->radioButton3->TabIndex = 44;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"5*";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// checkBoxIs_all_inclusive
			// 
			this->checkBoxIs_all_inclusive->AutoSize = true;
			this->checkBoxIs_all_inclusive->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->checkBoxIs_all_inclusive->Location = System::Drawing::Point(3, 48);
			this->checkBoxIs_all_inclusive->Name = L"checkBoxIs_all_inclusive";
			this->checkBoxIs_all_inclusive->Size = System::Drawing::Size(89, 19);
			this->checkBoxIs_all_inclusive->TabIndex = 45;
			this->checkBoxIs_all_inclusive->Text = L"All inclusive";
			this->checkBoxIs_all_inclusive->UseVisualStyleBackColor = true;
			// 
			// checkBoxIs_transfer_included
			// 
			this->checkBoxIs_transfer_included->AutoSize = true;
			this->checkBoxIs_transfer_included->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->checkBoxIs_transfer_included->Location = System::Drawing::Point(142, 48);
			this->checkBoxIs_transfer_included->Name = L"checkBoxIs_transfer_included";
			this->checkBoxIs_transfer_included->Size = System::Drawing::Size(132, 19);
			this->checkBoxIs_transfer_included->TabIndex = 46;
			this->checkBoxIs_transfer_included->Text = L"Трансфер включен";
			this->checkBoxIs_transfer_included->UseVisualStyleBackColor = true;
			// 
			// groupBoxHotel_category
			// 
			this->groupBoxHotel_category->Controls->Add(this->radioButton1);
			this->groupBoxHotel_category->Controls->Add(this->checkBoxIs_transfer_included);
			this->groupBoxHotel_category->Controls->Add(this->radioButton2);
			this->groupBoxHotel_category->Controls->Add(this->checkBoxIs_all_inclusive);
			this->groupBoxHotel_category->Controls->Add(this->radioButton3);
			this->groupBoxHotel_category->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->groupBoxHotel_category->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)),
				static_cast<System::Int32>(static_cast<System::Byte>(118)), static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->groupBoxHotel_category->Location = System::Drawing::Point(10, 310);
			this->groupBoxHotel_category->Name = L"groupBoxHotel_category";
			this->groupBoxHotel_category->Size = System::Drawing::Size(255, 87);
			this->groupBoxHotel_category->TabIndex = 47;
			this->groupBoxHotel_category->TabStop = false;
			this->groupBoxHotel_category->Text = L"Отель и услуги:";
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 2;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				44.70284F)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				55.29716F)));
			this->tableLayoutPanel4->Controls->Add(this->numericUpDownAvailable_spots, 1, 2);
			this->tableLayoutPanel4->Controls->Add(this->numericUpDownFlight_cost, 1, 1);
			this->tableLayoutPanel4->Controls->Add(this->label7, 0, 2);
			this->tableLayoutPanel4->Controls->Add(this->label8, 0, 1);
			this->tableLayoutPanel4->Controls->Add(this->numericUpDownHotel_cost, 1, 0);
			this->tableLayoutPanel4->Controls->Add(this->label9, 0, 0);
			this->tableLayoutPanel4->Location = System::Drawing::Point(294, 317);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 3;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(329, 80);
			this->tableLayoutPanel4->TabIndex = 48;
			// 
			// numericUpDownAvailable_spots
			// 
			this->numericUpDownAvailable_spots->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->numericUpDownAvailable_spots->Location = System::Drawing::Point(150, 55);
			this->numericUpDownAvailable_spots->Name = L"numericUpDownAvailable_spots";
			this->numericUpDownAvailable_spots->Size = System::Drawing::Size(109, 23);
			this->numericUpDownAvailable_spots->TabIndex = 42;
			// 
			// numericUpDownFlight_cost
			// 
			this->numericUpDownFlight_cost->DecimalPlaces = 2;
			this->numericUpDownFlight_cost->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->numericUpDownFlight_cost->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->numericUpDownFlight_cost->Location = System::Drawing::Point(150, 29);
			this->numericUpDownFlight_cost->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->numericUpDownFlight_cost->Name = L"numericUpDownFlight_cost";
			this->numericUpDownFlight_cost->Size = System::Drawing::Size(109, 23);
			this->numericUpDownFlight_cost->TabIndex = 41;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label7->Location = System::Drawing::Point(3, 52);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(112, 15);
			this->label7->TabIndex = 40;
			this->label7->Text = L"Свободные места:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label8->Location = System::Drawing::Point(3, 26);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(127, 15);
			this->label8->TabIndex = 39;
			this->label8->Text = L"Стоимость перелёта:";
			// 
			// numericUpDownHotel_cost
			// 
			this->numericUpDownHotel_cost->DecimalPlaces = 2;
			this->numericUpDownHotel_cost->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->numericUpDownHotel_cost->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->numericUpDownHotel_cost->Location = System::Drawing::Point(150, 3);
			this->numericUpDownHotel_cost->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->numericUpDownHotel_cost->Name = L"numericUpDownHotel_cost";
			this->numericUpDownHotel_cost->Size = System::Drawing::Size(109, 23);
			this->numericUpDownHotel_cost->TabIndex = 39;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label9->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label9->Location = System::Drawing::Point(3, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(107, 15);
			this->label9->TabIndex = 1;
			this->label9->Text = L"Стоимость отеля:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label10->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label10->Location = System::Drawing::Point(13, 410);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(95, 15);
			this->label10->TabIndex = 49;
			this->label10->Text = L"Описание тура:";
			// 
			// richTextBoxTour_description
			// 
			this->richTextBoxTour_description->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->richTextBoxTour_description->Location = System::Drawing::Point(10, 439);
			this->richTextBoxTour_description->Name = L"richTextBoxTour_description";
			this->richTextBoxTour_description->Size = System::Drawing::Size(373, 105);
			this->richTextBoxTour_description->TabIndex = 50;
			this->richTextBoxTour_description->Text = L"";
			// 
			// buttonTour
			// 
			this->buttonTour->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(243)));
			this->buttonTour->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonTour->ForeColor = System::Drawing::Color::White;
			this->buttonTour->Location = System::Drawing::Point(474, 539);
			this->buttonTour->Name = L"buttonTour";
			this->buttonTour->Size = System::Drawing::Size(98, 47);
			this->buttonTour->TabIndex = 51;
			this->buttonTour->Text = L"Добавить";
			this->buttonTour->UseVisualStyleBackColor = false;
			this->buttonTour->Click += gcnew System::EventHandler(this, &ToursForm::buttonTour_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label11->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label11->Location = System::Drawing::Point(9, 249);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(102, 15);
			this->label11->TabIndex = 52;
			this->label11->Text = L"Название отеля:";
			// 
			// textBoxHotal_name
			// 
			this->textBoxHotal_name->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->textBoxHotal_name->Location = System::Drawing::Point(10, 273);
			this->textBoxHotal_name->Name = L"textBoxHotal_name";
			this->textBoxHotal_name->Size = System::Drawing::Size(167, 23);
			this->textBoxHotal_name->TabIndex = 53;
			// 
			// ToursForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				static_cast<System::Int32>(static_cast<System::Byte>(252)));
			this->ClientSize = System::Drawing::Size(582, 596);
			this->Controls->Add(this->textBoxHotal_name);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->buttonTour);
			this->Controls->Add(this->richTextBoxTour_description);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->tableLayoutPanel4);
			this->Controls->Add(this->groupBoxHotel_category);
			this->Controls->Add(this->tableLayoutPanel3);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->tableLayoutPanel2);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->Name = L"ToursForm";
			this->Text = L"Добавление тура";
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownDuration))->EndInit();
			this->groupBoxHotel_category->ResumeLayout(false);
			this->groupBoxHotel_category->PerformLayout();
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownAvailable_spots))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownFlight_cost))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownHotel_cost))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonTour_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBoxTourName->Text->Trim() == "" ||
			comboBoxCountry->SelectedItem == nullptr ||
			textBoxCity->Text->Trim() == "" ||
			textBoxHotal_name->Text->Trim() == "" ||
			(!radioButton1->Checked && !radioButton2->Checked && !radioButton3->Checked))
		{
			MessageBox::Show("Не все обязательные поля заполнены!\n"
				"Заполните: название тура, страну, город, название отеля, сезон и выберите категорию отеля.",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		try {
			std::string name = marshal_as<std::string>(textBoxTourName->Text->Trim());
			std::string country = marshal_as<std::string>(comboBoxCountry->SelectedItem->ToString());
			std::string city = marshal_as<std::string>(textBoxCity->Text->Trim());
			std::string hotel_name = marshal_as<std::string>(textBoxHotal_name->Text->Trim());

			int duration_days = (int)numericUpDownDuration->Value;
			// Стоимость отеля и перелета (в копейках)
			double hotel_price_double = (double)numericUpDownHotel_cost->Value;
			money_t hotel_price = static_cast<money_t>(hotel_price_double * 100 + 0.5);

			double flight_price_double = (double)numericUpDownFlight_cost->Value;
			money_t flight_price = static_cast<money_t>(flight_price_double * 100 + 0.5);

			std::string hotel_category = "";
			if (radioButton1->Checked) hotel_category = "3*";
			else if (radioButton2->Checked) hotel_category = "4*";
			else if (radioButton3->Checked) hotel_category = "5*";

			bool all_inclusive = checkBoxIs_all_inclusive->Checked;
			bool transfer_included = checkBoxIs_transfer_included->Checked;
			int available_seats = (int)numericUpDownAvailable_spots->Value;
			DateTime start_date_obj = dateTimePickerStart_date->Value;
			String^ dateStr = String::Format("{0:0000}-{1:00}-{2:00}",
				start_date_obj.Year, start_date_obj.Month, start_date_obj.Day);
			std::string start_date = marshal_as<std::string>(dateStr);


			int month = start_date_obj.Month;
			std::string season;
			if (month >= 3 && month <= 5) season = "Весна";
			else if (month >= 6 && month <= 8) season = "Лето";
			else if (month >= 9 && month <= 11) season = "Осень";
			else season = "Зима";

			std::string description = marshal_as<std::string>(richTextBoxTour_description->Text->Trim());

			std::vector<Tour> all_tours;
			try {
				all_tours = Tour::loadToursFromCSV("Tours.csv");
			}
			catch (const std::exception&) {
				all_tours.clear();
			}

			if (isEditMode) {
				for (size_t i = 0; i < all_tours.size(); ++i) {
					if (all_tours[i].getId() == editingTourId) {
						all_tours[i] = Tour(editingTourId, name, country, city, hotel_name,
							hotel_price, flight_price, hotel_category,
							all_inclusive, season, duration_days,
							available_seats, start_date, description,
							transfer_included);

						Tour::saveToursToCSV("Tours.csv", all_tours);

						MessageBox::Show("Тур успешно обновлен!",
							"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
						this->Close();
						return;
					}
				}

				MessageBox::Show("Не удалось найти тур для редактирования!",
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			else {
				int new_id = 1;
				if (!all_tours.empty()) {
					for (const auto& t : all_tours) {
						if (t.getId() >= new_id) new_id = t.getId() + 1;
					}
				}

				Tour new_tour(new_id, name, country, city, hotel_name,
					hotel_price, flight_price, hotel_category,
					all_inclusive, season, duration_days,
					available_seats, start_date, description,
					transfer_included);

				all_tours.push_back(new_tour);
				Tour::saveToursToCSV("Tours.csv", all_tours);
				MessageBox::Show("Тур успешно добавлен!\nID тура: " + new_id.ToString(),
					"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
		}
		catch (const std::exception& ex) {
			MessageBox::Show("Ошибка при обработке данных: " +
				gcnew String(ex.what()),
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		catch (...) {
			MessageBox::Show("Неизвестная ошибка при обработке тура.",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
};
}
