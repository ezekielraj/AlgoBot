#include "StringCleaner.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>

StringCleaner::StringCleaner(const std::string& s) : str(s) {}

void StringCleaner::setToRemove(const std::string& s) {
    toRemove = s;
}

std::string StringCleaner::removeAll() const {
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find(toRemove, pos)) != std::string::npos) {
        result.erase(pos, toRemove.length());
    }
    return result;
}

std::string StringCleaner::getOriginal() const {
    return str;
}

std::string StringCleaner::url_encode(const std::string& value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (unsigned char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << '%' << std::uppercase << std::setw(2) << int(c);
            escaped << std::nouppercase;
        }
    }

    return escaped.str();
}
