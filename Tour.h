#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdint>

#include "Country.h"

using money_t = int64_t;

class Tour {
private:
    int id;
    std::string name;
    std::string country;
    std::string city;

    std::string hotel_name;
    money_t hotel_price;
    std::string hotel_category;

    money_t flight_price;
    bool all_inclusive;
    std::string season;
    int duration_days;
    int available_seats;
    std::string start_date;
    std::string description;
    bool transfer_included;


public:
    Tour() = default;

    Tour(int id_, const std::string& name_, const std::string& country_,
        const std::string& city_, const std::string& hotel_name_,
        money_t hotel_price_, money_t flight_price_,
        const std::string& hotel_category_, bool all_inclusive_,
        const std::string& season_, int duration_days_,
        int available_seats_, const std::string& start_date_,
        const std::string& description_, bool transfer_included_ = false)
        : id(id_),
        name(name_),
        country(country_),
        city(city_),
        hotel_name(hotel_name_),
        hotel_price(hotel_price_),
        hotel_category(hotel_category_),
        flight_price(flight_price_),
        all_inclusive(all_inclusive_),
        season(season_),
        duration_days(duration_days_),
        available_seats(available_seats_),
        start_date(start_date_),
        description(description_),
        transfer_included(transfer_included_) {
    }

    int getId() const { return id; }
    const std::string& getName() const { return name; }
    const std::string& getCountry() const { return country; }
    const std::string& getCity() const { return city; }
    const std::string& getHotelName() const { return hotel_name; }
    money_t getHotelPrice() const { return hotel_price; }
    money_t getFlightPrice() const { return flight_price; }
    const std::string& getHotelCategory() const { return hotel_category; }
    bool isAllInclusive() const { return all_inclusive; }
    const std::string& getSeason() const { return season; }
    int getDuration() const { return duration_days; }
    int getAvailableSeats() const { return available_seats; }
    const std::string& getStartDate() const { return start_date; }
    const std::string& getDescription() const { return description; }
    bool isTransferIncluded() const { return transfer_included; }

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


    // "123.45" -> 12345
    static money_t parseMoney(const std::string& s)
    {
        long long rub = 0;
        int kop = 0;
        bool afterDot = false;
        int digits = 0;

        for (char c : s)
        {
            if (c >= '0' && c <= '9')
            {
                if (!afterDot) rub = rub * 10 + (c - '0');
                else if (digits < 2)
                {
                    kop = kop * 10 + (c - '0');
                    digits++;
                }
            }
            else if (c == '.' || c == ',')
            {
                afterDot = true;
            }
        }

        if (digits == 1) kop *= 10;
        return rub * 100 + kop;
    }

    // 12345 -> "123.45"
    static std::string moneyToString2(money_t m)
    {
        std::ostringstream ss;
        if (m < 0) { ss << "-"; m = -m; }
        ss << (m / 100) << "." << std::setw(2) << std::setfill('0') << (m % 100);
        return ss.str();
    }

    money_t calculateFinalPrice(const Country& c) const
    {
        money_t total = hotel_price + flight_price;

        total = total + (total * c.getRiskFactor()) / 10000;

        if (season == "Лето" || season == "лето")
            total = total * 150 / 100;
        else if (season == "Зима" || season == "зима")
            total = total * 100 / 100;
        else
            total = total * 110 / 100;

        if (all_inclusive)
            total = total * 125 / 100;

        if (c.isVisaRequired())
            total += c.getVisaCost();

        total += c.getInsuranceCost();

        if (transfer_included)
        {
            total += 2000 * 100;
        }

        total = total + (total * 5 + 50) / 100;

        return total;
    }

    std::string getFinalPriceString(const Country& c) const
    {
        return moneyToString2(calculateFinalPrice(c)) + " руб.";
    }

    double getFinalPriceInRubles(const Country& c) const
    {
        return calculateFinalPrice(c) / 100.0;
    }

    static void decrementAvailableSeats(const std::string& filename, int tourId)
    {
        auto tours = loadToursFromCSV(filename);

        bool found = false;
        for (auto& tour : tours) {
            if (tour.getId() == tourId) {
                if (tour.getAvailableSeats() <= 0) {
                    throw std::runtime_error("Нет доступных мест для тура с ID " + std::to_string(tourId));
                }

                tour = Tour(
                    tour.getId(),
                    tour.getName(),
                    tour.getCountry(),
                    tour.getCity(),
                    tour.getHotelName(),
                    tour.getHotelPrice(),
                    tour.getFlightPrice(),
                    tour.getHotelCategory(),
                    tour.isAllInclusive(),
                    tour.getSeason(),
                    tour.getDuration(),
                    tour.getAvailableSeats() - 1, //уменьшаем на 1
                    tour.getStartDate(),
                    tour.getDescription(),
                    tour.isTransferIncluded()
                );
                found = true;
                break;
            }
        }

        if (!found) {
            throw std::runtime_error("Тур с ID " + std::to_string(tourId) + " не найден");
        }

        saveToursToCSV(filename, tours);
    }


    static std::vector<Tour> loadToursFromCSV(const std::string& filename)
    {
        std::ifstream fin(filename);
        if (!fin.is_open())
            throw std::runtime_error("Не удалось открыть CSV файл для сохранения");

        std::vector<Tour> tours;
        std::string line;

        std::getline(fin, line);

        while (std::getline(fin, line))
        {
            std::vector<std::string> cols;
            std::string field;
            bool inQuotes = false;

            for (char ch : line)
            {
                if (ch == '"') inQuotes = !inQuotes;
                else if (ch == ',' && !inQuotes)
                {
                    cols.push_back(field);
                    field.clear();
                }
                else field += ch;
            }
            cols.push_back(field);

            if (cols.size() < 15) continue;

            Tour t;
            int k = 0;

            t.id = std::stoi(cols[k++]);
            t.name = cols[k++];
            t.country = cols[k++];
            t.city = cols[k++];
            t.hotel_name = cols[k++];
            t.duration_days = std::stoi(cols[k++]);
            t.hotel_price = parseMoney(cols[k++]);
            t.flight_price = parseMoney(cols[k++]);
            t.hotel_category = cols[k++];
            t.all_inclusive = (cols[k++] == "1");
            t.season = cols[k++];
            t.available_seats = std::stoi(cols[k++]);
            t.start_date = cols[k++];
            t.description = cols[k++];
            t.transfer_included = (cols[k++] == "1");

            tours.push_back(t);
        }

        return tours;
    }

    static void saveToursToCSV(const std::string& filename, const std::vector<Tour>& tours)
    {
        std::ofstream fout(filename);
        if (!fout.is_open())
            throw std::runtime_error("Cannot open tours CSV for writing");

        fout << "id,name,country,city,hotel_name,duration_days,hotel_price,flight_price,"
            << "hotel_category,all_inclusive,season,available_seats,start_date,"
            << "description,transfer_included\n";

        for (const auto& t : tours)
        {
            fout << t.id << ","
                << escapeCSVField(t.name) << ","
                << escapeCSVField(t.country) << ","
                << escapeCSVField(t.city) << ","
                << escapeCSVField(t.hotel_name) << ","
                << t.duration_days << ","
                << moneyToString2(t.hotel_price) << ","
                << moneyToString2(t.flight_price) << ","
                << escapeCSVField(t.hotel_category) << ","
                << (t.all_inclusive ? "1" : "0") << ","
                << escapeCSVField(t.season) << ","
                << t.available_seats << ","
                << escapeCSVField(t.start_date) << ","
                << escapeCSVField(t.description) << ","
                << (t.transfer_included ? "1" : "0")
                << "\n";
        }
    }
};
