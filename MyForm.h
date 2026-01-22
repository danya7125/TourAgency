#pragma once
#include "Client.h"
#include "Country.h"
#include "Tour.h"
#include "Booking.h"
#include <fstream>
#include <map>
#include "ClientForm.h"
#include "ToursForm.h"
#include "CountryForm.h"
#include "BookingForm.h"
namespace TourAgency {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			InitalizeClient();
			InitializeCountries();
			InitializeTours();
			InitializeBookings();

			button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);

			textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			textBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);



			clientsGrid->CellDoubleClick +=
				gcnew DataGridViewCellEventHandler(this, &MyForm::clientsGrid_CellDoubleClick);

			countriesGrid->CellDoubleClick +=
				gcnew DataGridViewCellEventHandler(this, &MyForm::countriesGrid_CellDoubleClick);

			toursGrid->CellDoubleClick +=
				gcnew DataGridViewCellEventHandler(this, &MyForm::toursGrid_CellDoubleClick);

			bookingGrid->CellDoubleClick +=
				gcnew DataGridViewCellEventHandler(this, &MyForm::bookingGrid_CellDoubleClick);

			LoadClientsToDataGrid();
			LoadCountriesToDataGrid();
			LoadToursToDataGrid();
			LoadBookingsToDataGrid();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
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

	private: System::Windows::Forms::ToolStripMenuItem^ добавитьСтрануToolStripMenuItem;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::DataGridView^ countriesGrid;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::DataGridView^ clientsGrid;
	private: System::Windows::Forms::TabControl^ TabControlCountry;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::DataGridView^ toursGrid;
	private: System::Windows::Forms::ToolStripMenuItem^ добавитьБроньToolStripMenuItem;
	private: System::Windows::Forms::TabPage^ tabPage4;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::DataGridView^ bookingGrid;
	private: System::Windows::Forms::ToolStripMenuItem^ удалениеToolStripMenuItem;

	protected:
	private:
		std::vector<Client>* clients = nullptr;
		void InitalizeClient() {
			clients = new std::vector<Client>();
		}

		std::vector<Country>* countries = nullptr;

		void InitializeCountries() {
			countries = new std::vector<Country>();
		}

		std::vector<Tour>* tours = nullptr;

		void InitializeTours() {
			tours = new std::vector<Tour>();
		}

		std::vector<Booking>* bookings = nullptr;

		void InitializeBookings() {
			bookings = new std::vector<Booking>();
		}

		void LoadClientsToDataGrid() {
			clientsGrid->Rows->Clear();
			clientsGrid->Columns->Clear();

			clientsGrid->Columns->Add("id", "ID");
			clientsGrid->Columns->Add("full_name", "ФИО");
			clientsGrid->Columns->Add("gender", "Пол");
			clientsGrid->Columns->Add("birth_date", "Дата рождения");
			clientsGrid->Columns->Add("phone_number", "Телефон");
			clientsGrid->Columns->Add("email", "Email");
			clientsGrid->Columns->Add("address", "Адрес");
			clientsGrid->Columns->Add("domestic_passport", "Внутр. паспорт");
			clientsGrid->Columns->Add("foreign_passport", "Загран. паспорт");

			clientsGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			clientsGrid->AllowUserToResizeColumns = false;
			clientsGrid->ReadOnly = true;

			clientsGrid->BackgroundColor = Color::White;
			clientsGrid->BorderStyle = BorderStyle::None;
			clientsGrid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
			clientsGrid->GridColor = Color::LightGray;

			clientsGrid->ColumnHeadersDefaultCellStyle->BackColor = Color::SteelBlue;
			clientsGrid->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
			clientsGrid->ColumnHeadersDefaultCellStyle->Font =
				gcnew Drawing::Font("Arial", 9, FontStyle::Bold);
			clientsGrid->EnableHeadersVisualStyles = false;

			clientsGrid->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(245, 250, 255);

			try {
				auto loadedClients = Client::loadClientsFromCSV("Clients.csv");
				clients->assign(loadedClients.begin(), loadedClients.end());
			}
			catch (const exception& e) {

				MessageBox::Show(
					"Не удалось открыть файл клиентов.\n\nДетали ошибки:\n" +
					gcnew String(e.what()),
					"Ошибка загрузки файла",
					MessageBoxButtons::OK,
					MessageBoxIcon::Warning
				);
			}

			for each(Client client in * clients) {
				clientsGrid->Rows->Add(
					client.getId(),
					gcnew String(client.getInfo().getFullName().c_str()),
					gcnew String(client.getInfo().gender.c_str()),
					gcnew String(client.getInfo().birth_date.c_str()),
					gcnew String(client.getInfo().phone_number.c_str()),
					gcnew String(client.getInfo().email.c_str()),
					gcnew String(client.getInfo().adress.c_str()),
					gcnew String(client.getDomesticPassport().number.c_str()),
					gcnew String(client.getForeignPassport().number.c_str())
				);
			}
		}


		void clientsGrid_CellDoubleClick(Object^ sender, DataGridViewCellEventArgs^ e) {
			if (e->RowIndex >= 0 && e->RowIndex < clients->size()) {
				Client client = clients->at(e->RowIndex);
				ShowClientDetails(client);
			}
		}

		void ShowClientDetails(const Client& client) {

			String^ details = String::Format(
				"Детальная информация о клиенте:\n\n"
				"ФИО: {0}\n"
				"Дата рождения: {1}\n"
				"Пол: {2}\n"
				"Адрес: {3}\n"
				"Телефон: {4}\n"
				"Email: {5}\n"
				"Внутренний паспорт:\n"
				"  Тип: {6}\n"
				"  Номер: {7}\n"
				"  Кем выдан: {8}\n"
				"  Дата выдачи: {9}\n\n"
				"Загранпаспорт:\n"
				"  Тип: {10}\n"
				"  Номер: {11}\n"
				"  Кем выдан: {12}\n"
				"  Дата выдачи: {13}",

				gcnew String(client.getInfo().getFullName().c_str()),
				gcnew String(client.getInfo().birth_date.c_str()),
				gcnew String(client.getInfo().gender.c_str()),
				gcnew String(client.getInfo().adress.c_str()),
				gcnew String(client.getInfo().phone_number.c_str()),
				gcnew String(client.getInfo().email.c_str()),
				gcnew String(client.getDomesticPassport().type.c_str()),
				gcnew String(client.getDomesticPassport().number.c_str()),
				gcnew String(client.getDomesticPassport().issued_by.c_str()),
				gcnew String(client.getDomesticPassport().issue_date.c_str()),
				gcnew String(client.getForeignPassport().type.c_str()),
				gcnew String(client.getForeignPassport().number.c_str()),
				gcnew String(client.getForeignPassport().issued_by.c_str()),
				gcnew String(client.getForeignPassport().issue_date.c_str())
			);

			MessageBox::Show(details, "Информация о клиенте",
				MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		void LoadToursToDataGrid() {
			toursGrid->Rows->Clear();
			toursGrid->Columns->Clear();
			toursGrid->Columns->Add("id", "ID");
			toursGrid->Columns->Add("name", "Название тура");
			toursGrid->Columns->Add("country", "Страна");
			toursGrid->Columns->Add("city", "Город");
			toursGrid->Columns->Add("hotel", "Отель");
			toursGrid->Columns->Add("hotel_category", "Категория");
			toursGrid->Columns->Add("duration", "Дней");
			toursGrid->Columns->Add("hotel_price", "Отель (руб)");
			toursGrid->Columns->Add("flight_price", "Перелет (руб)");
			toursGrid->Columns->Add("final_price", "Конечная цена");
			toursGrid->Columns->Add("all_inclusive", "All Inc");
			toursGrid->Columns->Add("season", "Сезон");
			toursGrid->Columns->Add("seats", "Места");
			toursGrid->Columns->Add("start_date", "Дата начала");
			toursGrid->Columns->Add("transfer", "Трансфер");

			toursGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			toursGrid->AllowUserToResizeColumns = false;
			toursGrid->ReadOnly = true;
			toursGrid->BackgroundColor = Color::White;
			toursGrid->BorderStyle = BorderStyle::None;
			toursGrid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
			toursGrid->GridColor = Color::LightGray;

			toursGrid->ColumnHeadersDefaultCellStyle->BackColor = Color::SteelBlue;
			toursGrid->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
			toursGrid->ColumnHeadersDefaultCellStyle->Font =
				gcnew Drawing::Font("Arial", 9, FontStyle::Bold);
			toursGrid->EnableHeadersVisualStyles = false;

			toursGrid->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(245, 250, 255);

			try {
				auto loadedTours = Tour::loadToursFromCSV("Tours.csv");
				tours->assign(loadedTours.begin(), loadedTours.end());

				auto loadedCountries = Country::loadCountriesFromCSV("Countries.csv");

				map<string, Country> countryMap;
				for (const auto& c : loadedCountries) {
					countryMap[c.getName()] = c;
				}

				for each(Tour tour in * tours) {
					string finalPriceStr = "Не рассчитано";

					auto it = countryMap.find(tour.getCountry());
					if (it != countryMap.end()) {
						finalPriceStr = tour.getFinalPriceString(it->second);
					}

					toursGrid->Rows->Add(
						tour.getId(),
						gcnew String(tour.getName().c_str()),
						gcnew String(tour.getCountry().c_str()),
						gcnew String(tour.getCity().c_str()),
						gcnew String(tour.getHotelName().c_str()),
						gcnew String(tour.getHotelCategory().c_str()),
						tour.getDuration(),
						String::Format("{0:F2}", tour.getHotelPrice() / 100.0),
						String::Format("{0:F2}", tour.getFlightPrice() / 100.0),
						gcnew String(finalPriceStr.c_str()),
						tour.isAllInclusive() ? "Да" : "Нет",
						gcnew String(tour.getSeason().c_str()),
						tour.getAvailableSeats(),
						gcnew String(tour.getStartDate().c_str()),
						tour.isTransferIncluded() ? "Да" : "Нет"
					);
				}
			}
			catch (const exception& e) {
				MessageBox::Show(
					"Не удалось открыть файл туров.\n\nДетали ошибки:\n" +
					gcnew String(e.what()),
					"Ошибка загрузки файла",
					MessageBoxButtons::OK,
					MessageBoxIcon::Warning
				);
			}
		}
		void toursGrid_CellDoubleClick(Object^ sender, DataGridViewCellEventArgs^ e) {
			if (e->RowIndex >= 0 && e->RowIndex < tours->size()) {
				Tour tour = tours->at(e->RowIndex);
				ShowTourDetails(tour);
			}
		}

		void ShowTourDetails(const Tour& tour) {

			const Country* matchedCountry = nullptr;
			for (const auto& c : *countries) {
				if (c.getName() == tour.getCountry()) {
					matchedCountry = &c;
					break;
				}
			}

			std::string desc = tour.getDescription();
			size_t pos = 0;
			while ((pos = desc.find('\n', pos)) != std::string::npos) {
				desc.replace(pos, 1, "\r\n");
				pos += 2;
			}
			String^ descriptionStr = gcnew String(desc.c_str());
			String^ finalPriceStr = "Не удалось рассчитать";
			if (matchedCountry) {
				finalPriceStr = gcnew String(tour.getFinalPriceString(*matchedCountry).c_str());
			}

			String^ details = String::Format(
				"Детальная информация о туре:\n\n"
				"ID: {0}\n"
				"Название: {1}\n"
				"Страна: {2}\n"
				"Город: {3}\n"
				"Длительность: {4} дней\n"
				"Отель: {5} ({6} руб.)\n"
				"Перелет: {7} руб.\n"
				"Конечная цена: {8}\n"
				"All Inclusive: {9}\n"
				"Сезон: {10}\n"
				"Доступные места: {11}\n"
				"Дата начала: {12}\n"
				"Трансфер: {13}\n\n"
				"Описание:\n{14}" ,

				tour.getId(),
				gcnew String(tour.getName().c_str()),
				gcnew String(tour.getCountry().c_str()),
				gcnew String(tour.getCity().c_str()),
				tour.getDuration(),
				gcnew String(tour.getHotelCategory().c_str()),
				(tour.getHotelPrice() / 100.0),
				(tour.getFlightPrice() / 100.0),
				finalPriceStr,
				tour.isAllInclusive() ? "Да" : "Нет",
				gcnew String(tour.getSeason().c_str()),
				tour.getAvailableSeats(),
				gcnew String(tour.getStartDate().c_str()),
				tour.isTransferIncluded() ? "Включен" : "Не включен",
				descriptionStr
			);

			MessageBox::Show(details, "Информация о туре",
				MessageBoxButtons::OK, MessageBoxIcon::Information);
		}


		void LoadCountriesToDataGrid()
		{
			countriesGrid->Rows->Clear();
			countriesGrid->Columns->Clear();

			countriesGrid->Columns->Add("name", "Страна");
			countriesGrid->Columns->Add("risk", "Риск (%)");
			countriesGrid->Columns->Add("visa", "Виза");
			countriesGrid->Columns->Add("visa_cost", "Стоимость визы");
			countriesGrid->Columns->Add("insurance", "Страховка");
			countriesGrid->Columns->Add("med", "Мед. справки");

			countriesGrid->AutoSizeColumnsMode =
				DataGridViewAutoSizeColumnsMode::Fill;
			countriesGrid->ReadOnly = true;

			countriesGrid->BackgroundColor = Color::White;
			countriesGrid->BorderStyle = BorderStyle::None;
			countriesGrid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
			countriesGrid->GridColor = Color::LightGray;

			countriesGrid->ColumnHeadersDefaultCellStyle->BackColor = Color::SteelBlue;
			countriesGrid->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
			countriesGrid->ColumnHeadersDefaultCellStyle->Font =
				gcnew Drawing::Font("Arial", 9, FontStyle::Bold);
			countriesGrid->EnableHeadersVisualStyles = false;

			countriesGrid->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(245, 250, 255);

			try {
				auto loaded = Country::loadCountriesFromCSV("Countries.csv");
				countries->assign(loaded.begin(), loaded.end());
			}
			catch (const std::exception& e) {
				MessageBox::Show(
					"Ошибка загрузки стран:\n" + gcnew String(e.what()),
					"CSV ошибка",
					MessageBoxButtons::OK,
					MessageBoxIcon::Warning
				);
				return;
			}

			for each (Country c in *countries)
			{
				countriesGrid->Rows->Add(
					gcnew String(c.getName().c_str()),
					c.getRiskFactor() / 100.0,
					c.isVisaRequired() ? "Да" : "Нет",
					c.getVisaCost() / 100.0,
					c.getInsuranceCost() / 100.0,
					gcnew String(joinMedicalCerts(c).c_str())
				);
			}
		}

		void LoadBookingsToDataGrid() {
			bookingGrid->Rows->Clear();
			bookingGrid->Columns->Clear();

			bookingGrid->Columns->Add("booking_id", "ID брони");
			bookingGrid->Columns->Add("client_name", "Клиент");
			bookingGrid->Columns->Add("tour_name", "Тур");
			bookingGrid->Columns->Add("booking_date", "Дата брони");
			bookingGrid->Columns->Add("notes", "Примечания");

			bookingGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			bookingGrid->AllowUserToResizeColumns = false;
			bookingGrid->ReadOnly = true;
			bookingGrid->BackgroundColor = Color::White;
			bookingGrid->BorderStyle = BorderStyle::None;
			bookingGrid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
			bookingGrid->GridColor = Color::LightGray;

			bookingGrid->ColumnHeadersDefaultCellStyle->BackColor = Color::SteelBlue;
			bookingGrid->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
			bookingGrid->ColumnHeadersDefaultCellStyle->Font =
				gcnew Drawing::Font("Arial", 9, FontStyle::Bold);
			bookingGrid->EnableHeadersVisualStyles = false;

			bookingGrid->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(245, 250, 255);

			try {
				auto loadedBookings = Booking::loadBookingsFromCSV("Bookings.csv");
				if (bookings != nullptr) {
					bookings->assign(loadedBookings.begin(), loadedBookings.end());
				}

				auto loadedClients = Client::loadClientsFromCSV("Clients.csv");
				auto loadedTours = Tour::loadToursFromCSV("Tours.csv");

				System::Collections::Generic::Dictionary<int, String^>^ clientDict =
					gcnew System::Collections::Generic::Dictionary<int, String^>();
				System::Collections::Generic::Dictionary<int, String^>^ tourDict =
					gcnew System::Collections::Generic::Dictionary<int, String^>();

				for each (Client client in loadedClients) {
					clientDict->Add(client.getId(), gcnew String(client.getInfo().getFullName().c_str()));
				}

				for each (Tour tour in loadedTours) {
					tourDict->Add(tour.getId(), gcnew String(tour.getName().c_str()));
				}

				for each (Booking booking in loadedBookings) {
					// Получаем имя клиента
					String^ clientName = "Неизвестный клиент";
					if (clientDict->ContainsKey(booking.getClientId())) {
						clientName = clientDict[booking.getClientId()];
					}

					String^ tourName = "Неизвестный тур";
					if (tourDict->ContainsKey(booking.getTourId())) {
						tourName = tourDict[booking.getTourId()];
					}

					bookingGrid->Rows->Add(
						booking.getBookingId(),
						clientName,
						tourName,
						gcnew String(booking.getBookingDate().c_str()),
						gcnew String(booking.getNotes().c_str())
					);
				}
			}
			catch (const exception& e) {
				MessageBox::Show(
					"Не удалось загрузить бронирования.\n\nДетали ошибки:\n" +
					gcnew String(e.what()),
					"Ошибка загрузки",
					MessageBoxButtons::OK,
					MessageBoxIcon::Warning
				);
			}
		}

		void ShowBookingDetails(const Booking& booking) {
			String^ details = String::Format(
				"Детальная информация о бронировании:\n\n"
				"ID брони: {0}\n"
				"ID клиента: {1}\n"
				"ID тура: {2}\n"
				"Дата бронирования: {3}\n"
				"Примечания: {4}",
				booking.getBookingId(),
				booking.getClientId(),
				booking.getTourId(),
				gcnew String(booking.getBookingDate().c_str()),
				gcnew String(booking.getNotes().c_str())
			);

			MessageBox::Show(details, "Информация о бронировании",
				MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

private: System::Void bookingGrid_CellDoubleClick(System::Object^ sender, DataGridViewCellEventArgs^ e) {
	if (e->RowIndex >= 0 && e->RowIndex < bookings->size()) {
		Booking booking = bookings->at(e->RowIndex);
		ShowBookingDetails(booking);
	}
}



		string joinMedicalCerts(const Country& c)
		{
			std::string res;
			const auto& certs = c.getMedicalCerts();

			for (size_t i = 0; i < certs.size(); ++i) {
				res += certs[i];
				if (i + 1 < certs.size())
					res += "; ";
			}
			return res;
		}

		void countriesGrid_CellDoubleClick(
			Object^ sender,
			DataGridViewCellEventArgs^ e)
		{
			if (e->RowIndex >= 0 && e->RowIndex < countries->size()) {
				ShowCountryDetails(countries->at(e->RowIndex));
			}
		}

		void ShowCountryDetails(const Country& c)
		{
			String^ info = String::Format(
				"Страна: {0}\n"
				"Риск: {1}%\n"
				"Виза требуется: {2}\n"
				"Стоимость визы: {3} ₽\n"
				"Страховка: {4} ₽\n"
				"Медицинские справки:\n{5}",

				gcnew String(c.getName().c_str()),
				c.getRiskFactor() / 100.0,
				c.isVisaRequired() ? "Да" : "Нет",
				c.getVisaCost() / 100.0,
				c.getInsuranceCost() / 100.0,
				gcnew String(joinMedicalCerts(c).c_str())
			);

			MessageBox::Show(
				info,
				"Информация о стране",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
		}
		void FilterClients()
		{
			String^ searchText = textBox1->Text->Trim()->ToLower();

			clientsGrid->Rows->Clear();

			if (String::IsNullOrEmpty(searchText))
			{
				for each (Client client in *clients) {
					clientsGrid->Rows->Add(
						client.getId(),
						gcnew String(client.getInfo().getFullName().c_str()),
						gcnew String(client.getInfo().gender.c_str()),
						gcnew String(client.getInfo().birth_date.c_str()),
						gcnew String(client.getInfo().phone_number.c_str()),
						gcnew String(client.getInfo().email.c_str()),
						gcnew String(client.getInfo().adress.c_str()),
						gcnew String(client.getDomesticPassport().number.c_str()),
						gcnew String(client.getForeignPassport().number.c_str())
					);
				}
				return;
			}

			for each (Client client in *clients) {
				String^ fullName = (gcnew String(client.getInfo().getFullName().c_str()))->ToLower();
				String^ phone = (gcnew String(client.getInfo().phone_number.c_str()))->ToLower();
				String^ email = (gcnew String(client.getInfo().email.c_str()))->ToLower();
				String^ address = (gcnew String(client.getInfo().adress.c_str()))->ToLower();

				if (fullName->Contains(searchText) ||
					phone->Contains(searchText) ||
					email->Contains(searchText) ||
					address->Contains(searchText))
				{
					clientsGrid->Rows->Add(
						client.getId(),
						gcnew String(client.getInfo().getFullName().c_str()),
						gcnew String(client.getInfo().gender.c_str()),
						gcnew String(client.getInfo().birth_date.c_str()),
						gcnew String(client.getInfo().phone_number.c_str()),
						gcnew String(client.getInfo().email.c_str()),
						gcnew String(client.getInfo().adress.c_str()),
						gcnew String(client.getDomesticPassport().number.c_str()),
						gcnew String(client.getForeignPassport().number.c_str())
					);
				}
			}

			if (clientsGrid->Rows->Count == 0 && !String::IsNullOrEmpty(searchText))
			{
				MessageBox::Show("Клиенты по запросу \"" + searchText + "\" не найдены.",
					"Результаты поиска", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}

		void FilterTours()
		{
			String^ searchText = textBox2->Text->Trim()->ToLower();

			toursGrid->Rows->Clear();

			if (String::IsNullOrEmpty(searchText))
			{
				try {
					auto loadedTours = Tour::loadToursFromCSV("Tours.csv");
					auto loadedCountries = Country::loadCountriesFromCSV("Countries.csv");

					map<string, Country> countryMap;
					for (const auto& c : loadedCountries) {
						countryMap[c.getName()] = c;
					}

					for each (Tour tour in loadedTours) {
						string finalPriceStr = "Не рассчитано";
						auto it = countryMap.find(tour.getCountry());
						if (it != countryMap.end()) {
							finalPriceStr = tour.getFinalPriceString(it->second);
						}

						toursGrid->Rows->Add(
							tour.getId(),
							gcnew String(tour.getName().c_str()),
							gcnew String(tour.getCountry().c_str()),
							gcnew String(tour.getCity().c_str()),
							gcnew String(tour.getHotelName().c_str()),
							gcnew String(tour.getHotelCategory().c_str()),
							tour.getDuration(),
							String::Format("{0:F2}", tour.getHotelPrice() / 100.0),
							String::Format("{0:F2}", tour.getFlightPrice() / 100.0),
							gcnew String(finalPriceStr.c_str()),
							tour.isAllInclusive() ? "Да" : "Нет",
							gcnew String(tour.getSeason().c_str()),
							tour.getAvailableSeats(),
							gcnew String(tour.getStartDate().c_str()),
							tour.isTransferIncluded() ? "Да" : "Нет"
						);
					}
				}
				catch (const exception& e) {
				}
				return;
			}

			try {
				auto loadedTours = Tour::loadToursFromCSV("Tours.csv");
				auto loadedCountries = Country::loadCountriesFromCSV("Countries.csv");

				map<string, Country> countryMap;
				for (const auto& c : loadedCountries) {
					countryMap[c.getName()] = c;
				}

				for each (Tour tour in loadedTours) {
					String^ name = (gcnew String(tour.getName().c_str()))->ToLower();
					String^ country = (gcnew String(tour.getCountry().c_str()))->ToLower();
					String^ city = (gcnew String(tour.getCity().c_str()))->ToLower();
					String^ hotel = (gcnew String(tour.getHotelName().c_str()))->ToLower();
					String^ season = (gcnew String(tour.getSeason().c_str()))->ToLower();

					if (name->Contains(searchText) ||
						country->Contains(searchText) ||
						city->Contains(searchText) ||
						hotel->Contains(searchText) ||
						season->Contains(searchText))
					{
						string finalPriceStr = "Не рассчитано";
						auto it = countryMap.find(tour.getCountry());
						if (it != countryMap.end()) {
							finalPriceStr = tour.getFinalPriceString(it->second);
						}

						toursGrid->Rows->Add(
							tour.getId(),
							gcnew String(tour.getName().c_str()),
							gcnew String(tour.getCountry().c_str()),
							gcnew String(tour.getCity().c_str()),
							gcnew String(tour.getHotelName().c_str()),
							gcnew String(tour.getHotelCategory().c_str()),
							tour.getDuration(),
							String::Format("{0:F2}", tour.getHotelPrice() / 100.0),
							String::Format("{0:F2}", tour.getFlightPrice() / 100.0),
							gcnew String(finalPriceStr.c_str()),
							tour.isAllInclusive() ? "Да" : "Нет",
							gcnew String(tour.getSeason().c_str()),
							tour.getAvailableSeats(),
							gcnew String(tour.getStartDate().c_str()),
							tour.isTransferIncluded() ? "Да" : "Нет"
						);
					}
				}

				if (toursGrid->Rows->Count == 0 && !String::IsNullOrEmpty(searchText))
				{
					MessageBox::Show("Туры по запросу \"" + searchText + "\" не найдены.",
						"Результаты поиска", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
			catch (const exception& e) {
			}
		}

		void FilterCountries()
		{
			String^ searchText = textBox3->Text->Trim()->ToLower();

			countriesGrid->Rows->Clear();

			if (String::IsNullOrEmpty(searchText))
			{
				try {
					auto loaded = Country::loadCountriesFromCSV("Countries.csv");
					for each (Country c in loaded)
					{
						countriesGrid->Rows->Add(
							gcnew String(c.getName().c_str()),
							c.getRiskFactor() / 100.0,
							c.isVisaRequired() ? "Да" : "Нет",
							c.getVisaCost() / 100.0,
							c.getInsuranceCost() / 100.0,
							gcnew String(joinMedicalCerts(c).c_str())
						);
					}
				}
				catch (const std::exception& e) {
				}
				return;
			}

			try {
				auto loaded = Country::loadCountriesFromCSV("Countries.csv");
				for each (Country c in loaded)
				{
					String^ name = (gcnew String(c.getName().c_str()))->ToLower();

					if (name->Contains(searchText))
					{
						countriesGrid->Rows->Add(
							gcnew String(c.getName().c_str()),
							c.getRiskFactor() / 100.0,
							c.isVisaRequired() ? "Да" : "Нет",
							c.getVisaCost() / 100.0,
							c.getInsuranceCost() / 100.0,
							gcnew String(joinMedicalCerts(c).c_str())
						);
					}
				}

				if (countriesGrid->Rows->Count == 0 && !String::IsNullOrEmpty(searchText))
				{
					MessageBox::Show("Страны по запросу \"" + searchText + "\" не найдены.",
						"Результаты поиска", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
			catch (const std::exception& e) {
			}
		}
		void FilterBookings()
		{
			String^ searchText = textBox4->Text->Trim()->ToLower();
			bookingGrid->Rows->Clear();

			if (String::IsNullOrEmpty(searchText))
			{
				for each(Booking booking in * bookings)
				{
					String^ clientName = "Неизвестный клиент";
					for each(Client client in * clients)
					{
						if (client.getId() == booking.getClientId())
						{
							clientName = gcnew String(client.getInfo().getFullName().c_str());
							break;
						}
					}

					String^ tourName = "Неизвестный тур";
					for each(Tour tour in * tours)
					{
						if (tour.getId() == booking.getTourId())
						{
							tourName = gcnew String(tour.getName().c_str());
							break;
						}
					}

					bookingGrid->Rows->Add(
						booking.getBookingId(),
						clientName,
						tourName,
						gcnew String(booking.getBookingDate().c_str()),
						gcnew String(booking.getNotes().c_str())
					);
				}
				return;
			}

			bool found = false;

			for each(Booking booking in * bookings)
			{
				String^ clientName = "";
				for each(Client client in * clients)
				{
					if (client.getId() == booking.getClientId())
					{
						clientName = gcnew String(client.getInfo().getFullName().c_str());
						break;
					}
				}

				String^ tourName = "";
				for each(Tour tour in * tours)
				{
					if (tour.getId() == booking.getTourId())
					{
						tourName = gcnew String(tour.getName().c_str());
						break;
					}
				}

				String^ clientLower = clientName->ToLower();
				String^ tourLower = tourName->ToLower();
				String^ notesLower = (gcnew String(booking.getNotes().c_str()))->ToLower();
				String^ bookingIdStr = booking.getBookingId().ToString()->ToLower();
				String^ clientIdStr = booking.getClientId().ToString()->ToLower();
				String^ tourIdStr = booking.getTourId().ToString()->ToLower();

				if (clientLower->Contains(searchText) ||
					tourLower->Contains(searchText) ||
					notesLower->Contains(searchText) ||
					bookingIdStr->Contains(searchText) ||
					clientIdStr->Contains(searchText) ||
					tourIdStr->Contains(searchText))
				{
					bookingGrid->Rows->Add(
						booking.getBookingId(),
						clientName,
						tourName,
						gcnew String(booking.getBookingDate().c_str()),
						gcnew String(booking.getNotes().c_str())
					);
					found = true;
				}
			}

			if (!found)
			{
				MessageBox::Show("Бронирования по запросу \"" + searchText + "\" не найдены.",
					"Результаты поиска", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	protected:
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ правкаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ новыйКлиентToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ новыйТурToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ выходToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ изменитьДанныеToolStripMenuItem;
	private: System::ComponentModel::IContainer^ components;
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->новыйКлиентToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->новыйТурToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->добавитьСтрануToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->добавитьБроньToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выходToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->правкаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->изменитьДанныеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->countriesGrid = (gcnew System::Windows::Forms::DataGridView());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->clientsGrid = (gcnew System::Windows::Forms::DataGridView());
			this->TabControlCountry = (gcnew System::Windows::Forms::TabControl());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->toursGrid = (gcnew System::Windows::Forms::DataGridView());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->bookingGrid = (gcnew System::Windows::Forms::DataGridView());
			this->удалениеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->countriesGrid))->BeginInit();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->clientsGrid))->BeginInit();
			this->TabControlCountry->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->toursGrid))->BeginInit();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bookingGrid))->BeginInit();
			this->SuspendLayout();
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::Color::SteelBlue;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->файлToolStripMenuItem,
					this->правкаToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(668, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &MyForm::menuStrip1_ItemClicked);
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->новыйКлиентToolStripMenuItem,
					this->новыйТурToolStripMenuItem, this->добавитьСтрануToolStripMenuItem, this->добавитьБроньToolStripMenuItem, this->выходToolStripMenuItem
			});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->файлToolStripMenuItem->Text = L"Файл";
			this->файлToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::файлToolStripMenuItem_Click);
			// 
			// новыйКлиентToolStripMenuItem
			// 
			this->новыйКлиентToolStripMenuItem->Name = L"новыйКлиентToolStripMenuItem";
			this->новыйКлиентToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->новыйКлиентToolStripMenuItem->Text = L"Новый клиент";
			this->новыйКлиентToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::новыйКлиентToolStripMenuItem_Click);
			// 
			// новыйТурToolStripMenuItem
			// 
			this->новыйТурToolStripMenuItem->Name = L"новыйТурToolStripMenuItem";
			this->новыйТурToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->новыйТурToolStripMenuItem->Text = L"Новый тур";
			this->новыйТурToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::новыйТурToolStripMenuItem_Click);
			// 
			// добавитьСтрануToolStripMenuItem
			// 
			this->добавитьСтрануToolStripMenuItem->Name = L"добавитьСтрануToolStripMenuItem";
			this->добавитьСтрануToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->добавитьСтрануToolStripMenuItem->Text = L"Добавить страну";
			this->добавитьСтрануToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::добавитьСтрануToolStripMenuItem_Click);
			// 
			// добавитьБроньToolStripMenuItem
			// 
			this->добавитьБроньToolStripMenuItem->Name = L"добавитьБроньToolStripMenuItem";
			this->добавитьБроньToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->добавитьБроньToolStripMenuItem->Text = L"Добавить бронь";
			this->добавитьБроньToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::добавитьБроньToolStripMenuItem_Click);
			// 
			// выходToolStripMenuItem
			// 
			this->выходToolStripMenuItem->Name = L"выходToolStripMenuItem";
			this->выходToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->выходToolStripMenuItem->Text = L"Выход";
			// 
			// правкаToolStripMenuItem
			// 
			this->правкаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->изменитьДанныеToolStripMenuItem,
					this->удалениеToolStripMenuItem
			});
			this->правкаToolStripMenuItem->Name = L"правкаToolStripMenuItem";
			this->правкаToolStripMenuItem->Size = System::Drawing::Size(59, 20);
			this->правкаToolStripMenuItem->Text = L"Правка";
			// 
			// изменитьДанныеToolStripMenuItem
			// 
			this->изменитьДанныеToolStripMenuItem->Name = L"изменитьДанныеToolStripMenuItem";
			this->изменитьДанныеToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->изменитьДанныеToolStripMenuItem->Text = L"Изменить данные";
			this->изменитьДанныеToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::изменитьДанныеToolStripMenuItem_Click);
			// 
			// tabPage3
			// 
			this->tabPage3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(248)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->tabPage3->Controls->Add(this->label2);
			this->tabPage3->Controls->Add(this->button3);
			this->tabPage3->Controls->Add(this->label3);
			this->tabPage3->Controls->Add(this->textBox3);
			this->tabPage3->Controls->Add(this->countriesGrid);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(660, 463);
			this->tabPage3->TabIndex = 3;
			this->tabPage3->Text = L"Страны";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->label2->Location = System::Drawing::Point(12, 12);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(97, 17);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Поиск страны";
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->button3->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->button3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->button3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->button3->ForeColor = System::Drawing::Color::White;
			this->button3->Location = System::Drawing::Point(268, 32);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(90, 25);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Найти";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->label3->Location = System::Drawing::Point(12, 12);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 17);
			this->label3->TabIndex = 2;
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::White;
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F));
			this->textBox3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox3->Location = System::Drawing::Point(12, 32);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(250, 25);
			this->textBox3->TabIndex = 1;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			// 
			// countriesGrid
			// 
			this->countriesGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->countriesGrid->BackgroundColor = System::Drawing::Color::White;
			this->countriesGrid->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
			this->countriesGrid->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->countriesGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->countriesGrid->Location = System::Drawing::Point(12, 70);
			this->countriesGrid->Name = L"countriesGrid";
			this->countriesGrid->RowHeadersVisible = false;
			this->countriesGrid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->countriesGrid->Size = System::Drawing::Size(636, 381);
			this->countriesGrid->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(248)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Controls->Add(this->clientsGrid);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(660, 463);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Клиенты";
			this->tabPage1->Click += gcnew System::EventHandler(this, &MyForm::tabPage1_Click_1);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->label4->Location = System::Drawing::Point(12, 12);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(102, 17);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Поиск клиента";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(268, 32);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(90, 25);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Найти";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->label1->Location = System::Drawing::Point(12, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 17);
			this->label1->TabIndex = 2;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::White;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F));
			this->textBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox1->Location = System::Drawing::Point(12, 32);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(250, 25);
			this->textBox1->TabIndex = 1;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// clientsGrid
			// 
			this->clientsGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->clientsGrid->BackgroundColor = System::Drawing::Color::White;
			this->clientsGrid->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
			this->clientsGrid->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->clientsGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->clientsGrid->Location = System::Drawing::Point(12, 70);
			this->clientsGrid->Name = L"clientsGrid";
			this->clientsGrid->RowHeadersVisible = false;
			this->clientsGrid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->clientsGrid->Size = System::Drawing::Size(636, 381);
			this->clientsGrid->TabIndex = 0;
			// 
			// TabControlCountry
			// 
			this->TabControlCountry->Controls->Add(this->tabPage1);
			this->TabControlCountry->Controls->Add(this->tabPage2);
			this->TabControlCountry->Controls->Add(this->tabPage3);
			this->TabControlCountry->Controls->Add(this->tabPage4);
			this->TabControlCountry->Dock = System::Windows::Forms::DockStyle::Fill;
			this->TabControlCountry->Location = System::Drawing::Point(0, 24);
			this->TabControlCountry->Name = L"TabControlCountry";
			this->TabControlCountry->SelectedIndex = 0;
			this->TabControlCountry->Size = System::Drawing::Size(668, 489);
			this->TabControlCountry->TabIndex = 2;
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(248)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->tabPage2->Controls->Add(this->label5);
			this->tabPage2->Controls->Add(this->button2);
			this->tabPage2->Controls->Add(this->label6);
			this->tabPage2->Controls->Add(this->textBox2);
			this->tabPage2->Controls->Add(this->toursGrid);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(660, 463);
			this->tabPage2->TabIndex = 4;
			this->tabPage2->Text = L"Туры";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->label5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->label5->Location = System::Drawing::Point(12, 12);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(79, 17);
			this->label5->TabIndex = 5;
			this->label5->Text = L"Поиск тура";
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->button2->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->button2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->button2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Location = System::Drawing::Point(268, 32);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(90, 25);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Найти";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->label6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->label6->Location = System::Drawing::Point(12, 12);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(0, 17);
			this->label6->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::White;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F));
			this->textBox2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox2->Location = System::Drawing::Point(12, 32);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(250, 25);
			this->textBox2->TabIndex = 1;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			// 
			// toursGrid
			// 
			this->toursGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->toursGrid->BackgroundColor = System::Drawing::Color::White;
			this->toursGrid->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
			this->toursGrid->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->toursGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->toursGrid->Location = System::Drawing::Point(12, 70);
			this->toursGrid->Name = L"toursGrid";
			this->toursGrid->RowHeadersVisible = false;
			this->toursGrid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->toursGrid->Size = System::Drawing::Size(636, 381);
			this->toursGrid->TabIndex = 0;
			// 
			// tabPage4
			// 
			this->tabPage4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(248)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->tabPage4->Controls->Add(this->label7);
			this->tabPage4->Controls->Add(this->button4);
			this->tabPage4->Controls->Add(this->label8);
			this->tabPage4->Controls->Add(this->textBox4);
			this->tabPage4->Controls->Add(this->bookingGrid);
			this->tabPage4->Cursor = System::Windows::Forms::Cursors::Default;
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(660, 463);
			this->tabPage4->TabIndex = 5;
			this->tabPage4->Text = L"Бронирование";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->label7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->label7->Location = System::Drawing::Point(12, 12);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(91, 17);
			this->label7->TabIndex = 4;
			this->label7->Text = L"Поиск брони";
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->button4->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->button4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->button4->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->button4->ForeColor = System::Drawing::Color::White;
			this->button4->Location = System::Drawing::Point(268, 32);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(90, 25);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Найти";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->label8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->label8->Location = System::Drawing::Point(12, 12);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(0, 17);
			this->label8->TabIndex = 2;
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::Color::White;
			this->textBox4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F));
			this->textBox4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox4->Location = System::Drawing::Point(12, 32);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(250, 25);
			this->textBox4->TabIndex = 1;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox4_TextChanged);
			// 
			// bookingGrid
			// 
			this->bookingGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->bookingGrid->BackgroundColor = System::Drawing::Color::White;
			this->bookingGrid->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
			this->bookingGrid->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->bookingGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->bookingGrid->Location = System::Drawing::Point(12, 70);
			this->bookingGrid->Name = L"bookingGrid";
			this->bookingGrid->RowHeadersVisible = false;
			this->bookingGrid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->bookingGrid->Size = System::Drawing::Size(636, 381);
			this->bookingGrid->TabIndex = 0;
			// 
			// удалениеToolStripMenuItem
			// 
			this->удалениеToolStripMenuItem->Name = L"удалениеToolStripMenuItem";
			this->удалениеToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->удалениеToolStripMenuItem->Text = L"Удаление";
			this->удалениеToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::удалениеToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(668, 513);
			this->Controls->Add(this->TabControlCountry);
			this->Controls->Add(this->menuStrip1);
			this->Name = L"MyForm";
			this->Text = L"Туристическое агенство";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->countriesGrid))->EndInit();
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->clientsGrid))->EndInit();
			this->TabControlCountry->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->toursGrid))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bookingGrid))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tabPage1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void menuStrip1_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
	}
	private: System::Void файлToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void изменитьДанныеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		TabPage^ currentTab = TabControlCountry->SelectedTab;

		if (currentTab == tabPage1) {
			if (clientsGrid->SelectedRows->Count > 0) {
				int index = clientsGrid->SelectedRows[0]->Index;
				if (index >= 0 && index < clients->size()) {
					Client& clientToEdit = clients->at(index);

					ClientForm^ editForm = gcnew ClientForm(clientToEdit);
					editForm->ShowDialog();

					LoadClientsToDataGrid();
				}
			}
			else {
				MessageBox::Show("Пожалуйста, выберите клиента для редактирования.",
					"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
		else if (currentTab == tabPage3) {
			if (countriesGrid->SelectedRows->Count > 0) {
				int index = countriesGrid->SelectedRows[0]->Index;
				if (index >= 0 && index < countries->size()) {
					Country& countryToEdit = countries->at(index);

					CountryForm^ editForm = gcnew CountryForm(countryToEdit);
					editForm->ShowDialog();

					LoadCountriesToDataGrid();
				}
			}
			else {
				MessageBox::Show("Пожалуйста, выберите страну для редактирования.",
					"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
		else if (currentTab == tabPage2) {
			if (toursGrid->SelectedRows->Count > 0) {
				int index = toursGrid->SelectedRows[0]->Index;
				if (index >= 0 && index < tours->size()) {
					Tour& tourToEdit = tours->at(index);

					ToursForm^ editForm = gcnew ToursForm(tourToEdit);
					editForm->ShowDialog();

					LoadToursToDataGrid();
				}
			}
			else {
				MessageBox::Show("Пожалуйста, выберите тур для редактирования.",
					"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
		else if (currentTab == tabPage4) {
			if (bookingGrid->SelectedRows->Count > 0) {
				int index = bookingGrid->SelectedRows[0]->Index;
				if (index >= 0 && index < bookings->size()) {
					Booking& bookingToEdit = bookings->at(index);

					BookingForm^ editForm = gcnew BookingForm(bookingToEdit);
					editForm->ShowDialog();
					LoadBookingsToDataGrid();
				}
			}
			else {
				MessageBox::Show("Пожалуйста, выберите бронирование для редактирования.",
					"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
		else {
			// Для других вкладок (если есть) редактирование не реализовано
			MessageBox::Show("Редактирование недоступно для этой вкладки.",
				"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		
	}
	private: System::Void новыйКлиентToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

		ClientForm^ cf = gcnew ClientForm();
		cf->ShowDialog();
		LoadClientsToDataGrid();
	}
	private: System::Void добавитьСтрануToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		CountryForm^ cf = gcnew CountryForm();
		cf->ShowDialog();
		LoadCountriesToDataGrid();
	}

private: System::Void новыйТурToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	ToursForm^ tf = gcnew ToursForm();
	tf->ShowDialog();
	LoadToursToDataGrid();
}
private: System::Void добавитьБроньToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	BookingForm^ bf = gcnew BookingForm();
	bf->ShowDialog();
	LoadToursToDataGrid();
	LoadBookingsToDataGrid();
}
private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	FilterTours();
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	FilterClients();
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	FilterCountries();
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	FilterBookings();
}
private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tabPage1_Click_1(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void удалениеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	TabPage^ currentTab = TabControlCountry->SelectedTab;

	if (currentTab == tabPage1) {
		if (clientsGrid->SelectedRows->Count > 0) {
			int index = clientsGrid->SelectedRows[0]->Index;
			if (index >= 0 && index < static_cast<int>(clients->size())) {
				System::Windows::Forms::DialogResult result = MessageBox::Show(
					"Вы уверены, что хотите удалить выбранного клиента?",
					"Подтверждение удаления",
					MessageBoxButtons::YesNo,
					MessageBoxIcon::Question
				);

				if (result == System::Windows::Forms::DialogResult::Yes) {
					clients->erase(clients->begin() + index);
					try {
						Client::saveClientsToCSV("Clients.csv", *clients);
						LoadClientsToDataGrid();
						MessageBox::Show("Клиент успешно удалён.",
							"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					catch (System::Exception^ ex) {
						MessageBox::Show("Ошибка при сохранении: " + ex->Message,
							"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}
		}
		else {
			MessageBox::Show("Пожалуйста, выберите клиента для удаления.",
				"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		}
	}
	else if (currentTab == tabPage3) {
		if (countriesGrid->SelectedRows->Count > 0) {
			int index = countriesGrid->SelectedRows[0]->Index;
			if (index >= 0 && index < static_cast<int>(countries->size())) {
				System::Windows::Forms::DialogResult result = MessageBox::Show(
					"Вы уверены, что хотите удалить выбранную страну?\n" +
					"Это может повлиять на расчёт цен туров!",
					"Подтверждение удаления",
					MessageBoxButtons::YesNo,
					MessageBoxIcon::Warning
				);

				if (result == System::Windows::Forms::DialogResult::Yes) {
					countries->erase(countries->begin() + index);
					try {
						Country::saveCountriesToCSV("Countries.csv", *countries);
						LoadCountriesToDataGrid();
						MessageBox::Show("Страна успешно удалена.",
							"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					catch (System::Exception^ ex) {
						MessageBox::Show("Ошибка при сохранении: " + ex->Message,
							"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}
		}
		else {
			MessageBox::Show("Пожалуйста, выберите страну для удаления.",
				"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		}
	}
	else if (currentTab == tabPage2) {
		if (toursGrid->SelectedRows->Count > 0) {
			int index = toursGrid->SelectedRows[0]->Index;
			if (index >= 0 && index < static_cast<int>(tours->size())) {
				System::Windows::Forms::DialogResult result = MessageBox::Show(
					"Вы уверены, что хотите удалить выбранный тур?",
					"Подтверждение удаления",
					MessageBoxButtons::YesNo,
					MessageBoxIcon::Question
				);

				if (result == System::Windows::Forms::DialogResult::Yes) {
					tours->erase(tours->begin() + index);
					try {
						Tour::saveToursToCSV("Tours.csv", *tours);
						LoadToursToDataGrid();
						MessageBox::Show("Тур успешно удалён.",
							"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					catch (System::Exception^ ex) {
						MessageBox::Show("Ошибка при сохранении: " + ex->Message,
							"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}
		}
		else {
			MessageBox::Show("Пожалуйста, выберите тур для удаления.",
				"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		}
	}
	else if (currentTab == tabPage4) {
		if (bookingGrid->SelectedRows->Count > 0) {
			int index = bookingGrid->SelectedRows[0]->Index;
			if (index >= 0 && index < static_cast<int>(bookings->size())) {
				System::Windows::Forms::DialogResult result = MessageBox::Show(
					"Вы уверены, что хотите удалить выбранное бронирование?",
					"Подтверждение удаления",
					MessageBoxButtons::YesNo,
					MessageBoxIcon::Question
				);

				if (result == System::Windows::Forms::DialogResult::Yes) {
					bookings->erase(bookings->begin() + index);
					try {
						Booking::saveBookingsToCSV("Bookings.csv", *bookings);
						LoadBookingsToDataGrid();
						MessageBox::Show("Бронирование успешно удалено.",
							"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					catch (System::Exception^ ex) {
						MessageBox::Show("Ошибка при сохранении: " + ex->Message,
							"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}
		}
		else {
			MessageBox::Show("Пожалуйста, выберите бронирование для удаления.",
				"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		}
	}
	else {
		MessageBox::Show("Удаление недоступно для этой вкладки.",
			"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}
};
}