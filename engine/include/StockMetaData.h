#pragma once
#include <string>
#include "RequestTask.h"
#include "JsonParser.h"
#include "StringCleaner.h"
#include "StockData.h"
using json = nlohmann::json;

class StockMetaData {
private:
    std::string url = "https://www.nseindia.com/api/NextApi/apiClient/GetQuoteApi?functionName=getMetaData&symbol=";
    std::string requestData;
    RequestTask task;
    JsonParser jsonParser;
    //std::vector<std::string> stockListsresult;
    std::string stockMetaData;

public:
    StockMetaData(){ };
    StockMetaData(const std::string &rqData);

    // Download JSON response
    std::vector<std::string> fetchStockMetaData();
    std::string getData();
    // Get URL (optional)
    std::string getUrl() const;


};
