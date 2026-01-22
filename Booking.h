// Booking.h
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

class Booking {
private:
    int booking_id;
    int client_id;
    int tour_id;
    string booking_date;
    string notes;

public:
    Booking() = default;

    Booking(int booking_id, int client_id, int tour_id, const string& notes = "")
        : booking_id(booking_id), client_id(client_id), tour_id(tour_id), notes(notes) {
    }

    int getBookingId() const { return booking_id; }
    int getClientId() const { return client_id; }
    int getTourId() const { return tour_id; }
    string getBookingDate() const { return booking_date; }
    string getNotes() const { return notes; }
    void setBookingDate(const string& date) { booking_date = date; }
    void setNotes(const string& notes_) { notes = notes_; }

    static std::string escapeCSVField(const std::string& field) {
        if (field.find(',') != std::string::npos ||
            field.find('"') != std::string::npos ||
            field.find('\n') != std::string::npos ||
            field.find('\r') != std::string::npos) {

            std::string escaped = "\"";
            for (char c : field) {
                if (c == '"') {
                    escaped += "\"\"";
                }
                else {
                    escaped += c;
                }
            }
            escaped += "\"";
            return escaped;
        }
        return field;
    }

    static std::vector<Booking> loadBookingsFromCSV(const std::string& filename) {
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            throw std::runtime_error("Не удалось открыть файл CSV бронирований");
        }

        std::vector<Booking> bookings;
        std::string line;

        std::getline(fin, line);

        while (std::getline(fin, line)) {
            std::vector<std::string> cols;
            std::string col;
            bool inQuotes = false;
            std::string currentField;

            for (size_t i = 0; i < line.length(); i++) {
                char ch = line[i];

                if (ch == '"') {
                    inQuotes = !inQuotes;
                }
                else if (ch == ',' && !inQuotes) {
                    cols.push_back(currentField);
                    currentField.clear();
                }
                else {
                    currentField += ch;
                }
            }
            cols.push_back(currentField);

            if (cols.size() < 5) {
                std::cerr << "Пропущена строка: недостаточно колонок ("
                    << cols.size() << " из 5)" << std::endl;
                continue;
            }

            int k = 0;
            int booking_id = std::stoi(cols[k++]);
            int client_id = std::stoi(cols[k++]);
            int tour_id = std::stoi(cols[k++]);
            string booking_date = cols[k++];
            string notes = cols[k++];

            Booking booking(booking_id, client_id, tour_id, notes);
            booking.setBookingDate(booking_date);
            bookings.push_back(booking);
        }

        fin.close();
        return bookings;
    }

    static void saveBookingsToCSV(const std::string& filename, const std::vector<Booking>& bookings) {
        std::ofstream fout(filename);
        if (!fout.is_open())
            throw std::runtime_error("Не удалось открыть CSV файл для сохранения");

        fout << "booking_id,client_id,tour_id,booking_date,notes\n";

        for (const auto& b : bookings) {
            fout << b.booking_id << ","
                << b.client_id << ","
                << b.tour_id << ","
                << b.booking_date << ","
                << escapeCSVField(b.notes) << "\n";
        }

        fout.close();
    }
};