#include "StockYearWiseData.h"
#include <stdexcept>
#include <JsonParser.h>
#include "StringCleaner.h"

using json = nlohmann::json;

StockYearWiseData::StockYearWiseData(const std::string &rqData, const std::string &markettype, const std::string &series) {
    StringCleaner sc(rqData);
    std::string _symbol = sc.url_encode(rqData);
    jsonParser.setClassname(std::string("SIstockyearwisedata"));    
    StringCleaner sc1(markettype);
    std::string _markettype = sc.url_encode(markettype);
    
    StringCleaner sc2(series);
    std::string _series = sc.url_encode(series);
    
    requestData = _symbol + _series + _markettype;

    task.setUrl(url + requestData);
}

std::vector<std::string> StockYearWiseData::fetchStockWeekData() {
    std::string response = task.fetch();
    std::vector<std::string> output;
    //StringCleaner sc(response);
    //sc.setToRemove("Indices List Response: ");
    jsonParser.fromQuotetoWeekData(response, stockYearWiseData);
    return output;
}

double StockYearWiseData::getData()
{
    return stockYearWiseData;
}

std::string StockYearWiseData::getUrl() const {
    return url;
}


