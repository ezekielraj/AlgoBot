#pragma once
#include <string>
#include "RequestTask.h"
#include "JsonParser.h"
#include "StringCleaner.h"
#include "StockData.h"
using json = nlohmann::json;

class StockQuoteData {
private:
//marketType=N&series=EQ&symbol=
    std::string url = "https://www.nseindia.com/api/NextApi/apiClient/GetQuoteApi?functionName=getSymbolData&";
    std::string requestData;
    RequestTask task;
    JsonParser jsonParser;
    //std::vector<std::string> stockListsresult;
    std::string stockQuoteData;

public:
    StockQuoteData(){ };
    StockQuoteData(const std::string &type, const std::string &series, const std::string &symbol);

    // Download JSON response
    std::vector<std::string> fetchStockQuoteData();
    std::string getData();
    // Get URL (optional)
    std::string getUrl() const;


};
