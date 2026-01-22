#pragma once
#include "Booking.h"
#include "Client.h"
#include "Tour.h"
#include "Country.h"
#include <msclr/marshal_cppstd.h>
using namespace msclr::interop;
#include <vector>
#include <map>

namespace TourAgency {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Сводка для BookingForm
	/// </summary>
	public ref class BookingForm : public System::Windows::Forms::Form
	{
	public:
		BookingForm(void)
		{
			InitializeComponent();
			LoadData();
			LoadComboBoxes();
			//
			//TODO: добавьте код конструктора
			//
		}

		BookingForm(const Booking& booking)
		{
			InitializeComponent();
			LoadData();
			LoadComboBoxes();
			isEditMode = true;
			editingBookingId = booking.getBookingId();
			buttonBooking->Text = L"Сохранить";
			this->Text = L"Редактирование бронирования";
			SetSelectedClientById(booking.getClientId());
			SetSelectedTourById(booking.getTourId());

			try {
				String^ dateStr = gcnew String(booking.getBookingDate().c_str());
				if (!String::IsNullOrEmpty(dateStr)) {
					bookingDatePicker->Value = DateTime::Parse(dateStr);
				}
			}
			catch (...) {
				bookingDatePicker->Value = DateTime::Now;
			}
			notesTextBox->Text = gcnew String(booking.getNotes().c_str());
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~BookingForm()
		{
			if (components)
			{
				delete components;
			}
			if (clients != nullptr)
			{
				delete clients;
				clients = nullptr;
			}
			if (countries != nullptr) {
				delete countries;
				countries = nullptr;
			}
			if (tours != nullptr) {
				delete tours;
				tours = nullptr;
			}
			if (bookings != nullptr) {
				delete bookings;
				bookings = nullptr;
			}
		}
	private:
		bool isEditMode = false;
		int editingBookingId = -1;
		std::vector<Booking>* bookings = nullptr;
		std::vector<Client>* clients = nullptr;
		std::vector<Tour>* tours = nullptr;
		std::vector<Country>* countries = nullptr;
		System::Collections::Generic::Dictionary<int, String^>^ clientMap;
		System::Collections::Generic::Dictionary<int, String^>^ tourMap;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::CheckedListBox^ medicalDocsListBox;
	private: System::Windows::Forms::RichTextBox^ notesTextBox;


	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::DateTimePicker^ bookingDatePicker;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ buttonBooking;




	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::ComboBox^ comboBoxTour;
	private: System::Windows::Forms::ComboBox^ comboBoxClient;
	private:

		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

		bool IsBookingDuplicate(int clientId, int tourId)
		{
			if (bookings == nullptr) return false;

			for (const auto& booking : *bookings)
			{
				if (isEditMode && booking.getBookingId() == editingBookingId)
					continue;

				if (booking.getClientId() == clientId && booking.getTourId() == tourId)
				{
					return true;
				}
			}
			return false;
		}

		bool AreAllMedicalRequirementsMet(int tourId)
		{
			// Получаем список требуемых справок для тура
			std::vector<std::string> requiredDocs = GetMedicalRequirementsForTour(tourId);

			if (requiredDocs.empty()) {
				return true;
			}

			// Если список не совпадает по длине — уже ошибка
			if (medicalDocsListBox->Items->Count != static_cast<int>(requiredDocs.size())) {
				return false;
			}

			// Проверяем, что ВСЕ элементы отмечены
			for (int i = 0; i < medicalDocsListBox->Items->Count; i++) {
				if (!medicalDocsListBox->GetItemChecked(i)) {
					return false;
				}
			}

			return true;
		}

		void LoadData()
		{
			try {
				bookings = new std::vector<Booking>(Booking::loadBookingsFromCSV("Bookings.csv"));
			}
			catch (...) {
				bookings = new std::vector<Booking>();
			}

			try {
				clients = new std::vector<Client>(Client::loadClientsFromCSV("Clients.csv"));
			}
			catch (...) {
				clients = new std::vector<Client>();
			}

			try {
				tours = new std::vector<Tour>(Tour::loadToursFromCSV("Tours.csv"));
			}
			catch (...) {
				tours = new std::vector<Tour>();
			}

			try {
				countries = new std::vector<Country>(Country::loadCountriesFromCSV("Countries.csv"));
			}
			catch (...) {
				countries = new std::vector<Country>();
			}
		}

		std::vector<std::string> GetMedicalRequirementsForTour(int tourId)
		{
			std::vector<std::string> medicalDocs;

			if (tours == nullptr || countries == nullptr) {
				return medicalDocs;
			}

			for (const auto& tour : *tours) {
				if (tour.getId() == tourId) {
					for (const auto& country : *countries) {
						if (country.getName() == tour.getCountry()) {
							const auto& docs = country.getMedicalCerts();
							medicalDocs.assign(docs.begin(), docs.end());
							break;
						}
					}
					break;
				}
			}

			return medicalDocs;
		}


		bool ClientExists(int clientId)
		{
			if (clients == nullptr) return false;

			for (const auto& client : *clients) {
				if (client.getId() == clientId) {
					return true;
				}
			}
			return false;
		}

		bool TourExists(int tourId)
		{
			if (tours == nullptr) return false;

			for (const auto& tour : *tours) {
				if (tour.getId() == tourId) {
					return true;
				}
			}
			return false;
		}

		bool CheckTourAvailability(int tourId)
		{
			if (tours == nullptr) return false;

			for (const auto& tour : *tours) {
				if (tour.getId() == tourId) {
					int bookedCount = 0;
					if (bookings != nullptr) {
						for (const auto& booking : *bookings) {
							if (booking.getTourId() == tourId) {
								bookedCount++;
							}
						}
					}
					return bookedCount < tour.getAvailableSeats();
				}
			}
			return false;
		}

		void UpdateTourInfo(int tourId)
		{
			medicalDocsListBox->Items->Clear();

			if (tourId <= 0 || tours == nullptr || countries == nullptr) return;

			for (const auto& tour : *tours) {
				if (tour.getId() == tourId) {
					std::vector<std::string> medicalDocs = GetMedicalRequirementsForTour(tourId);

					if (medicalDocs.empty()) {
						medicalDocsListBox->Items->Add("Для этой страны медицинские справки не требуются");
						medicalDocsListBox->Enabled = false;
					}
					else {
						for (const auto& doc : medicalDocs) {
							medicalDocsListBox->Items->Add(gcnew String(doc.c_str()));
						}
						medicalDocsListBox->Enabled = true;
					}
					break;
				}
			}

			if (medicalDocsListBox->Items->Count == 0) {
				medicalDocsListBox->Items->Add("Тур не найден или данные не загружены");
				medicalDocsListBox->Enabled = false;
			}
		}

		void LoadComboBoxes()
		{
			clientMap = gcnew System::Collections::Generic::Dictionary<int, String^>();
			tourMap = gcnew System::Collections::Generic::Dictionary<int, String^>();

			comboBoxClient->Items->Clear();
			clientMap->Clear();

			if (clients != nullptr) {
				for (const auto& client : *clients) {
					String^ displayText = String::Format("ID: {0} - {1}",
						client.getId(),
						gcnew String(client.getInfo().getFullName().c_str()));
					comboBoxClient->Items->Add(displayText);
					clientMap->Add(client.getId(), displayText);
				}
			}

			comboBoxTour->Items->Clear();
			tourMap->Clear();

			if (tours != nullptr) {
				for (const auto& tour : *tours) {
					String^ displayText = String::Format("ID: {0} - {1} ({2})",
						tour.getId(),
						gcnew String(tour.getName().c_str()),
						gcnew String(tour.getCountry().c_str()));
					comboBoxTour->Items->Add(displayText);
					tourMap->Add(tour.getId(), displayText);
				}
			}
		}
		int GetSelectedClientId()
		{
			if (comboBoxClient->SelectedIndex == -1) return -1;

			String^ selectedText = comboBoxClient->SelectedItem->ToString();
			for each (KeyValuePair<int, String^> pair in clientMap) {
				if (pair.Value == selectedText) {
					return pair.Key;
				}
			}
			return -1;
		}

		int GetSelectedTourId()
		{
			if (comboBoxTour->SelectedIndex == -1) return -1;

			String^ selectedText = comboBoxTour->SelectedItem->ToString();
			for each (System::Collections::Generic::KeyValuePair<int, String^> pair in tourMap) {
				if (pair.Value == selectedText) {
					return pair.Key;
				}
			}
			return -1;
		}

		void SetSelectedClientById(int clientId)
		{
			if (clientMap->ContainsKey(clientId)) {
				comboBoxClient->SelectedItem = clientMap[clientId];
			}
		}

		void SetSelectedTourById(int tourId)
		{
			if (tourMap->ContainsKey(tourId)) {
				comboBoxTour->SelectedItem = tourMap[tourId];
				UpdateTourInfo(tourId);
			}
		}



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBoxTour = (gcnew System::Windows::Forms::ComboBox());
			this->comboBoxClient = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->medicalDocsListBox = (gcnew System::Windows::Forms::CheckedListBox());
			this->notesTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->bookingDatePicker = (gcnew System::Windows::Forms::DateTimePicker());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->buttonBooking = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(248)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->groupBox1->Controls->Add(this->comboBoxTour);
			this->groupBox1->Controls->Add(this->comboBoxClient);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->groupBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->groupBox1->Location = System::Drawing::Point(17, 17);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(291, 78);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Клиент и тур";
			// 
			// comboBoxTour
			// 
			this->comboBoxTour->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->comboBoxTour->FormattingEnabled = true;
			this->comboBoxTour->Location = System::Drawing::Point(86, 48);
			this->comboBoxTour->Name = L"comboBoxTour";
			this->comboBoxTour->Size = System::Drawing::Size(166, 23);
			this->comboBoxTour->TabIndex = 3;
			this->comboBoxTour->SelectedIndexChanged += gcnew System::EventHandler(this, &BookingForm::comboBoxTour_SelectedIndexChanged);
			// 
			// comboBoxClient
			// 
			this->comboBoxClient->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->comboBoxClient->FormattingEnabled = true;
			this->comboBoxClient->Location = System::Drawing::Point(86, 22);
			this->comboBoxClient->Name = L"comboBoxClient";
			this->comboBoxClient->Size = System::Drawing::Size(166, 23);
			this->comboBoxClient->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label2->Location = System::Drawing::Point(9, 50);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(50, 15);
			this->label2->TabIndex = 1;
			this->label2->Text = L"ID тура:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label1->Location = System::Drawing::Point(9, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(73, 15);
			this->label1->TabIndex = 0;
			this->label1->Text = L"ID клиента:";
			// 
			// medicalDocsListBox
			// 
			this->medicalDocsListBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->medicalDocsListBox->FormattingEnabled = true;
			this->medicalDocsListBox->Location = System::Drawing::Point(17, 121);
			this->medicalDocsListBox->Name = L"medicalDocsListBox";
			this->medicalDocsListBox->Size = System::Drawing::Size(223, 76);
			this->medicalDocsListBox->TabIndex = 1;
			// 
			// notesTextBox
			// 
			this->notesTextBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->notesTextBox->Location = System::Drawing::Point(17, 234);
			this->notesTextBox->Name = L"notesTextBox";
			this->notesTextBox->Size = System::Drawing::Size(223, 70);
			this->notesTextBox->TabIndex = 2;
			this->notesTextBox->Text = L"";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label3->Location = System::Drawing::Point(17, 217);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(85, 15);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Примечание:";
			// 
			// bookingDatePicker
			// 
			this->bookingDatePicker->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->bookingDatePicker->Location = System::Drawing::Point(103, 321);
			this->bookingDatePicker->Name = L"bookingDatePicker";
			this->bookingDatePicker->Size = System::Drawing::Size(138, 23);
			this->bookingDatePicker->TabIndex = 4;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label4->Location = System::Drawing::Point(17, 323);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(75, 15);
			this->label4->TabIndex = 5;
			this->label4->Text = L"Дата брони:";
			// 
			// buttonBooking
			// 
			this->buttonBooking->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(243)));
			this->buttonBooking->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonBooking->ForeColor = System::Drawing::Color::White;
			this->buttonBooking->Location = System::Drawing::Point(474, 539);
			this->buttonBooking->Name = L"buttonBooking";
			this->buttonBooking->Size = System::Drawing::Size(98, 47);
			this->buttonBooking->TabIndex = 32;
			this->buttonBooking->Text = L"Добавить";
			this->buttonBooking->UseVisualStyleBackColor = false;
			this->buttonBooking->Click += gcnew System::EventHandler(this, &BookingForm::buttonBooking_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->label5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(118)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->label5->Location = System::Drawing::Point(17, 104);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(59, 15);
			this->label5->TabIndex = 33;
			this->label5->Text = L"Справки:";
			// 
			// BookingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				static_cast<System::Int32>(static_cast<System::Byte>(252)));
			this->ClientSize = System::Drawing::Size(582, 596);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->buttonBooking);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->bookingDatePicker);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->notesTextBox);
			this->Controls->Add(this->medicalDocsListBox);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->Name = L"BookingForm";
			this->Text = L"Бронирование";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonBooking_Click(System::Object^ sender, System::EventArgs^ e) {
		if (comboBoxClient->SelectedItem == nullptr ||
			comboBoxTour->SelectedItem == nullptr) {
			MessageBox::Show("Заполните обязательные поля: выберите клиента и тур!",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		int clientId = GetSelectedClientId();
		int tourId = GetSelectedTourId();

		if (clientId == -1 || tourId == -1) {
			MessageBox::Show("Ошибка при получении данных клиента или тура!",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (IsBookingDuplicate(clientId, tourId))
		{
			MessageBox::Show("Этот клиент уже забронировал данный тур!\n"
				"Повторное бронирование запрещено.",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (!CheckTourAvailability(tourId)) {
			MessageBox::Show("В выбранном туре нет свободных мест!",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!AreAllMedicalRequirementsMet(tourId)) {
			MessageBox::Show(
				"Не все медицинские справки отмечены!\n"
				"Пожалуйста, подтвердите наличие всех требуемых документов.",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!ClientExists(clientId)) {
			MessageBox::Show("Клиент с ID " + clientId + " не найден!",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!TourExists(tourId)) {
			MessageBox::Show("Тур с ID " + tourId + " не найден!",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!CheckTourAvailability(tourId)) {
			MessageBox::Show("В туре с ID " + tourId + " нет свободных мест!",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		std::string notes = marshal_as<std::string>(notesTextBox->Text->Trim());
		std::string bookingDate = marshal_as<std::string>(bookingDatePicker->Value.ToString("yyyy-MM-dd"));

		try {
			std::vector<Booking> allBookings;
			if (bookings != nullptr) {
				allBookings = *bookings;
			}

			if (isEditMode) {
				bool found = false;
				for (size_t i = 0; i < allBookings.size(); ++i) {
					if (allBookings[i].getBookingId() == editingBookingId) {
						Booking updatedBooking(editingBookingId, clientId, tourId, notes);
						updatedBooking.setBookingDate(bookingDate);
						allBookings[i] = updatedBooking;
						found = true;
						break;
					}
				}

				if (!found) {
					MessageBox::Show("Бронирование для редактирования не найдено!",
						"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}
			}
			else {
				Tour::decrementAvailableSeats("Tours.csv", tourId);
				int newId = 1;
				if (!allBookings.empty()) {
					for (const auto& booking : allBookings) {
						if (booking.getBookingId() >= newId) {
							newId = booking.getBookingId() + 1;
						}
					}
				}

				Booking newBooking(newId, clientId, tourId, notes);
				newBooking.setBookingDate(bookingDate);
				allBookings.push_back(newBooking);
			}

			Booking::saveBookingsToCSV("Bookings.csv", allBookings);

			String^ message = isEditMode ? "Бронирование обновлено!" : "Бронирование создано!";
			MessageBox::Show(message, "Успех",
				MessageBoxButtons::OK, MessageBoxIcon::Information);

			this->Close();
		}
		catch (std::exception& ex) {
			MessageBox::Show("Ошибка сохранения: " + gcnew String(ex.what()),
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		catch (...) {
			MessageBox::Show("Неизвестная ошибка сохранения!",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
private: System::Void comboBoxTour_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	int tourId = GetSelectedTourId();
	UpdateTourInfo(tourId);
}
};
}
