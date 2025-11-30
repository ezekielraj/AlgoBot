#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "StockData.h"
class JsonParser {
public:
    JsonParser() = default;

    // Convert JSON string → array (vector of JSON objects)
    std::vector<std::string> toArray(const std::string& jsonStr, std::vector<std::vector<std::string>> &result);

    void toArray(const std::string& jsonStr, std::vector<std::pair<std::string, StockData>> &result);

    void toArray(const std::string& jsonStr, std::string &result);

    void fromQuotetoArray(const std::string& jsonStr, std::string &result);

    void fromQuotetoWeekData(const std::string& jsonStr, double &result);

    // Convert JSON string → single JSON object
    nlohmann::json toJson(const std::string& jsonStr);

};
