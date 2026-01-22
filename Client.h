#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
using namespace std;

struct ClientInfo
{
    string last_name;
    string first_name;
    string patronymic;
    string birth_date;
    string adress;
    string phone_number;
    string email;
    string gender;

    string getFullName() const {
        if (last_name.empty() && first_name.empty() && patronymic.empty())
            return "";
        return last_name + " " + first_name + " " + patronymic;
    }
};

struct PassportData {
    string type;
    string number;
    string issued_by;
    string issue_date;
};


class Client {
private:
    int id;
    ClientInfo info;
    PassportData domestic_passport;
    PassportData foreign_passport;

public:
    Client() = default;

    Client(int id_, const ClientInfo& info_,
        const PassportData& domestic_,
        const PassportData& foreign_)
        : id(id_), info(info_), domestic_passport(domestic_), foreign_passport(foreign_) {
    }
    int getId() const { return id; }
    string getEmail() const { return info.email; }
    ClientInfo getInfo() const { return info; }
    PassportData getDomesticPassport() const { return domestic_passport; }
    PassportData getForeignPassport() const { return foreign_passport; }


    static bool isValidDomesticPassport(const std::string& fullNumber);
    static bool isValidForeignPassport(const std::string& fullNumber);
    static bool isValidName(const string& name);
    static bool isValidEmail(const string& email);
    static bool isValidPhone(const string& phone);

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

    static void parseFullName(const std::string& full, std::string& last, std::string& first, std::string& patronymic) {
        std::istringstream iss(full);
        std::vector<std::string> parts{ std::istream_iterator<std::string>(iss),
                                       std::istream_iterator<std::string>() };
        last = parts.size() > 0 ? parts[0] : "";
        first = parts.size() > 1 ? parts[1] : "";
        patronymic = parts.size() > 2 ? parts[2] : "";
    }

    static std::vector<Client> loadClientsFromCSV(const std::string& filename)
    {
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            throw std::runtime_error("Не удалось открыть файл CSV клиентов");
        }

        std::vector<Client> clients;
        std::string line;

        std::getline(fin, line);

        while (std::getline(fin, line))
        {
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

            if (cols.size() < 15) {
                std::cerr << "Пропущена строка: недостаточно колонок ("
                    << cols.size() << " из 16)" << std::endl;
                continue;
            }

            Client c;
            int k = 0;

            c.id = std::stoi(cols[k++]);
            string full_name = cols[k++];
            parseFullName(full_name, c.info.last_name, c.info.first_name, c.info.patronymic);
            c.info.gender = cols[k++];
            c.info.birth_date = cols[k++];
            c.info.adress = cols[k++];
            c.info.phone_number = cols[k++];
            c.info.email = cols[k++];

            c.domestic_passport.type = cols[k++];
            c.domestic_passport.number = cols[k++];
            c.domestic_passport.issued_by = cols[k++];
            c.domestic_passport.issue_date = cols[k++];

            c.foreign_passport.type = cols[k++];
            c.foreign_passport.number = cols[k++];
            c.foreign_passport.issued_by = cols[k++];
            c.foreign_passport.issue_date = cols[k++];

            clients.push_back(c);
        }

        fin.close();
        return clients;
    }

    static void saveClientsToCSV(const std::string& filename, const std::vector<Client>& clients)
    {
        std::ofstream fout(filename);
        if (!fout.is_open())
            throw std::runtime_error("Не удалось открыть CSV файл для сохранения");

        fout << "id,full_name,gender,birth_date,address,phone_number,email"
            << "domestic_type,domestic_number,domestic_issued_by,domestic_issue_date,"
            << "foreign_type,foreign_number,foreign_issued_by,foreign_issue_date\n";

        for (const auto& c : clients)
        {
            fout << c.id << ","
                << escapeCSVField(c.getInfo().getFullName()) << ","
                << escapeCSVField(c.info.gender) << ","
                << escapeCSVField(c.info.birth_date) << ","
                << escapeCSVField(c.info.adress) << ","
                << escapeCSVField(c.info.phone_number) << ","
                << escapeCSVField(c.info.email) << ","
                << escapeCSVField(c.domestic_passport.type) << ","
                << escapeCSVField(c.domestic_passport.number) << ","
                << escapeCSVField(c.domestic_passport.issued_by) << ","
                << escapeCSVField(c.domestic_passport.issue_date) << ","
                << escapeCSVField(c.foreign_passport.type) << ","
                << escapeCSVField(c.foreign_passport.number) << ","
                << escapeCSVField(c.foreign_passport.issued_by) << ","
                << escapeCSVField(c.foreign_passport.issue_date)
                << "\n";
        }

        fout.close();
    }
};