#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class JsonParser {
public:
    JsonParser() = default;

    // Convert JSON string → array (vector of JSON objects)
    std::vector<nlohmann::json> toArray(const std::string& jsonStr);

    // Convert JSON string → single JSON object
    nlohmann::json toJson(const std::string& jsonStr);
};
