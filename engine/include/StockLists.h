#pragma once
#include <string>
#include "RequestTask.h"
#include "JsonParser.h"
#include "StringCleaner.h"
#include "StockData.h"
using json = nlohmann::json;

class StockLists {
private:
    std::string url = "https://www.nseindia.com/api/equity-stockIndices";
    std::string requestData;
    RequestTask task;
    JsonParser jsonParser;
    //std::vector<std::string> stockListsresult;
    std::vector<std::pair<std::string, StockData>> stockListsresult;

public:
    StockLists(){ };
    StockLists(const std::string &rqData);

    // Download JSON response
    std::vector<std::string> fetchStockList();
    std::vector<std::pair<std::string, StockData>> getList();
    // Get URL (optional)
    std::string getUrl() const;


};
