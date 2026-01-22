#include "Client.h"
#include <regex>


bool Client::isValidEmail(const string& email) {
    regex email_pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, email_pattern);
}

bool Client::isValidName(const string& name) {
    regex pattern(R"(^([А-ЯЁ][а-яё]+(-[А-ЯЁ][а-яё]+)?|[А-ЯЁ]\.)\s+([А-ЯЁ][а-яё]+|[А-ЯЁ]\.)(\s+([А-ЯЁ][а-яё]+|[А-ЯЁ]\.))?$)");

    if (!regex_match(name, pattern)) {
        return false;
    }

    if (name.length() < 5 || name.length() > 100) return false;

    if (name.find("  ") != string::npos) return false;

    return true;
}

bool Client::isValidPhone(const string& phone) {
    if (phone.empty()) return false;

    for (unsigned char c : phone) {
        if (!(std::isdigit(c) || c == '+' || c == '(' || c == ')' || c == '-' || c == ' ')) {
            return false;
        }
    }

    string digits;
    for (unsigned char c : phone) {
        if (std::isdigit(c)) digits += c;
    }

    if (digits.length() == 11 && (digits[0] == '7' || digits[0] == '8')) {
        return true;
    }

    return false;
}

bool Client::isValidDomesticPassport(const std::string& fullNumber) {
    if (fullNumber.empty()) return false;
    std::regex pattern(R"(^\d{4}\s\d{6}$)");
    return std::regex_match(fullNumber, pattern);
}

bool Client::isValidForeignPassport(const std::string& fullNumber) {
    if (fullNumber.empty()) return false;

    std::regex pattern1(R"(^\d{2}\s\d{6}$)");
    std::regex pattern2(R"(^\d{4}\s\d{7}$)");

    return std::regex_match(fullNumber, pattern1) || std::regex_match(fullNumber, pattern2);
}