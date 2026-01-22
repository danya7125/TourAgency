#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdint>

using money_t = int64_t;
using percent_t = int32_t;

class Country {
private:
    std::string name;
    percent_t risk_factor;
    bool visa_required;
    money_t visa_cost;
    money_t insurance_cost;
    std::vector<std::string> medical_certs;

public:
    Country() = default;

    Country(const std::string& n,
        percent_t r,
        bool visa,
        money_t vc,
        money_t ic,
        const std::vector<std::string>& certs)
        : name(n), risk_factor(r), visa_required(visa), visa_cost(vc), insurance_cost(ic), medical_certs(certs)
    {
    }

    const std::string& getName() const { return name; }
    percent_t getRiskFactor() const { return risk_factor; }
    bool isVisaRequired() const { return visa_required; }
    money_t getVisaCost() const { return visa_cost; }
    money_t getInsuranceCost() const { return insurance_cost; }
    const std::vector<std::string>& getMedicalCerts() const { return medical_certs; }


    // "123.45" -> 12345 (копейки)
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
                if (!afterDot)
                    rub = rub * 10 + (c - '0');
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
    static std::string moneyToString(money_t m)
    {
        std::ostringstream ss;
        if (m < 0) { ss << "-"; m = -m; }
        ss << (m / 100) << "." << std::setw(2) << std::setfill('0') << (m % 100);
        return ss.str();
    }

    static percent_t parsePercent(const std::string& s)
    {
        int whole = 0;
        int frac = 0;
        bool afterDot = false;
        int digits = 0;

        for (char c : s)
        {
            if (c >= '0' && c <= '9')
            {
                if (!afterDot)
                    whole = whole * 10 + (c - '0');
                else if (digits < 2)
                {
                    frac = frac * 10 + (c - '0');
                    digits++;
                }
            }
            else if (c == '.' || c == ',')
            {
                afterDot = true;
            }
        }

        if (digits == 1) frac *= 10;
        return whole * 100 + frac;
    }

    static std::string percentToString(percent_t p)
    {
        std::ostringstream ss;
        if (p < 0) { ss << "-"; p = -p; }
        ss << (p / 100) << "." << std::setw(2) << std::setfill('0') << (p % 100);
        return ss.str();
    }


    static std::vector<Country> loadCountriesFromCSV(const std::string& filename)
    {
        std::ifstream fin(filename);
        if (!fin.is_open())
            throw std::runtime_error("Не удалось открыть файл CSV стран");

        std::vector<Country> countries;
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

            if (cols.size() < 6) continue;

            Country c;
            c.name = cols[0];
            c.risk_factor = parsePercent(cols[1]);
            c.visa_required = (cols[2] == "1");
            c.visa_cost = parseMoney(cols[3]);
            c.insurance_cost = parseMoney(cols[4]);

            c.medical_certs.clear();
            if (!cols[5].empty() && cols[5] != "\"\"")
            {
                std::stringstream ss(cols[5]);
                std::string cert;
                while (std::getline(ss, cert, ';'))
                {
                    if (!cert.empty())
                        c.medical_certs.push_back(cert);
                }
            }

            countries.push_back(c);
        }

        return countries;
    }

    static void saveCountriesToCSV(const std::string& filename, const std::vector<Country>& countries)
    {
        std::ofstream fout(filename);
        if (!fout.is_open())
            throw std::runtime_error("Не удалось открыть CSV файл для сохранения");

        fout << "name,risk_factor,visa_required,visa_cost,insurance_cost,medical_certificates\n";

        for (const auto& c : countries)
        {
            fout << c.name << ","
                << percentToString(c.risk_factor) << ","
                << (c.visa_required ? "1" : "0") << ","
                << moneyToString(c.visa_cost) << ","
                << moneyToString(c.insurance_cost) << ",";

            if (c.medical_certs.empty())
            {
                fout << "\"\"";
            }
            else
            {
                fout << '"';
                for (size_t i = 0; i < c.medical_certs.size(); i++)
                {
                    fout << c.medical_certs[i];
                    if (i + 1 < c.medical_certs.size()) fout << ';';
                }
                fout << '"';
            }

            fout << "\n";
        }
    }
};
