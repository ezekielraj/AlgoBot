#include "JsonParser.h"
#include <iostream>
#include <stdexcept>

using json = nlohmann::json;

void JsonParser::setClassname(std::string classname) {
    this->classname = classname;
}

json JsonParser::toJson(const std::string& jsonStr) {
    try {
        json j = json::parse(jsonStr);      // j is a STRING, not array
        //auto arr = j["Indices Eligible In Derivatives"];
        //auto vec = arr.get<std::vector<std::string>>();

        return j; //json::parse(jsonStr);
    } 
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("JSON parse error: ") + e.what() + jsonStr + this->classname);
    }
}

std::vector<std::string> JsonParser::toArray(const std::string& jsonStr, std::vector<std::vector<std::string>> &result) {
    
    
    json parsed = toJson(toJson(jsonStr).dump());
    
    if (!parsed.is_array()) {
    //    throw std::runtime_error("JSON is not an array");
    }

    std::vector<std::string> output;

//    std::vector<std::vector<std::string>> result;

    for (auto& item : parsed) {
        result.push_back(item.get<std::vector<std::string>>());
    }
    
    return output;
}

void JsonParser::toArray(const std::string& jsonStr, std::vector<std::pair<std::string, StockData>> &result) {
    
    
    json parsed = toJson(toJson(jsonStr).dump());
    
    if (!parsed.is_array()) {
    //    throw std::runtime_error("JSON is not an array");
    }

    auto arr = parsed["data"];
    for (auto& item : arr)
    {
        if(item["priority"] == 0)
        {
            StockData sd;
            sd.symbol = item["symbol"];
            sd.series = item["series"];
            result.push_back({item["symbol"], sd});
        }
    }
//    std::vector<std::vector<std::string>> result;
    
    /*for (auto& item : parsed) {
        result.push_back(item.get<std::vector<std::string>>());
    }
    
    return output;*/
}

void JsonParser::toArray(const std::string& jsonStr, std::string &result) {
    json parsed = toJson(toJson(jsonStr).dump());
    
    if (!parsed.is_array()) {
    //    throw std::runtime_error("JSON is not an array");
    }
    result = parsed["marketType"];
}

void JsonParser::fromQuotetoArray(const std::string& jsonStr, std::string &result) {
    json parsed = toJson(toJson(jsonStr).dump());
    
    if (!parsed.is_array()) {
    //    throw std::runtime_error("JSON is not an array");
    }
    if(!parsed["equityResponse"][0]["secInfo"]["pdSectorPe"].empty())
    {
        result = parsed["equityResponse"][0]["secInfo"]["pdSectorPe"];
    } else 
    {
        result = "0";
    }
}

void JsonParser::fromQuotetoWeekData(const std::string& jsonStr, double &result) {
    json parsed = toJson(toJson(jsonStr).dump());
    
    if (!parsed.is_array()) {
    //    throw std::runtime_error("JSON is not an array");
    }
    //std::cout<<parsed.dump();
    if(!parsed[0]["one_week_chng_per"].empty())
    {
        result = parsed[0]["one_week_chng_per"];
    } else 
    {
        result = 0;
    }
}
