#pragma once
#include <string>
#include "RequestTask.h"
#include "JsonParser.h"
#include "StringCleaner.h"
#include "StockData.h"
using json = nlohmann::json;

class StockYearWiseData {
private:
//marketType=N&series=EQ&symbol=
    std::string url = "https://www.nseindia.com/api/NextApi/apiClient/GetQuoteApi?functionName=getYearwiseData&symbol=";
    
    std::string requestData;
    RequestTask task;
    JsonParser jsonParser;
    //std::vector<std::string> stockListsresult;
    double stockYearWiseData;

public:
    StockYearWiseData(){ };
    StockYearWiseData(const std::string &symbol, const std::string &markettype, const std::string &series);

    // Download JSON response
    std::vector<std::string> fetchStockWeekData();
    double getData();
    // Get URL (optional)
    std::string getUrl() const;


};
